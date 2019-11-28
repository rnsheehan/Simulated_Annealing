#ifndef ATTACH_H
#include "Attach.h"
#endif

// The aim of this project is to implement the code needed to perform optimisation by simulated annealing
// R. Sheehan 28 - 11 - 2019

int main() 
{
	
	std::cout << "Something\n"; 
	double a, b, c, d; 

	a = 0; b = 1; c = 0; d = 1;

	std::cout << template_funcs::ALEN(a, b, c, d)<<"\n";

	std::cout << "Press Enter to Close\n"; 
	std::cin.get(); 

	return 0; 
}