#include <iostream>
#include <string>
#include <cstdlib> //system()
#include "myfuncs.h"
#include "constants.h"

int main() {
	//setlocale(LC_ALL, "Rus");
	std::system("chcp 1251 > nul");
	//std::system("Color F0");
	//Модель БЛМ (Белла-ЛаПадулы).
	int subjects_level_access[NUM_SUBJECTS]{};	//Уровни доступа субъектов.
	int objects_level_access[NUM_OBJECTS]{};	//Грифы секретности объектов.
	//Заполнение модели БЛМ случайным образом с учетом наличия админа Admin первым элементом массива субъектов.
	GenerateModelBLM(subjects_level_access, objects_level_access);
	//Программная копия уровней доступа субъектов.
	int copy_subjects_level_access[NUM_SUBJECTS]{};
	CopySubjectLevelAccess(copy_subjects_level_access, subjects_level_access); 
	//Отображение модели БЛМ.
	DisplayModelBLM(subjects_level_access, objects_level_access);
	//Вход в программу.
	int subject_index{ Authenticate() };
	if (subject_index != -1) 
	{
		//Цикл работы с программой.
		bool cycle{ true };
		while (cycle) 
		{
			if (subject_index == -1) break;
			switch (GetMenuCase()) 
			{
			case '1'://Чтение.
				DrawLine();
				std::cout << std::endl;
				ReadTheObjectBySubject(subjects_level_access[subject_index], objects_level_access);
				break;
			case '2'://Запись.
				DrawLine();
				std::cout << std::endl;
				WriteToObjectBySubject(subjects_level_access[subject_index], objects_level_access);
				break;
			case '3'://Изменение.
				DrawLine();
				std::cout << std::endl;
				ChangeLevelAccessBySubject(copy_subjects_level_access, subjects_level_access, subject_index);
				break;
			case '4'://Показать модель БЛМ.
				DrawLine();
				std::cout << std::endl;
				DisplayModelBLM(subjects_level_access, objects_level_access);
				break;
			case 'q'://Выход.
				system("cls");
				DisplayModelBLM(subjects_level_access, objects_level_access);
				subject_index = Authenticate();
				if (subject_index == -1)
				{
					cycle = false;
				}
				break;
			default:;
			}
			DrawLine();
			std::cout << std::endl;
		}
	}
	std::system("chcp 866 > nul");
	return 0;
}
