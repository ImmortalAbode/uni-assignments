#include <iostream>
#include <string>

#include "myfuncs.h"
#include "MyList.h"

//������� ��� ������ �������� �� �������.
void MenuOfProgram()
{
	std::cout << "��� �� ������ ������� �� �������?" << std::endl;
	std::cout << "1 - ������ �� ������ � ������� �� ����� �������������� ������ ���������.\n"
		<< "2 - ����� �������� � �������� �������������� ������.\n"
		<< "3 - ���������� ������ ��������.\n"
		<< "4 - �������� ��������� ��������.\n"
		<< "5 - ����� �� ���������.";
	std::cout << std::endl;
}
char getChoice()
{
	while (true)
	{
		std::string choice{};
		std::cout << "��� �����: ";
		std::getline(std::cin, choice);
		if (choice == "1" || choice == "2" || choice == "3" || choice == "4" || choice == "5")
		{
			return choice[0];
		}
		else
			std::cout << "�� ������ ������ ����� ����� �� 1 �� 5. ��������� ����. " << std::endl;
	}
}

//��������������� ����������� �������.
bool isEmpty(List list)
{
	return list.count == 0 ? true : false;
}
bool isFull(List list)
{
	return list.count == size ? true : false;
}

//������� ��������� � �������� ����������������� �����.
bool checkStrIsShort(std::string userStr)
{
	for (int i{}; i < userStr.length();i++)
	{
		if (userStr.length() > 15)
			return false;
		if (userStr[i] == ' ' || userStr[i] < 'A' || (userStr[i] > 'Z' && userStr[i] < 'a') || userStr[i] > 'z')
			return false;
	}
	return true;
}
std::string getUserInput()
{
	std::cout << "������ �������� ������ ������� �� 'a' �� 'z' � �� 'A' �� 'Z'." << std::endl;
	std::cout << "������� �������������� ����� �������� ��� '-1', ����� ��������� � ����: ";
	while (true)
	{
		std::string userStr{};
		std::getline(std::cin, userStr);
		if (userStr.length() == 0)
			std::cout << "������ �����. ������� �������� ������ ��� '-1': ";
		else if (userStr == "-1" || checkStrIsShort(userStr))
			return userStr;
		else
			std::cout << "������ �����. ������� �������� ������ ��� '-1': ";
	}
}

//������� ��� ������ �� �������.
void printDataList(List list)
{
	if (!isEmpty(list))
	{
		std::cout << "��� ������: " << std::endl;
		for (int i{}; i < list.count; i++)
		{
			if (list.count % 20 == 0)
				std::cout << "\n";
			std::cout << list.list[i] << " ";
		}
		std::cout << std::endl;
	}
	else
		std::cout << "��� ������ ����." << std::endl;
}
void searchDataList(List list)
{
	if (!isEmpty(list))
	{
		while (true)
		{
			std::string userStr{ getUserInput() };
			if (userStr != "-1")
			{
				int count{};
				for (int i{}; i < list.count; i++)
					if (list.list[i] == userStr)
					{
						count++;
						std::cout << i << "-��/-��/-�� ������� ������: " << list.list[i] << std::endl;
					}
				if (count != 0)
					std::cout << "����� ���� ������� " << count << " �������(-a/-��)." << std::endl;
				else
					std::cout << "� ������ ��� ��������� � ������ �������������� ������." << std::endl;
				break;
			}
			else
			{
				std::cout << "����������� � ����. " << std::endl;
				break;
			}
		}
	}
	else
		std::cout << "��� ������ ����, ������� �������� ��������." << std::endl;
}
void addNewElement(List& list)
{
	if (isFull(list))
	{
		std::cout << "��� ������ �����, ���������� ������ �������� ����������." << std::endl;
	}
	else if (isEmpty(list))
	{
		std::string userStr{ getUserInput() };
		if (userStr != "-1")
		{
			list.list[list.count] = userStr;
			list.count++;
			std::cout << "������� " << userStr << " ��� ������� �������� � ������." << std::endl;
		}
		else
			std::cout << "����������� � ����." << std::endl;
	}
	else
	{
		std::string userStr{ getUserInput() };
		if (userStr != "-1")
		{
			bool maxStr{ true };
			for (int i{}; i < list.count;i++)
			{
				if (list.list[i] < userStr)
				{
					for (int j{ list.count };j > i;j--)
						list.list[j] = list.list[j - 1];
					list.list[i] = userStr;
					list.count++;
					maxStr = false;
					break;
				}
			}
			if (maxStr)
			{
				list.list[list.count] = userStr;
				list.count++;
			}
			std::cout << "����� ������� " << userStr << " ��� ������� �������� � ������." << std::endl;
		}
		else
			std::cout << "����������� � ����." << std::endl;
	}
}
void removeElement(List& list)
{
	if (!isEmpty(list))
	{
		printDataList(list);
		while (true)
		{
			std::string userStr{ getUserInput() };
			if (userStr != "-1")
			{
				bool isData{ false };
				for (int i{}; i < list.count;i++)
				{
					if (list.list[i] == userStr)
					{
						isData = true;
						if (i == list.count - 1)
							list.count--;
						else
						{
							for (int j{ i };j < list.count;j++)
								list.list[j] = list.list[j + 1];
							list.count--;
						}
						std::cout << "������� " << userStr << " ��� ������� ������ �� ������." << std::endl;
						break;
					}
				}
				if (isData)
					break;
				std::cout << "���������� �������� ��� � ������. ��������� ����. " << std::endl;
			}
			else
			{
				std::cout << "����������� � ����. " << std::endl;
				break;
			}
		}
	}
	else
		std::cout << "��� ������ ����, ������� �������� ��������." << std::endl;
}