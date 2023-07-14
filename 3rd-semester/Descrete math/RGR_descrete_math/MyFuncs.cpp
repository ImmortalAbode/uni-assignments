#include <iostream>
#include <string>

#include "MyFuncs.h"

//Проверяет вводимую строку на возможность преобразования в число.
bool checkStrIsNumeric(std::string const& tempStr)
{
	for (int i{}; i < tempStr.length(); i++)
	{
		if ((tempStr[i] < '0') || (tempStr[i] > '9'))
			return false;
	}
	return !tempStr.empty();
}
//Преобразует строку в число.
int convertStrToInt(std::string convertStr)
{
	double number{};
	for (int i{}; i < convertStr.length(); i++)
		number += (convertStr[i] - '0') * pow(10, convertStr.length() - 1 - i);
	return static_cast<int>(number);
}
//Получение количества вершин и проверка на корректный пользовательский ввод.
int getNumberVertexes()
{
	while (true)
	{
		std::string tempStrVerts{};
		std::getline(std::cin, tempStrVerts);
		if (!checkStrIsNumeric(tempStrVerts))
		{
			std::cin.clear();
			std::cout << "Ошибка ввода. Вы должны ввести натуральное число. Повторите ввод:\n";
		}
		else
		{
			return convertStrToInt(tempStrVerts);
		}
	}
}
//Получение количества рёбер и проверка на корректный пользовательский ввод.
int getNumberEdges(const int& p)
{
	while (true)
	{
		std::string tempStrEdges{};
		std::getline(std::cin, tempStrEdges);
		if (!checkStrIsNumeric(tempStrEdges))
		{
			std::cin.clear();
			std::cout << "Ошибка ввода. Вы должны ввести целое неотрицательное число. Повторите ввод:\n";
		}
		else
		{
			if (convertStrToInt(tempStrEdges) <= p * (p - 1) / 2) //Так как в простом графе максимум столько рёбер
				return convertStrToInt(tempStrEdges);
			else
				std::cout << "Количество рёбер слишком большое. Вы можете ввести число рёбер от 0 до " << p * (p - 1) / 2 << ". Повторите ввод:\n";
		}
	}
}
//Получение номера вершины и проверка на корректный пользовательский ввод.
int getVertex(int number_vertexes)
{
	while (true)
	{
		std::string tempStrVert{};
		std::getline(std::cin, tempStrVert);
		if (!checkStrIsNumeric(tempStrVert) || convertStrToInt(tempStrVert) >= number_vertexes)
		{
			std::cin.clear();
			std::cout << "Ошибка ввода. Вы должны ввести целое неотрицательное число от 0 до " << number_vertexes - 1 << ". Повторите ввод последней введённой вершины:\n";
		}
		else
		{
			return convertStrToInt(tempStrVert);
		}
	}
}
//Получение матрицы смежности по вводимым рёбрам и вывод её на консоль и проверка на корректный пользовательский ввод.
void getAdjacencyMatrix(int**& adjacency_matrix, int& p, int& q)
{
	std::cout << "\nЗадайте рёбра графа." << std::endl;
	int count{};
	while (count != q)
	{
		while (true)
		{
			std::cout << "Введите первую вершину ребра: ";
			int first_adj_vert{ getVertex(p) };
			std::cout << "Введите вторую вершину ребра: ";
			int second_adj_vert{ getVertex(p) };
			if (first_adj_vert != second_adj_vert) //Проверяем, что пользователь вводит не петлю.
			{
				for (int rows{}; rows < p; rows++)
				{
					for (int columns{}; columns < p; columns++)
					{
						if ((rows == first_adj_vert) && (columns == second_adj_vert))
						{
							if (adjacency_matrix[rows][columns] == 0)
							{
								adjacency_matrix[rows][columns] = 1; //Ставим в матрицу смежности 1 на пересечении соответсвующих вершин. А так как граф неориентированный, 
								adjacency_matrix[columns][rows] = 1; //то и симметрично относительно главной диагонали матрицы тоже ставим 1.
								std::cout << count + 1 << "-е ребро было введено между вершинами " << rows << " и " << columns << "." << std::endl;
								count++;
							}
							else
							{
								std::cout << "Ошибка ввода ребра между указанными вершинами. Оно уже было введено. Повторите ввод смежных вершин заново." << std::endl;
							}
							break;
						}
					}
				}
				break;
			}
			else
			{
				std::cout << "Вы не можете ввести петлю по условию задачи. Повторите ввод смежных вершин." << std::endl;
			}
		}
	}
	std::cout << "\t\tМатрица смежности графа: " << std::endl << std::endl; //Осуществляем вывод матрицы смежности на консоль пользователю.
	for (int i{}; i < p; i++)
		std::cout << "\t" << i;
	std::cout << std::endl << std::endl;
	for (int i{}; i < p; i++)
	{
		std::cout << i << "\t";
		for (int j{}; j < p; j++)
		{
			std::cout << adjacency_matrix[i][j] << "\t";
		}
		std::cout << std::endl << std::endl;
	}
}
//Получение интересущей длины между некоторой парой вершин и проверка на корректный пользовательский ввод.
int getInterestingLength()
{
	while (true)
	{
		std::string tempStrDistance{};
		std::getline(std::cin, tempStrDistance);
		if (!checkStrIsNumeric(tempStrDistance) || convertStrToInt(tempStrDistance) < 0)
		{
			std::cin.clear();
			std::cout << "Ошибка ввода. Вы должны ввести целое неотрицательное число. Повторите ввод:\n";
		}
		else
		{
			return convertStrToInt(tempStrDistance);
		}
	}
}

