/*
 * translate_polynomials.cpp
 *
 *  Created on: Jan 12, 2022
 *      Author: Will Bradley
 */
#include <iostream>
#include <complex>
#include <vector>
#include <cmath>

/// \namespace PolynomialOperations A namespace of functions to translate polynomials.
/// \file translate_polynomials.h
namespace PolynomialOperations
{

/// \fn const std::vector<T> computeHorizontalShiftNewMethod(const std::vector<T>&, const T&)
///
///  Shift the polynomial described by
/// \p coeffs to the right by \p shift units,
/// using the new method.
///
///
/// \tparam T Type of \p coeffs and \p shift.
/// \param coeffs Coefficients to operate on, in decreasing power
///	left to right.
/// \param shift How much to shift to the right by.
/// \return A new coefficients list, similar to \p coeffs.
template<typename T = int>
const std::vector<T> computeHorizontalShiftNewMethod(
		const std::vector<T> &coeffs, const T &shift)
{
	const std::size_t size = coeffs.size();

	std::vector<T> out(coeffs); // out stores intermediate synth div rows

	for (std::size_t j = size; j > 0; j--)
	{
		for (std::size_t i = 1; i < j; i++)
		{
			out[i] = out[i] - shift * out[i - 1];
		}
	}

	return out;
}

/*
 adapted from https://stackoverflow.com/questions/55421835/c-binomial-coefficient-is-too-slow
 */
template<typename T = int, typename U = unsigned long long int>
static inline U computeBinomialCoefficient(const T &n, const T &k)
{
	if (n == k || k == 0)
	{
		return 1;
	}

	U out = n - k + 1;

	for (T i = 1; i < k; ++i)
	{
		out = out * (n - k + 1 + i) / (i + 1);
	}

	return out;
}

template<typename T>
static inline bool isZero(const T &n)
{
	return (n == 0);
}

template<typename TComplex>
static inline bool isZero(const std::complex<TComplex> &n)
{
	return (n.real() == 0 && n.imag() == 0);
}

template<typename T>
static inline T computeKthPower(const std::size_t &n, const std::size_t &k,
		const T &shift)
{
	return powl(-1 * shift, n - k) * computeBinomialCoefficient(n, k);
}


template<typename TComplex>
static inline std::complex<TComplex> computeKthPower(const std::size_t &n,
		const std::size_t &k, const std::complex<TComplex> &shift)
{
	std::complex<TComplex> invertedShift = static_cast<TComplex>(-1) * shift;
	std::complex<TComplex> power = pow(
			invertedShift, static_cast<TComplex>(n - k));
	return power * static_cast<TComplex>(computeBinomialCoefficient(n, k));
}

/// \fn const std::vector<T> computeHorizontalShiftBinomialThm(const std::vector<T>&, const T&)
///
/// Shift the polynomial described by
/// \p coeffs to the right by \p shift units,
/// using the "classical" binomial theorem method.
///
///
/// \tparam T Type of \p coeffs and \p shift.
/// \param coeffs Coefficients to operate on, in decreasing power
///	left to right.
/// \param shift How much to shift to the right by.
/// \return A new coefficients list, similar to \p coeffs.
template<typename T = int>
const std::vector<T> computeHorizontalShiftBinomialThm(
		const std::vector<T> &coeffs, const T &shift)
{
	std::size_t size = coeffs.size();
	std::vector<T> out(size, 0);

	for (std::size_t i = 0; i < size; i++)
	{
		T coefficient = coeffs[i];
		if (isZero(coefficient))
		{
			continue;
		}

		std::size_t n = size - i - 1; // power of monomial
		for (std::size_t k = 0; k <= n; k++)
		{

			T kthPower = computeKthPower(n, k, shift);
			out[size - k - 1] += coefficient * kthPower;
		}
	}

	return out;
}

}

