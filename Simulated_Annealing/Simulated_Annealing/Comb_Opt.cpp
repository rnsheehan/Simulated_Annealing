#ifndef ATTACH_H
#include "Attach.h"
#endif 

int SA::metrop(double de, double t)
{
	// Metropolis algorithm. metrop returns a boolean variable that issues a verdict on whether
	// to accept a reconfiguration that leads to a change de in the objective function e.If de<0,
	// metrop = 1 (true), while if de>0, metrop is only true with probability exp(-de / t), where
	// t is a temperature determined by the annealing schedule.

	try {	
		if (t > 0.0) {
			static long gljdum = 1;

			return de < 0.0 || rng::ran1(&gljdum) < exp(-de / t);
		}
		else {
			std::string reason;
			reason = "Error: int SA::metrop(double de, double t)\n";
			reason += "t input with value = " + template_funcs::toString(t) + "\n";
			throw std::invalid_argument(reason);
		}
	}
	catch (std::invalid_argument &e) {
		useful_funcs::exit_failure_output(e.what());
		exit(EXIT_FAILURE);
	}
}

void SA::trnspt(std::vector<int> &iorder, int &ncity, std::vector<int> &n)
{
	// This routine does the actual path transport, once metrop has approved. iorder[0..ncity-1]
	// is an input array giving the present itinerary.The array n has as its six elements the beginning
	// n[0] and end n[1] of the path to be transported, the adjacent cities n[2] and n[3] between
	// which the path is to be placed, and the cities n[4] and n[5] that precede and follow the path.
	// n[3], n[4], and n[5] are calculated by function trncst. On output, iorder is modified to
	// reflect the movement of the path segment.

	try {
		
		bool c1 = ncity > 0 ? true : false;
		bool c2 = iorder.size() == ncity ? true : false; 
		bool c3 = n.size() == 6 ? true : false; 
		bool c10 = c1 && c2 && c3; 

		if (c10) {
			int m1, m2, m3, nn, j, jj;

			std::vector<int> jorder(ncity);

			m1 = (n[1] - n[0] + ncity) % ncity; // Find number of cities from n[0] to n[1]
			m2 = (n[4] - n[3] + ncity) % ncity; // and the number from n[3] to n[4]
			m3 = (n[2] - n[5] + ncity) % ncity; // and the numbre from n[5] to n[2]
			
			nn = 0;			
			for (j = 0; j <= m1; j++) {
				jj = (j + n[0]) % ncity; // copy the chosen segment
				jorder[nn++] = iorder[jj];
			}

			if (m2>0) {
				for (j = 0; j <= m2; j++) {
					jj = (j + n[3]) % ncity; // copy the segment n[3] to n[4]
					jorder[nn++] = iorder[jj];
				}
			}
			
			if (m3>0) {
				for (j = 0; j <= m3; j++) {
					jj = (j + n[5]) % ncity; // copy the segment n[5] to n[2]
					jorder[nn++] = iorder[jj];
				}
			}

			for (j = 0; j < ncity; j++)
				iorder[j] = jorder[j]; // copy jorder into iorder
			
			jorder.clear(); 
		}
		else {
			std::string reason;
			reason = "Error: void SA::trnspt(std::vector<int> &iorder, int &ncity, std::vector<int> &n)\n";
			if(!c1) reason += "ncity input with value = " + template_funcs::toString(ncity) + "\n";
			if(!c2) reason += "iorder does not have correct size\n";
			if(!c3) reason += "n does not have correct size\n";
			throw std::invalid_argument(reason);
		}
	}
	catch (std::invalid_argument &e) {
		useful_funcs::exit_failure_output(e.what());
		exit(EXIT_FAILURE);
	}
}

void SA::reverse(std::vector<int> &iorder, int &ncity, std::vector<int> &n)
{
	// This routine performs a path segment reversal.iorder[0..ncity-1] is an input array giving the
	// present itinerary.The vector n has as its first four elements the first and last cities n[0], n[1]
	// of the path segment to be reversed, and the two cities n[2] and n[3] that immediately
	// precede and follow this segment.n[2] and n[3] are found by function revcst.On output,
	// iorder[0..ncity-1] contains the segment from n[0] to n[1] in reversed order

	try {
	
		bool c1 = ncity > 0 ? true : false;
		bool c2 = iorder.size() == ncity ? true : false;
		bool c3 = n.size() == 6 ? true : false;
		bool c10 = c1 && c2 && c3;

		if (c10) {
		
			int nn, j, k, l, itmp;

			nn = (1 + ((n[1] - n[0] + ncity) % ncity)) / 2; // This many cities must be swapped to effect the reversal
			for (j = 0; j < nn; j++) {
				k = ((n[0] + j) % ncity); // start at end of segment, swap pairs of cities, work towards the centre
				l = ((n[1] - j + ncity) % ncity);
				itmp = iorder[k];
				iorder[k] = iorder[l];
				iorder[l] = itmp;
			}

		}
		else {
			std::string reason;
			reason = "Error: void SA::reverse(std::vector<int> &iorder, int &ncity, std::vector<int> &n)\n";
			if (!c1) reason += "ncity input with value = " + template_funcs::toString(ncity) + "\n";
			if (!c2) reason += "iorder does not have correct size\n";
			if (!c3) reason += "n does not have correct size\n";
			throw std::invalid_argument(reason);
		}
	}
	catch (std::invalid_argument &e) {
		useful_funcs::exit_failure_output(e.what());
		exit(EXIT_FAILURE);
	}
}

