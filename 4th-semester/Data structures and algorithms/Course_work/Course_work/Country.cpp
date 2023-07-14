#include <iostream>
#include <string>

#include "Country.h"

Country::Country()
	:m_name{ "Unknown" },
	m_head_republics{ nullptr }
{
	//std::cout << "Пустой объект-страна был успешно создан." << std::endl;
}

void Country::setName(std::string new_name)
{
	this->m_name = new_name;
}
std::string Country::getName()
{
	return this->m_name;
}

Republic*& Country::getHeadOfRepublics()
{
	return this->m_head_republics;
}

void Country::AddNewRepublicInOrder(std::string const& republic_name)
{
	if (this->countryIsEmpty())
	{
		Republic* new_republic = new Republic{ republic_name };
		this->m_head_republics = new Republic{};
		this->m_head_republics->setNext(new_republic);
	}
	else
	{
		Republic* new_republic = new Republic{ republic_name };
		Republic* cur_republic{ this->m_head_republics };
		while (cur_republic->getNext() != nullptr && cur_republic->getNext()->getName().length() < new_republic->getName().length())
			cur_republic = cur_republic->getNext();
		if (cur_republic->getNext() == nullptr)
			cur_republic->setNext(new_republic);
		else if (cur_republic->getNext()->getName().length() == new_republic->getName().length())
		{
			while (cur_republic->getNext() != nullptr && cur_republic->getNext()->getName().length() == new_republic->getName().length())
			{
				for (int i{}; i < cur_republic->getNext()->getName().length();i++)
				{
					if (cur_republic->getNext()->getName()[i] > new_republic->getName()[i])
					{
						new_republic->setNext(cur_republic->getNext());
						cur_republic->setNext(new_republic);
						return;
					}
				}
				cur_republic = cur_republic->getNext();
			}
			if (cur_republic->getNext() != nullptr)
				new_republic->setNext(cur_republic->getNext());
			cur_republic->setNext(new_republic);
		}
		else
		{
			new_republic->setNext(cur_republic->getNext());
			cur_republic->setNext(new_republic);
		}
	}
}
Republic*& Country::findRepublicInCountry(std::string const& key_republic_name)
{
	if (!this->countryIsEmpty())
	{
		Republic* cur_republic{ this->m_head_republics };
		while (cur_republic->getNext() != nullptr)
		{
			cur_republic = cur_republic->getNext();
			if (cur_republic->getName() == key_republic_name)
				return cur_republic;
		}
	}
	return this->m_head_republics;
}

bool Country::countryIsEmpty()
{
	return this->m_head_republics == nullptr ? true : false;
}

void Country::delRepublic(Republic*& del_republic)
{
	Republic* cur_republic{ this->m_head_republics };
	while (cur_republic->getNext() != del_republic)
		cur_republic = cur_republic->getNext();
	cur_republic->setNext(del_republic->getNext());
	int count{ del_republic->getCountOfTowns() };
	for (int i{ count - 1 }; i >= 0; i--)
		del_republic->delTown(i);
	delete del_republic;
}

Country::~Country()
{
	std::cout << "Страна " << this->m_name << " была удалена." << std::endl;
}

