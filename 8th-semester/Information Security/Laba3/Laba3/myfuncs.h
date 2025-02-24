#ifndef MYFUNCS_H_
#define MYFUNCS_H_

#include <string>
#include "constants.h"

/*ПОЛЬЗОВАТЕЛЬСКИЙ ВЫБОР*/
void UserMenu();
char GetMenuCase();

/*ДОПОЛНИТЕЛЬНЫЕ ФУНКЦИИ*/
void HorizontalLineForModel(const int& col_width);
std::string CenterText(const std::string& text, const int& width);
void DrawLine();

void CopySubjectLevelAccess(int(&copy_subjects_level_access)[NUM_SUBJECTS], const int(&subject_level_access)[NUM_SUBJECTS]);
std::string AccessLevelToString(const int& access);
int AccessLevelToValue(const std::string& access);
int FindSubject(const std::string& subject_name);
int FindObject(const std::string& object_name);

/*ОСНОВНЫЕ ФУНКЦИИ*/
void GenerateModelBLM(int(&subjects_level_access)[NUM_SUBJECTS], int(&objects_level_access)[NUM_OBJECTS]);
void DisplayModelBLM(const int(&subjects_level_access)[NUM_SUBJECTS], const int(&objects_level_access)[NUM_OBJECTS]);
int Authenticate();
bool CheckNRU(const int& subject_level_access, const int& object_level_access);
bool CheckNWD(const int& subject_level_access, const int& object_level_access);
void ReadTheObjectBySubject(const int& subject_level_access, const int(&objects_level_access)[NUM_OBJECTS]);
void WriteToObjectBySubject(const int& subject_level_access, const int(&objects_level_access)[NUM_OBJECTS]);
void ChangeLevelAccessBySubject(const int(&copy_subjects_level_access)[NUM_SUBJECTS], int(&subjects_level_access)[NUM_SUBJECTS], const int& subject_index);

#endif /*MYFUNCS_H_*/
