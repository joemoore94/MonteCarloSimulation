#ifndef _MCCORE_HPP
#define _MCCORE_HPP

#include <vector>
#include "mt.hpp"
#include "lattice.hpp"

class MCCORE
{
	private:
  double energy; // variable to store the energy of the system
  double energy2; // variable to store the square of the energy of the system
  double magz; // variable to store the magnetization per site of the system
  double magz2;// variable to store the square of the (magnetization per site) of the system
	// stores the value of each spin on the lattice (+1 or -1 for Ising model)
	std::vector<double> Pvalues; // stores precalculated values of the acceptance probabilities

	/* Local references to reference the inputted objects. These objects are initialized in simpleMC and are passed to the constructor of MCCORE so that we can make use of them in this class. In the case of the LATTICE class, for example, we did not have to store the inputted PARAMS object as an attribute in LATTICE because all the work in LATTICE was done in the constructor. We could therefore just reference the name of the inputted argument to the constructor whenever we wanted something from the PARAMS object. Here, we have several other functions defined in the MCCORE class and we want each of them to have access to the three inputted objects. For that reason, we have to store references to them as attributes. We would like these variables to have the same behavior as the original ones defined in simpleMC.  For example, if we want to reference the L1 attribute in the param object, we wish to just say param.L1.  This means that we *must* use references for these variables and not pointers.  The trouble with doing things this way is that references, unlike pointers, must be initialized immediately when the constructor is called. You'll see how we accomplish this in mccore.cpp. */
	block::MT& ran;
	const PARAMS& param;
	const LATTICE& latt;

	/* These are functions that will be called by the spinflip function to facilitate the process. You should not feel obligated to do things this way.  These are optional helper functions. */
	void populateSpins();
	void buildPvalues();
	int getDeltaE(int j) const;
	double getP(double deltaE) const;
	void attemptFlip(int j, double P);

	/* These are functions that will be called by the measure function to measure each type of quantity.  We abstract out this functionality so we can focus on a single type of measurement within one function. More on how to calculate these in the notes. */
	void measure_energy();
	void measure_mag();

	public:
	/* Stores the value of each spin on the lattice (+1 or -1 for Ising model)
	 The only reason this is public is so that the FILEOPS class can read/write the configuration */
	std::vector<int> spins;
	/* Constructor for MCCORE class. Doesn't need to do much aside from initializing the attributes to zero and assigning the input objects to the local references. */
  MCCORE(block::MT& r, const PARAMS& p, const LATTICE& l);

    /* The updateSpins function is used for sampling. It picks many random spins on the lattice, one at a time, calculates the relative probability of flipping each spin using the Boltzmann distribution, decides whether or not to flip the spin based on that probability, and then either flips it or does nothing. To calculate the needed probability, we need to understand how the energy is calculated and how it is affected by flipping a single spin. See notes on the Ising Model. */
  void updateSpins();

    /* The measure function calculates various quantities of interest using the current state of the system and adds those measurements to the running tally stored in the variables like energy, energy2, magz, magz2, etc.  Later, these sums will be divided by the number of times measurements were taken. */
  void measure();

    /* Clears the values of the variables storing the measurements after they have been recorded to a file.  We compute our measurement averages several times throughout a simulation and save to a file so that we can perform error analysis on our results.  This is called "binning the data." */
  void measure_clear();

	/* Get functions for measurement variables. */
	double getEnergy() const;
	double getEnergySquared() const;
	double getMagnetization() const;
	double getMagnetizationSquared() const;

	/* Prints out the current contents of the spins vector in some human-readable format. */
  void printSpins() const;

};
#endif
