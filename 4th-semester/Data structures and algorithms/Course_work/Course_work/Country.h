#ifndef COUNTRY_H_
#define COUNTRY_H_

#include <string>
#include "Republic.h"

//Динамическая реализация линейного упорядоченного списка.
class Country
{
private:
	std::string m_name{ "" };
	Republic* m_head_republics{ nullptr };

public:
	Country();

	void setName(std::string new_name);
	std::string getName();

	Republic*& getHeadOfRepublics();

	void AddNewRepublicInOrder(std::string const& republic_name);
	Republic*& findRepublicInCountry(std::string const& key_republic_name);

	bool countryIsEmpty();

	void delRepublic(Republic*& key_republic);

	~Country();
};

#endif /*COUNTRY_H_*/