void SA::anneal(std::vector<double> &x, std::vector<double> &y, std::vector<int> &iorder, int &ncity)
{
	// This algorithm finds the shortest round-trip path to ncity cities whose coordinates are in the
	// arrays x[0..ncity-1], y[0..ncity-1].The array iorder[0..ncity-1] specifies the order in
	// which the cities are visited.On input, the elements of iorder may be set to any permutation
	// of the numbers 0 to ncity-1.This routine will return the best alternative path it can find.

	// Enjoy https://www.youtube.com/watch?v=eFTx1A3fsTM 

	try {
		bool c1 = ncity > 0 ? true : false;
		bool c2 = iorder.size() == ncity ? true : false;
		bool c4 = x.size() == ncity ? true : false;
		bool c5 = y.size() == ncity ? true : false;
		bool c10 = c1 && c2 && c4 && c5;

		if (c10) {

			int ans, nover, nlimit, i1, i2;
			int i, j, k, nsucc, nn, idec;

			long idum;
			unsigned long iseed;
			double path, de, t, TFACTR;

			TFACTR = 0.9; 

			std::vector<int> n(6); 
			
			nover = 100 * ncity; // max no. of paths to be tried at any T
			nlimit = 10 * ncity; // max no. of successful path changes before continuing
			path = 0.0;
			t = 0.5; // initial temperature
			// calculate initial path-length
			for (i = 0; i<ncity-1; i++) {
				i1 = iorder[i];
				i2 = iorder[i + 1];
				path += template_funcs::ALEN(x[i1], x[i2], y[i1], y[i2]);
			}

			i1 = iorder[ncity-1];
			i2 = iorder[0];
			path += template_funcs::ALEN(x[i1], x[i2], y[i1], y[i2]);
			idum = -1;
			iseed = 111;
			std::cout << std::fixed << std::setprecision(6); 
			// try 100 temperature steps
			for (j = 0; j < 100; j++) {
				nsucc = 0;
				for (k = 0; k < nover; k++) {
					do {
						n[0] = (int)(ncity*rng::ran1(&idum)); // choose the beginning and end of the segment
						n[1] = (int)((ncity - 1)*rng::ran1(&idum));
						if (n[1] >= n[0]) ++n[1];
						nn = (n[0] - n[1] + ncity - 1) % ncity; // nn is the number of cities not on the segment	
					} while (nn<2);
					
					// Decide whether to do segment reversal or transport
					idec = rng::irbit1(&iseed);

					if (idec == 0) { // do transport
						n[2] = n[1] + (int)(abs(nn - 1)*rng::ran1(&idum)) + 1;
						n[2] %= ncity; // transport to location not on the path
						de = trncst(x, y, iorder, ncity, n); // compute cost
						ans = metrop(de, t); // consult the oracle
						if (ans) {
							++nsucc;
							path += de;
							trnspt(iorder, ncity, n); // carry out the transport
						}
					}
					else { // Do path reversal
						de = revcst(x, y, iorder, ncity, n); // compute cost
						ans = metrop(de, t); // consult the oracle
						if (ans) {
							++nsucc;
							path += de;
							reverse(iorder, ncity, n); // carry out reversal
						}
					}
					if (nsucc >= nlimit) break;
				}
				
				std::cout << "\nT = " << std::setw(12) << t; 
				std::cout << "Path-length" << std::setw(12) << path << "\n";
				std::cout << "Successul moves: " << nsucc << "\n"; 
				t *= TFACTR;
				if (nsucc == 0) return;
			}
		}
		else {
			std::string reason;
			reason = "Error: void SA::anneal(std::vector<double> &x, std::vector<double> &y, std::vector<int> &iorder, int &ncity)\n";
			if (!c1) reason += "ncity input with value = " + template_funcs::toString(ncity) + "\n";
			if (!c2) reason += "iorder does not have correct size\n";
			if (!c4) reason += "x does not have correct size\n";
			if (!c5) reason += "y does not have correct size\n";
			throw std::invalid_argument(reason);
		}
	}
	catch (std::invalid_argument &e) {
		useful_funcs::exit_failure_output(e.what());
		exit(EXIT_FAILURE);
	}
}

