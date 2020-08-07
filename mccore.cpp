#include "mccore.hpp"
#include <iostream>

MCCORE::MCCORE(block::MT& r, const PARAMS& p, const LATTICE& l) : ran(r), param(p), latt(l)
{
	std::cout << "Setting up MCCORE object..." << std::endl;
	energy = 0;
	energy2 = 0;
	magz = 0;
	magz2 = 0;

	spins.resize(l.getNsites());
	Pvalues.resize(2*l.getDim()+1);

	populateSpins();
	buildPvalues();
}

void MCCORE::populateSpins()
{
	auto n = ran.rand_int(1,2);
	for(int i=0; i<latt.getNsites(); i++)
	{
		if(n(param.getSeed())==1)
			spins.at(i) = -1;
		else
			spins.at(i) = 1;
		//std::cout << i << ": " << spins.at(i) << std::endl;
	}
}

void MCCORE::buildPvalues()
{
	double delE;
	for(int i=0; i<2*latt.getDim()+1; i++)
	{
		delE = 4*(-latt.getDim()+i)*param.getCbond1();
		//std::cout << delE << std::endl;
		Pvalues.at(i) = exp(-1*param.getBeta()*delE);
		//std::cout << Pvalues.at(i) << std::endl;
	}
}

int MCCORE::getDeltaE(int j) const
{
	int deltaE=0;
	for(int i=0; i<2*latt.getDim(); i++)
	{
		deltaE = deltaE - latt.Js.at(j)*spins.at(j)*spins.at(latt.neighbors.at(j).at(i));
		//std::cout << spins.at(latt.neighbors.at(j).at(i)) << std::endl;
	}
	deltaE = -2*deltaE;
	//std::cout << deltaE << std::endl;
	return deltaE;
}

double MCCORE::getP(double deltaE) const
{
	double P = 0.0;
	for(int i=0; i<2*latt.getDim()+1; i++)
	{
		if(deltaE == 4*(-latt.getDim()+i)*param.getCbond1())
			P = Pvalues.at(i);
	}
	//std::cout << P << std::endl;
	return P;
}

void MCCORE::attemptFlip(int j, double P)
{
	auto n = ran.rand_real(0,1);
	if(P > n())
		spins.at(j) = -1*spins.at(j);
}

void MCCORE::updateSpins()
{
	auto k = ran.rand_int(0,latt.getNsites()-1);
	for(int j=0; j<latt.getNsites(); j++)
	{
		attemptFlip(k(param.getSeed()), getP(getDeltaE(j)));
		//std::cout << k() << std::endl;
	}
}

void MCCORE::measure_energy()
{
	double H=0;
	for(int i=0; i<latt.getNbonds(); i++)
	{
		H -= latt.Js.at(i)*spins.at(latt.bonds.at(i).at(0))*spins.at(latt.bonds.at(i).at(1));
		//std::cout << H << std::endl;
	}
	energy += H;
	energy2 += H*H;
}

// Helper function to calculate the current magnetization per site and (magnetization per site)^2 of the system and add these to the running totals (stored in magz and magz2)
void MCCORE::measure_mag()
{
	double M=0;
	for(int i=0; i<latt.getNsites(); i++)
	{
		M += spins.at(i);
	}
	magz += M;
	magz2 += M*M;
}

// If you've set up the above two helper functions, then this function merely needs to call them both.
void MCCORE::measure()
{
	measure_energy();
	measure_mag();
}

// After each bin's averages are printed to the data file, the running totals must be reset.
void MCCORE::measure_clear()
{
	energy = 0;
	energy2 = 0;
	magz = 0;
	magz2 = 0;
}

double MCCORE::getEnergy() const
{
	return this -> energy;
}

double MCCORE::getEnergySquared() const
{
	return this -> energy2;
}

double MCCORE::getMagnetization() const
{
	return this -> magz;
}

double MCCORE::getMagnetizationSquared() const
{
	return this -> magz2;
}

// Prints out the spins vector in some human-readable format
void MCCORE::printSpins() const
{
	std::cout << std::endl << "-------- spins --------" << std::endl;
	for(int i=0; i<latt.getNsites(); i++)
	{
		std::cout << i << ": " << spins.at(i) << std::endl;
	}
	std::cout << std::endl;
}
