#ifndef MYFUNCS_H_
#define MYFUNCS_H_

#include <string>

//Объявление функций программы. Их предназначение подробно описано в файле MyFuncs.cpp.
//Вспомогательные функции программы:
bool checkStrIsNumeric(std::string const& tempStr);
int convertStrToInt(std::string convertStr);
int getNumberVertexes(); 
int getNumberEdges(const int& p); 
int getVertex(int number_vertexes); 
void getAdjacencyMatrix(int**& adjacency_matrix, int& p, int& q); 
int getInterestingLength(); 


//Основные функции программы:
bool bfs(int** graph, int p, int to_vertex, int* visited, int* layers, int* distances, int count_layers, int length, int check_count_layers);
void print_path(int** graph, int p, int from_vertex, int& current_vertex, int* path, int* distances, int* visited, int count_path, int& answer_first_question);
void multi_AdjacencyMatrix(int** graph, int** matrix_multi, int** answer_matrix, int p);

#endif /*MYFUNCS_H_*/
