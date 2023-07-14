#include <iostream>
#include <istream>
#include <fstream>
#include <limits>
#include <string>
#include "constants.h"
#include "myfuncs.h"

std::string selectFile(Blank blank, const std::string defaultPath)
{
	std::string s;
	std::cout << "���� �� ����� " << ((blank == Blank::INPUT) ? "�����" : "������") << "[" << defaultPath << "]: ";
	std::getline(std::cin, s);
	if (s.empty())
	{
		return defaultPath;
	}
	else
	{
		return s;
	}
}

bool getNext()
{
	std::cout << "����������?(0 - ���, 1 - ��): ";
	while (true)
	{
		char sm;
		std::cin >> sm;
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		if (sm == '0' || sm == '1')
		{
			return sm == '1' ? true : false;
		}
		else
		{
			std::cout << "������ �����. ������� 0 ��� 1:\n";
		}
	}
}

unsigned char get_0_1()
{
	while (true)
	{
		char sm;
		std::cin >> sm;
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		if (sm == '0' || sm == '1')
		{
			return sm;
		}
		else
		{
			std::cout << "������ �����. ������� 0 ��� 1:\n";
		}
	}
}

double getLength()
{
	while (true)
	{
		double a;
		std::cin >> a;
		if (std::cin.fail() || a != int(a) || a <= 0)
		{
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cout << "������ �����. ������� ����������� �����. \n";
		}
		else
		{
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			return a;
		}
	}
}

std::string CheckStrLength(double NM)
{
	while (true)
	{
		std::string StrForCheck;
		std::getline(std::cin, StrForCheck);
		if (StrForCheck.length() != NM)
		{
			std::cout << "����� ������������������ �� ������������� ���������� N (N=" << NM << " != " << StrForCheck.length() << ")."
				<< " ��������� ����: " << std::endl;
		}
		else
		{
			return StrForCheck;
		}
	}
}

bool initStr(Select select, std::istream& f, std::string& subsequence, double& NM)
{
	if (select == Select::CONSOLE)
	{
		std::cout << "������� ����� N (���-�� �������� � ������): ";
		NM = getLength();
		std::cout << "������� ������������������ �������� S1,S2,...,Sn: ";
		subsequence = CheckStrLength(NM);
	}
	else
	{
		f >> NM;
		if (f.fail() || NM != int(NM) || NM <= 0)
		{
			std::cout << "������ ����� �� ����� ����� ������������������ S1,S2,...,Sn. ";
			return false;
		}
		f >> subsequence;
		if (subsequence.length() != NM)
		{
			std::cout << "����� ������������������ �� ������������� ���������� N (N=" << NM << " != " << subsequence.length() << ").";
			return false;
		}
	}
	if (f.fail())
	{
		std::cout << "������ ����� ����� ������������������ �� " << ((Select::FILE == select) ? "�����" : "�������") << "." << std::endl;
		return false;
	}
	return true;
}

void result(std::ostream& f, double NM, std::string str)
{
	f << "�������� ������������������: " << std::endl;
	f << str << std::endl;
	unsigned count{};
	for (count = 0;count < 4;count++)
	{
		char* res = new char[str.length() * 4];
		unsigned i = 0, j = 0;
		if (count == 0)
		{
			for (i = 0, j = 0;i < str.length();i++)
			{
				if (str[i] == '!') res[j++] = '.';
				else res[j++] = str[i];
			}
			f << "�) ���� ��������������� ������ �������� S � ������� ���� ��������������� ������ �������:" << std::endl;
			res[j++] = '\0';
			f << res << std::endl;
			delete res;
		}
		else if (count == 1)
		{
			for (i = 0, j = 0;i < str.length();i++)
			{
				if (str[i] == '.')
				{
					int k{};
					for (k = 0; k < 3; k++)
					{
						res[j++] = '.';
					}
				}
				else res[j++] = str[i];
			}
			f << "�) ���� ��������������� ������ �������� S � ������� ������ ����� �����������:" << std::endl;
			res[j++] = '\0';
			f << res << std::endl;
			delete res;
		}
		else if (count == 2)
		{
			for (i = 0, j = 0; i < str.length(); i++)
			{
				res[j++] = str[i];
			}
			res[j++] = '\0';
			for (i = 0; res[i] != '\0'; i++)
			{
				if (res[i] == '.' && res[i + 1] == res[i])
				{
					while (res[i + 1] == '.')
					{
						int k = i;
						while (res[k] != '\0')
							res[k++] = res[k + 1];
					}
				}
			}
			f << "�) ���� ��������������� ������ �������� S � ������� ������ �� ����� ������� ����� ����� ����� ������:" << std::endl;
			f << res << std::endl;
			delete res;
		}
		else
		{
			for (i = 0, j = 0; i < str.length(); i++)
			{
				if (str[i] == '.' && str[i + 1] == str[i])
				{
					while (str[i + 1] == '.')
					{
						i += 1;
					}
					int l{};
					for (l = 0; l < 3; l++)
					{
						res[j++] = '.';
					}
				}
				else res[j++] = str[i];
			}
			f << "�) ���� ��������������� ������ �������� S � ������� ������ �� ����� ������� ����� ����� �����������:" << std::endl;
			res[j++] = '\0';
			f << res << std::endl;
			delete res;
		}
	}
}
