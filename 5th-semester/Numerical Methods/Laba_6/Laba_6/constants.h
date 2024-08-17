#ifndef CONSTANTS_H_
#define CONSTANTS_H_

const int a{ 1 };
const int b{ 2 };
//F(x) = 2 * x * sqrt(x) + 3/2*x^2.
//a = 1, b = 2. По формуле Ньютона-Лейбница: 
//I = F(b) - F(a) = (2 * b * sqrt(b) + 3.0 / 2.0 * b * b) - (2 * a * sqrt(a) + 3.0 / 2.0 * a * a)
const double I{ ((2 * b * sqrt(b) + 3.0 / 2.0 * b * b) - (2 * a * sqrt(a) + 3.0 / 2.0 * a * a)) };

#endif /*CONSTANTS_H_*/