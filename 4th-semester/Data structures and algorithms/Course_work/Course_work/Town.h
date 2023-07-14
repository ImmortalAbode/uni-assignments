#ifndef TOWN_H_
#define TOWN_H_

#include <string>

//Статическая реализация node ("узлов") списка.
class Town
{
private:
	std::string m_name{""};
	int m_population{};

public:
	Town();

	void setName(std::string new_name);
	std::string getName();

	void setPopulation(int new_population);
	int getPopulation();

	~Town();
};

#endif /*TOWN_H_*/