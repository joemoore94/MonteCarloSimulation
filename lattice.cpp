#include "lattice.hpp"
#include <iostream>

LATTICE::LATTICE(const PARAMS& param) //constructor
{
	std::cout << "Setting up lattice..." << std::endl;

	// -----------------  Ising Square ----------------- //
	if (param.getLattType()=="Ising_square")
  {
		std::cout << param.getLattType() << " lattice type selected." << std::endl;

		Lx = param.getL1();
		Ly = param.getL2();
		Lz = param.getL3();
		dim = 2;
		Nsites = Lx*Ly;
		NbondsX = Nsites;
		NbondsY = Nsites;
		NbondsZ = 0;
		Nbonds = NbondsX + NbondsY + NbondsZ;
		//std::cout << Nbonds << std::endl;

		if(Lz != 1)
			std::cout << "L3 must be set to 1 in order to build 2D lattice" << std::endl;

		/*
		std::cout << "Lx = " << Lx << std::endl;
		std::cout << "Ly = " << Ly << std::endl;
		std::cout << "Lz = " << Lz << std::endl;
		std::cout << "dim = " << dim << std::endl;
		std::cout << "Nsites = " << Nsites << std::endl;
		std::cout << "NbondsX = " << NbondsX << std::endl;
		std::cout << "NbondsY = " << NbondsY << std::endl;
		std::cout << "NbondsZ = " << NbondsZ << std::endl;
		std::cout << "Nbonds = " << Nbonds << std::endl;
		*/

		Js.resize(Nbonds, param.getCbond1());
		bonds.resize(Nbonds, std::vector<int>(dim));
		neighbors.resize(Nsites, std::vector<int>(4));

		//populating bonds vector
		for(int i=0; i<Nsites; i=i+1)
		{
			int x = i%Lx;
			int y = i/Lx;
			//(x,y)
			bonds.at(i).at(0) = y*Lx+x;
			//(x+1,y)
			bonds.at(i).at(1) = y*Lx+(x+1)%Lx;
			//(x,y)
			bonds.at(i+1).at(0) = y*Lx+x;
			//(x,y+1)
			bonds.at(i+1).at(1) = (y+1)%Lx*Lx+x;
			//std::cout << y*Lx+x << " " << y*Lx+(x+1)%Lx << std::endl;
			//std::cout << y*Lx+x << " " << (y+1)%Lx*Lx+x << std::endl;
		}

		//populating neighbors vector
		for(int i=0; i<Nsites; i=i+1)
		{
			int x = i%Lx;
			int y = i/Lx;
			//(x-1,y)
			neighbors.at(i).at(0) = y*Lx+(x-1+Lx)%Lx;
			//(x+1,y)
			neighbors.at(i).at(1) = y*Lx+(x+1)%Lx;
			//(x,y-1)
			neighbors.at(i).at(2) = (y-1+Ly)%Ly*Lx+x;
			//(x,y+1)
			neighbors.at(i).at(3) = (y+1)%Ly*Lx+x;
			//std::cout << y*Lx+(x-1+Lx)%Lx << " " << y*Lx+(x+1)%Lx << " ";
			//std::cout << (y-1+Ly)%Ly*Lx+x << " " << (y+1)%Ly*Lx+x << std::endl;

		}
	}// end Ising Square

	else
  {
    std::cout << "Dont know which model you want to simulate." << std::endl;
    exit(1);
  }

}

const int LATTICE::getLx() const
{
	return this -> Lx;
}

const int LATTICE::getLy() const
{
	return this -> Ly;
}

const int LATTICE::getLz() const
{
	return this -> Lz;
}

const int LATTICE::getNsites() const
{
	return this -> Nsites;
}

const int LATTICE::getNbonds() const
{
	return this -> Nbonds;
}

const int LATTICE::getDim() const
{
	return this -> dim;
}

void LATTICE::printLatt() const
{
// TASK 4: Design some function to print out useful information about the lattice.
	std::cout << "Lx = " << Lx << std::endl;
	std::cout << "Ly = " << Ly << std::endl;
	std::cout << "Lz = " << Lz << std::endl;
	std::cout << "dim = " << dim << std::endl;
	std::cout << "Nsites = " << Nsites << std::endl;
	std::cout << "NbondsX = " << NbondsX << std::endl;
	std::cout << "NbondsY = " << NbondsY << std::endl;
	std::cout << "NbondsZ = " << NbondsZ << std::endl;
	std::cout << "Nbonds = " << Nbonds << std::endl;
}
