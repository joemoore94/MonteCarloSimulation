#ifndef _LATTICE_HPP
#define _LATTICE_HPP

#include "params.hpp"
#include <vector>

class LATTICE
{

	private:
    // Attributes needed for all lattice types
	int Nsites; // number of sites on the lattice

    /* The simplest, non-trivial interactions between spins on a lattice involve two spins, usually close by, interacting with one another.  For this reason, it makes more sense to talk about the bonds of a given lattice rather than the individual sites.  In a typical model (called the Hamiltonian of the system), the sum will be over bonds, not sites. */
	int Nbonds; // number of nearest-neighbor bonds
	
    /* The most generic models involve what are called isotropic interactions.  To give a concrete example, imagine the square lattice.  The Hamiltonian is said to be isotropic if the interactions between two spins adjacent to one another along the x-axis have the same strength as the interactions between two spins adjacent to one another along the y-axis.  Very interesting physics lives in isotropic models, but sometimes we are interested in looking at anisotropic models and for that reason it helps to keep track of x-bonds, y-bonds, and potentially z-bonds separately. */
    // Attributes specific to square and cubic lattices
	int NbondsX; // # of nearest-neighbor bonds in x
	int NbondsY; // # of nearest-neighbor bonds in y
	int NbondsZ; // # of nearest-neighbor bonds in z;

	int Lx; // # of sites in the x-direction
	int Ly; // # of sites in the y-direction
	int Lz; // # of sites in the z-direction (set to 1 for 2D problem)
	int dim; // dimension of lattice (usually 2 or 3)
	
    /*  We'll use the vector class for storing any array-type variables.  We'll be directly accessing the values in these vectors a lot so it's worth declaring them as public. */

	public:
    /*  Here, Js will eventually be initialized as a vector of length Nbonds.  This allows us the flexibility to assign a different interaction strength to each and every bond in the lattice.  Of course, for any realistic model, one expects that there will only be a few different bond types, each with its own interaction strength and so the Js vector will have a lot of repetition.  In fact, in an isotropic, nearest-neighbor model, there is only a single value of the coupling for the whole lattice. */

	std::vector<double> Js; // stores the coupling values for each bond

    /*  Usually, constructing a list of sites (or spins) on a lattice is pretty straightforward, but since we are more concerned with the bonds on a lattice, it makes sense to set up a structure that keeps track of which pairs of sites are involved in each bond.  For example, imagine a simple square lattice with the sites labeled as follows:
 
                    6---7---8
                    |   |   |
                    3---4---5
                    |   |   |
                    0---1---2
     
    Assuming open boundary conditions (periodic boundary conditions are often chosen, but we'll go with open to keep things simple here), there are 12 nearest-neighbor bonds.  Bond 0 might be said to contain sites 0 and 1, bond 1 might be said to contain sites 1 and 2, and so on.  The Bond attribute stores this information as a vector of vectors:
                0: (0,1)        6: (0,3)
                1: (1,2)        7: (1,4)
                2: (3,4)        8: (2,5)
                3: (4,5)        9: (3,6)
                4: (6,7)        10: (4,7)
                5: (7,8)        11: (5,8)
     Note that I assigned Bonds 0-5 to be the x-bonds and bonds 6-11 to be the y-bonds.  I didn't *have* to do it this way, but however you set it up, there should be some structure to it.  In an anisotropic model, sometimes it's useful to have all of one bond type grouped together in the Bond vector.
 
     What if there were next-nearest-neighbor bonds as well?  I would usually add these on to the end.  In this case, there are eight such bonds:
                12: (0,4)       16: (1,3)
                13: (1,5)       17: (2,4)
                14: (3,7)       18: (4,6)
                15: (4,8)       19: (5,7)
     Again, purely by choice, I've put all the bonds with positive slopes first and all the bonds with negative slopes last.  Doesn't have to be that way.  Also, it should make no difference at all to the program in which order the two sites are listed for each bond (but see the BondDir vector below).
 
     Finally, I should mention periodic boundary conditions since we'll mostly be using those.  If you're old school, like me, you might understand what I mean if I call them "Mario Bros" boundary conditions, referring to the original arcade game.  In it, Mario and Luigi can walk off one side of the screen and appear at the same vertical height but on the other side of the screen.  That's how we want our lattice to behave.  Technically, we can impose these conditions on the x- or y-directions independently, but usually we'll do it for both.  Just for your own knowledge, there's also such a thing as anti-periodic boundary conditions, which involves a sign flip taking place when the boundary is traversed.
 
     If we had periodic boundary conditions in the lattice above, we'd also have nearest-neighbor bonds involving sites (0,2), (3,5), (6,8), (0,6), (1,7), and (2,8).  We'd have next-nearest-neighbor bonds involving sites (2,3), (5,6), (0,8), (0,5), (3,8), and (2,6).  Be sure to convince yourself that all this makes sense so you'll know how to set up your Bond vector. */

	std::vector<std::vector<int> > bonds;

	/* In calculating the acceptance probabilities, it will be useful to have a list of neighboring sites for each site on the lattice.  Looking back at the example above, we'd have that site 0 has neighbors 1, 2, 3, and 6 using periodic boundary conditions.  Every site on the square lattice has four neighbors.  Site 4 has neighbors 1, 3, 5, and 7. */

	std::vector<std::vector<int> > neighbors;

    /* In our case here, we want our LATTICE constructor to take a PARAMS object as an argument so that it will have access to all the input parameters, which it needs to set up the lattice. The & after PARAMS denotes that this argument, param, is a reference to a PARAMS object; in other words, it's an alias; we are not copying the PARAMS object, but merely creating an identifier, param, that references it.  We always pass references (or pointers) to objects when they are used as arguments of functions. */
	LATTICE(const PARAMS& param); //takes all parameters as input

	// Get functions for Lx, Ly, Lz, Nsites, Nbonds, dim; the other attributes don't require public access
	const int getLx() const;
	const int getLy() const;
	const int getLz() const;
	const int getNsites() const;
	const int getNbonds() const;
	const int getDim() const;
	
    /* It is often useful to be able to see a textual output of how our lattice is stored once it's set up.  This could be an ASCII drawing of the lattice or a dump of the contents of the bonds and neighbors vectors above.  It just depends what you want to see.  This print() function will be written to give us some useful information about how the lattice has been set up for debugging purposes. */
	void printLatt() const; //debugger

};

#endif
