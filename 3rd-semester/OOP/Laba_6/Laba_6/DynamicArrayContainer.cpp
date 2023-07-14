#include "SFML/Graphics.hpp"

#include "DynamicArrayContainer.h"
#include "TFigure.h"

void DynamicArrayContainer::move_figures_W(int i)
{
	int choice_figure{ getChoiceFigureForMethods(i) };
	switch (choice_figure)
	{
	case 0:
	{
		TCircle* ptr_circle{ static_cast<TCircle*>(m_data_figures[i]) };
		if ((ptr_circle->getCoordinateY() - ptr_circle->getRadius() - 10) >= 115)
		{
			ptr_circle->MoveTo(0, -10);
		}
		break;
	}
	case 1:
	{
		TEllipse* ptr_ellipse{ static_cast<TEllipse*>(m_data_figures[i]) };
		if ((ptr_ellipse->getCoordinateY() - ptr_ellipse->getSemiMinorAxis() - 10) >= 115)
		{
			ptr_ellipse->MoveTo(0, -10);
		}
		break;
	}
	case 2:
	{
		TQuadrilateral* ptr_quadrilateral{ static_cast<TQuadrilateral*>(m_data_figures[i]) };
		if ((ptr_quadrilateral->getCoordinateY() - 10) >= 115 && (ptr_quadrilateral->getCoordinateY2() - 10) >= 115)
		{
			ptr_quadrilateral->MoveTo(0, -10);
			ptr_quadrilateral->changeCoordinateX234_Y234(0, -10);
		}
		break;
	}
	case 3:
	{
		TRectangle* ptr_rectangle{ static_cast<TRectangle*>(m_data_figures[i]) };
		if ((ptr_rectangle->getCoordinateY() - 10) >= 115)
		{
			ptr_rectangle->MoveTo(0, -10);
			ptr_rectangle->changeCoordinateX234_Y234(0, -10);
		}
		break;
	}
	case 4:
	{
		TRhombus* ptr_rhombus{ static_cast<TRhombus*>(m_data_figures[i]) };
		if ((ptr_rhombus->getCoordinateY2() - 10) >= 115)
		{
			ptr_rhombus->MoveTo(0, -10);
			ptr_rhombus->changeCoordinateX234_Y234(0, -10);
		}
		break;
	}
	case 5:
	{
		TTrapeze* ptr_trapeze{ static_cast<TTrapeze*>(m_data_figures[i]) };
		if ((ptr_trapeze->getCoordinateY2() - 10) >= 115 && (ptr_trapeze->getCoordinateY3() - 10) >= 115)
		{
			ptr_trapeze->MoveTo(0, -10);
			ptr_trapeze->changeCoordinateX234_Y234(0, -10);
		}
		break;
	}
	default:
	{
		break;
	}
	}
}
void DynamicArrayContainer::move_figures_A(int i)
{
	int choice_figure{ getChoiceFigureForMethods(i) };
	switch (choice_figure)
	{
	case 0:
	{
		TCircle* ptr_circle{ static_cast<TCircle*>(m_data_figures[i]) };
		if ((ptr_circle->getCoordinateX() - ptr_circle->getRadius() - 10) >= 465)
		{
			ptr_circle->MoveTo(-10, 0);
		}
		break;
	}
	case 1:
	{
		TEllipse* ptr_ellipse{ static_cast<TEllipse*>(m_data_figures[i]) };
		if ((ptr_ellipse->getCoordinateX() - ptr_ellipse->getRadius() - 10) >= 465)
		{
			ptr_ellipse->MoveTo(-10, 0);
		}
		break;
	}
	case 2:
	{
		TQuadrilateral* ptr_quadrilateral{ static_cast<TQuadrilateral*>(m_data_figures[i]) };
		if ((ptr_quadrilateral->getCoordinateX() - 10) >= 465 && (ptr_quadrilateral->getCoordinateX4() - 10) >= 465)
		{
			ptr_quadrilateral->MoveTo(-10, 0);
			ptr_quadrilateral->changeCoordinateX234_Y234(-10, 0);
		}
		break;
	}
	case 3:
	{
		TRectangle* ptr_rectangle{ static_cast<TRectangle*>(m_data_figures[i]) };
		if ((ptr_rectangle->getCoordinateX() - 10) >= 465)
		{
			ptr_rectangle->MoveTo(-10, 0);
			ptr_rectangle->changeCoordinateX234_Y234(-10, 0);
		}
		break;
	}
	case 4:
	{
		TRhombus* ptr_rhombus{ static_cast<TRhombus*>(m_data_figures[i]) };
		if ((ptr_rhombus->getCoordinateX() - 10) >= 465)
		{
			ptr_rhombus->MoveTo(-10, 0);
			ptr_rhombus->changeCoordinateX234_Y234(-10, 0);
		}
		break;
	}
	case 5:
	{
		TTrapeze* ptr_trapeze{ static_cast<TTrapeze*>(m_data_figures[i]) };
		if ((ptr_trapeze->getCoordinateX() - 10) >= 465)
		{
			ptr_trapeze->MoveTo(-10, 0);
			ptr_trapeze->changeCoordinateX234_Y234(-10, 0);
		}
		break;
	}
	default:
	{
		break;
	}
	}
}
void DynamicArrayContainer::move_figures_S(int i)
{
	int choice_figure{ getChoiceFigureForMethods(i) };
	switch (choice_figure)
	{
	case 0:
	{
		TCircle* ptr_circle{ static_cast<TCircle*>(m_data_figures[i]) };
		if (ptr_circle->getCoordinateY() + ptr_circle->getRadius() + 10 <= 715)
		{
			ptr_circle->MoveTo(0, 10);
		}
		break;
	}
	case 1:
	{
		TEllipse* ptr_ellipse{ static_cast<TEllipse*>(m_data_figures[i]) };
		if ((ptr_ellipse->getCoordinateY() + 10 + ptr_ellipse->getSemiMinorAxis()) <= 715)
		{
			ptr_ellipse->MoveTo(0, 10);
		}
		break;
	}
	case 2:
	{
		TQuadrilateral* ptr_quadrilateral{ static_cast<TQuadrilateral*>(m_data_figures[i]) };
		if ((ptr_quadrilateral->getCoordinateY3() + 10) <= 715 && (ptr_quadrilateral->getCoordinateY4() + 10) <= 715)
		{
			ptr_quadrilateral->MoveTo(0, 10);
			ptr_quadrilateral->changeCoordinateX234_Y234(0, 10);
		}
		break;
	}
	case 3:
	{
		TRectangle* ptr_rectangle{ static_cast<TRectangle*>(m_data_figures[i]) };
		if ((ptr_rectangle->getCoordinateY() + ptr_rectangle->getWidth() + 10) <= 715)
		{
			ptr_rectangle->MoveTo(0, 10);
			ptr_rectangle->changeCoordinateX234_Y234(0, 10);
		}
		break;
	}
	case 4:
	{
		TRhombus* ptr_rhombus{ static_cast<TRhombus*>(m_data_figures[i]) };
		if ((ptr_rhombus->getCoordinateY4() + 10) <= 715)
		{
			ptr_rhombus->MoveTo(0, 10);
			ptr_rhombus->changeCoordinateX234_Y234(0, 10);
		}
		break;
	}
	case 5:
	{
		TTrapeze* ptr_trapeze{ static_cast<TTrapeze*>(m_data_figures[i]) };
		if ((ptr_trapeze->getCoordinateY() + 10) <= 715 && (ptr_trapeze->getCoordinateY4() + 10) <= 715)
		{
			ptr_trapeze->MoveTo(0, 10);
			ptr_trapeze->changeCoordinateX234_Y234(0, 10);
		}
		break;
	}
	default:
	{
		break;
	}
	}
}
void DynamicArrayContainer::move_figures_D(int i)
{
	int choice_figure{ getChoiceFigureForMethods(i) };
	switch (choice_figure)
	{
	case 0:
	{
		TCircle* ptr_circle{ static_cast<TCircle*>(m_data_figures[i]) };
		if (ptr_circle->getCoordinateX() + ptr_circle->getRadius() + 10 <= 1415)
		{
			ptr_circle->MoveTo(10, 0);
		}
		break;
	}
	case 1:
	{
		TEllipse* ptr_ellipse{ static_cast<TEllipse*>(m_data_figures[i]) };
		if ((ptr_ellipse->getCoordinateX() + 10 + ptr_ellipse->getRadius()) <= 1415)
		{
			ptr_ellipse->MoveTo(10, 0);
		}
		break;
	}
	case 2:
	{
		TQuadrilateral* ptr_quadrilateral{ static_cast<TQuadrilateral*>(m_data_figures[i]) };
		if ((ptr_quadrilateral->getCoordinateX2() + 10) <= 1415 && (ptr_quadrilateral->getCoordinateX3() + 10) <= 1415)
		{
			ptr_quadrilateral->MoveTo(10, 0);
			ptr_quadrilateral->changeCoordinateX234_Y234(10, 0);
		}
		break;
	}
	case 3:
	{
		TRectangle* ptr_rectangle{ static_cast<TRectangle*>(m_data_figures[i]) };
		if ((ptr_rectangle->getCoordinateX() + ptr_rectangle->getLength() + 10) <= 1415)
		{
			ptr_rectangle->MoveTo(10, 0);
			ptr_rectangle->changeCoordinateX234_Y234(10, 0);
		}
		break;
	}
	case 4:
	{
		TRhombus* ptr_rhombus{ static_cast<TRhombus*>(m_data_figures[i]) };
		if ((ptr_rhombus->getCoordinateX3() + 10) <= 1415)
		{
			ptr_rhombus->MoveTo(10, 0);
			ptr_rhombus->changeCoordinateX234_Y234(10, 0);
		}
		break;
	}
	case 5:
	{
		TTrapeze* ptr_trapeze{ static_cast<TTrapeze*>(m_data_figures[i]) };
		if ((ptr_trapeze->getCoordinateX4() + 10) <= 1415 && (ptr_trapeze->getCoordinateX3() + 10) <= 1415)
		{
			ptr_trapeze->MoveTo(10, 0);
			ptr_trapeze->changeCoordinateX234_Y234(10, 0);
		}
		break;
	}
	default:
	{
		break;
	}
	}
}
void DynamicArrayContainer::move_figures_Q(int i)
{
	int choice_figure{ getChoiceFigureForMethods(i) };
	switch (choice_figure)
	{
	case 0:
	{
		TCircle* ptr_under_circle_hierarchy{ static_cast<TCircle*>(m_data_figures[i]) };
		if ((ptr_under_circle_hierarchy->getRadius() - 1) >= 15)
		{
			ptr_under_circle_hierarchy->ChangeRadius(-1);
		}
		break;
	}
	case 1:
	{
		TEllipse* ptr_ellipse{ static_cast<TEllipse*>(m_data_figures[i]) };
		if ((ptr_ellipse->getSemiMinorAxis() - 1) >= 15)
		{
			ptr_ellipse->changeSemiMinorAxis(-1);
		}
		break;
	}
	case 3:
	{
		TRectangle* ptr_rectangle{ static_cast<TRectangle*>(m_data_figures[i]) };
		if ((ptr_rectangle->getLength() - 1) >= 30)
			ptr_rectangle->changeLength(-1);
		break;
	}
	case 4:
	{
		TRhombus* ptr_rhombus{ static_cast<TRhombus*>(m_data_figures[i]) };
		if ((ptr_rhombus->getDegree() - 1 >= 15) && ptr_rhombus->getCoordinateX3() <= 1415)
		{
			ptr_rhombus->changeDegree(-1);
		}
		break;
	}
	case 5:
	{
		TTrapeze* ptr_trapeze{ static_cast<TTrapeze*>(m_data_figures[i]) };
		if ((ptr_trapeze->getCoordinateX4() - ptr_trapeze->getCoordinateX3() - 1 <= 50))
		{
			ptr_trapeze->changeTopBase(-1);
		}
		break;
	}
	default:
	{
		break;
	}
	}
}
void DynamicArrayContainer::move_figures_E(int i)
{
	int choice_figure{ getChoiceFigureForMethods(i) };
	switch (choice_figure)
	{
	case 0:
	{
		TCircle* ptr_under_circle_hierarchy{ static_cast<TCircle*>(m_data_figures[i]) };
		if (((ptr_under_circle_hierarchy->getCoordinateX() - ptr_under_circle_hierarchy->getRadius() - 1) >= 465 &&
			(ptr_under_circle_hierarchy->getCoordinateX() + ptr_under_circle_hierarchy->getRadius() + 1) <= 1415 &&
			(ptr_under_circle_hierarchy->getCoordinateY() - ptr_under_circle_hierarchy->getRadius() - 1) >= 115 &&
			(ptr_under_circle_hierarchy->getCoordinateY() + ptr_under_circle_hierarchy->getRadius() + 1) <= 715))
		{
			ptr_under_circle_hierarchy->ChangeRadius(1);
		}
		break;
	}
	case 1:
	{
		TEllipse* ptr_ellipse{ static_cast<TEllipse*>(m_data_figures[i]) };
		if (((ptr_ellipse->getCoordinateY() - ptr_ellipse->getSemiMinorAxis() - 1) >= 115 &&
			(ptr_ellipse->getCoordinateY() + ptr_ellipse->getSemiMinorAxis() + 1) <= 715))
		{
			ptr_ellipse->changeSemiMinorAxis(1);
		}
		break;
	}
	case 3:
	{
		TRectangle* ptr_rectangle{ static_cast<TRectangle*>(m_data_figures[i]) };
		if ((ptr_rectangle->getCoordinateX() + ptr_rectangle->getLength() + 1) <= 1415)
			ptr_rectangle->changeLength(1);
		break;
	}
	case 4:
	{
		TRhombus* ptr_rhombus{ static_cast<TRhombus*>(m_data_figures[i]) };
		if ((ptr_rhombus->getDegree() + 1 <= 60) && ptr_rhombus->getCoordinateY2() >= 115 &&
			ptr_rhombus->getCoordinateY4() <= 715)
		{
			ptr_rhombus->changeDegree(1);
		}
		break;
	}
	case 5:
	{
		TTrapeze* ptr_trapeze{ static_cast<TTrapeze*>(m_data_figures[i]) };
		if (ptr_trapeze->getCoordinateX3() <= ptr_trapeze->getCoordinateX4())
		{
			ptr_trapeze->changeTopBase(1);
		}
		break;
	}
	default:
	{
		break;
	}
	}
}
void DynamicArrayContainer::move_figures_C(int i)
{
	int choice_figure{ getChoiceFigureForMethods(i) };
	switch (choice_figure)
	{
	case 1:
	{
		TEllipse* ptr_ellipse{ static_cast<TEllipse*>(m_data_figures[i]) };
		if ((ptr_ellipse->getCoordinateX() - ptr_ellipse->getRadius() - 1) >= 465 && (ptr_ellipse->getCoordinateX() +
			ptr_ellipse->getRadius() + 1) <= 1415)
		{
			ptr_ellipse->ChangeRadius(1);
		}
		break;
	}
	case 3:
	{
		TRectangle* ptr_rectangle{ static_cast<TRectangle*>(m_data_figures[i]) };
		if ((ptr_rectangle->getCoordinateY() + ptr_rectangle->getWidth() + 1) <= 715)
			ptr_rectangle->changeWidth(1);
		break;
	}
	case 4:
	{
		TRhombus* ptr_rhombus{ static_cast<TRhombus*>(m_data_figures[i]) };
		if ((ptr_rhombus->getCoordinateY2() >= 115) && ptr_rhombus->getCoordinateY4() <= 715 &&
			ptr_rhombus->getCoordinateX3() <= 1415)
		{
			ptr_rhombus->changeLength(1);
		}
		break;
	}
	case 5:
	{
		TTrapeze* ptr_trapeze{ static_cast<TTrapeze*>(m_data_figures[i]) };
		if ((ptr_trapeze->getCoordinateX4() + 1) <= 1415 && (ptr_trapeze->getCoordinateX4() + 1) <= (ptr_trapeze->getCoordinateX3() + 60))
		{
			ptr_trapeze->changeBottomBase(1);
		}
		break;
	}
	default:
	{
		break;
	}
	}
}
void DynamicArrayContainer::move_figures_Z(int i)
{
	int choice_figure{ getChoiceFigureForMethods(i) };
	switch (choice_figure)
	{
	case 1:
	{
		TEllipse* ptr_ellipse{ static_cast<TEllipse*>(m_data_figures[i]) };
		if (ptr_ellipse->getRadius() - 1 >= 40)
		{
			ptr_ellipse->ChangeRadius(-1);
		}
		break;
	}
	case 3:
	{
		TRectangle* ptr_rectangle{ static_cast<TRectangle*>(m_data_figures[i]) };
		if ((ptr_rectangle->getWidth() - 1) >= 30)
			ptr_rectangle->changeWidth(-1);
		break;
	}
	case 4:
	{
		TRhombus* ptr_rhombus{ static_cast<TRhombus*>(m_data_figures[i]) };
		if ((ptr_rhombus->getLength() - 1 >= 30))
		{
			ptr_rhombus->changeLength(-1);
		}
		break;
	}
	case 5:
	{
		TTrapeze* ptr_trapeze{ static_cast<TTrapeze*>(m_data_figures[i]) };
		if ((ptr_trapeze->getCoordinateX4() - 1 >= ptr_trapeze->getCoordinateX3()))
		{
			ptr_trapeze->changeBottomBase(-1);
		}
		break;
	}
	default:
	{
		break;
	}
	}
}
void DynamicArrayContainer::move_figures_F(int i)
{
	if (dynamic_cast<TTrapeze*>(m_data_figures[i]) != nullptr)
	{
		TTrapeze* ptr_trapeze{ static_cast<TTrapeze*>(m_data_figures[i]) };
		if ((ptr_trapeze->getCoordinateY2() - 1) >= 115 && (ptr_trapeze->getCoordinateY() - ptr_trapeze->getCoordinateY2() + 1) <= 100)
		{
			ptr_trapeze->changeHeight(-1);
		}
	}
}
void DynamicArrayContainer::move_figures_R(int i)
{
	int choice_figure{ getChoiceFigureForMethods(i) };
	switch (choice_figure)
	{
	case 1:
	{
		TEllipse* ptr_ellipse{ static_cast<TEllipse*>(m_data_figures[i]) };
		if ((ptr_ellipse->getCoordinateY() - ptr_ellipse->getRadius()) >= 115 &&
			(ptr_ellipse->getCoordinateY() + ptr_ellipse->getRadius()) <= 715 &&
			(ptr_ellipse->getCoordinateX() - ptr_ellipse->getSemiMinorAxis()) >= 465 &&
			(ptr_ellipse->getCoordinateX() + ptr_ellipse->getSemiMinorAxis()) <= 1415)
		{
			ptr_ellipse->Rotate90degrees();
		}
		break;
	}
	case 5:
	{
		TTrapeze* ptr_trapeze{ static_cast<TTrapeze*>(m_data_figures[i]) };
		if ((ptr_trapeze->getCoordinateY() - ptr_trapeze->getCoordinateY2() - 1 >= 30))
		{
			ptr_trapeze->changeHeight(1);
		}
		break;
	}
	default:
	{
		break;
	}
	}
}

