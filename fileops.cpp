#include "fileops.hpp"
#include <iostream>
#include <fstream>

// Here we see the special syntax that allows us to immediately initialize the attributes param, latt, and mc
FILEOPS::FILEOPS(const PARAMS& p, MCCORE& m) : param(p), mc(m)
{
	std::cout << "Setting up FILEOPS object..." << std::endl;

	confFilename = "spins.conf";

	dataFilename = "data.dat";

}

// Stores the contents of the spins vector to the conf file; I also store its length
void FILEOPS::writeconfig() const
{
	std::ofstream dataOut(confFilename);
	if(!dataOut.is_open())
		std::cout << "Error while opening the file" << std::endl;
	dataOut << mc.spins.size() << std::endl;
	for(unsigned int i=0; i<mc.spins.size(); i++)
	{
		dataOut << mc.spins.at(i) << " ";
	}
	dataOut.close();
}

// Reads in the contents of the conf file and uses it to initialize the spins vector
void FILEOPS::readconfig()
{
	int size;
	std::ifstream dataIn(confFilename);
	if(!dataIn.is_open())
		std::cout << "Error while opening the file" << std::endl;
	dataIn >> size;
	mc.spins.resize(size);
	for(unsigned int i=0; i<mc.spins.size(); i++)
	{
		dataIn >> mc.spins.at(i);
	}
	dataIn.close();
}

// Use get functions defined within MCCORE class
void FILEOPS::writedata() const
{
	std::ofstream dataOut(dataFilename, std::ofstream::app);
	if(!dataOut.is_open())
		std::cout << "Error while opening the file" << std::endl;
	dataOut << mc.getEnergy()/param.getEquil() << " ";
	dataOut << mc.getEnergySquared()/param.getEquil() << " ";
	dataOut << mc.getMagnetization()/param.getEquil() << " ";
	dataOut << mc.getMagnetizationSquared()/param.getEquil() << std::endl;
	dataOut.close();
}