double SA::trncst(std::vector<double> &x, std::vector<double> &y, std::vector<int> &iorder, int &ncity, std::vector<int> &n)
{
	// This routine returns the value of the cost function for a proposed path segment transport. ncity
	// is the number of cities, and arrays x[0..ncity-1] and y[0..ncity-1] give the city coordinates.
	// iorder[0..ncity-1] is an array giving the present itinerary.The first three elements of array
	// n give the starting and ending cities of the path to be transported, and the point among the
	// remaining cities after which it is to be inserted. On output, de is the cost of the change.The
	// actual transport is not performed by this routine.	

	try {

		bool c1 = ncity > 0 ? true : false;
		bool c2 = iorder.size() == ncity ? true : false;
		bool c3 = n.size() == 6 ? true : false;
		bool c4 = x.size() == ncity ? true : false;
		bool c5 = y.size() == ncity ? true : false;
		bool c10 = c1 && c2 && c3 && c4 && c5;

		if (c10) {
			double de;
			int j, ii;

			std::vector<double> xx(ncity);
			std::vector<double> yy(ncity);

			n[3] = (n[2] + 1) % ncity; // find the city following n[2]
			n[4] = (n[0] + ncity - 1) % ncity; // find city preceding n[0]
			n[5] = (n[1] + 1) % ncity; /// find city following n[1]

			for (j = 0; j < 6; j++) {
				ii = iorder[n[j]]; // determine coordinates for 6 cities involved
				xx[j] = x[ii];
				yy[j] = y[ii];
			}

			// compute cost of disconnecting path segment n[0] to n[1] opening a space n[2] to n[3]
			// connecting that segment and connecting to n[4] and n[5]
			de = -template_funcs::ALEN(xx[1], xx[5], yy[1], yy[5]);
			de -= template_funcs::ALEN(xx[0], xx[4], yy[0], yy[4]);
			de -= template_funcs::ALEN(xx[2], xx[3], yy[2], yy[3]);
			de += template_funcs::ALEN(xx[0], xx[2], yy[0], yy[2]);
			de += template_funcs::ALEN(xx[1], xx[3], yy[1], yy[3]);
			de += template_funcs::ALEN(xx[4], xx[5], yy[4], yy[5]);

			return de;
		}
		else {
			std::string reason;
			reason = "Error: double SA::trncst(std::vector<double> &x, std::vector<double> &y, std::vector<int> &iorder, int &ncity, std::vector<int> &n)\n";
			if (!c1) reason += "ncity input with value = " + template_funcs::toString(ncity) + "\n";
			if (!c2) reason += "iorder does not have correct size\n";
			if (!c3) reason += "n does not have correct size\n";
			if (!c4) reason += "x does not have correct size\n";
			if (!c5) reason += "y does not have correct size\n";
			throw std::invalid_argument(reason);
		}
	}
	catch (std::invalid_argument &e) {
		useful_funcs::exit_failure_output(e.what());
		exit(EXIT_FAILURE);
	}
}

double SA::revcst(std::vector<double> &x, std::vector<double> &y, std::vector<int> &iorder, int &ncity, std::vector<int> &n)
{
	// This function returns the value of the cost function for a proposed path reversal. ncity is the
	// number of cities, and arrays x[0..ncity-1], y[0..ncity-1] give the coordinates of these cities.
	// iorder[0..ncity-1] holds the present itinerary.The first two values n[0] and n[1] of array
	// n give the starting and ending cities along the path segment which is to be reversed.On output,
	// de is the cost of making the reversal.The actual reversal is not performed by this routine.

	try {
	
		bool c1 = ncity > 0 ? true : false;
		bool c2 = iorder.size() == ncity ? true : false;
		bool c3 = n.size() == 6 ? true : false;
		bool c4 = x.size() == ncity ? true : false;
		bool c5 = y.size() == ncity ? true : false;
		bool c10 = c1 && c2 && c3 && c4 && c5;

		if (c10) {
		
			double de;
			int j, ii;

			std::vector<double> xx(ncity);
			std::vector<double> yy(ncity);

			n[2] = (n[0] + ncity - 1) % ncity; // Find city before n[0]
			n[3] = (n[1] + 1) % ncity; // find city after n[1]

			for (j = 0; j < 4; j++) {
				ii = iorder[n[j]]; // get coordinates of the 4 cities involved
				xx[j] = x[ii];
				yy[j] = y[ii];
			}

			// Compute cost of disconnecting at both ends and reconnecting in opposite order
			de = -template_funcs::ALEN(xx[0], xx[2], yy[0], yy[2]);
			de -= template_funcs::ALEN(xx[1], xx[3], yy[1], yy[3]);
			de += template_funcs::ALEN(xx[0], xx[3], yy[0], yy[3]);
			de += template_funcs::ALEN(xx[1], xx[2], yy[1], yy[2]);

			return de;
		}
		else {
			std::string reason;
			reason = "Error: double SA::revcst(std::vector<double> &x, std::vector<double> &y, std::vector<int> &iorder, int &ncity, std::vector<int> &n)\n";
			if (!c1) reason += "ncity input with value = " + template_funcs::toString(ncity) + "\n";
			if (!c2) reason += "iorder does not have correct size\n";
			if (!c3) reason += "n does not have correct size\n";
			if (!c4) reason += "x does not have correct size\n";
			if (!c5) reason += "y does not have correct size\n";
			throw std::invalid_argument(reason);
		}
	}
	catch (std::invalid_argument &e) {
		useful_funcs::exit_failure_output(e.what());
		exit(EXIT_FAILURE);
	}
}