DynamicArrayContainer::DynamicArrayContainer()
	:m_size{ 0 }, m_data_figures{ nullptr }
{
	m_data_figures = new TFigure * [m_size];
	std::cout << "ѕустой контейнер на базе динамического массива был успешно создан. " << std::endl;
}

void DynamicArrayContainer::addElement(TFigure* ptr_obj_shape)
{
	TFigure** new_m_data_figures{ new TFigure * [m_size + 1] };
	for (int i{};i < m_size;i++)
	{
		new_m_data_figures[i] = m_data_figures[i];
	}

	new_m_data_figures[m_size] = ptr_obj_shape;
	m_size += 1;
	delete[] m_data_figures; m_data_figures = nullptr;
	m_data_figures = new_m_data_figures;
}
void DynamicArrayContainer::removeElement()
{
	TFigure** new_m_data_figures{ new TFigure * [m_size - 1] };
	for (int i{};i < m_size - 1;i++)
	{
		new_m_data_figures[i] = m_data_figures[i];
	}
	m_size -= 1;
	delete m_data_figures[m_size]; m_data_figures[m_size] = nullptr;
	delete[] m_data_figures; m_data_figures = nullptr;
	m_data_figures = new_m_data_figures;
}
int DynamicArrayContainer::getChoiceFigureForMethods(int index)
{
	int choice_figure{};
	TCircle* ptr_circle{ dynamic_cast<TCircle*>(m_data_figures[index]) };
	if (ptr_circle)
	{
		choice_figure = 0;
	}
	TEllipse* ptr_ellipse{ dynamic_cast<TEllipse*>(m_data_figures[index]) };
	if (ptr_ellipse)
	{
		choice_figure = 1;
	}
	TQuadrilateral* ptr_quadrilateral{ dynamic_cast<TQuadrilateral*>(m_data_figures[index]) };
	if (ptr_quadrilateral)
	{
		choice_figure = 2;
	}
	TRectangle* ptr_rectangle{ dynamic_cast<TRectangle*>(m_data_figures[index]) };
	if (ptr_rectangle)
	{
		choice_figure = 3;
	}
	TRhombus* ptr_rhombus{ dynamic_cast<TRhombus*>(m_data_figures[index]) };
	if (ptr_rhombus)
	{
		choice_figure = 4;
	}
	TTrapeze* ptr_trapeze{ dynamic_cast<TTrapeze*>(m_data_figures[index]) };
	if (ptr_trapeze)
	{
		choice_figure = 5;
	}
	return choice_figure;
}
void DynamicArrayContainer::iterator(int choice, int index_of_element, sf::RenderWindow& window)
{
	switch (choice)
	{
	case 0:
	{
		int choice_figure{ getChoiceFigureForMethods(index_of_element) };
		switch (choice_figure)
		{
		case 0:
		{
			TCircle* ptr_circle{ static_cast<TCircle*>(m_data_figures[index_of_element]) };
			ptr_circle->Free(ptr_circle);
			break;
		}
		case 1:
		{
			TEllipse* ptr_ellipse{ static_cast<TEllipse*>(m_data_figures[index_of_element]) };
			ptr_ellipse->Free(ptr_ellipse);
			break;
		}
		case 2:
		{
			TQuadrilateral* ptr_quadrilateral{ static_cast<TQuadrilateral*>(m_data_figures[index_of_element]) };
			ptr_quadrilateral->Free(ptr_quadrilateral);
			break;
		}
		case 3:
		{
			TRectangle* ptr_rectangle{ static_cast<TRectangle*>(m_data_figures[index_of_element]) };
			ptr_rectangle->Free(ptr_rectangle);
			break;
		}
		case 4:
		{
			TRhombus* ptr_rhombus{ static_cast<TRhombus*>(m_data_figures[index_of_element]) };
			ptr_rhombus->Free(ptr_rhombus);
			break;
		}
		case 5:
		{
			TTrapeze* ptr_trapeze{ static_cast<TTrapeze*>(m_data_figures[index_of_element]) };
			ptr_trapeze->Free(ptr_trapeze);
			break;
		}
		default:
		{
			break;
		}
		}
		if (index_of_element == m_size - 1)
		{
			Free();
		}
		break;
	}
	case 1:
	{
		removeElement();
		break;
	}
	case 2:
	{
		m_data_figures[index_of_element]->Show(window);
		break;
	}
	case 3:
	{
		break;
	}
	case 4:
	{
		move_figures_W(index_of_element);
		break;
	}
	case 5:
	{
		move_figures_A(index_of_element);
		break;

	}
	case 6:
	{
		move_figures_S(index_of_element);
		break;

	}
	case 7:
	{
		move_figures_D(index_of_element);
		break;
	}
	case 8:
	{
		move_figures_Q(index_of_element);
		break;
	}
	case 9:
	{
		move_figures_E(index_of_element);
		break;
	}
	case 10:
	{
		move_figures_Z(index_of_element);
		break;
	}
	case 11:
	{
		move_figures_C(index_of_element);
		break;
	}
	case 12:
	{
		move_figures_F(index_of_element);
		break;
	}
	case 13:
	{
		move_figures_R(index_of_element);
		break;
	}
	}
}
void DynamicArrayContainer::Free()
{
	delete[] m_data_figures;
	m_data_figures = nullptr;
	m_size = 0;
	std::cout << " онтейнер на основе полиморфного динамического массива был очищен. ¬се примитивы были удалены из кучи." << std::endl;
}
int DynamicArrayContainer::getSize()
{
	return m_size;
}
TFigure* DynamicArrayContainer::getElement(int index_element)
{
	return m_data_figures[index_element];
}
DynamicArrayContainer::~DynamicArrayContainer()
{
	std::cout << " онтейнер на базе динамического массива был успешно уничтожен. " << std::endl;
}
