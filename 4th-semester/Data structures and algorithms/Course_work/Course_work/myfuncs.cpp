#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

#include "myfuncs.h"
#include "Country.h"
#include "Republic.h"
#include "Town.h"

void MenuOfProgram()
{
	std::cout << "��� �� ������ ������� �� ����������?" << std::endl;
	std::cout << "0 - ��������� �� �����.\n"
		<< "1 - ������ �������� ������.\n"
		<< "2 - �������� ��� ���������.\n"
		<< "3 - �������� �������.\n"
		<< "4 - ������� �������.\n"
		<< "5 - ����� �������.\n"
		<< "6 - ��������� � ����.\n"
		<< "7 - ����� �� ���������.\n";
	std::cout << std::endl;
}
int getPointOfMenu()
{
	while (true)
	{
		std::string point{};
		std::cout << "��� �����: ";
		std::getline(std::cin, point);
		if (point == "0" || point == "1" || point == "2" || point == "3" || point == "4" || point == "5" || point == "6" || point == "7")
		{
			std::cout << std::endl;
			return convertStrToInt(point);
		}
		else
			std::cout << "�� ������ ������ ����� ����� �� 0 �� 7. ��������� ����. " << std::endl;
	}
}

int convertStrToInt(std::string const& convertStr)
{
	int number{};
	if (convertStr.length() > 10 || convertStr.length() == 10 &&
		(convertStr[0] > '2' || convertStr[1] > '1' || convertStr[2] > '4' || convertStr[3] > '7' || convertStr[4] > '4' ||
			convertStr[5] > '8' || convertStr[6] > '3' || convertStr[7] > '6' || convertStr[8] > '4' || convertStr[9] > '7'))
	{
		std::cout << "������ �����. ����������� ��������� �����: 2 147 483 647. ����� ���������� -1." << std::endl;
		return -1;
	}
	for (int i{}; i < convertStr.length();i++)
	{
		number += static_cast<int>((convertStr[i] - '0') * pow(10, convertStr.length() - 1 - i));
	}
	return number;
}
bool checkStrIsNumeric(std::string const& userStr)
{
	for (int i{}; i < userStr.length();i++)
		if (userStr[i] < '0' || userStr[i] > '9')
			return false;
	return true;
}

bool NameOfObjectIsCorrect(std::string const& ObjectName)
{
	for (int i{}; i < ObjectName.length();i++)
	{
		if (ObjectName[i] >= '�' && ObjectName[i] <= '�' || ObjectName[i] >= '�' && ObjectName[i] <= '�' ||
			ObjectName[i] == ' ' && i != 0 && i != ObjectName.length() - 1 ||
			ObjectName[i] == '-' && i != 0 && i != ObjectName.length() - 1)
			continue;
		else
			return false;
	}
	return true;
}
std::string getDataUserElem()
{
	while (true)
	{
		std::string ObjectName{};
		std::getline(std::cin, ObjectName);
		if (ObjectName.length() == 0)
			std::cout << "������ �� ����� ���� ������. ��������� ����: ";
		else if (NameOfObjectIsCorrect(ObjectName) || ObjectName == "-1")
		{
			return ObjectName;
		}
		else
			std::cout << "������ �������� ������������ ������� ��� ��������. ��������� ����: ";
	}
}
int get0_1()
{
	while (true)
	{
		std::string choice{};
		std::getline(std::cin, choice);
		if (choice == "0" || choice == "1")
			return convertStrToInt(choice);
		else
			std::cout << "�� ������ ������ 0 ��� 1. ��������� ����: ";
	}
}
int getPopulation()
{
	std::cout << "������� ��������� ������: ";
	while (true)
	{
		std::string userNum{};
		std::getline(std::cin, userNum);
		if (userNum.length() == 0)
			std::cout << "������ �����. ������� ����������� ����� ��� 0: ";
		else if (checkStrIsNumeric(userNum) && convertStrToInt(userNum) >= 0)
			return convertStrToInt(userNum);
		else
			std::cout << "������ �����. ������� ����������� ����� ��� 0: ";
	}
}

