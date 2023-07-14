#include <iostream>
#include <string>

#include "MyFuncs.h"

//Программа все входные данные получает через консоль, а также имеет проверку этих данных на корректный пользовательский ввод.

int main()
{
	setlocale(LC_ALL, "Rus");

	//Ввод входных данных. Что это за переменные говорят информационные сообщения пользователю.
	std::cout << "Задайте простой неориентированный граф (вершины на графе начинаются с v0).\n\n";
	std::cout << "Введите количество вершин в графе p = | V | : ";
	int p{ getNumberVertexes() };
	std::cout << "Введите количество рёбер в графе q=|X|: ";
	int q{ getNumberEdges(p) };
	std::cout << "Задайте вершины, между которыми нужно найти расстояние: " << std::endl;
	std::cout << "Первая вершина: ";
	int from_rhombus_vertex{ getVertex(p) };
	std::cout << "Вторая вершина: ";
	int to_rhombus_vertex{ getVertex(p) };
	std::cout << "Задайте вершины, между которыми нужно найти количество маршрутов интересующей длины: " << std::endl;
	std::cout << "Первая вершина: ";
	int from_circle_vertex{ getVertex(p) };
	std::cout << "Вторая вершина: ";
	int to_circle_vertex{ getVertex(p) };
	std::cout << "Введите интересующую длину между данными вершинами: ";
	int intresting_length{ getInterestingLength() };
	 
	/*Матрица matrix_multi служит временной матрицей для записи значений в результате возведения матрицы смежности в степень, 
	 *так как иначе бы искажался результат перемножения(если значения сразу присваивать одной из матриц).
	 */
	int** graph = new int* [p]; //Матрица смежности, строящаяся по графу.
	int** matrix_multi = new int* [p]; //Матрица, хранящая матрицу смежности, возведённую в степень.
	int** answer_matrix = new int* [p]; //Матрица, хранящая ответ на второй вопрос задачи.

	//Инициализация матриц: создание непосредственно матриц и присваивание всем их элементам нулевое значение.
	for (int i{}; i < p; i++)
	{
		graph[i] = new int[p];
		matrix_multi[i] = new int[p];
		answer_matrix[i] = new int[p];
	}
	for (int i{}; i < p;i++)
	{
		for (int j{}; j < p;j++)
		{
			graph[i][j] = 0;
			matrix_multi[i][j] = 0;
			answer_matrix[i][j] = 0;
		}
	}

	/*Получение матрицы смежности по вводимым рёбрам и вывод её на консоль.
	 *Так как граф простой и неориентированный, то матрица смежности симметричная, содержит нули на главной диагонали и бинарная, то есть её элементы =:
	 * 0 - если вершины не соединены ребром, 1 - если вершины соединены ребром.
	 */
	getAdjacencyMatrix(graph, p, q); //Заполнение матрицы смежности "1" по вводимым рёбрам.

	int* visited = new int[p]; //Создание массива, в котором будет вестись учёт уже посещённых вершин.
	int* path = new int[p]; //Создание массива, который будет хранить маршрут между вершинами.
	int count_path{}; //Переменная, хранящая число вершин в массиве path.
	int* layers = new int[p]; //Создание массива, в котором будет вестись учёт вершин, уже получивших метку.
	int count_layers{}; //Переменная, хранящая число элементов в массиве layers.
	int check_count_layers{}; //Переменная, которая будет проверять все ли возможные метки были проставлены.
	int* distances = new int[p]; //Создание массива, который будет хранить расстояния до каждой вершины, причём будем считать, что если его элемент равен -1, то вершина не получила метки.


	int answer_first_question{}; //Переменная, которая будет хранить ответ на первый вопрос задачи.
	int answer_second_question{};//Переменная, которая будет хранить ответ на второй вопрос задачи.

	
	//Приведение вспомогательных массивов к начальному состоянию:
	for (int i{}; i < p; i++)
	{
		visited[i] = 0; //Изначально никакие вершины не были посещены.
		distances[i] = -1; //Изначально расстояния до любой вершины неизвестны, равны -1, "слои" не проставлены, меток нет.
		path[i] = 0; //Так как существует путь или нет, мы не знает, то изначально массив пуст.
	}
	int length{}; //Переменная, которая будет определять расстояние на том или ином этапе алгоритма, то есть метку.
	layers[count_layers] = from_rhombus_vertex; //Изначально начальная вершина получила метку 0, то есть была обработа "слоем".
	count_layers += 1;
	distances[from_rhombus_vertex] = length; //Заносим расстояние до соответствующей вершины в массив, то есть начальная вершина получает метку 0.

	//Основная работа программы.
	// Для ответа на первый вопрос задачи.
	if (from_rhombus_vertex != to_rhombus_vertex) //Случай, когда вершины начала и конца маршрута не совпадают.
	{
		//Проверяем, есть ли вообще путь к конечной вершине маршрута.
		if (bfs(graph, p, to_rhombus_vertex, visited, layers, distances, count_layers, length, check_count_layers) == false) //Если нет, выводим соответствующую информацию пользователю.
		{
			std::cout << "Между вершинами " << from_rhombus_vertex << " и " << to_rhombus_vertex << " нельзя построить путь, так как данные вершины не связаны ребрами(-ом)!" << std::endl;
		}
		else
		{
			for (int i{}; i < p; i++) //Если есть, обнуляем массив посещённых вершин (так нужно для дальнейшей функции построения пути от конца). 
			{
				visited[i] = 0;
			}
			path[count_path] = to_rhombus_vertex; //Сразу добавляем конечную вершину маршрута.
			count_path += 1;
			std::cout << "Искомый(-ые) кратчайший(-ие) путь(-и) между вершинами " << from_rhombus_vertex << " и " << to_rhombus_vertex << ":" << std::endl;
			print_path(graph, p, from_rhombus_vertex, to_rhombus_vertex, path, distances, visited, count_path, answer_first_question); //Выполняем построение пути.
			std::cout << "Расстояние между вершинами " << from_rhombus_vertex << " и " << to_rhombus_vertex << " равно " << answer_first_question << "." << std::endl;
			std::cout << std::endl;
		}
	}
	else //Случай, когда вершины начала и конца маршрута совпадают.
	{
		std::cout << "Вершины начала пути (" << from_rhombus_vertex << ") и конца пути (" << to_rhombus_vertex << ") совпадают. Расстояние между ними равно 0." << std::endl;
	}
	

	//Для ответа на второй вопрос задачи.
	switch (intresting_length) //В зависимости от интересующей длины маршрута выполняем следующие действия.
	{
	case 0: //Если интересующая длина маршрута равна 0, то путь между ними построить нельзя в любом случае. Если вершины начала и конца маршрута совпадают, то сообщаем об этом пользователю.
	{
		if (from_circle_vertex == to_circle_vertex)
			std::cout << "Вершины начала маршрута " << from_circle_vertex << " и конца маршрута " << to_circle_vertex << " совпадают. " << std::endl;
		std::cout << "Между вершинами " << from_circle_vertex << " и " << to_circle_vertex << " нельзя построить маршрут интересующей длины (" << intresting_length << ")!" << std::endl;
		break;
	}
	case 1://Если интересующая длина маршрута равна 1, то построить единственный маршрут между ними мы либо можем, когда они соединены ребром, либо не можем.
	{
		if(graph[from_circle_vertex][to_circle_vertex] == 0)
			std::cout << "Между вершинами " << from_circle_vertex << " и " << to_circle_vertex << " нельзя построить маршрут интересующей длины ("
			<< intresting_length << ")!" << std::endl;
		else
			std::cout << "Количество маршрутов длины " << intresting_length << " между вершинами " << from_circle_vertex << " и " << to_circle_vertex 
			<< " равно 1." << std::endl;
		break;
	}
	default://Если интересующая длина маршрута > 1, то выполняем соответствующий алгоритм:
	{
		for (int i{}; i < p; i++) //Выполняем необходимое копирование матрицы смежности в матрицу answer_matrix, так как она хранит результаты перемножения матриц.
		{
			for (int j{}; j < p;j++)
			{
				answer_matrix[i][j] = graph[i][j];
			}
		}
		for (int i{}; i < intresting_length - 1; i++) //Выполняем возведение матрицы смежности в степень необходимое число раз.
		{
			multi_AdjacencyMatrix(graph, matrix_multi, answer_matrix, p);
		}
		//Смотрим на нужное нам значение в соответствующей строке и столбце матрицы answer_matrix, записываем его в переменную answer_second_question.
		answer_second_question = answer_matrix[from_circle_vertex][to_circle_vertex]; 
		//Делаем соответствующий вывод о полученных результатах.
		if (answer_second_question == 0)
			std::cout << "Между вершинами " << from_circle_vertex << " и " << to_circle_vertex << " нельзя построить маршрут интересующей длины (" 
			<< intresting_length << ")!" << std::endl;
		else
			std::cout << "Количество маршрутов длины " << intresting_length << " между вершинами " << from_circle_vertex << " и " << to_circle_vertex << " равно "
			<< answer_second_question << "." << std::endl;
		break;
	}
	}
	
	//Производим очистку памяти в кучи, которая была выделена под массивы, размеры которых определяются во время исполнения программы.
	for (int i{}; i < p; i++)
	{
		delete[] graph[i];
		delete[] matrix_multi[i];
		delete[] answer_matrix[i];
	}
	delete[] graph;
	delete[] matrix_multi;
	delete[] answer_matrix;

	delete[] visited;
	delete[] path;
	delete[] layers;
	delete[] distances;

	return 0;
}
