#include <iostream>
#include <string>
#include <cstdlib> //rand() и srand()
#include <ctime>   //time()
#include <iomanip>
#include "myfuncs.h"
#include "constants.h"

/*ВЫВОД ПЕРЕЧНЯ ДОСТУПНЫХ ФУНКЦИЙ И ВЫБОР*/
//Пользовательское меню.
void UserMenu()
{
	std::cout << "Жду Ваших указаний:" << std::endl <<
		"1 - Взаимодействие с файлом." << std::endl <<
		"2 - Выйти из системы." << std::endl <<
		"q - Выход из программы." << std::endl;
}
//Запрос дейтсвий у пользователя.
char GetMenuCase()
{
	UserMenu();
	while (true)
	{
		std::cout << "Ваш выбор: ";
		std::string choice{};
		std::getline(std::cin, choice);
		if (choice == "1" || choice == "2" || choice == "q")
		{
			return choice[0];
		}
		else
		{
			std::cout << std::endl << "Ошибка ввода, Вам нужно ввести номер вашего выбора в соответствии с вышеперечисленными пунктами. Повторите ввод:" << std::endl;
		}
	}
}
//Пользовательское подменю.
void UserSubMenu(const std::string& object_name) 
{
	std::cout << "Какое действие с файлом " << object_name << " Вы хотите совершить?" << std::endl <<
		"1 - Чтение файла." << std::endl <<
		"2 - Запись в файл." << std::endl <<
		"3 - Передача прав." << std::endl <<
		"q - Выход." << std::endl;
}
//Запрос действий в подменю.
char GetSubMenuCase(const std::string& object_name) 
{

	UserSubMenu(object_name);
	while (true)
	{
		std::cout << "Ваш выбор: ";
		std::string choice{};
		std::getline(std::cin, choice);
		if (choice == "1" || choice == "2" || choice == "3" || choice == "q")
		{
			return choice[0];
		}
		else
		{
			std::cout << std::endl << "Ошибка ввода, Вам нужно ввести номер вашего выбора в соответствии с вышеперечисленными пунктами. Повторите ввод:" << std::endl;
		}
	}
}


/*ДОПОЛНИТЕЛЬНЫЕ ФУНКЦИИ ТАБЛИЦЫ*/
//Функция для отрисовки горизонтальной линии таблицы.
void DrawHorizontalTableLine(const int& col_width, const int& objects) 
{
	std::cout << "\n" << std::string(col_width * (objects + 1) + objects + 2, '-') << "\n";
}
//Функция для центрирования текста.
std::string CenterText(const std::string& text, const int& width)
{
	int padding = width - static_cast<int>(text.size()); // Свободное пространство.
	int left_padding = padding / 2;  // Левая часть.
	int right_padding = padding - left_padding; // Правая часть.
	return std::string(left_padding, ' ') + text + std::string(right_padding, ' ');
}
//Функция для преобразования уровня доступа в строку прав.
std::string AccessLevelToChar(const int& access) 
{
	std::string result = "";

	//Проверка каждого бита и добавление соответствующего символа.
	result += (access & 4) ? "R" : "-"; // Чтение.
	result += (access & 2) ? "W" : "-"; // Запись.
	result += (access & 1) ? "G" : "-"; // Передача прав.

	return result;
}
//Функция отрисовки разделительной черты.
void DrawLine() 
{
	std::cout << std::string(200, '-') << std::endl;
}

