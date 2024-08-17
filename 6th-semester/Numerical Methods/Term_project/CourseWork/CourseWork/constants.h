#ifndef CONSTANTS_H_
#define CONSTANTS_H_

#include <vector>
//Коэффициенты полинома.
const std::vector<std::vector<long double>> base_coefs{
	std::vector<long double>{ 1.0f },
	std::vector<long double>{ 2.0f },
	std::vector<long double>{ 2.0f },
	std::vector<long double>{ -8.0f },
	std::vector<long double>{ 16.0f }
};

#endif /*CONSTANTS_H_*/
