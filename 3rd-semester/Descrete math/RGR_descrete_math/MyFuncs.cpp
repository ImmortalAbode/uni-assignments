#include <iostream>
#include <string>

#include "MyFuncs.h"

//��������� �������� ������ �� ����������� �������������� � �����.
bool checkStrIsNumeric(std::string const& tempStr)
{
	for (int i{}; i < tempStr.length(); i++)
	{
		if ((tempStr[i] < '0') || (tempStr[i] > '9'))
			return false;
	}
	return !tempStr.empty();
}
//����������� ������ � �����.
int convertStrToInt(std::string convertStr)
{
	double number{};
	for (int i{}; i < convertStr.length(); i++)
		number += (convertStr[i] - '0') * pow(10, convertStr.length() - 1 - i);
	return static_cast<int>(number);
}
//��������� ���������� ������ � �������� �� ���������� ���������������� ����.
int getNumberVertexes()
{
	while (true)
	{
		std::string tempStrVerts{};
		std::getline(std::cin, tempStrVerts);
		if (!checkStrIsNumeric(tempStrVerts))
		{
			std::cin.clear();
			std::cout << "������ �����. �� ������ ������ ����������� �����. ��������� ����:\n";
		}
		else
		{
			return convertStrToInt(tempStrVerts);
		}
	}
}
//��������� ���������� ���� � �������� �� ���������� ���������������� ����.
int getNumberEdges(const int& p)
{
	while (true)
	{
		std::string tempStrEdges{};
		std::getline(std::cin, tempStrEdges);
		if (!checkStrIsNumeric(tempStrEdges))
		{
			std::cin.clear();
			std::cout << "������ �����. �� ������ ������ ����� ��������������� �����. ��������� ����:\n";
		}
		else
		{
			if (convertStrToInt(tempStrEdges) <= p * (p - 1) / 2) //��� ��� � ������� ����� �������� ������� ����
				return convertStrToInt(tempStrEdges);
			else
				std::cout << "���������� ���� ������� �������. �� ������ ������ ����� ���� �� 0 �� " << p * (p - 1) / 2 << ". ��������� ����:\n";
		}
	}
}
//��������� ������ ������� � �������� �� ���������� ���������������� ����.
int getVertex(int number_vertexes)
{
	while (true)
	{
		std::string tempStrVert{};
		std::getline(std::cin, tempStrVert);
		if (!checkStrIsNumeric(tempStrVert) || convertStrToInt(tempStrVert) >= number_vertexes)
		{
			std::cin.clear();
			std::cout << "������ �����. �� ������ ������ ����� ��������������� ����� �� 0 �� " << number_vertexes - 1 << ". ��������� ���� ��������� �������� �������:\n";
		}
		else
		{
			return convertStrToInt(tempStrVert);
		}
	}
}
//��������� ������� ��������� �� �������� ����� � ����� � �� ������� � �������� �� ���������� ���������������� ����.
void getAdjacencyMatrix(int**& adjacency_matrix, int& p, int& q)
{
	std::cout << "\n������� ���� �����." << std::endl;
	int count{};
	while (count != q)
	{
		while (true)
		{
			std::cout << "������� ������ ������� �����: ";
			int first_adj_vert{ getVertex(p) };
			std::cout << "������� ������ ������� �����: ";
			int second_adj_vert{ getVertex(p) };
			if (first_adj_vert != second_adj_vert) //���������, ��� ������������ ������ �� �����.
			{
				for (int rows{}; rows < p; rows++)
				{
					for (int columns{}; columns < p; columns++)
					{
						if ((rows == first_adj_vert) && (columns == second_adj_vert))
						{
							if (adjacency_matrix[rows][columns] == 0)
							{
								adjacency_matrix[rows][columns] = 1; //������ � ������� ��������� 1 �� ����������� �������������� ������. � ��� ��� ���� �����������������, 
								adjacency_matrix[columns][rows] = 1; //�� � ����������� ������������ ������� ��������� ������� ���� ������ 1.
								std::cout << count + 1 << "-� ����� ���� ������� ����� ��������� " << rows << " � " << columns << "." << std::endl;
								count++;
							}
							else
							{
								std::cout << "������ ����� ����� ����� ���������� ���������. ��� ��� ���� �������. ��������� ���� ������� ������ ������." << std::endl;
							}
							break;
						}
					}
				}
				break;
			}
			else
			{
				std::cout << "�� �� ������ ������ ����� �� ������� ������. ��������� ���� ������� ������." << std::endl;
			}
		}
	}
	std::cout << "\t\t������� ��������� �����: " << std::endl << std::endl; //������������ ����� ������� ��������� �� ������� ������������.
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
//��������� ����������� ����� ����� ��������� ����� ������ � �������� �� ���������� ���������������� ����.
int getInterestingLength()
{
	while (true)
	{
		std::string tempStrDistance{};
		std::getline(std::cin, tempStrDistance);
		if (!checkStrIsNumeric(tempStrDistance) || convertStrToInt(tempStrDistance) < 0)
		{
			std::cin.clear();
			std::cout << "������ �����. �� ������ ������ ����� ��������������� �����. ��������� ����:\n";
		}
		else
		{
			return convertStrToInt(tempStrDistance);
		}
	}
}

/* 1-�� ���� ������� ������. breadth - first search - ����� � ������. ����:
 *����������� ����� �� ������ (0) � "������" (� ������������ �����).
 *����� ������ - ��� ���������� �� ������, ������ ��� ���������� -> ����� �� ��������.
 *����������� ��� �� ��� ���, ���� ����� �� ������� ����� (���� ��������� ��� ��������� �����, � ����� � ��� � �� ������� -> ���� ���.
 *
 *��� ���������� ������ ������� ����� ��������� ��������� �������:
 *�� ������ ����������� ���������������� ����� �� �����-���� ������, ���� ��� ��� ���� ���������� - ��� � ���������� ������ layers;
 *�������� ��������� ������ ������������ �� ������� ��������� - ���� ����� ���� ����� �����, ��� ���;
 *����� ������� ������ ������ �������������� �� ���� ��� ���������� - ��� ����� � ����� ������ visited.
 */
bool bfs(int** graph, int p, int to_vertex, int* visited, int* layers, int* distances, int count_layers, int length, int check_count_layers)
{
	for (int i{}; i < p; i++) //���� ���������� �� ������� ����� ��������� �����, �� �������� � ��� ����������, �� ���� �� � ��� ��� ��������.
	{
		if (distances[i] == length)
		{
			visited[i] = 1;
		}
	}

	if (distances[to_vertex] >= 0 || check_count_layers == -1)//�������� ������������ �� ��� ���, ���� �������� ������� �� ������� �����, ��� ��� ��������� ����� �� ����� �����������.
	{
		if (distances[to_vertex] >= 0) //���� �������� ������� �������� �������� ����� - ���� ����, ����� ����.
		{
			return true;
		}
		else
			return false;
	}

	length += 1; //����������� ����� ����, �� ���� �����, ��� ��� ������� ���������� ��� ���� �����������.

	for (int i{}; i < p;i++) //������� ������� ������� �� ���� ��� ���������� ������, �� ���� ������ � ������, ������ ������ ���������� �����.
	{
		if (visited[i] && distances[i] == length - 1)
		{
			for (int j{}; j < p; j++) //������������ ����� ������� ������, ������:
			{
				bool flag{ false };
				if (graph[i][j] == 0 || visited[j] == 1) //����������, ���� ������� ��� ��������, �� ���� �� � ��� ��� ��������, ��� �� ������ � �������.
				{
					continue;
				}
				for (int k{}; k < count_layers; k++) //����������, ���� ������� ��� � ������.
				{
					if (layers[k] == j)
					{
						flag = true;
					}
				}
				if (flag) { continue; }
				distances[j] = length; //���� ��� �������� ������� ������, �� ���������� ��������������� ���������� �� ������� � ������,
				layers[count_layers] = j; //������� � � ������ ������, ��� ������� �����,
				count_layers += 1; //����������� ���������� ������ � ������� layers.
			}
		}
	}

	//���� ���������� ������ � ������ ����������, �� ������������ ���������� check_count_layers � ���������� count_layers. ����� ������������� �������� ���������� 
	//check_count_layers �� �����, ��� �������� ��� � ��������� ���� �������, ��� ����� ����� ���������� �� ����.
	if (check_count_layers != count_layers)
	{
		check_count_layers = count_layers;
	}
	else
	{
		check_count_layers = -1;
	}

	return bfs(graph, p, to_vertex, visited, layers, distances, count_layers, length, check_count_layers); //���������� ��������� ��������, ���� �� ���������� ������� ������.
}
// 2-�� ���� ������� ������. ���������� ���� (������������������ ������ � ���) �� �����.
void print_path(int** graph, int p, int from_vertex, int& current_vertex, int* path, int* distances, int* visited, int count_path, int& answer_first_question)
{
	//���� ������� ������� ����� ��������� � �������� �������� ��������, �� ������� ��������� � ��� ���� �� ������� ������������, � ����� ���������� ������� ����� ����.
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
	visited[current_vertex] = 1;//�������� ������� �������, ��� ����������.

	//���������� ����� ������� ������� � ������ ��� ������, ������� ��� �� ���� ��������. ���� ����� �����, ��:
	for (int i{}; i < p; i++)
	{
		if (graph[current_vertex][i] == 1 && visited[i] == 0 && distances[current_vertex] == distances[i] + 1)
		{
			path[count_path] = i;//������� � � ������ ���������� ����;
			count_path += 1;
			print_path(graph, p, from_vertex, i, path, distances, visited, count_path, answer_first_question); //���������� ��������� �������� �� ��������� �������.
			count_path -= 1; //��� ������ �������� ����������, �� ���� ��������� ���������� ��� ������� ������� � ������.
		}
	}
	visited[current_vertex] = 0; //���� ���� ���������� ������� ������ ������� �� ����, �� �������� ������ ������� ��� ������������, ����� � �� ���� ����� ������ ���� ����.
}

/* 3-�� ���� ������� ������.
 *������� �������� � ������� ������� ��������� ����� �� �������� ��������� ������, ��� ��������� �������� �� ������ ������ ������.
 *������� ������� - ����� ����.
 *����������� ��������������� ������ � ������� (������� ������ � ����� �������� ��������������) - ���������� ��������� ��������������� �����.
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