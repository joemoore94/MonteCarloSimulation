#include "params.hpp"
#include <iostream>
#include <fstream>

void PARAMS::load_params(std::string param_filename)
{
	std::ifstream dataIn(param_filename);
	if(!dataIn.is_open())
		std::cout << "Error while opening the file" << std::endl;
	dataIn >> L1;
	dataIn >> L2;
	dataIn >> L3;
	dataIn >> cbond1;
	dataIn >> cbond2;
	dataIn >> cbond3;
	dataIn >> beta;
	dataIn >> equil;
	dataIn >> binSize;
	dataIn >> Nbins;
	dataIn >> seed;
	dataIn >> lattType;
	dataIn.close();
	if(cbond1>0)
		signJ = 1;
	else
		signJ = -1;
}

PARAMS::PARAMS()
{
	std::cout << "Reading in parameters from default parameters file..." << std::endl;
	load_params("params.dat");
}

PARAMS::PARAMS(std::string param_filename)
{
	std::cout << "Reading in parameters from custom parameters file..." << std::endl;
	load_params(param_filename);
}

const int PARAMS::getL1() const
{
	return this -> L1;
}

const int PARAMS::getL2() const
{
	return this -> L2;
}

const int PARAMS::getL3() const
{
	return this -> L3;
}

const double PARAMS::getCbond1() const
{
	return this -> cbond1;
}

const double PARAMS::getCbond2() const
{
	return this -> cbond2;
}

const double PARAMS::getCbond3() const
{
	return this -> cbond3;
}

const double PARAMS::getBeta() const
{
	return this -> beta;
}

const int PARAMS::getEquil() const
{
	return this -> equil;
}

const int PARAMS::getBinSize() const
{
	return this -> binSize;
}

const int PARAMS::getNbins() const
{
	return this -> Nbins;
}

const long PARAMS::getSeed() const
{
	return this -> seed;
}

const std::string PARAMS::getLattType() const
{
	return this -> lattType;
}

const int PARAMS::getSignJ() const
{
	return this -> signJ;
}

void PARAMS::printParams() const
{
	std::cout << "L1 = " << L1 << std::endl;
	std::cout << "L2 = " << L2 << std::endl;
	std::cout << "L3 = " << L3 << std::endl;
	std::cout << "cbond1 = " << cbond1 << std::endl;
	std::cout << "cbond2 = " << cbond2 << std::endl;
	std::cout << "cbond3 = " << cbond3 << std::endl;
	std::cout << "beta = " << beta << std::endl;
	std::cout << "equil = " << equil << std::endl;
	std::cout << "binSize = " << binSize << std::endl;
	std::cout << "Nbins = " << Nbins << std::endl;
	std::cout << "seed = " << seed << std::endl;
	std::cout << "lattType = " << lattType << std::endl;
}
