all: MC

MC: main.o fileops.o mccore.o lattice.o params.o
	g++ lattice.o mccore.o fileops.o main.o params.o -o MC

main.o: main.cpp fileops.hpp mccore.hpp lattice.hpp params.hpp
	g++ -Wall -c main.cpp

fileops.o: fileops.cpp fileops.hpp params.hpp mccore.hpp
	g++ -Wall -c fileops.cpp

mccore.0: mccore.cpp mccore.hpp lattice.hpp
	g++ -Wall -c mccore.cpp

lattice.o: lattice.cpp lattice.hpp params.hpp
	g++ -Wall -c lattice.cpp

params.o: params.cpp params.hpp
	g++ -Wall -c params.cpp

clean:
	rm *.o MC
