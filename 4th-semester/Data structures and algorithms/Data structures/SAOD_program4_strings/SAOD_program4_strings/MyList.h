#ifndef MYLIST_H_
#define MYLIST_H_

#include <string>

const int size{ 10 };

struct List
{
	int count{};
	std::string list[size]{};
};

#endif /*MYLIST_H_*/