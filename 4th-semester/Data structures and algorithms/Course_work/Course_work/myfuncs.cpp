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
	std::cout << "Что вы хотите сделать со структурой?" << std::endl;
	std::cout << "0 - Загрузить из файла.\n"
		<< "1 - Задать название стране.\n"
		<< "2 - Показать всю структуру.\n"
		<< "3 - Добавить элемент.\n"
		<< "4 - Удалить элемент.\n"
		<< "5 - Найти элемент.\n"
		<< "6 - Выгрузить в файл.\n"
		<< "7 - Выход из программы.\n";
	std::cout << std::endl;
}
int getPointOfMenu()
{
	while (true)
	{
		std::string point{};
		std::cout << "Ваш выбор: ";
		std::getline(std::cin, point);
		if (point == "0" || point == "1" || point == "2" || point == "3" || point == "4" || point == "5" || point == "6" || point == "7")
		{
			std::cout << std::endl;
			return convertStrToInt(point);
		}
		else
			std::cout << "Вы должны ввести целое число от 0 до 7. Повторите ввод. " << std::endl;
	}
}

int convertStrToInt(std::string const& convertStr)
{
	int number{};
	if (convertStr.length() > 10 || convertStr.length() == 10 &&
		(convertStr[0] > '2' || convertStr[1] > '1' || convertStr[2] > '4' || convertStr[3] > '7' || convertStr[4] > '4' ||
			convertStr[5] > '8' || convertStr[6] > '3' || convertStr[7] > '6' || convertStr[8] > '4' || convertStr[9] > '7'))
	{
		std::cout << "Ошибка ввода. Максимально возможное число: 2 147 483 647. Будет возвращено -1." << std::endl;
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
		if (ObjectName[i] >= 'а' && ObjectName[i] <= 'я' || ObjectName[i] >= 'А' && ObjectName[i] <= 'Я' ||
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
			std::cout << "Строка не может быть пустой. Повторите ввод: ";
		else if (NameOfObjectIsCorrect(ObjectName) || ObjectName == "-1")
		{
			return ObjectName;
		}
		else
			std::cout << "Строка содержит некорректные символы для названия. Повторите ввод: ";
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
			std::cout << "Вы должны ввести 0 или 1. Повторите ввод: ";
	}
}
int getPopulation()
{
	std::cout << "Введите население города: ";
	while (true)
	{
		std::string userNum{};
		std::getline(std::cin, userNum);
		if (userNum.length() == 0)
			std::cout << "Ошибка ввода. Введите натуральное число или 0: ";
		else if (checkStrIsNumeric(userNum) && convertStrToInt(userNum) >= 0)
			return convertStrToInt(userNum);
		else
			std::cout << "Ошибка ввода. Введите натуральное число или 0: ";
	}
}

void GiveNameToCountry(Country*& ptr_struct)
{
	std::cout << "Как вы хотите назвать страну(-1 для выхода в меню)? ";
	std::string country_name{ getDataUserElem() };
	if (country_name == "-1") return;
	ptr_struct->setName(country_name);
	std::cout << "Страна была названа " << country_name << "." << std::endl;
}
void showAllStruct(Country*& ptr_struct)
{
	if (!ptr_struct->countryIsEmpty())
	{
		std::cout << "Шаблон вывода." << std::endl;
		std::cout << "Республика: город[население], город[население]...;\n" << std::endl;
		std::cout << "\t\t\tСтрана " << ptr_struct->getName() << "\n" << std::endl;
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
		std::cout << "Ваша структура пустая." << std::endl;
}
void AddElemToStruct(Country*& ptr_struct)
{
	showAllStruct(ptr_struct);
	if (ptr_struct->countryIsEmpty())
	{
		std::cout << "Добавьте первую республику." << std::endl << std::endl;
		std::cout << "Введите название республики или -1, чтобы вернуться в меню: ";
		std::string republic_name{ getDataUserElem() };
		if (republic_name == "-1") return;
		ptr_struct->AddNewRepublicInOrder(republic_name);
	}
	else
	{
		std::cout << "Что вы хотите добавить в структуру?" << std::endl;
		std::cout << "0 - республику, 1 - город: ";
		int type{ get0_1() };
		std::cout << std::endl;
		if (type == 0)
		{
			std::cout << "Введите название республики или -1, чтобы вернуться в меню: ";
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
					std::cout << "Данная республика уже есть в стране. Повторите ввод: ";
			}
		}
		else if (type == 1)
		{
			std::cout << "Введите название республики, в которую вы хотите добавить город, или -1, чтобы вернуться в меню: ";
			std::string republic_name{};
			while (true)
			{
				republic_name = getDataUserElem();
				if (republic_name == "-1") return;
				if (ptr_struct->findRepublicInCountry(republic_name) == ptr_struct->getHeadOfRepublics())
					std::cout << "Данной республики нет в данной стране. Повторите ввод: ";
				else if (ptr_struct->findRepublicInCountry(republic_name)->subListisFull())
					std::cout << "Республика переполнена. Повторите ввод: ";
				else
					break;
			}
			if (ptr_struct->findRepublicInCountry(republic_name)->getCountOfTowns() != 0)
			{
				std::cout << "Задайте название города, до/после которой вы хотите осуществить добавление, или -1, чтобы вернуться в меню: ";
				int index_town{};
				while (true)
				{
					std::string key_town{ getDataUserElem() };
					if (key_town == "-1") return;
					index_town = ptr_struct->findRepublicInCountry(republic_name)->findTownInRepublic(key_town);
					if (index_town == -1)
						std::cout << "Данного города нет в данной республике. Повторите ввод: ";
					else
						break;
				}
				std::cout << "Вы хотите добавить новый город до (0) или после (1) заданного элемента? ";
				if (get0_1() == 0)
				{
					std::cout << "Введите название города, который хотите добавить (он не должен иметь повторение с имеющимися), или -1, чтобы вернуться в меню: ";
					std::string town_name{};
					while (true)
					{
						town_name = getDataUserElem();
						if (town_name == "-1") return;
						if (ptr_struct->findRepublicInCountry(republic_name)->findTownInRepublic(town_name) != -1)
							std::cout << "Данный город уже есть в республике. Повторите ввод: ";
						else
							break;
					}
					int town_population{ getPopulation() };
					ptr_struct->findRepublicInCountry(republic_name)->addNewTownBefore(town_name, town_population, index_town);
				}
				else
				{
					std::cout << "Введите название города, который хотите добавить (он не должен иметь повторение с имеющимися), или -1, чтобы вернуться в меню: ";
					std::string town_name{};
					while (true)
					{
						town_name = getDataUserElem();
						if (town_name == "-1") return;
						if (ptr_struct->findRepublicInCountry(republic_name)->findTownInRepublic(town_name) != -1)
							std::cout << "Данный город уже есть в республике. Повторите ввод: ";
						else
							break;
					}
					int town_population{ getPopulation() };
					ptr_struct->findRepublicInCountry(republic_name)->addNewTownAfter(town_name, town_population, index_town);
				}
			}
			else
			{
				std::cout << "Введите название города, который хотите добавить, или -1, чтобы вернуться в меню: ";
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
		std::cout << "Введите название объекта, который хотите найти: ";
		std::string finding_elem{ getDataUserElem() };
		Republic* cur_republic{ ptr_struct->getHeadOfRepublics() };
		int finding_results{};
		std::cout << "Результаты поиска: ([x], где x - номер текущего результата)" << std::endl;
		while (cur_republic->getNext() != nullptr)
		{
			cur_republic = cur_republic->getNext();
			if (cur_republic->getName() == finding_elem)
			{
				finding_results++;
				std::cout << "[" << finding_results << "]:" << " Республика " << cur_republic->getName() << "." << std::endl;
			}
			for (int i{}; i < cur_republic->getCountOfTowns();i++)
			{
				if (cur_republic->getTown(i).getName() == finding_elem)
				{
					finding_results++;
					std::cout << "[" << finding_results << "]:" << " Город " << cur_republic->getTown(i).getName() << "." << std::endl;
				}
			}
			std::cout << std::endl;
		}
		if (finding_results == 0) std::cout << "Ничего найдено не было." << std::endl;
	}
	else
		std::cout << "Ваша структура пустая." << std::endl;

}
void DeleteElemFromStruct(Country*& ptr_struct)
{
	if (ptr_struct->countryIsEmpty())
	{
		std::cout << "Ваша структура пустая. Сначала заполните ее." << std::endl;
		return;
	}
	showAllStruct(ptr_struct);
	std::cout << "Что вы хотите удалить из структуры?" << std::endl;
	std::cout << "0 - республику, 1 - город: ";
	int type{ get0_1() };
	if (type == 0)
	{
		std::cout << "Напишите название республики, которую хотите удалить, или -1, чтобы выйти в меню: ";
		while (true)
		{
			std::string republic_name{ getDataUserElem() };
			if (republic_name == "-1") return;
			Republic* del_republic{ ptr_struct->findRepublicInCountry(republic_name) };
			if (del_republic == ptr_struct->getHeadOfRepublics())
				std::cout << "Заданной республики нет в данной стране. Повторите ввод: ";
			else
			{
				ptr_struct->delRepublic(del_republic);
				break;
			}
		}
	}
	else
	{
		std::cout << "Напишите название республики, которой принадлежит удаляемый город, или -1, чтобы выйти в меню: ";
		std::string republic_name{};
		Republic* del_republic{};
		while (true)
		{
			republic_name = getDataUserElem();
			if (republic_name == "-1") return;
			del_republic = ptr_struct->findRepublicInCountry(republic_name);
			if (del_republic == ptr_struct->getHeadOfRepublics())
				std::cout << "Заданной республики нет в данной стране. Повторите ввод: ";
			else
				break;
		}
		if (del_republic->getCountOfTowns() != 0)
		{
			std::cout << "Напишите название города, который хотите удалить, или -1, чтобы выйти в меню: ";
			while (true)
			{
				std::string town_name{ getDataUserElem() };
				if (town_name == "-1") return;
				int index_town{ del_republic->findTownInRepublic(town_name) };
				if (index_town == -1)
					std::cout << "Заданный город не принадлежит данной республике в данной стране. Повторите ввод: ";
				else
				{
					del_republic->delTown(index_town);
					break;
				}
			}
		}
		else
			std::cout << "Данная республика пустая. Удаление города невозможно." << std::endl;
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
		std::cout << "Не удалось выделить память из кучи. Кучи переполнена!" << std::endl;
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
		std::cout << "Не удалось выделить память из кучи. Кучи переполнена!" << std::endl;
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
						std::cout << "ОШИБКА: Файл содержит республику, которая уже есть в структуре (" << elem_str << ").Такого быть не может." << std::endl;
						return false;
					}
				addObjectToCheckingMass(mass_of_republics, count_of_republics, elem_str);
				continue;
			}
			else
			{
				std::cout << "ОШИБКА: Неправильное название республики " << elem_str << "." << std::endl;
				return false;
			}
		}
		count_of_elements++;
		if (count_of_elements / 2 + count_of_elements % 2 > size)
		{
			std::cout << "ОШИБКА: Указано слишком большое количество городов в республике " << mass_of_republics[count_of_republics - 1] << "." << std::endl;
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
						std::cout << "ОШИБКА: Республика не может содержать городов с одинаковыми названиями (" << elem_str << ")." << std::endl;
						delete[] mass_of_towns;
						return false;
					}
				addObjectToCheckingMass(mass_of_towns, count_of_towns, elem_str);
			}
			else
			{
				std::cout << "ОШИБКА: Неправильное название города " << elem_str << "." << std::endl;
				delete[] mass_of_towns;
				return false;
			}
		}
		else
		{
			if (!checkStrIsNumeric(elem_str))
			{
				std::cout << "ОШИБКА: Нельзя распознать количество населения " << elem_str << "." << std::endl;
				delete[] mass_of_towns;
				return false;
			}
		}
	}
	if (count_of_elements % 2 != 0)
	{
		std::cout << "ОШИБКА: Последний город республики " << mass_of_republics[count_of_republics - 1] << " не имеет значения населения." << std::endl;
		delete[] mass_of_towns;
		return false;
	}
	delete[] mass_of_towns;
	return true;
}
void DataFromFile(Country*& ptr_struct, std::stringstream& data_field)
{
	std::string elem_str{}; //Хранит подстроку текущей строки с данными.

	bool is_republic{ false }; //Для контролирования, когда считывается республика.
	int town_or_population{}; //Подсчитывает кол-во раз считывания города или населения. Помогает учитывать необходимые параметры.

	std::string republic_name{}; //Запоминает имя текущей республики.

	std::string town_name{}; //Запоминаем имя текущего города.
	int town_population{}; //Запоминает текущее кол-во населения.
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
	std::cout << "Введите название файла, из которого нужно загрузить данные для структуры: ";
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
		std::cout << "Не удалось открыть файл!" << std::endl;
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
							std::cout << "ОШИБКА: Первая строка файла содержит ошибочное написание страны " << country_name << "." << std::endl;
							return;
						}
					}
					else
					{
						std::cout << "ОШИБКА: Первая строка файла должна содержать только название страны." << std::endl;
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
			std::cout << "Ваш файл пустой." << std::endl;
		else
			std::cout << "Данные из файла " << name_loading_file << " были считаны и добавлены в структуру." << std::endl;
	}
	delete[] mass_of_republics;
}
bool NameFileIsCorrect(std::string const& name_saving_file)
{
	for (int i{}; i < name_saving_file.length();i++)
	{
		if (name_saving_file[i] >= 'а' && name_saving_file[i] <= 'я' || name_saving_file[i] >= 'А' && name_saving_file[i] <= 'Я' ||
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
			std::cout << "Имя файла не может быть пустым. Повторите ввод: ";
		else if (NameFileIsCorrect(name_saving_file))
			return name_saving_file;
		else
			std::cout << "Имя файла содержит недопустимые знаки. Повторите ввод: ";
	}
}
void LoadInFile(Country*& ptr_struct)
{
	if (!ptr_struct->countryIsEmpty())
	{
		std::cout << "Введите название файла, в который сохранится структура: ";
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
		std::cout << "Данные структуры были сохранены в файле " << name_saving_file << "!" << std::endl;
	}
	else
		std::cout << "Ваша структура пустая." << std::endl;
}