/*ДОПОЛНИТЕЛЬНЫЕ ФУНКЦИИ*/
//Поиск субъекта по идентификатору.
int FindUser(const std::string& user_name) 
{
	int user_index{ -1 };
	for (size_t i = 0; i < NUM_USERS; ++i) 
	{
		if (users[i] == user_name) 
		{
			user_index = static_cast<int>(i);
			break;
		}
	}
	return user_index;
}
//Поиск объекта по названию.
int FindObject(const std::string& object_name)
{
	int object_index{ -1 };
	for (size_t i = 0; i < NUM_OBJECTS; ++i) 
	{
		if (objects[i] == object_name) 
		{
			object_index = static_cast<int>(i);
			break;
		}
	}
	return object_index;
}
//Проверка прав субъекта над объектом.
bool CheckPermission(int(&access_matrix)[NUM_USERS][NUM_OBJECTS], const int& user_index, const int& object_index, const int& bit)
{
	return (access_matrix[user_index][object_index] >> bit) % 2 == 1;
}
//Преобразование матрицы доступа при передаче прав.
void ModifyAccessMatrix(const int& target_object_index, int(&access_matrix)[NUM_USERS][NUM_OBJECTS], const int& user_index)
{
	while (true)
	{
		//Кому передается право.
		std::cout << std::endl;
		std::cout << "Кому Вы хотите передать доступ? Введите идентификатор: (quit - выход)" << std::endl;
		std::cout << "Имя пользователя: ";
		std::string target_user_name{};
		std::getline(std::cin, target_user_name);
		if (target_user_name == "quit") return;
		int target_user_index = FindUser(target_user_name);
		if (target_user_index == -1)
		{
			std::cout << "Указанный идентификатор не обнаружен в системе. Попробуйте заново." << std::endl;
			continue;
		}

		//Проверка, не передает ли пользователь права самому себе.
		if (target_user_index == user_index)
		{
			std::cout << "Передача прав самому себе запрещена! Можете попробовать передать права другому пользователю или завершить работу с файлом." << std::endl;
			continue;
		}

		//Какое право передается.
		std::cout << "Введите право: (read/write/grant)" << std::endl;
		std::cout << "Право: ";
		std::string right{};
		std::getline(std::cin, right);
		if (right == "read" || right == "write" || right == "grant")
		{
			int right_value = (right == "read") ? 4 : (right == "write") ? 2 : (right == "grant") ? 1 : 0;

			//Проверка, есть ли у субъекта вообще это право над объектом, чтобы его передать.
			if (!(access_matrix[user_index][target_object_index] & right_value))
			{
				std::cout << "Ошибка: Вы не обладаете правом '" << right << "', чтобы его передать!\n";
				continue;
			}

			//Проверка, есть ли у субъекта уже это право над объектом.
			if (access_matrix[target_user_index][target_object_index] & right_value)
			{
				std::cout << "Ошибка: Пользователь " << target_user_name << " уже обладает правом '" << right << "'!\n";
				continue;
			}

			access_matrix[target_user_index][target_object_index] |= right_value;
			std::cout << "Идет передача прав пользователю " << users[target_user_index] << "...\nПрава успешно переданы!" << std::endl;
			break;
		}
		else {
			std::cout << "Указанное право некорректно. Попробуйте заново." << std::endl;
		}
	}
}

