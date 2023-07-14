#ifndef LINEARDYNAMICLISTCONTAINER_H_
#define LINEARDYNAMICLISTCONTAINER_H_

#include "SFML/Graphics.hpp"
#include "TFigure.h"

class LinearDynamicListContainer
{
private:
	class Node
	{
	public:
		Node* m_pNext{};
		TFigure* m_pData{};

		Node(TFigure* pData, Node* pNext = nullptr)
			:m_pData{ pData }, m_pNext{ pNext }
		{
			std::cout << "Новый узел линейного динамического списка был успешно создан." << std::endl;
		}

		~Node()
		{
			std::cout << "Узел линейного динамического списка был уничтожен." << std::endl;
		}
	};

	Node* m_pHead{};
	int m_size{};

	void move_figures_W(int i);
	void move_figures_A(int i);
	void move_figures_S(int i);
	void move_figures_D(int i);
	void move_figures_Q(int i);
	void move_figures_E(int i);
	void move_figures_C(int i);
	void move_figures_Z(int i);
	void move_figures_F(int i);
	void move_figures_R(int i);

	void removeNodeData();
public:
	LinearDynamicListContainer();
	void addNewNode(TFigure* pData);
	int getChoiceFigureForMethods(int index);
	void iterator(int choice, int index_of_element, sf::RenderWindow& window);
	void Free();
	TFigure* getNodeData(int index_element);
	int getSize();
	Node* get_pHead();
	~LinearDynamicListContainer();
};

#endif /*LINEARDYNAMICLISTCONTAINER*/