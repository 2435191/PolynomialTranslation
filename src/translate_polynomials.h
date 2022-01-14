/*
 * translate_polynomials.h
 *
 *  Created on: Jan 12, 2022
 *      Author: Will Bradley
 */

#ifndef TRANSLATE_POLYNOMIALS_H_
#define TRANSLATE_POLYNOMIALS_H_

#include <complex>

namespace PolynomialOperations {

template<typename T>
const std::vector<T> computeHorizontalShiftNewMethod(
		const std::vector<T> &coeffs, const T &shift);



template<typename T>
const std::vector<T> computeHorizontalShiftBinomialThm(
		const std::vector<T> &coeffs, const T &shift);


}
#include "translate_polynomials.cpp"

#endif /* TRANSLATE_POLYNOMIALS_H_ */
