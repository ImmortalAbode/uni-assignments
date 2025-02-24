#ifndef CONSTANTS_H_
#define CONSTANTS_H_

#include <string>
#include <map>

//Массив субъектов длиной 5.
const int NUM_USERS{ 5 };
const std::string users[NUM_USERS] = { "Admin", "User_1", "User_2", "User_3", "User_4" };

//Массив объектов длиной 4.
const int NUM_OBJECTS{ 4 };
const std::string objects[NUM_OBJECTS] = { "File_1", "File_2", "File_3", "File_4" };

//Множества типов доступа и соответствующие им значения. Индекс - трехбитное числое (Read, Write, Grant), указывает множество. 
const std::string permissions[8] = { "Запрет", "Передача прав", "Запись", "Запись, Передача прав", "Чтение", "Чтение, Передача прав", "Чтение, Запись", "Полные права" };

#endif /*CONSTANTS_H_*/