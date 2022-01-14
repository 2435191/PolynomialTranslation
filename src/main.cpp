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
#include <stdexcept>

#include "translate_polynomials.h"
using namespace PolynomialOperations;

template<typename T>
static void print(const std::vector<T>& vec) {
    for (const T& n : vec) {
        std::cout << n << " ";
    }
    std::cout << "\n";
}


int main(int argc, char* argv[])
{
	if (argc != 4) {
		throw std::invalid_argument(
			"Invalid number of arguments, expected 3");
	}

	int num_tests = std::stoi(argv[1]);
	int degree    = std::stoi(argv[2]);
	int max       = std::stoi(argv[3]);

    std::vector<std::uint_fast32_t> testCoeffs[num_tests];
    std::uint_fast32_t testShifts[num_tests];

    std::mt19937 rng;
    rng.seed(10);

    for (auto i = 0; i < num_tests; i++) {
        for (auto j = 0; j < degree; j++) {
            testCoeffs[i].push_back(rng() % max);
        }
        testShifts[i] = rng() % max;
    }

    using namespace std::chrono;


    //benchmark naive approach
    auto start = high_resolution_clock::now();
    for (auto i = 0; i < num_tests; i++) {
        computeHorizontalShiftBinomialThm(testCoeffs[i], testShifts[i]);
    }
    auto end = high_resolution_clock::now();
    microseconds elapsed = duration_cast<microseconds>(end - start);
    std::cout << elapsed.count() << " usec\n";

    //benchmark new approach
    start = high_resolution_clock::now();
    for (auto i = 0; i < num_tests; i++) {
        computeHorizontalShiftBinomialThm(testCoeffs[i], testShifts[i]);
    }
    end = high_resolution_clock::now();
    elapsed = duration_cast<microseconds>(end - start);
    std::cout << elapsed.count() << " usec\n";

    return 0;

}
