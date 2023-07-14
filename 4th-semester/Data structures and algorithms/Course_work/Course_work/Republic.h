#ifndef REPUBLIC_H_
#define REPUBLIC_H_

#include <string>
#include "Town.h"
#include "constants.h"

//Статическая реализация неупорядоченного линейного списка.
class Republic
{
private:
	static const int m_size{ size };

	std::string m_name{ "" };

	int m_count_of_towns{};
	Town m_towns[m_size];

	Republic* m_next{ nullptr };

public:
	Republic();
	Republic(std::string name);

	void addNewTownAfter(std::string const& town_name, const int& town_population, const int& index);
	void addNewTownBefore(std::string const& town_name, const int& town_population, const int& index);
	int findTownInRepublic(std::string const& town_name);

	void setNext(Republic*& next);
	Republic*& getNext();

	void setName(std::string new_name);
	std::string getName();

	Town& getTown(int town_index);

	void setCountOfTowns(int new_count_of_towns);
	int getCountOfTowns();

	bool subListisFull();

	void delTown(const int& town_index);

	~Republic();
};

#endif /*REPUBLIC_H_*/