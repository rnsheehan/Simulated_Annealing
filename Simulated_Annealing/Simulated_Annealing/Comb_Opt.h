#ifndef COMB_OPT_H
#define COMB_OPT_H

// code required for performing combinatorial optimisation, in particular for simulated annealing
// R. Sheehan 28 - 11 - 2019

namespace SA {
	
	int metrop(double de, double t); 

	void trnspt(std::vector<int> &iorder, int &ncity, std::vector<int> &n);
	void reverse(std::vector<int> &iorder, int &ncity, std::vector<int> &n);
	void anneal(std::vector<double> &x, std::vector<double> &y, std::vector<int> &iorder, int &ncity);

	double trncst(std::vector<double> &x, std::vector<double> &y, std::vector<int> &iorder, int &ncity, std::vector<int> &n);
	double revcst(std::vector<double> &x, std::vector<double> &y, std::vector<int> &iorder, int &ncity, std::vector<int> &n);
}

#endif
