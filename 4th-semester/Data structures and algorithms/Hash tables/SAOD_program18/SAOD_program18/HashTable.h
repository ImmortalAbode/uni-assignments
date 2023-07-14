#ifndef HASHTABLE_H_
#define HASHTABLE_H_

#include "constants.h"

struct Node
{
	std::string key{};
	Node* next{ nullptr };
};

struct Key
{
	std::string key{};
	Node* first{ nullptr };
	Node* last{ nullptr };
};

struct HashTable
{
	int count_key{};
	Key array[m]{};
};

#endif /*HASHTABLE_H_*/