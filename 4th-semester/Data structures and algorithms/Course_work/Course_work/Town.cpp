#include <iostream>
#include <string>

#include "Town.h"

Town::Town()
	:m_name{ "" }, m_population{}
{
	//std::cout << "Пустой объект-город был успешно создан." << std::endl;
}

void Town::setName(std::string new_name)
{
	this->m_name = new_name;
}
std::string Town::getName()
{
	return this->m_name;
}

void Town::setPopulation(int new_population)
{
	this->m_population = new_population;
}
int Town::getPopulation()
{
	return this->m_population;
}

Town::~Town()
{}