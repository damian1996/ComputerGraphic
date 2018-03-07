#ifndef WDGK_SCALAR_HEADER
#define WDGK_SCALAR_HEADER

#include <algorithm>
#include <cmath>

// Computes the minimum of 3 values of any type
template <typename T>
T min(T a, T b, T c) { return std::min(std::min(a,b),c); }

// Computes the maximum of 3 values of any type
template <typename T>
T max(T a, T b, T c) { return std::max(std::max(a,b),c); }

// Computes a square of
template <typename T>
T sqr(const T& a) { return a*a; }

// Returns the fractional part of a number. For negative numbers it returns the negative fractional
float fractional(float f);

// Returns the difference between the given value and the nearest lower integer. Always in range [0, 1)
float absfractional(float f);

// The mathematical pi constant
static const float pi = 3.141592f;

// Approximate equal of two floats
bool approx_equal(float a, float b);

typedef unsigned int uint;

#endif
