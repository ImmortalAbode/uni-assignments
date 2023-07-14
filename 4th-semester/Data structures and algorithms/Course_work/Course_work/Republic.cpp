#include <iostream>
#include <string>

#include "Republic.h"

Republic::Republic()
	:m_name{ "" }, m_next{ nullptr }, m_count_of_towns{}
{}

Republic::Republic(std::string name)
	:m_count_of_towns{}, m_name{ name }, m_next{nullptr}
{
	//std::cout << "Пустой объект-республика был успешно создан." << std::endl;
}

void Republic::addNewTownAfter(std::string const& town_name, const int& town_population, const int& index)
{
	for (int i{ this->m_count_of_towns - 1 }; i > index;i--)
		this->m_towns[i + 1] = this->m_towns[i];
	this->m_towns[index + 1].setPopulation(town_population);
	this->m_towns[index + 1].setName(town_name);
	this->m_count_of_towns++;
}
void Republic::addNewTownBefore(std::string const& town_name, const int& town_population, const int& index)
{
	for (int i{ this->m_count_of_towns - 1 }; i >= index;i--)
		this->m_towns[i + 1] = this->m_towns[i];
	this->m_towns[index].setPopulation(town_population);
	this->m_towns[index].setName(town_name);
	this->m_count_of_towns++;
}
int Republic::findTownInRepublic(std::string const& town_name)
{
	for (int i{}; i < this->m_count_of_towns; i++)
	{
		if (this->m_towns[i].getName() == town_name) return i;
	}
	return -1;
}

void Republic::setNext(Republic*& new_next)
{
	this->m_next = new_next;
}
Republic*& Republic::getNext()
{
	return this->m_next;
}

void Republic::setName(std::string new_name)
{
	this->m_name = new_name;
}
std::string Republic::getName()
{
	return this->m_name;
}

Town& Republic::getTown(int town_index)
{
	return this->m_towns[town_index];
}

void Republic::setCountOfTowns(int new_count_of_towns)
{
	this->m_count_of_towns = new_count_of_towns;
}
int Republic::getCountOfTowns()
{
	return this->m_count_of_towns;
}

bool Republic::subListisFull()
{
	return this->m_size == this->m_count_of_towns ? true : false;
}

void Republic::delTown(const int& town_index)
{
	std::cout << "Город " << this->m_towns[town_index].getName() << " был удален." << std::endl;
	this->m_count_of_towns--;
	for (int i{ town_index }; i < this->m_count_of_towns;i++)
		this->m_towns[i] = this->m_towns[i + 1];
}

Republic::~Republic()
{
	std::cout << "Республика " << this->m_name << " была удалена." << std::endl;
} 