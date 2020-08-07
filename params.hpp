#ifndef _PARAMS_HPP
#define _PARAMS_HPP

#include <string>

//Class to read in the simulation parameters from a file
class PARAMS
{
	private:
	int L1;
	int L2;
	int L3;
	double cbond1; // coupling bond 1 -- these are assigned depending on the model
	double cbond2; // coupling bond 2
	double cbond3; // coupling bond 3
	double beta; //the inverse temperature
	int equil; //the number of equilibriation MC steps
	int binSize; //the number of production MC steps per bin
	int Nbins; // # of bins (for statistics)
	long seed; // seed for the Mersenne Twister object
	std::string lattType; // identifies lattice type

	void load_params(std::string param_filename);
	
	int signJ; // +1 for ferromagnetic model; -1 for antiferromagnetic model

	public:
	PARAMS(); //default constructor
	PARAMS(std::string param_filename); // constructor that takes custom parameters filename
	
	// get functions; putting "const" in front of the return type is reasonable because these parameter values don't change; putting "const" after each one promises that these functions won't change anything about the object; they won't since all they do is return values of attributes
	const int getL1() const;
	const int getL2() const;
	const int getL3() const;
	const double getCbond1() const;
	const double getCbond2() const;
	const double getCbond3() const;
	const double getBeta() const;
	const int getEquil() const;
	const int getBinSize() const;
	const int getNbins() const;
	const long getSeed() const;
	const std::string getLattType() const;
	const int getSignJ() const;
	
	// Function to print out all the parameters to the screen
	void printParams() const;

}; //PARAMS

#endif
