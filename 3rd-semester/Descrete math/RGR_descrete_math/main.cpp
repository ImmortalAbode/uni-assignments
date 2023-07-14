#include <iostream>
#include <string>

#include "MyFuncs.h"

//��������� ��� ������� ������ �������� ����� �������, � ����� ����� �������� ���� ������ �� ���������� ���������������� ����.

int main()
{
	setlocale(LC_ALL, "Rus");

	//���� ������� ������. ��� ��� �� ���������� ������� �������������� ��������� ������������.
	std::cout << "������� ������� ����������������� ���� (������� �� ����� ���������� � v0).\n\n";
	std::cout << "������� ���������� ������ � ����� p = | V | : ";
	int p{ getNumberVertexes() };
	std::cout << "������� ���������� ���� � ����� q=|X|: ";
	int q{ getNumberEdges(p) };
	std::cout << "������� �������, ����� �������� ����� ����� ����������: " << std::endl;
	std::cout << "������ �������: ";
	int from_rhombus_vertex{ getVertex(p) };
	std::cout << "������ �������: ";
	int to_rhombus_vertex{ getVertex(p) };
	std::cout << "������� �������, ����� �������� ����� ����� ���������� ��������� ������������ �����: " << std::endl;
	std::cout << "������ �������: ";
	int from_circle_vertex{ getVertex(p) };
	std::cout << "������ �������: ";
	int to_circle_vertex{ getVertex(p) };
	std::cout << "������� ������������ ����� ����� ������� ���������: ";
	int intresting_length{ getInterestingLength() };
	 
	/*������� matrix_multi ������ ��������� �������� ��� ������ �������� � ���������� ���������� ������� ��������� � �������, 
	 *��� ��� ����� �� ��������� ��������� ������������(���� �������� ����� ����������� ����� �� ������).
	 */
	int** graph = new int* [p]; //������� ���������, ���������� �� �����.
	int** matrix_multi = new int* [p]; //�������, �������� ������� ���������, ���������� � �������.
	int** answer_matrix = new int* [p]; //�������, �������� ����� �� ������ ������ ������.

	//������������� ������: �������� ��������������� ������ � ������������ ���� �� ��������� ������� ��������.
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

	/*��������� ������� ��������� �� �������� ����� � ����� � �� �������.
	 *��� ��� ���� ������� � �����������������, �� ������� ��������� ������������, �������� ���� �� ������� ��������� � ��������, �� ���� � �������� =:
	 * 0 - ���� ������� �� ��������� ������, 1 - ���� ������� ��������� ������.
	 */
	getAdjacencyMatrix(graph, p, q); //���������� ������� ��������� "1" �� �������� �����.

	int* visited = new int[p]; //�������� �������, � ������� ����� ������� ���� ��� ���������� ������.
	int* path = new int[p]; //�������� �������, ������� ����� ������� ������� ����� ���������.
	int count_path{}; //����������, �������� ����� ������ � ������� path.
	int* layers = new int[p]; //�������� �������, � ������� ����� ������� ���� ������, ��� ���������� �����.
	int count_layers{}; //����������, �������� ����� ��������� � ������� layers.
	int check_count_layers{}; //����������, ������� ����� ��������� ��� �� ��������� ����� ���� �����������.
	int* distances = new int[p]; //�������� �������, ������� ����� ������� ���������� �� ������ �������, ������ ����� �������, ��� ���� ��� ������� ����� -1, �� ������� �� �������� �����.


	int answer_first_question{}; //����������, ������� ����� ������� ����� �� ������ ������ ������.
	int answer_second_question{};//����������, ������� ����� ������� ����� �� ������ ������ ������.

	
	//���������� ��������������� �������� � ���������� ���������:
	for (int i{}; i < p; i++)
	{
		visited[i] = 0; //���������� ������� ������� �� ���� ��������.
		distances[i] = -1; //���������� ���������� �� ����� ������� ����������, ����� -1, "����" �� �����������, ����� ���.
		path[i] = 0; //��� ��� ���������� ���� ��� ���, �� �� �����, �� ���������� ������ ����.
	}
	int length{}; //����������, ������� ����� ���������� ���������� �� ��� ��� ���� ����� ���������, �� ���� �����.
	layers[count_layers] = from_rhombus_vertex; //���������� ��������� ������� �������� ����� 0, �� ���� ���� �������� "�����".
	count_layers += 1;
	distances[from_rhombus_vertex] = length; //������� ���������� �� ��������������� ������� � ������, �� ���� ��������� ������� �������� ����� 0.

	//�������� ������ ���������.
	// ��� ������ �� ������ ������ ������.
	if (from_rhombus_vertex != to_rhombus_vertex) //������, ����� ������� ������ � ����� �������� �� ���������.
	{
		//���������, ���� �� ������ ���� � �������� ������� ��������.
		if (bfs(graph, p, to_rhombus_vertex, visited, layers, distances, count_layers, length, check_count_layers) == false) //���� ���, ������� ��������������� ���������� ������������.
		{
			std::cout << "����� ��������� " << from_rhombus_vertex << " � " << to_rhombus_vertex << " ������ ��������� ����, ��� ��� ������ ������� �� ������� �������(-��)!" << std::endl;
		}
		else
		{
			for (int i{}; i < p; i++) //���� ����, �������� ������ ���������� ������ (��� ����� ��� ���������� ������� ���������� ���� �� �����). 
			{
				visited[i] = 0;
			}
			path[count_path] = to_rhombus_vertex; //����� ��������� �������� ������� ��������.
			count_path += 1;
			std::cout << "�������(-��) ����������(-��) ����(-�) ����� ��������� " << from_rhombus_vertex << " � " << to_rhombus_vertex << ":" << std::endl;
			print_path(graph, p, from_rhombus_vertex, to_rhombus_vertex, path, distances, visited, count_path, answer_first_question); //��������� ���������� ����.
			std::cout << "���������� ����� ��������� " << from_rhombus_vertex << " � " << to_rhombus_vertex << " ����� " << answer_first_question << "." << std::endl;
			std::cout << std::endl;
		}
	}
	else //������, ����� ������� ������ � ����� �������� ���������.
	{
		std::cout << "������� ������ ���� (" << from_rhombus_vertex << ") � ����� ���� (" << to_rhombus_vertex << ") ���������. ���������� ����� ���� ����� 0." << std::endl;
	}
	

	//��� ������ �� ������ ������ ������.
	switch (intresting_length) //� ����������� �� ������������ ����� �������� ��������� ��������� ��������.
	{
	case 0: //���� ������������ ����� �������� ����� 0, �� ���� ����� ���� ��������� ������ � ����� ������. ���� ������� ������ � ����� �������� ���������, �� �������� �� ���� ������������.
	{
		if (from_circle_vertex == to_circle_vertex)
			std::cout << "������� ������ �������� " << from_circle_vertex << " � ����� �������� " << to_circle_vertex << " ���������. " << std::endl;
		std::cout << "����� ��������� " << from_circle_vertex << " � " << to_circle_vertex << " ������ ��������� ������� ������������ ����� (" << intresting_length << ")!" << std::endl;
		break;
	}
	case 1://���� ������������ ����� �������� ����� 1, �� ��������� ������������ ������� ����� ���� �� ���� �����, ����� ��� ��������� ������, ���� �� �����.
	{
		if(graph[from_circle_vertex][to_circle_vertex] == 0)
			std::cout << "����� ��������� " << from_circle_vertex << " � " << to_circle_vertex << " ������ ��������� ������� ������������ ����� ("
			<< intresting_length << ")!" << std::endl;
		else
			std::cout << "���������� ��������� ����� " << intresting_length << " ����� ��������� " << from_circle_vertex << " � " << to_circle_vertex 
			<< " ����� 1." << std::endl;
		break;
	}
	default://���� ������������ ����� �������� > 1, �� ��������� ��������������� ��������:
	{
		for (int i{}; i < p; i++) //��������� ����������� ����������� ������� ��������� � ������� answer_matrix, ��� ��� ��� ������ ���������� ������������ ������.
		{
			for (int j{}; j < p;j++)
			{
				answer_matrix[i][j] = graph[i][j];
			}
		}
		for (int i{}; i < intresting_length - 1; i++) //��������� ���������� ������� ��������� � ������� ����������� ����� ���.
		{
			multi_AdjacencyMatrix(graph, matrix_multi, answer_matrix, p);
		}
		//������� �� ������ ��� �������� � ��������������� ������ � ������� ������� answer_matrix, ���������� ��� � ���������� answer_second_question.
		answer_second_question = answer_matrix[from_circle_vertex][to_circle_vertex]; 
		//������ ��������������� ����� � ���������� �����������.
		if (answer_second_question == 0)
			std::cout << "����� ��������� " << from_circle_vertex << " � " << to_circle_vertex << " ������ ��������� ������� ������������ ����� (" 
			<< intresting_length << ")!" << std::endl;
		else
			std::cout << "���������� ��������� ����� " << intresting_length << " ����� ��������� " << from_circle_vertex << " � " << to_circle_vertex << " ����� "
			<< answer_second_question << "." << std::endl;
		break;
	}
	}
	
	//���������� ������� ������ � ����, ������� ���� �������� ��� �������, ������� ������� ������������ �� ����� ���������� ���������.
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