/*ОСНОВНЫЕ ФУНКЦИИ*/
//Функция для генерации матрицы доступа
void GenerateAccessMatrix(int(&access_matrix)[NUM_USERS][NUM_OBJECTS])
{
	std::srand(static_cast<unsigned int>(std::time(nullptr))); //ГПСЧ.
	for (size_t i = 0; i < NUM_USERS; ++i)
	{
		for (size_t j = 0; j < NUM_OBJECTS; ++j)
		{
			access_matrix[i][j] = (i == 0) ? 7 : rand() % 8; // Администратор получает полный доступ.
		}
	}
}
//Вывод таблицы.
void DisplayAccessTable(const int(&access_matrix)[NUM_USERS][NUM_OBJECTS])
{
	const int col_width{ 20 }; // Ширина столбца.

	//Заголовок таблицы.
	DrawHorizontalTableLine(col_width, NUM_OBJECTS);
	std::cout << "|" << CenterText("МАТРИЦА ДОСТУПА СУБЪЕКТОВ К ОБЪЕКТАМ", col_width * (NUM_OBJECTS + 1) + NUM_OBJECTS) << "|";
	DrawHorizontalTableLine(col_width, NUM_OBJECTS);
	//Шапка таблицы.
	std::cout << "|" << CenterText("Субъект / Объект", col_width) << "|";
	for (size_t i{}; i < NUM_OBJECTS; ++i) 
	{
		std::cout << CenterText(objects[i], col_width) << "|";
	}
	DrawHorizontalTableLine(col_width, NUM_OBJECTS);
	//Вывод строк таблицы.
	for (size_t i = 0; i < NUM_USERS; ++i) 
	{
		std::cout << "|" << CenterText(users[i], col_width) << "|"; // Имя субъекта.
		for (size_t j = 0; j < NUM_OBJECTS; ++j) 
		{
			std::cout << CenterText(AccessLevelToChar(access_matrix[i][j]), col_width) << "|"; //Уровень доступа.
		}
		if (i != static_cast<size_t>(NUM_USERS) - 1) { std::cout << "\n"; }
	}
	DrawHorizontalTableLine(col_width, NUM_OBJECTS);
	std::cout << std::endl;
}
//Запрос идентификатора пользователя.
int AuthenticateUser() 
{
	std::string user_name{};
	std::cout << "Пожалуйста, введите свой логин для входа! (quit - выход)" << std::endl;
	while (true) {
		std::getline(std::cin, user_name);
		if (user_name == "quit") return -1;
		int user_index = FindUser(user_name);
		if (user_index != -1) 
		{
			DrawLine();
			std::cout << std::endl << "Здравствуйте, " << users[user_index] << "!\nДобро пожаловать в систему!" << std::endl << std::endl;
			return user_index;
		}
		std::cout << "Ошибка аутентификации. Попробуйте снова или выйдите из программы:" << std::endl;
	}
}
//Вывод прав субъекта над объектом.
void DisplayUserPermissions(const int& user_index, const int (&access_matrix)[NUM_USERS][NUM_OBJECTS]) 
{
	std::cout << "Перечень Ваших прав:" << std::endl;
	for (size_t i = 0; i < NUM_OBJECTS; ++i) 
	{
		std::cout << objects[i] << " -> " << permissions[i] << std::endl;
	}
}
//Выбор объекта.
void ObjectChoice(const int& user_index, int (&access_matrix)[NUM_USERS][NUM_OBJECTS])
{
	while (true) 
	{
		std::cout << "С каким файлом Вы хотите взаимодействовать? Введите название файла: (quit - выход)" << std::endl;
		std::string object_name{};
		std::getline(std::cin, object_name);
		if (object_name == "quit") return;
		int object_index = FindObject(object_name);
		if (object_index == -1) 
		{
			std::cout << "Данный файл не был обнаружен в системе. Попробуйте снова." << std::endl << std::endl;
			continue;
		}

		while (true) 
		{
			if (!ExecuteCommand(user_index, object_index, access_matrix))
			{
				std::cout << "Работа с файлом " << object_name << " закончена!" << std::endl << std::endl;
				break;
			}
		}
	}
}
//Взаимодействие с объектом.
bool ExecuteCommand(const int& user_index, const int& object_index, int(&access_matrix)[NUM_USERS][NUM_OBJECTS])
{
	std::cout << std::endl;
	bool access{};

	switch (GetSubMenuCase(objects[object_index])) 
	{
	case '1'://Чтение.
		access = CheckPermission(access_matrix, user_index, object_index, 2);
		if (access) 
		{
			std::cout << std::endl << "Чтение файла...\nФайл успешно прочитан!" << std::endl;
		}
		else
			std::cout << "Отказано в доступе! У Вас нет прав для совершения этого действия!" << std::endl << std::endl;
		break;
	case '2'://Запись.
		access = CheckPermission(access_matrix, user_index, object_index, 1);
		if (access) 
		{
			std::cout << std::endl << "Идет запись в файл...\nФайл успешно перезаписан!" << std::endl;
		}
		else
			std::cout << "Отказано в доступе! У Вас нет прав для совершения этого действия!" << std::endl << std::endl;
		break;
	case '3'://Передача прав.
		access = CheckPermission(access_matrix, user_index, object_index, 0);
		if (access) 
		{
			ModifyAccessMatrix(object_index, access_matrix, user_index);
		}
		else
			std::cout << "Отказано в доступе! У Вас нет прав для совершения этого действия!" << std::endl;
		break;
	case 'q'://Выход.
		return false;
	default:;
	}
	return true;
}
