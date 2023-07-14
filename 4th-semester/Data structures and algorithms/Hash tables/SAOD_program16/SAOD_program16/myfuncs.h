#ifndef MYFUNCS_H_
#define MYFUNCS_H_

#include <string>
#include "HashTable.h"

int hashFunc(std::string const& new_key);
void buildNonConflictHashTable(HashTable& hash_table);
void printHashTable(const HashTable& hash_table);
void findKeyInHashTable(const HashTable& hash_table);

#endif /*MYFUNCS_H_*/