void GiveNameToCountry(Country*& ptr_struct)
{
	std::cout << "��� �� ������ ������� ������(-1 ��� ������ � ����)? ";
	std::string country_name{ getDataUserElem() };
	if (country_name == "-1") return;
	ptr_struct->setName(country_name);
	std::cout << "������ ���� ������� " << country_name << "." << std::endl;
}
void showAllStruct(Country*& ptr_struct)
{
	if (!ptr_struct->countryIsEmpty())
	{
		std::cout << "������ ������." << std::endl;
		std::cout << "����������: �����[���������], �����[���������]...;\n" << std::endl;
		std::cout << "\t\t\t������ " << ptr_struct->getName() << "\n" << std::endl;
		Republic* cur_republic{ ptr_struct->getHeadOfRepublics() };
		while (cur_republic->getNext() != nullptr)
		{
			cur_republic = cur_republic->getNext();
			std::cout << cur_republic->getName() << ": ";
			for (int i{}; i < cur_republic->getCountOfTowns();i++)
			{
				std::cout << cur_republic->getTown(i).getName() << "[" << cur_republic->getTown(i).getPopulation() << "]";
				if (i + 1 != cur_republic->getCountOfTowns()) std::cout << ", ";
				else std::cout << ";";
			}
			std::cout << std::endl;
		}
		std::cout << std::endl;
	}
	else
		std::cout << "���� ��������� ������." << std::endl;
}
void AddElemToStruct(Country*& ptr_struct)
{
	showAllStruct(ptr_struct);
	if (ptr_struct->countryIsEmpty())
	{
		std::cout << "�������� ������ ����������." << std::endl << std::endl;
		std::cout << "������� �������� ���������� ��� -1, ����� ��������� � ����: ";
		std::string republic_name{ getDataUserElem() };
		if (republic_name == "-1") return;
		ptr_struct->AddNewRepublicInOrder(republic_name);
	}
	else
	{
		std::cout << "��� �� ������ �������� � ���������?" << std::endl;
		std::cout << "0 - ����������, 1 - �����: ";
		int type{ get0_1() };
		std::cout << std::endl;
		if (type == 0)
		{
			std::cout << "������� �������� ���������� ��� -1, ����� ��������� � ����: ";
			while (true)
			{
				std::string republic_name{ getDataUserElem() };
				if (republic_name == "-1") return;
				if (ptr_struct->findRepublicInCountry(republic_name) == ptr_struct->getHeadOfRepublics())
				{
					ptr_struct->AddNewRepublicInOrder(republic_name);
					break;
				}
				else
					std::cout << "������ ���������� ��� ���� � ������. ��������� ����: ";
			}
		}
		else if (type == 1)
		{
			std::cout << "������� �������� ����������, � ������� �� ������ �������� �����, ��� -1, ����� ��������� � ����: ";
			std::string republic_name{};
			while (true)
			{
				republic_name = getDataUserElem();
				if (republic_name == "-1") return;
				if (ptr_struct->findRepublicInCountry(republic_name) == ptr_struct->getHeadOfRepublics())
					std::cout << "������ ���������� ��� � ������ ������. ��������� ����: ";
				else if (ptr_struct->findRepublicInCountry(republic_name)->subListisFull())
					std::cout << "���������� �����������. ��������� ����: ";
				else
					break;
			}
			if (ptr_struct->findRepublicInCountry(republic_name)->getCountOfTowns() != 0)
			{
				std::cout << "������� �������� ������, ��/����� ������� �� ������ ����������� ����������, ��� -1, ����� ��������� � ����: ";
				int index_town{};
				while (true)
				{
					std::string key_town{ getDataUserElem() };
					if (key_town == "-1") return;
					index_town = ptr_struct->findRepublicInCountry(republic_name)->findTownInRepublic(key_town);
					if (index_town == -1)
						std::cout << "������� ������ ��� � ������ ����������. ��������� ����: ";
					else
						break;
				}
				std::cout << "�� ������ �������� ����� ����� �� (0) ��� ����� (1) ��������� ��������? ";
				if (get0_1() == 0)
				{
					std::cout << "������� �������� ������, ������� ������ �������� (�� �� ������ ����� ���������� � ����������), ��� -1, ����� ��������� � ����: ";
					std::string town_name{};
					while (true)
					{
						town_name = getDataUserElem();
						if (town_name == "-1") return;
						if (ptr_struct->findRepublicInCountry(republic_name)->findTownInRepublic(town_name) != -1)
							std::cout << "������ ����� ��� ���� � ����������. ��������� ����: ";
						else
							break;
					}
					int town_population{ getPopulation() };
					ptr_struct->findRepublicInCountry(republic_name)->addNewTownBefore(town_name, town_population, index_town);
				}
				else
				{
					std::cout << "������� �������� ������, ������� ������ �������� (�� �� ������ ����� ���������� � ����������), ��� -1, ����� ��������� � ����: ";
					std::string town_name{};
					while (true)
					{
						town_name = getDataUserElem();
						if (town_name == "-1") return;
						if (ptr_struct->findRepublicInCountry(republic_name)->findTownInRepublic(town_name) != -1)
							std::cout << "������ ����� ��� ���� � ����������. ��������� ����: ";
						else
							break;
					}
					int town_population{ getPopulation() };
					ptr_struct->findRepublicInCountry(republic_name)->addNewTownAfter(town_name, town_population, index_town);
				}
			}
			else
			{
				std::cout << "������� �������� ������, ������� ������ ��������, ��� -1, ����� ��������� � ����: ";
				std::string town_name{ getDataUserElem() };
				if (town_name == "-1") return;
				int town_population{ getPopulation() };
				ptr_struct->findRepublicInCountry(republic_name)->addNewTownAfter(town_name, town_population, -1);
			}
		}
	}
}
void FindElemInStruct(Country*& ptr_struct)
{
	if (!ptr_struct->countryIsEmpty())
	{
		std::cout << "������� �������� �������, ������� ������ �����: ";
		std::string finding_elem{ getDataUserElem() };
		Republic* cur_republic{ ptr_struct->getHeadOfRepublics() };
		int finding_results{};
		std::cout << "���������� ������: ([x], ��� x - ����� �������� ����������)" << std::endl;
		while (cur_republic->getNext() != nullptr)
		{
			cur_republic = cur_republic->getNext();
			if (cur_republic->getName() == finding_elem)
			{
				finding_results++;
				std::cout << "[" << finding_results << "]:" << " ���������� " << cur_republic->getName() << "." << std::endl;
			}
			for (int i{}; i < cur_republic->getCountOfTowns();i++)
			{
				if (cur_republic->getTown(i).getName() == finding_elem)
				{
					finding_results++;
					std::cout << "[" << finding_results << "]:" << " ����� " << cur_republic->getTown(i).getName() << "." << std::endl;
				}
			}
			std::cout << std::endl;
		}
		if (finding_results == 0) std::cout << "������ ������� �� ����." << std::endl;
	}
	else
		std::cout << "���� ��������� ������." << std::endl;

}
void DeleteElemFromStruct(Country*& ptr_struct)
{
	if (ptr_struct->countryIsEmpty())
	{
		std::cout << "���� ��������� ������. ������� ��������� ��." << std::endl;
		return;
	}
	showAllStruct(ptr_struct);
	std::cout << "��� �� ������ ������� �� ���������?" << std::endl;
	std::cout << "0 - ����������, 1 - �����: ";
	int type{ get0_1() };
	if (type == 0)
	{
		std::cout << "�������� �������� ����������, ������� ������ �������, ��� -1, ����� ����� � ����: ";
		while (true)
		{
			std::string republic_name{ getDataUserElem() };
			if (republic_name == "-1") return;
			Republic* del_republic{ ptr_struct->findRepublicInCountry(republic_name) };
			if (del_republic == ptr_struct->getHeadOfRepublics())
				std::cout << "�������� ���������� ��� � ������ ������. ��������� ����: ";
			else
			{
				ptr_struct->delRepublic(del_republic);
				break;
			}
		}
	}
	else
	{
		std::cout << "�������� �������� ����������, ������� ����������� ��������� �����, ��� -1, ����� ����� � ����: ";
		std::string republic_name{};
		Republic* del_republic{};
		while (true)
		{
			republic_name = getDataUserElem();
			if (republic_name == "-1") return;
			del_republic = ptr_struct->findRepublicInCountry(republic_name);
			if (del_republic == ptr_struct->getHeadOfRepublics())
				std::cout << "�������� ���������� ��� � ������ ������. ��������� ����: ";
			else
				break;
		}
		if (del_republic->getCountOfTowns() != 0)
		{
			std::cout << "�������� �������� ������, ������� ������ �������, ��� -1, ����� ����� � ����: ";
			while (true)
			{
				std::string town_name{ getDataUserElem() };
				if (town_name == "-1") return;
				int index_town{ del_republic->findTownInRepublic(town_name) };
				if (index_town == -1)
					std::cout << "�������� ����� �� ����������� ������ ���������� � ������ ������. ��������� ����: ";
				else
				{
					del_republic->delTown(index_town);
					break;
				}
			}
		}
		else
			std::cout << "������ ���������� ������. �������� ������ ����������." << std::endl;
	}
}
void ClearStruct(Country*& ptr_struct)
{
	if (ptr_struct->getHeadOfRepublics() != nullptr)
		while (ptr_struct->getHeadOfRepublics()->getNext() != nullptr)
		{
			Republic* del_republic{ ptr_struct->getHeadOfRepublics()->getNext() };
			ptr_struct->delRepublic(del_republic);
		}
	delete ptr_struct;
	std::cout << std::endl;
}

