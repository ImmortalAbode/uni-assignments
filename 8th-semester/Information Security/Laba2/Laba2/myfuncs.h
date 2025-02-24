#ifndef MYFUNCS_H_
#define MYFUNCS_H_

#include <string>
#include "constants.h"

/*ВЫВОД ПЕРЕЧНЯ ДОСТУПНЫХ ФУНКЦИЙ И ВЫБОР*/
//Пользовательское меню.
void UserMenu();
char GetMenuCase();
void UserSubMenu(const std::string& object_name);
char GetSubMenuCase(const std::string& object_name);


/*ДОПОЛНИТЕЛЬНЫЕ ФУНКЦИИ ТАБЛИЦЫ*/
void DrawHorizontalTableLine(const int& col_width, const int& objects);
std::string CenterText(const std::string& text, const int& width);
std::string AccessLevelToChar(const int& access);
void DrawLine();

/*ДОПОЛНИТЕЛЬНЫЕ ФУНКЦИИ*/
int FindUser(const std::string& user_name);
int FindObject(const std::string& object_name);
bool CheckPermission(int(&access_matrix)[NUM_USERS][NUM_OBJECTS], const int& user_index, const int& object_index, const int& bit);
void ModifyAccessMatrix(const int& target_object_index, int(&access_matrix)[NUM_USERS][NUM_OBJECTS], const int& user_index);

/*ОСНОВНЫЕ ФУНКЦИИ*/
void GenerateAccessMatrix(int(&access_matrix)[NUM_USERS][NUM_OBJECTS]);
void DisplayAccessTable(const int(&access_matrix)[NUM_USERS][NUM_OBJECTS]);
int AuthenticateUser();
void DisplayUserPermissions(const int& user_index, const int(&access_matrix)[NUM_USERS][NUM_OBJECTS]);
void ObjectChoice(const int& user_index, int(&access_matrix)[NUM_USERS][NUM_OBJECTS]);
bool ExecuteCommand(const int& user_index, const int& object_index, int(&access_matrix)[NUM_USERS][NUM_OBJECTS]);

#endif /*MYFUNCS_H_*/