#include <iostream>
#include <string>
#include <cstdlib> //rand() и srand()
#include <ctime>   //time()
#include <iomanip>
#include "myfuncs.h"
#include "constants.h"

/*ПОЛЬЗОВАТЕЛЬСКИЕ ФУНКЦИИ*/
//Пользовательское меню.
void UserMenu()
{
	std::cout << "Список команд для работы с системой:" << std::endl <<
		"1 - Прочитать файл" << std::endl <<
		"2 - Записать в файл" << std::endl <<
		"3 - Изменить уровень доступа" << std::endl <<
		"4 - Показать модель БЛМ" << std::endl <<
		"q - Выход из системы" << std::endl;
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
		if (choice == "1" || choice == "2" || choice == "3" || choice == "4" || choice == "q")
		{
			return choice[0];
		}
		else
		{
			std::cout << std::endl << "Ошибка ввода, Вам нужно ввести номер вашего выбора в соответствии с вышеперечисленными пунктами. Повторите ввод:" << std::endl;
		}
	}
}

/*ДОПОЛНИТЕЛЬНЫЕ ФУНКЦИИ*/
//Функция для отрисовки горизонтальной линии таблицы.
void HorizontalLineForModel(const int& col_width) {
	std::cout << "+" << std::string(col_width * 2 + 3 - 2, '-') << "+" << std::endl;
}
//Функция для центрирования текста.
std::string CenterText(const std::string& text, const int& width) {
	int padding = width - static_cast<int>(text.size()); // Свободное пространство.
	int left_padding = padding / 2;  // Левая часть.
	int right_padding = padding - left_padding; // Правая часть.
	return std::string(left_padding, ' ') + text + std::string(right_padding, ' ');
}
//Функция отрисовки разделительной черты.
void DrawLine()
{
	std::cout << std::string(200, '-') << std::endl;
}

