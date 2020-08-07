#ifndef _FILEOPS_HPP
#define _FILEOPS_HPP

#include "mccore.hpp"
#include "params.hpp"
#include <string>

// Class declarations which define file
// names and operators for reading/writing
//
class FILEOPS
{
	private:
	// For this class, it will be useful to have local variables assigned to the references for the other objects that are passed to the constructor.  In order for a class to have references as attributes, they must be initialized *immediately* upon construction of the object.  There is a special syntax for this that we've seen in the MCCORE class.  See fileops.cpp for how this works.
	const PARAMS& param;
	MCCORE& mc;

	public:
    /* This file will be used to store the configuration of the system after each bin completes.  For now, the configuration is just the spins vector. */
	std::string confFilename;  // configuration filename

    /* This file will be used to store the measurement data.  Have it store energy, energy2, magz, and magz2 all on one line for each bin, then go to the next line. */
	std::string dataFilename;  // data filename

	FILEOPS(const PARAMS& p, MCCORE& m);
	void writeconfig() const; // writes the current configuration to a file
	void readconfig(); // reads a configuration from a file
	void writedata() const; // write the data to a file

};

#endif
