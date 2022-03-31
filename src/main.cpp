//============================================================================
// Name        : main.cpp
// Author      : Will Bradley
// Version     :
// Copyright   : MIT License
// Description : Driver and testing code
//============================================================================


#include <iostream>
#include <complex>
#include <vector>
#include <cmath>
#include <random>
#include <chrono>
#include <thread>
#include <stdexcept>
#include <fstream>
#include <algorithm>

#include "translate_polynomials.h"
#include <random>
using namespace PolynomialOperations;


void run_simulation(
	int trials_per_run, int number_of_runs, 
	int len_increase_per_run, int max_coeff_shift_value,
	bool use_new_method
) {

	using std::chrono::high_resolution_clock;
    using std::chrono::duration_cast;
    using std::chrono::microseconds;


	std::mt19937 gen(13);
	std::uniform_int_distribution<> values_distr(
		-max_coeff_shift_value, max_coeff_shift_value);

	std::string fname;
	if (use_new_method) {
		fname = "data/new_method_data.csv";
	} else {
		fname = "data/old_method_data.csv";
	}
	
	std::ofstream file(fname);
	assert (file.is_open());
	file << "coeffs_len,us\n";

	std::vector<int> run_indices(number_of_runs);
	std::iota(std::begin(run_indices), std::end(run_indices), 0);
	std::shuffle(std::begin(run_indices), std::end(run_indices), gen);

	int logging_index = 1;
	for (int run_num : run_indices) {
		std::cout << logging_index << "\n";

		int len = (run_num + 1) * len_increase_per_run;
		logging_index++;
		double total_us = 0;

		for (int trial_num = 0; trial_num < trials_per_run; trial_num++) {
			std::vector<int> coeffs(len);
			for (int& n : coeffs) {
				n = values_distr(gen);
			}
			int shift = values_distr(gen);

			auto t1 = high_resolution_clock::now();
			if (use_new_method) {
				computeHorizontalShiftNewMethod(coeffs, shift);
			} else {
				computeHorizontalShiftBinomialThm(coeffs, shift);
			}
			auto t2 = high_resolution_clock::now();

			int us = duration_cast<microseconds>(t2 - t1).count();
			total_us += us;

		}

		double avg_us = total_us / trials_per_run;
		file << len << "," << avg_us << "\n";
		file.flush();
	}
}

// supply 0 (old) or 1 (new)
int main(int argc, char* argv[])
{
	assert(argc == 2);
	bool mode = std::stoi(argv[1]);
	run_simulation(5, mode ? 1000 : 100, 5, 50000, mode);

	
	return 0;
}