//Функция копии начальных уровней доступов всубъектов.
void CopySubjectLevelAccess(int(&copy_subjects_level_access)[NUM_SUBJECTS], const int(&subject_level_access)[NUM_SUBJECTS])
{
	for (size_t i = 0; i < NUM_SUBJECTS; ++i)
	{
		copy_subjects_level_access[i] = subject_level_access[i];
	}
}
//Функция для преобразования уровня доступа/грифа секретности в строку.
std::string AccessLevelToString(const int& access) 
{
	std::string result = "";

	switch (access) 
	{
	case 0:
		result += "NONCONFIDENTIAL";
		break;
	case 1:
		result += "CONFIDENTIAL";
		break;
	case 2:
		result += "SECRET";
		break;
	case 3:
		result += "TOP SECRET";
		break;
	default:;
	}

	return result;
}
//Функция для преобразования уровня доступа/грифа секретности в значение.
int AccessLevelToValue(const std::string& access)
{
	if (access == "NONCONFIDENTIAL") return 0;
	else if (access == "CONFIDENTIAL") return 1;
	else if (access == "SECRET") return 2;
	else if (access == "TOP SECRET") return 3;
	else return -1;
}
//Поиск субъекта по идентификатору.
int FindSubject(const std::string& subject_name) 
{
	int subject_index{ -1 };
	for (size_t i = 0; i < NUM_SUBJECTS; ++i) 
	{
		if (subjects[i] == subject_name) 
		{
			subject_index = static_cast<int>(i);
			break;
		}
	}
	return subject_index;
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

/*ОСНОВНЫЕ ФУНКЦИИ*/
//Отображение модели БЛМ.
void DisplayModelBLM(const int (&subjects_level_access)[NUM_SUBJECTS], const int (&objects_level_access)[NUM_OBJECTS])
{
	const int col_width{ 20 }; //Ширина столбца.

	//Заголовок.
	std::cout << std::endl;
	HorizontalLineForModel(col_width);
	std::cout << "|" << CenterText("Модель БЛМ", col_width * 2 + 1) << "|" << std::endl;
	HorizontalLineForModel(col_width);

	//Шапка для субъектов.
	std::cout << "|" << std::right << std::setw(col_width) << "Идентификатор" << "|" << std::right << std::setw(col_width) << "Уровень доступа" << "|" << std::endl;
	HorizontalLineForModel(col_width);
	//Строки для субъектов.
	for (size_t i = 0; i < NUM_SUBJECTS; ++i)
	{
		std::cout << "|" << std::right << std::setw(col_width) << subjects[i] << "|" << std::right << std::setw(col_width) << AccessLevelToString(subjects_level_access[i]) << "|" << std::endl;
	}
	HorizontalLineForModel(col_width);

	//Шапка для объектов.
	std::cout << "|" << std::right << std::setw(col_width) << "Название" << "|" << std::right << std::setw(col_width) << "Гриф секретности" << "|" << std::endl;
	HorizontalLineForModel(col_width);
	//Строки для объектов.
	for (size_t i = 0; i < NUM_OBJECTS; ++i) 
	{
		std::cout << "|" << std::right << std::setw(col_width) << objects[i] << "|" << std::right << std::setw(col_width) << AccessLevelToString(objects_level_access[i]) << "|" << std::endl;
	}
	HorizontalLineForModel(col_width);
	std::cout << std::endl;
}
//Функция для генерации модели БЛМ.
void GenerateModelBLM(int (&subjects_level_access)[NUM_SUBJECTS], int(&objects_level_access)[NUM_OBJECTS])
{
	std::srand(static_cast<unsigned int>(std::time(nullptr))); //ГПСЧ.
	//Уровни доступа субъектов.
	for (size_t i = 0; i < NUM_SUBJECTS; ++i) 
	{
		subjects_level_access[i] = (i == 0) ? 3 : rand() % 4; //Администратор имеет уровень доступа TOP SECRET.
	}
	//Грифы секретности объектов.
	for (size_t i = 0; i < NUM_OBJECTS; ++i) 
	{
		objects_level_access[i] = rand() % 4;
	}
}

//Запрос идентификатора пользователя.
int Authenticate() 
{
	std::string subject_name{};
	std::cout << "Пожалуйста, введите свой логин для входа! (quit - выход)" << std::endl;
	while (true) 
	{
		std::getline(std::cin, subject_name);
		if (subject_name == "quit") return -1;
		int subject_index = FindSubject(subject_name);
		if (subject_index != -1)
		{
			DrawLine();
			std::cout << std::endl << "Здравствуйте, " << subjects[subject_index] << "!\nДобро пожаловать в систему!" << std::endl << std::endl;
			return subject_index;
		}
		std::cout << "Ошибка аутентификации. Попробуйте снова или выйдите из программы:" << std::endl;
	}
}
//Проверка уровня доступа к грифу секретности.
bool CheckNRU(const int& subject_level_access, const int& object_level_access) 
{
	return object_level_access <= subject_level_access ? true : false;
}
bool CheckNWD(const int& subject_level_access, const int& object_level_access) 
{
	return object_level_access >= subject_level_access ? true : false;
}
//Чтение файла пользователем.
void ReadTheObjectBySubject(const int& subject_level_access, const int (&objects_level_access)[NUM_OBJECTS]) 
{
	while (true) 
	{
		//Запрос названия объекта.
		std::cout << "Какой файл Вы хотите прочитать? (quit - выход)" << std::endl;
		std::cout << "Файл: ";
		std::string object_name{};
		std::getline(std::cin, object_name);
		if (object_name == "quit") return;
		int object_index = FindObject(object_name);
		if (object_index == -1) 
		{
			std::cout << "Данный файл не был обнаружен в системе. Попробуйте снова." << std::endl << std::endl;
			continue;
		}

		//Проверка выполнения операции чтения.
		if (CheckNRU(subject_level_access, objects_level_access[object_index])) 
			std::cout << "Операция чтения выполнена успешно!" << std::endl;
		else 
			std::cout << "Операция не выполнена! Ваш уровень доступа ниже грифа секретности файла." << std::endl;
		break;
	}
	return;
}
//Запись в файл пользователем.
void WriteToObjectBySubject(const int& subject_level_access, const int (&objects_level_access)[NUM_OBJECTS]) 
{
	while (true) 
	{
		//Запрос названия объекта.
		std::cout << "В какой файл Вы хотите записать? (quit - выход)" << std::endl;
		std::cout << "Файл: ";
		std::string object_name{};
		std::getline(std::cin, object_name);
		if (object_name == "quit") return;
		int object_index = FindObject(object_name);
		if (object_index == -1) 
		{
			std::cout << "Данный файл не был обнаружен в системе. Попробуйте снова." << std::endl << std::endl;
			continue;
		}

		//Проверка выполнения операции записи.
		if (CheckNWD(subject_level_access, objects_level_access[object_index])) 
			std::cout << "Операция записи выполнена успешно!" << std::endl;
		else 
			std::cout << "Операция не выполнена! Ваш уровень доступа выше грифа секретности файла." << std::endl;
		break;
	}
}
//Изменение уровня доступа пользователя.
void ChangeLevelAccessBySubject(const int (&copy_subjects_level_access)[NUM_SUBJECTS], int (&subjects_level_access)[NUM_SUBJECTS], const int& subject_index) 
{
	while (true) 
	{
		//Запрос требуемого уровня доступа (понижение или тот же).
		std::cout << "Какой уровень доступа Вы хотите получить? ('NONCONFIDENTIAL', 'CONFIDENTIAL', 'SECRET', 'TOP SECRET' или quit - выход)" << std::endl;
		std::cout << "Уровень доступа: ";
		std::string subject_target_level_access{};
		std::getline(std::cin, subject_target_level_access);
		if (subject_target_level_access == "quit") return;

		//Проверка возможности получения заданного уровня доступа.
		int target_level_access{ AccessLevelToValue(subject_target_level_access) };
		if (target_level_access == -1) 
		{
			std::cout << "Такого уровня доступа не существует! Повторите ввод." << std::endl << std::endl;
			continue;
		}

		//Проверка: Новый уровень доступа не может превышать исходный.
		if (target_level_access > copy_subjects_level_access[subject_index]) 
		{
			std::cout << "Нельзя установить уровень доступа выше исходного согласно правилу слабого спокойствия! Текущий уровень доступа: " <<
				AccessLevelToString(subjects_level_access[subject_index]) << ". Повторите ввод." << std::endl << std::endl;
			continue;
		}

		//Проверка: Изменение допустимо, обновление уровня доступа.
		subjects_level_access[subject_index] = target_level_access;
		std::cout << "Ваш уровень доступа успешно изменен на " << AccessLevelToString(target_level_access) << std::endl;
		break;
	}
	return;
}
