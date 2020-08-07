#include <iostream>
#include <fstream>
#include "mt.hpp"
#include "params.hpp"
#include "lattice.hpp"
#include "mccore.hpp"
#include "fileops.hpp"

using std::cout;
using std::endl;

int main(int argc, char** argv)
{
    PARAMS param;

    block::MT ran(param.getSeed());

    LATTICE latt(param);

    MCCORE mc(ran,param,latt);

    FILEOPS fops(param,mc);

    cout << "Equilibrating..." << endl;

    for(int i=0; i<param.getEquil(); i++)
    {
      mc.updateSpins();
    }
    fops.writeconfig();

    cout << "Begin measurements..." << endl;

    std::ofstream dataOut(fops.dataFilename, std::ofstream::out | std::ofstream::trunc);
		dataOut.close();

    for(int i=0; i<param.getNbins(); i++)
    {
      fops.readconfig();
      mc.measure_clear();
      for(int i=0; i<param.getEquil(); i++)
      {
        mc.updateSpins();
        mc.measure();
      }
      //std::cout << mc.getEnergy()/param.getEquil() << std::endl;
      fops.writeconfig();
      fops.writedata();
    }

	return EXIT_SUCCESS;
}