int getCountOfFields(std::string ss_data)
{
	std::stringstream data_field{ ss_data };
	std::string elem_str{};
	int count_of_fields{};
	while (std::getline(data_field, elem_str, ';'))
		count_of_fields++;
	return count_of_fields;
}
void addObjectToCheckingMass(std::string*& old_mass_of_objects, int& old_count_of_objects, std::string const& new_name)
{
	std::string* new_mass_of_objects{ nullptr };
	try
	{
		new_mass_of_objects = new std::string[old_count_of_objects + 1]{};
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
		std::cout << "�� ������� �������� ������ �� ����. ���� �����������!" << std::endl;
		delete[] old_mass_of_objects;
		delete[] new_mass_of_objects;
		exit(-1);
	}
	for (int i{};i < old_count_of_objects; i++)
		new_mass_of_objects[i] = old_mass_of_objects[i];
	new_mass_of_objects[old_count_of_objects] = new_name;
	old_count_of_objects += 1;
	delete[] old_mass_of_objects;
	old_mass_of_objects = new_mass_of_objects;
}
bool checkSSIsCorrect(std::string ss_data, std::string*& mass_of_republics, int& count_of_republics)
{
	std::stringstream data_field{ ss_data };
	std::string elem_str{};
	bool is_republic{ false };
	int count_of_elements{};

	int count_of_towns{};
	std::string* mass_of_towns{ nullptr };
	try
	{
		mass_of_towns = new std::string[count_of_towns]{};
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
		std::cout << "�� ������� �������� ������ �� ����. ���� �����������!" << std::endl;
		delete[] mass_of_towns;
		exit(-1);
	}

	while (std::getline(data_field, elem_str, ';'))
	{
		if (!is_republic)
		{
			if (NameOfObjectIsCorrect(elem_str))
			{
				is_republic = true;
				for (int i{}; i < count_of_republics; i++)
					if (mass_of_republics[i] == elem_str)
					{
						std::cout << "������: ���� �������� ����������, ������� ��� ���� � ��������� (" << elem_str << ").������ ���� �� �����." << std::endl;
						return false;
					}
				addObjectToCheckingMass(mass_of_republics, count_of_republics, elem_str);
				continue;
			}
			else
			{
				std::cout << "������: ������������ �������� ���������� " << elem_str << "." << std::endl;
				return false;
			}
		}
		count_of_elements++;
		if (count_of_elements / 2 + count_of_elements % 2 > size)
		{
			std::cout << "������: ������� ������� ������� ���������� ������� � ���������� " << mass_of_republics[count_of_republics - 1] << "." << std::endl;
			delete[] mass_of_towns;
			return false;
		}
		else if (count_of_elements % 2 != 0)
		{
			if (NameOfObjectIsCorrect(elem_str))
			{
				for (int i{}; i < count_of_towns; i++)
					if (mass_of_towns[i] == elem_str)
					{
						std::cout << "������: ���������� �� ����� ��������� ������� � ����������� ���������� (" << elem_str << ")." << std::endl;
						delete[] mass_of_towns;
						return false;
					}
				addObjectToCheckingMass(mass_of_towns, count_of_towns, elem_str);
			}
			else
			{
				std::cout << "������: ������������ �������� ������ " << elem_str << "." << std::endl;
				delete[] mass_of_towns;
				return false;
			}
		}
		else
		{
			if (!checkStrIsNumeric(elem_str))
			{
				std::cout << "������: ������ ���������� ���������� ��������� " << elem_str << "." << std::endl;
				delete[] mass_of_towns;
				return false;
			}
		}
	}
	if (count_of_elements % 2 != 0)
	{
		std::cout << "������: ��������� ����� ���������� " << mass_of_republics[count_of_republics - 1] << " �� ����� �������� ���������." << std::endl;
		delete[] mass_of_towns;
		return false;
	}
	delete[] mass_of_towns;
	return true;
}
void DataFromFile(Country*& ptr_struct, std::stringstream& data_field)
{
	std::string elem_str{}; //������ ��������� ������� ������ � �������.

	bool is_republic{ false }; //��� ���������������, ����� ����������� ����������.
	int town_or_population{}; //������������ ���-�� ��� ���������� ������ ��� ���������. �������� ��������� ����������� ���������.

	std::string republic_name{}; //���������� ��� ������� ����������.

	std::string town_name{}; //���������� ��� �������� ������.
	int town_population{}; //���������� ������� ���-�� ���������.
	while (std::getline(data_field, elem_str, ';'))
	{
		if (!is_republic)
		{
			ptr_struct->AddNewRepublicInOrder(elem_str);
			republic_name = elem_str;
			is_republic = true;
		}
		else
		{
			town_or_population++;
			if (town_or_population % 2 != 0)
				town_name = elem_str;
			else
			{
				town_population = convertStrToInt(elem_str);
				int count_of_towns{ town_or_population / 2 };
				ptr_struct->findRepublicInCountry(republic_name)->addNewTownAfter(town_name, town_population, count_of_towns - 2);
				ptr_struct->findRepublicInCountry(republic_name)->setCountOfTowns(count_of_towns);
			}
		}
	}
}
void LoadFromFile(Country*& ptr_struct)
{
	std::cout << "������� �������� �����, �� �������� ����� ��������� ������ ��� ���������: ";
	std::string name_loading_file{ getNameOfFile() + ".txt" };
	std::ifstream data_file{ name_loading_file };
	std::string ss_data{};

	int count_of_republics{};
	std::string* mass_of_republics = new std::string[count_of_republics];
	if (ptr_struct->getHeadOfRepublics() != nullptr)
	{
		Republic* cur_republic{ ptr_struct->getHeadOfRepublics() };
		while (cur_republic->getNext() != nullptr)
		{
			cur_republic = cur_republic->getNext();
			addObjectToCheckingMass(mass_of_republics, count_of_republics, cur_republic->getName());
		}
	}

	bool empty{ true };
	int is_country{ false };

	if (!data_file.is_open())
	{
		std::cout << "�� ������� ������� ����!" << std::endl;
		return;
	}
	else
	{
		while (!data_file.eof())
		{
			if (std::getline(data_file, ss_data))
			{
				std::stringstream data_field{ ss_data };
				empty = false;
				int count_of_fields{ getCountOfFields(ss_data) };
				if (!is_country)
				{
					if (count_of_fields == 1)
					{
						std::string country_name{};
						std::getline(data_field, country_name, ';');
						if (NameOfObjectIsCorrect(country_name))
						{
							ptr_struct->setName(country_name);
							is_country = true;
							continue;
						}
						else
						{
							std::cout << "������: ������ ������ ����� �������� ��������� ��������� ������ " << country_name << "." << std::endl;
							return;
						}
					}
					else
					{
						std::cout << "������: ������ ������ ����� ������ ��������� ������ �������� ������." << std::endl;
						return;
					}
				}
				if (checkSSIsCorrect(ss_data, mass_of_republics, count_of_republics))
					DataFromFile(ptr_struct, data_field);
				else
				{
					delete[] mass_of_republics;
					return;
				}
			}
		}
		if (empty)
			std::cout << "��� ���� ������." << std::endl;
		else
			std::cout << "������ �� ����� " << name_loading_file << " ���� ������� � ��������� � ���������." << std::endl;
	}
	delete[] mass_of_republics;
}
bool NameFileIsCorrect(std::string const& name_saving_file)
{
	for (int i{}; i < name_saving_file.length();i++)
	{
		if (name_saving_file[i] >= '�' && name_saving_file[i] <= '�' || name_saving_file[i] >= '�' && name_saving_file[i] <= '�' ||
			name_saving_file[i] >= 'a' && name_saving_file[i] <= 'z' || name_saving_file[i] >= 'A' && name_saving_file[i] <= 'Z' ||
			name_saving_file[i] >= '0' && name_saving_file[i] <= '9' ||
			name_saving_file[i] == ' ' && i != 0 && i != name_saving_file.length() - 1 ||
			name_saving_file[i] == '_' && i != 0 && i != name_saving_file.length() - 1)
			continue;
		else
			return false;
	}
	return true;
}
std::string getNameOfFile()
{
	while (true)
	{
		std::string name_saving_file{};
		std::getline(std::cin, name_saving_file);
		if (name_saving_file.length() == 0)
			std::cout << "��� ����� �� ����� ���� ������. ��������� ����: ";
		else if (NameFileIsCorrect(name_saving_file))
			return name_saving_file;
		else
			std::cout << "��� ����� �������� ������������ �����. ��������� ����: ";
	}
}
void LoadInFile(Country*& ptr_struct)
{
	if (!ptr_struct->countryIsEmpty())
	{
		std::cout << "������� �������� �����, � ������� ���������� ���������: ";
		std::string name_saving_file{ getNameOfFile() + ".txt" };
		std::ofstream out_data_file{ name_saving_file };

		Republic* cur_republic{ ptr_struct->getHeadOfRepublics() };

		out_data_file << ptr_struct->getName() << std::endl;
		while (cur_republic->getNext() != nullptr)
		{
			cur_republic = cur_republic->getNext();
			out_data_file << cur_republic->getName() << ";";
			for (int i{}; i < cur_republic->getCountOfTowns();i++)
			{
				out_data_file << cur_republic->getTown(i).getName() << ";" << cur_republic->getTown(i).getPopulation();
				if (i + 1 != cur_republic->getCountOfTowns()) out_data_file << ";";
			}
			out_data_file << std::endl;
		}
		std::cout << "������ ��������� ���� ��������� � ����� " << name_saving_file << "!" << std::endl;
	}
	else
		std::cout << "���� ��������� ������." << std::endl;
}
