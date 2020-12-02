#ifndef ATTACH_H
#include "Attach.h"
#endif

void testing::annealing()
{
	// test the simulated annealing approach for the travelling salesman problem
	int NCITY = 200; 
	int i, ii; 
	long idum = rng::ranseed(); 

	std::vector<int> iorder(NCITY); 
	std::vector<double> x(NCITY); 
	std::vector<double> y(NCITY); 

	// populte the locations to be visited
	// totally random choice of positions
	for (i = 0; i < NCITY; i++) {
		x[i] = rng::ran1(&idum); 
		y[i] = rng::ran1(&idum); 
		iorder[i] = i; 
	}

	// Distribute positions along the arc of a circle
	// Does SA process reproduce the circle? Yes it does. 
	/*double R = 0.5, Rsqr = template_funcs::DSQR(R), a = 0.5; 
	for (i = 0; i < NCITY; i++) {
		x[i] = rng::ran1(&idum);
		y[i] = sqrt(Rsqr - template_funcs::DSQR(x[i] - a));
		iorder[i] = i; 
	}*/

	// Output the original data set to a file for later comparison
	std::string filename = "OriginalDistribution.txt"; 
	std::ofstream write(filename, std::ios_base::out, std::ios_base::trunc);

	if (write.is_open()) {
		
		for (i = 0; i < NCITY; i++) write << std::setprecision(10) << x[iorder[i]] << " , " << y[iorder[i]] << "\n";
		i = 0; // include the first point again to complete the loop
		write << std::setprecision(10) << x[iorder[i]] << " , " << y[iorder[i]] << "\n";

		write.close(); 
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

	// Output the optimised data set to a file for later comparison
	filename = "OptimisedDistribution.txt";
	write.open(filename, std::ios_base::out, std::ios_base::trunc);

	if (write.is_open()) {

		for (i = 0; i < NCITY; i++) write << std::setprecision(10) << x[iorder[i]] << " , " << y[iorder[i]] << "\n";
		i = 0; // include the first point again to complete the loop
		write << std::setprecision(10) << x[iorder[i]] << " , " << y[iorder[i]] << "\n";
		write.close();
	}
}