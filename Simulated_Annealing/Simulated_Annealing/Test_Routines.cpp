#ifndef ATTACH_H
#include "Attach.h"
#endif

void testing::annealing()
{
	// test the simulated annealing approach for the travelling salesman problem
	int NCITY = 10; 
	int i, ii; 
	long idum = -111; 

	std::vector<int> iorder(NCITY); 
	std::vector<double> x(NCITY); 
	std::vector<double> y(NCITY); 

	// populte the locations to be visited
	for (i = 0; i < NCITY; i++) {
		x[i] = rng::ran1(&idum); 
		y[i] = rng::ran1(&idum); 
		iorder[i] = i; 
	}

	std::cout << "Start Path:\n";
	std::cout << std::setw(5) << "city" << std::setw(8) << "x" << std::setw(11) << "y\n";
	std::cout << std::fixed << std::setprecision(4);
	for (i = 0; i < NCITY; i++) {
		ii = iorder[i];
		std::cout << std::setw(4) << ii << std::setw(11) << x[ii];
		std::cout << std::setw(11) << y[ii] << "\n";
	}

	// compute the optimum path
	SA::anneal(x, y, iorder, NCITY); 

	// output the solution
	std::cout << "\n*** System Frozen ***\n"; 
	std::cout << "Final Path:\n";
	std::cout << std::setw(5) << "city" << std::setw(8) << "x" << std::setw(11) << "y\n"; 
	std::cout << std::fixed << std::setprecision(4); 
	for (i = 0; i < NCITY; i++) {
		ii = iorder[i]; 
		std::cout << std::setw(4) << ii << std::setw(11) << x[ii]; 
		std::cout << std::setw(11) << y[ii] << "\n"; 
	}
}