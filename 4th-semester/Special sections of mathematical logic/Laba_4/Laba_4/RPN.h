#ifndef RPN_H_
#define RPN_H_

#include <string>

struct Stack
{
	Stack* next{ nullptr };
	char current_value{};
};

struct OutString
{
	OutString* next{ nullptr };
	std::string current_out_value{};
	OutString* prev{ nullptr };
};

#endif /*RPN_H_*/