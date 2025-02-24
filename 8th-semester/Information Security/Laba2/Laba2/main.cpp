#include <iostream>
#include <string>
#include <cstdlib> //system()

#include "myfuncs.h"
#include "constants.h"

int main()
{
	//std::setlocale(LC_ALL, "RUS");
	std::system("chcp 1251 > nul");
	//std::system("Color F0");
	//Матрица доступа.
	int access_matrix[NUM_USERS][NUM_OBJECTS]{};
	//Заполнение матрицы доступа случайным образом с учетом наличия админа Admin на первой строке матрицы.
	GenerateAccessMatrix(access_matrix);
	//Вывод исходных данных.
	DisplayAccessTable(access_matrix);
	//Вход в программу.
	int user_index{ AuthenticateUser() };
	if (user_index != -1) 
	{
		//Вывод прав пользователя.
		DisplayUserPermissions(user_index, access_matrix);
		std::cout << std::endl;
		//Цикл работы программы.
		bool cycle{ true };
		while (cycle) 
		{
			if (user_index == -1) break;
			switch (GetMenuCase()) 
			{
			case '1':
				std::cout << std::endl;
				ObjectChoice(user_index, access_matrix);
				break;
			case '2':
				system("cls");
				//Оторбажение исходных данных.
				DisplayAccessTable(access_matrix);
				user_index = AuthenticateUser();
				if (user_index != -1) 
				{
					//Вывод прав пользователя.
					DisplayUserPermissions(user_index, access_matrix);
				}
				break;
			case 'q':
				cycle = false;
				break;
			default:;
			}
			std::cout << std::endl;
		}
	}

	std::system("chcp 866 > nul");
	return 0;
}