/* 1-ый этап решения задачи. breadth - first search - поиск в ширину. Идея:
 *расстановка меток от начала (0) и "слоями" (с возрастанием метки).
 *Метки вершин - это расстояния от начала, причём они постоянные -> метки не меняются.
 *Расстановка идёт до тех пор, пока конец не получит метку (либо расставим все возможные метки, а конец её так и не получил -> пути нет.
 *
 *При выполнение данной функции нужно учитывать следующие моменты:
 *не должно происходить переприсваивание метки на какую-либо другую, если она уже была поставлена - это и определяет массив layers;
 *проверка смежности вершин определяется по матрице смежности - есть между ними общее ребро, или нет;
 *поиск смежных вершин должен осуществляться от всех уже посещённых - для этого и нужен массив visited.
 */
bool bfs(int** graph, int p, int to_vertex, int* visited, int* layers, int* distances, int count_layers, int length, int check_count_layers)
{
	for (int i{}; i < p; i++) //Если расстояние до вершины равно имеющейся метке, то отмечаем её как посещённую, то есть мы в ней уже побывали.
	{
		if (distances[i] == length)
		{
			visited[i] = 1;
		}
	}

	if (distances[to_vertex] >= 0 || check_count_layers == -1)//Алгоритм продолжается до тех пор, пока конечная вершина не получит метку, или все возможные метки не будут расставлены.
	{
		if (distances[to_vertex] >= 0) //Если конечная вершина маршрута получила метку - путь есть, иначе нету.
		{
			return true;
		}
		else
			return false;
	}

	length += 1; //Увеличиваем длину пути, то есть метку, так как прежнее расстояние уже было рассмотрено.

	for (int i{}; i < p;i++) //Смотрим смежные вершины от всех уже посещенных вершин, то есть вершин с меткой, причём равной предыдущей метке.
	{
		if (visited[i] && distances[i] == length - 1)
		{
			for (int j{}; j < p; j++) //Осуществляем поиск смежных вершин, причём:
			{
				bool flag{ false };
				if (graph[i][j] == 0 || visited[j] == 1) //Игнорируем, если вершина уже посещена, то есть мы в ней уже побывали, или не смежна с текущей.
				{
					continue;
				}
				for (int k{}; k < count_layers; k++) //Игнорируем, если вершина уже с меткой.
				{
					if (layers[k] == j)
					{
						flag = true;
					}
				}
				if (flag) { continue; }
				distances[j] = length; //Если все проверки вершина прошла, то записываем соответствующее расстояние до вершины в массив,
				layers[count_layers] = j; //заносим её в массив вершин, уже имеющих метку,
				count_layers += 1; //увеличиваем количество вершин в массиве layers.
			}
		}
	}

	//Если количество вершин с меткой изменилось, то приравниваем переменную check_count_layers к переменной count_layers. Иначе устанавливаем значение переменной 
	//check_count_layers на такое, что позволит нам в программе явно увидеть, что новых меток поставлено не было.
	if (check_count_layers != count_layers)
	{
		check_count_layers = count_layers;
	}
	else
	{
		check_count_layers = -1;
	}

	return bfs(graph, p, to_vertex, visited, layers, distances, count_layers, length, check_count_layers); //Рекурсивно повторяем алгоритм, пока не выполнится условие выхода.
}
// 2-ой этап решения задачи. Построение пути (последовательности вершин и дуг) от конца.
void print_path(int** graph, int p, int from_vertex, int& current_vertex, int* path, int* distances, int* visited, int count_path, int& answer_first_question)
{
	//Если текущая вершина будет совпадать с конечной вершиной маршрута, то выводим имеющийся у нас путь на консоль пользователю, а также производим подсчёт длины пути.
	if (current_vertex == from_vertex)
	{
		answer_first_question = 0;
		for (int i{ count_path - 1 }; i >= 1; i--)
		{
			answer_first_question += 1;
			std::cout << path[i] << " -> ";
		}
		std::cout << path[0] << std::endl;
		return;
	}
	visited[current_vertex] = 1;//Отмечаем текущую вершину, как посещённую.

	//Производим поиск смежной вершины с нужной нам меткой, которая ещё не была посещена. Если нашли такую, то:
	for (int i{}; i < p; i++)
	{
		if (graph[current_vertex][i] == 1 && visited[i] == 0 && distances[current_vertex] == distances[i] + 1)
		{
			path[count_path] = i;//заносим её в массив имеющегося пути;
			count_path += 1;
			print_path(graph, p, from_vertex, i, path, distances, visited, count_path, answer_first_question); //рекурсивно повторяем алгоритм от найденной вершины.
			count_path -= 1; //Как только рекурсия закончится, то ищем следующую подходящую нам смежную вершину с меткой.
		}
	}
	visited[current_vertex] = 0; //Если иных подходящих смежных вершин найдено не было, то отмечаем текщую вершину как непосещённую, чтобы в неё было можно прийти иным путём.
}

/* 3-ий этап решения задачи.
 *Функция возводит в степень матрицу смежности графа по правилам умножения матриц, что позволяет ответить на второй вопрос задачи.
 *Степень матрицы - длина пути.
 *Пересечение соответствующей строки и столбца (вершины начала и конца маршрута соответственно) - количество маршрутов соответствующей длины.
 */
void multi_AdjacencyMatrix(int** graph, int** matrix_multi, int** answer_matrix, int p)
{
	for (int i{}; i < p;i++)
	{
		for (int j{}; j < p;j++)
		{
			int c{};
			for (int k{}; k < p; k++)
			{
				c += graph[i][k] * answer_matrix[k][j];
			}
			matrix_multi[i][j] = c;
		}
	}
	for (int i{}; i < p; i++)
	{
		for (int j{}; j < p; j++)
		{
			answer_matrix[i][j] = matrix_multi[i][j];
		}
	}
}