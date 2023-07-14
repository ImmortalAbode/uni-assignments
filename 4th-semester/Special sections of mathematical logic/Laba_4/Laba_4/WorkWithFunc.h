#ifndef WORKWITHFUNC_H_
#define WORKWITHFUNC_H_

#include <string>

struct Func
{
	std::string func{};
	int k{};
	int n{};
};

struct Result
{
	int value{};
	Result* next{ nullptr };
};

#endif /*WORKWITHFUNC_H_*/