#include <SFML/Graphics.hpp>
#include <iostream>

#include "MyFuncs.h"
#include "TFigure.h"
#include "UserButton.h"

float getRandomNumber(float min, float max)
{
	static const float fraction = 1.0 / (static_cast<float>(RAND_MAX) + 1.0);
	return (rand() * fraction * (max - min + 1) + min);
}

void AddCircleToMass(TFigure**& ptr_figures_mass, int& count_size_mass_figures)
{
	float restrict_radius{ getRandomNumber(10, 90) };
	float restrict_x{ getRandomNumber(465, 1415) };
	float restrict_y{ getRandomNumber(115, 715) };
	TFigure* ptr_new_figure{ new TCircle{restrict_radius,restrict_x,restrict_y} };
	ptr_new_figure->setOutlineColor(getRandomNumber(0, 255), getRandomNumber(0, 255), getRandomNumber(0, 255));
	ptr_new_figure->setFillColor(getRandomNumber(0, 255), getRandomNumber(0, 255), getRandomNumber(0, 255));
	ptr_new_figure->setVisibility(getRandomNumber(50, 255));
	push_back_shape<TFigure>(ptr_figures_mass, count_size_mass_figures, ptr_new_figure);
}

void AddEllipseToMass(TFigure**& ptr_figures_mass, int& count_size_mass_figures)
{
	TFigure* ptr_new_figure{ nullptr };
	while (true)
	{
		float restrict_semi_minor_axis{ getRandomNumber(10, 90) };
		float restrict_semi_major_axis{ getRandomNumber(90, 130) };
		float restrict_x{ getRandomNumber(465, 1415) };
		float restrict_y{ getRandomNumber(115, 715) };
		TEllipse ellipse{ restrict_semi_minor_axis, restrict_semi_major_axis, restrict_x, restrict_y };
		if (ellipse.getSemiMinorAxis() >= 15 && ellipse.getRadius() >= 40)
		{
			ptr_new_figure = new TEllipse{ ellipse.getSemiMinorAxis(), ellipse.getRadius(), restrict_x, restrict_y };
			break;
		}
		else
		{
			std::cout << "!!!Созданный эллипс не удовлетворил условиям создания в ходе попытки реализации." << std::endl;
			std::cout << ".......Заново......." << std::endl;
		}
	}
	ptr_new_figure->setOutlineColor(getRandomNumber(0, 255), getRandomNumber(0, 255), getRandomNumber(0, 255));
	ptr_new_figure->setFillColor(getRandomNumber(0, 255), getRandomNumber(0, 255), getRandomNumber(0, 255));
	ptr_new_figure->setVisibility(getRandomNumber(50, 255));
	push_back_shape<TFigure>(ptr_figures_mass, count_size_mass_figures, ptr_new_figure);
}

void AddQuadrilateralToMass(TFigure**& ptr_figures_mass, int& count_size_mass_figures)
{
	float restrict_x1{ getRandomNumber(480, 1315) };
	float restrict_x2{ getRandomNumber(restrict_x1 + 50, restrict_x1 + 100) };
	float restrict_x3{ getRandomNumber(restrict_x1 + 50, restrict_x1 + 100) };
	float restrict_x4{ getRandomNumber(restrict_x1 - 25, restrict_x3 - 50) };
	float restrict_y1{ getRandomNumber(140, 590) };
	float restrict_y2{ getRandomNumber(restrict_y1 - 25, restrict_y1 + 25) };
	float restrict_y3{ getRandomNumber(restrict_y2 + 50, restrict_y2 + 100) };
	float restrict_y4{ getRandomNumber(restrict_y1 + 50, restrict_y1 + 100) };
	TFigure* ptr_new_figure{ new TQuadrilateral{ restrict_x1, restrict_y1,restrict_x2,restrict_y2, restrict_x3,
		restrict_y3, restrict_x4, restrict_y4 } };
	ptr_new_figure->setOutlineColor(getRandomNumber(0, 255), getRandomNumber(0, 255), getRandomNumber(0, 255));
	ptr_new_figure->setFillColor(getRandomNumber(0, 255), getRandomNumber(0, 255), getRandomNumber(0, 255));
	ptr_new_figure->setVisibility(getRandomNumber(50, 255));
	push_back_shape<TFigure>(ptr_figures_mass, count_size_mass_figures, ptr_new_figure);
}

void AddRectangleToMass(TFigure**& ptr_figures_mass, int& count_size_mass_figures)
{
	float restrict_length{ getRandomNumber(30, 400) };
	float restrict_width{ getRandomNumber(30, 250) };
	float restrict_x{ getRandomNumber(465, 1415) };
	float restrict_y{ getRandomNumber(115, 715) };
	TFigure* ptr_new_figure{ new TRectangle{ restrict_x, restrict_y, restrict_length, restrict_width } };
	ptr_new_figure->setOutlineColor(getRandomNumber(0, 255), getRandomNumber(0, 255), getRandomNumber(0, 255));
	ptr_new_figure->setFillColor(getRandomNumber(0, 255), getRandomNumber(0, 255), getRandomNumber(0, 255));
	ptr_new_figure->setVisibility(getRandomNumber(50, 255));
	push_back_shape<TFigure>(ptr_figures_mass, count_size_mass_figures, ptr_new_figure);
}

void AddRhombusToMass(TFigure**& ptr_figures_mass, int& count_size_mass_figures)
{
	float length{ getRandomNumber(50, 100) };
	int degree{ static_cast<int>(getRandomNumber(15, 60)) };
	float restrict_x{ getRandomNumber(465, 1415 - 2 * length * cos(degree * acos(-1.0f) / 180)) };
	float restrict_y{ getRandomNumber(115 + length * sin(degree * acos(-1.0f) / 180), 715 - length * sin(degree * acos(-1.0f) / 180)) };
	TFigure* ptr_new_figure{ new TRhombus{ restrict_x, restrict_y, length, degree } };
	ptr_new_figure->setOutlineColor(getRandomNumber(0, 255), getRandomNumber(0, 255), getRandomNumber(0, 255));
	ptr_new_figure->setFillColor(getRandomNumber(0, 255), getRandomNumber(0, 255), getRandomNumber(0, 255));
	ptr_new_figure->setVisibility(getRandomNumber(50, 255));
	push_back_shape<TFigure>(ptr_figures_mass, count_size_mass_figures, ptr_new_figure);
}

void AddTrapezeToMass(TFigure**& ptr_figures_mass, int& count_size_mass_figures)
{
	int degree{ static_cast<int>(getRandomNumber(30, 90)) };
	float height{ getRandomNumber(50, 80) };
	float bottom_base_length{ getRandomNumber(150, 300) };
	float top_base_length{ getRandomNumber(60, bottom_base_length - height / tan(degree * acos(-1.0f) / 180)) };
	float restrict_x{ getRandomNumber(465, 1415 - bottom_base_length) };
	float restrict_y{ getRandomNumber(115 + height, 715) };
	TFigure* ptr_new_figure{ new TTrapeze{ restrict_x, restrict_y, degree, bottom_base_length, top_base_length, height } };
	ptr_new_figure->setOutlineColor(getRandomNumber(0, 255), getRandomNumber(0, 255), getRandomNumber(0, 255));
	ptr_new_figure->setFillColor(getRandomNumber(0, 255), getRandomNumber(0, 255), getRandomNumber(0, 255));
	ptr_new_figure->setVisibility(getRandomNumber(50, 255));
	push_back_shape<TFigure>(ptr_figures_mass, count_size_mass_figures, ptr_new_figure);
}

int getChoiceFigureForMethods(TFigure** ptr_figures_mass, int index_of_element)
{
	int choice_figure{};
	TCircle* ptr_circle{ dynamic_cast<TCircle*>(ptr_figures_mass[index_of_element]) };
	if (ptr_circle)
	{
		choice_figure = 0;
	}
	TEllipse* ptr_ellipse{ dynamic_cast<TEllipse*>(ptr_figures_mass[index_of_element]) };
	if (ptr_ellipse)
	{
		choice_figure = 1;
	}
	TQuadrilateral* ptr_quadrilateral{ dynamic_cast<TQuadrilateral*>(ptr_figures_mass[index_of_element]) };
	if (ptr_quadrilateral)
	{
		choice_figure = 2;
	}
	TRectangle* ptr_rectangle{ dynamic_cast<TRectangle*>(ptr_figures_mass[index_of_element]) };
	if (ptr_rectangle)
	{
		choice_figure = 3;
	}
	TRhombus* ptr_rhombus{ dynamic_cast<TRhombus*>(ptr_figures_mass[index_of_element]) };
	if (ptr_rhombus)
	{
		choice_figure = 4;
	}
	TTrapeze* ptr_trapeze{ dynamic_cast<TTrapeze*>(ptr_figures_mass[index_of_element]) };
	if (ptr_trapeze)
	{
		choice_figure = 5;
	}
	return choice_figure;
}

void move_figures_W(TFigure** ptr_figures_mass, int index_of_element)
{
	int choice_figure{ getChoiceFigureForMethods(ptr_figures_mass,index_of_element) };
	switch (choice_figure)
	{
	case 0:
	{
		TCircle* ptr_circle{ dynamic_cast<TCircle*>(ptr_figures_mass[index_of_element]) };
		if ((ptr_circle->getCoordinateY() - ptr_circle->getRadius() - 10) >= 115)
		{
			ptr_circle->MoveTo(0, -10);
		}
		break;
	}
	case 1:
	{
		TEllipse* ptr_ellipse{ dynamic_cast<TEllipse*>(ptr_figures_mass[index_of_element]) };
		if ((ptr_ellipse->getCoordinateY() - ptr_ellipse->getSemiMinorAxis() - 10) >= 115)
		{
			ptr_ellipse->MoveTo(0, -10);
		}
		break;
	}
	case 2:
	{
		TQuadrilateral* ptr_quadrilateral{ dynamic_cast<TQuadrilateral*>(ptr_figures_mass[index_of_element]) };
		if ((ptr_quadrilateral->getCoordinateY() - 10) >= 115 && (ptr_quadrilateral->getCoordinateY2() - 10) >= 115)
		{
			ptr_quadrilateral->MoveTo(0, -10);
			ptr_quadrilateral->changeCoordinateX234_Y234(0, -10);
		}
		break;
	}
	case 3:
	{
		TRectangle* ptr_rectangle{ dynamic_cast<TRectangle*>(ptr_figures_mass[index_of_element]) };
		if ((ptr_rectangle->getCoordinateY() - 10) >= 115)
		{
			ptr_rectangle->MoveTo(0, -10);
			ptr_rectangle->changeCoordinateX234_Y234(0, -10);
		}
		break;
	}
	case 4:
	{
		TRhombus* ptr_rhombus{ dynamic_cast<TRhombus*>(ptr_figures_mass[index_of_element]) };
		if ((ptr_rhombus->getCoordinateY2() - 10) >= 115)
		{
			ptr_rhombus->MoveTo(0, -10);
			ptr_rhombus->changeCoordinateX234_Y234(0, -10);
		}
		break;
	}
	case 5:
	{
		TTrapeze* ptr_trapeze{ dynamic_cast<TTrapeze*>(ptr_figures_mass[index_of_element]) };
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

void move_figures_A(TFigure** ptr_figures_mass, int index_of_element)
{
	int choice_figure{ getChoiceFigureForMethods(ptr_figures_mass,index_of_element) };
	switch (choice_figure)
	{
	case 0:
	{
		TCircle* ptr_circle{ dynamic_cast<TCircle*>(ptr_figures_mass[index_of_element]) };
		if ((ptr_circle->getCoordinateX() - ptr_circle->getRadius() - 10) >= 465)
		{
			ptr_circle->MoveTo(-10, 0);
		}
		break;
	}
	case 1:
	{
		TEllipse* ptr_ellipse{ dynamic_cast<TEllipse*>(ptr_figures_mass[index_of_element]) };
		if ((ptr_ellipse->getCoordinateX() - ptr_ellipse->getRadius() - 10) >= 465)
		{
			ptr_ellipse->MoveTo(-10, 0);
		}
		break;
	}
	case 2:
	{
		TQuadrilateral* ptr_quadrilateral{ dynamic_cast<TQuadrilateral*>(ptr_figures_mass[index_of_element]) };
		if ((ptr_quadrilateral->getCoordinateX() - 10) >= 465 && (ptr_quadrilateral->getCoordinateX4() - 10) >= 465)
		{
			ptr_quadrilateral->MoveTo(-10, 0);
			ptr_quadrilateral->changeCoordinateX234_Y234(-10, 0);
		}
		break;
	}
	case 3:
	{
		TRectangle* ptr_rectangle{ dynamic_cast<TRectangle*>(ptr_figures_mass[index_of_element]) };
		if ((ptr_rectangle->getCoordinateX() - 10) >= 465)
		{
			ptr_rectangle->MoveTo(-10, 0);
			ptr_rectangle->changeCoordinateX234_Y234(-10, 0);
		}
		break;
	}
	case 4:
	{
		TRhombus* ptr_rhombus{ dynamic_cast<TRhombus*>(ptr_figures_mass[index_of_element]) };
		if ((ptr_rhombus->getCoordinateX() - 10) >= 465)
		{
			ptr_rhombus->MoveTo(-10, 0);
			ptr_rhombus->changeCoordinateX234_Y234(-10, 0);
		}
		break;
	}
	case 5:
	{
		TTrapeze* ptr_trapeze{ dynamic_cast<TTrapeze*>(ptr_figures_mass[index_of_element]) };
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

void move_figures_S(TFigure** ptr_figures_mass, int index_of_element)
{
	int choice_figure{ getChoiceFigureForMethods(ptr_figures_mass,index_of_element) };
	switch (choice_figure)
	{
	case 0:
	{
		TCircle* ptr_circle{ dynamic_cast<TCircle*>(ptr_figures_mass[index_of_element]) };
		if (ptr_circle->getCoordinateY() + ptr_circle->getRadius() + 10 <= 715)
		{
			ptr_circle->MoveTo(0, 10);
		}
		break;
	}
	case 1:
	{
		TEllipse* ptr_ellipse{ dynamic_cast<TEllipse*>(ptr_figures_mass[index_of_element]) };
		if ((ptr_ellipse->getCoordinateY() + 10 + ptr_ellipse->getSemiMinorAxis()) <= 715)
		{
			ptr_ellipse->MoveTo(0, 10);
		}
		break;
	}
	case 2:
	{
		TQuadrilateral* ptr_quadrilateral{ dynamic_cast<TQuadrilateral*>(ptr_figures_mass[index_of_element]) };
		if ((ptr_quadrilateral->getCoordinateY3() + 10) <= 715 && (ptr_quadrilateral->getCoordinateY4() + 10) <= 715)
		{
			ptr_quadrilateral->MoveTo(0, 10);
			ptr_quadrilateral->changeCoordinateX234_Y234(0, 10);
		}
		break;
	}
	case 3:
	{
		TRectangle* ptr_rectangle{ dynamic_cast<TRectangle*>(ptr_figures_mass[index_of_element]) };
		if ((ptr_rectangle->getCoordinateY() + ptr_rectangle->getWidth() + 10) <= 715)
		{
			ptr_rectangle->MoveTo(0, 10);
			ptr_rectangle->changeCoordinateX234_Y234(0, 10);
		}
		break;
	}
	case 4:
	{
		TRhombus* ptr_rhombus{ dynamic_cast<TRhombus*>(ptr_figures_mass[index_of_element]) };
		if ((ptr_rhombus->getCoordinateY4() + 10) <= 715)
		{
			ptr_rhombus->MoveTo(0, 10);
			ptr_rhombus->changeCoordinateX234_Y234(0, 10);
		}
		break;
	}
	case 5:
	{
		TTrapeze* ptr_trapeze{ dynamic_cast<TTrapeze*>(ptr_figures_mass[index_of_element]) };
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

void move_figures_D(TFigure** ptr_figures_mass, int index_of_element)
{
	int choice_figure{ getChoiceFigureForMethods(ptr_figures_mass,index_of_element) };	
	switch (choice_figure)
	{
	case 0:
	{
		TCircle* ptr_circle{ dynamic_cast<TCircle*>(ptr_figures_mass[index_of_element]) };
		if (ptr_circle->getCoordinateX() + ptr_circle->getRadius() + 10 <= 1415)
		{
			ptr_circle->MoveTo(10, 0);
		}
		break;
	}
	case 1:
	{
		TEllipse* ptr_ellipse{ dynamic_cast<TEllipse*>(ptr_figures_mass[index_of_element]) };
		if ((ptr_ellipse->getCoordinateX() + 10 + ptr_ellipse->getRadius()) <= 1415)
		{
			ptr_ellipse->MoveTo(10, 0);
		}
		break;
	}
	case 2:
	{
		TQuadrilateral* ptr_quadrilateral{ dynamic_cast<TQuadrilateral*>(ptr_figures_mass[index_of_element]) };
		if ((ptr_quadrilateral->getCoordinateX2() + 10) <= 1415 && (ptr_quadrilateral->getCoordinateX3() + 10) <= 1415)
		{
			ptr_quadrilateral->MoveTo(10, 0);
			ptr_quadrilateral->changeCoordinateX234_Y234(10, 0);
		}
		break;
	}
	case 3:
	{
		TRectangle* ptr_rectangle{ dynamic_cast<TRectangle*>(ptr_figures_mass[index_of_element]) };
		if ((ptr_rectangle->getCoordinateX() + ptr_rectangle->getLength() + 10) <= 1415)
		{
			ptr_rectangle->MoveTo(10, 0);
			ptr_rectangle->changeCoordinateX234_Y234(10, 0);
		}
		break;
	}
	case 4:
	{
		TRhombus* ptr_rhombus{ dynamic_cast<TRhombus*>(ptr_figures_mass[index_of_element]) };
		if ((ptr_rhombus->getCoordinateX3() + 10) <= 1415)
		{
			ptr_rhombus->MoveTo(10, 0);
			ptr_rhombus->changeCoordinateX234_Y234(10, 0);
		}
		break;
	}
	case 5:
	{
		TTrapeze* ptr_trapeze{ dynamic_cast<TTrapeze*>(ptr_figures_mass[index_of_element]) };
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

void work_with_under_circle_hierarchy(TFigure** ptr_figures_mass, int count_size_mass_figures, sf::Event event_click)
{
	for (unsigned i{}; i < count_size_mass_figures;i++)
	{
		if (dynamic_cast<TCircle*>(ptr_figures_mass[i]) != nullptr)
		{
			TCircle* ptr_under_circle_hierarchy{ static_cast<TCircle*>(ptr_figures_mass[i]) };
			switch (event_click.key.code)
			{
			case sf::Keyboard::W:
			{
				move_figures_W(ptr_figures_mass, i);
				break;
			}
			case sf::Keyboard::A:
			{
				move_figures_A(ptr_figures_mass, i);
				break;
			}
			case sf::Keyboard::S:
			{

				move_figures_S(ptr_figures_mass, i);
				break;
			}
			case sf::Keyboard::D:
			{
				move_figures_D(ptr_figures_mass, i);
				break;
			}
			case sf::Keyboard::Q:
			{
				if ((ptr_under_circle_hierarchy->getRadius() - 1) >= 15)
				{
					ptr_under_circle_hierarchy->ChangeRadius(-1);
				}
				break;
			}
			case sf::Keyboard::E:
			{
				if (((ptr_under_circle_hierarchy->getCoordinateX() - ptr_under_circle_hierarchy->getRadius() - 1) >= 465 &&
					(ptr_under_circle_hierarchy->getCoordinateX() + ptr_under_circle_hierarchy->getRadius() + 1) <= 1415 &&
					(ptr_under_circle_hierarchy->getCoordinateY() - ptr_under_circle_hierarchy->getRadius() - 1) >= 115 &&
					(ptr_under_circle_hierarchy->getCoordinateY() + ptr_under_circle_hierarchy->getRadius() + 1) <= 715))
				{
					ptr_under_circle_hierarchy->ChangeRadius(1);
				}
				break;
			}
			default: 
			{
				break;
			}
			}
		}
	}
}

void work_with_under_quadrilateral_hierarchy(TFigure** ptr_figures_mass, int count_size_mass_figures, sf::Event event_click)
{
	for (unsigned i{}; i < count_size_mass_figures;i++)
	{
		if (dynamic_cast<TQuadrilateral*>(ptr_figures_mass[i]) != nullptr)
		{
			TQuadrilateral* ptr_under_quadrilateral_hierarchy{ static_cast<TQuadrilateral*>(ptr_figures_mass[i]) };
			switch (event_click.key.code)
			{
			case sf::Keyboard::W:
			{
				move_figures_W(ptr_figures_mass, i);
				break;
			}
			case sf::Keyboard::A:
			{
				move_figures_A(ptr_figures_mass, i);
				break;
			}
			case sf::Keyboard::S:
			{

				move_figures_S(ptr_figures_mass, i);
				break;
			}
			case sf::Keyboard::D:
			{
				move_figures_D(ptr_figures_mass, i);
				break;
			}
			default:
			{
				break;
			}
			}
		}
	}
}

void work_with_specific_class(TFigure** ptr_figures_mass, int count_size_mass_figures, int specific_counter, sf::Event event_click)
{
	switch (specific_counter % 4)
	{
	case 0:
	{
		for (unsigned i{}; i < count_size_mass_figures;i++)
		{
			TEllipse* ptr_ellipse{ dynamic_cast<TEllipse*>(ptr_figures_mass[i]) };
			if (ptr_ellipse)
			{
				switch (event_click.key.code)
				{
				case sf::Keyboard::W:
				{
					if ((ptr_ellipse->getCoordinateY() - ptr_ellipse->getSemiMinorAxis() - 10) >= 115)
					{
						ptr_ellipse->MoveTo(0, -10);
					}
					break;
				}
				case sf::Keyboard::A:
				{
					if ((ptr_ellipse->getCoordinateX() - ptr_ellipse->getRadius() - 10) >= 465)
					{
						ptr_ellipse->MoveTo(-10, 0);
					}
					break;
				}
				case sf::Keyboard::S:
				{
					if ((ptr_ellipse->getCoordinateY() + 10 + ptr_ellipse->getSemiMinorAxis()) <= 715)
					{
						ptr_ellipse->MoveTo(0, 10);
					}
					break;
				}
				case sf::Keyboard::D:
				{
					if ((ptr_ellipse->getCoordinateX() + 10 + ptr_ellipse->getRadius()) <= 1415)
					{
						ptr_ellipse->MoveTo(10, 0);
					}
					break;
				}
				case sf::Keyboard::E:
				{
					if (((ptr_ellipse->getCoordinateY() - ptr_ellipse->getSemiMinorAxis() - 1) >= 115 &&
						(ptr_ellipse->getCoordinateY() + ptr_ellipse->getSemiMinorAxis() + 1) <= 715))
					{
						ptr_ellipse->changeSemiMinorAxis(1);
					}
					break;
				}
				case sf::Keyboard::Q:
				{
					if ((ptr_ellipse->getSemiMinorAxis() - 1) >= 15)
					{
						ptr_ellipse->changeSemiMinorAxis(-1);
					}
					break;
				}
				case sf::Keyboard::C:
				{
					if ((ptr_ellipse->getCoordinateX() - ptr_ellipse->getRadius() - 1) >= 465 && (ptr_ellipse->getCoordinateX() +
						ptr_ellipse->getRadius() + 1) <= 1415)
					{
						ptr_ellipse->ChangeRadius(1);
					}
					break;
				}
				case sf::Keyboard::Z:
				{
					if (ptr_ellipse->getRadius() - 1 >= 40)
					{
						ptr_ellipse->ChangeRadius(-1);
					}
					break;
				}
				case sf::Keyboard::R:
				{
					if ((ptr_ellipse->getCoordinateY() - ptr_ellipse->getRadius()) >= 115 &&
						(ptr_ellipse->getCoordinateY() + ptr_ellipse->getRadius()) <= 715 &&
						(ptr_ellipse->getCoordinateX() - ptr_ellipse->getSemiMinorAxis()) >= 465 &&
						(ptr_ellipse->getCoordinateX() + ptr_ellipse->getSemiMinorAxis()) <= 1415)
					{
						ptr_ellipse->Rotate90degrees();
					}
					break;
				}
				default:
				{
					break;
				}
				}
			}
		}
		break;
	}
	case 1:
	{
		for (unsigned i{}; i < count_size_mass_figures;i++)
		{
			TRectangle* ptr_rectangle{ dynamic_cast<TRectangle*>(ptr_figures_mass[i]) };
			if (ptr_rectangle)
			{
				switch (event_click.key.code)
				{
				case sf::Keyboard::W:
				{
					if ((ptr_rectangle->getCoordinateY() - 10) >= 115)
					{
						ptr_rectangle->MoveTo(0, -10);
						ptr_rectangle->changeCoordinateX234_Y234(0, -10);
					}
					break;
				}
				case sf::Keyboard::A:
				{
					if ((ptr_rectangle->getCoordinateX() - 10) >= 465)
					{
						ptr_rectangle->MoveTo(-10, 0);
						ptr_rectangle->changeCoordinateX234_Y234(-10, 0);
					}
					break;
				}
				case sf::Keyboard::S:
				{
					if ((ptr_rectangle->getCoordinateY() + ptr_rectangle->getWidth() + 10) <= 715)
					{
						ptr_rectangle->MoveTo(0, 10);
						ptr_rectangle->changeCoordinateX234_Y234(0, 10);
					}
					break;
				}
				case sf::Keyboard::D:
				{
					if ((ptr_rectangle->getCoordinateX() + ptr_rectangle->getLength() + 10) <= 1415)
					{
						ptr_rectangle->MoveTo(10, 0);
						ptr_rectangle->changeCoordinateX234_Y234(10, 0);
					}
					break;
				}
				case sf::Keyboard::E:
				{
					if ((ptr_rectangle->getCoordinateX() + ptr_rectangle->getLength() + 1) <= 1415)
						ptr_rectangle->changeLength(1);
					break;
				}
				case sf::Keyboard::Q:
				{
					if ((ptr_rectangle->getLength() - 1) >= 30)
						ptr_rectangle->changeLength(-1);
					break;
				}
				case sf::Keyboard::C:
				{
					if ((ptr_rectangle->getCoordinateY() + ptr_rectangle->getWidth() + 1) <= 715)
						ptr_rectangle->changeWidth(1);
					break;
				}
				case sf::Keyboard::Z:
				{
					if ((ptr_rectangle->getWidth() - 1) >= 30)
						ptr_rectangle->changeWidth(-1);
					break;
				}
				default:
				{
					break;
				}
				}
			}
		}
		break;
	}
	case 2:
	{
		for (unsigned i{}; i < count_size_mass_figures;i++)
		{
			TTrapeze* ptr_trapeze{ dynamic_cast<TTrapeze*>(ptr_figures_mass[i]) };
			if (ptr_trapeze)
			{
				switch (event_click.key.code)
				{
				case sf::Keyboard::W:
				{
					if ((ptr_trapeze->getCoordinateY2() - 10) >= 115 &&
						(ptr_trapeze->getCoordinateY3() - 10) >= 115)
					{
						ptr_trapeze->MoveTo(0, -10);
						ptr_trapeze->changeCoordinateX234_Y234(0, -10);
					}
					break;
				}
				case sf::Keyboard::A:
				{
					if ((ptr_trapeze->getCoordinateX() - 10) >= 465)
					{
						ptr_trapeze->MoveTo(-10, 0);
						ptr_trapeze->changeCoordinateX234_Y234(-10, 0);
					}
					break;
				}
				case sf::Keyboard::S:
				{
					if ((ptr_trapeze->getCoordinateY() + 10) <= 715 &&
						(ptr_trapeze->getCoordinateY4() + 10) <= 715)
					{
						ptr_trapeze->MoveTo(0, 10);
						ptr_trapeze->changeCoordinateX234_Y234(0, 10);
					}
					break;
				}
				case sf::Keyboard::D:
				{
					if ((ptr_trapeze->getCoordinateX4() + 10) <= 1415 &&
						(ptr_trapeze->getCoordinateX3() + 10) <= 1415)
					{
						ptr_trapeze->MoveTo(10, 0);
						ptr_trapeze->changeCoordinateX234_Y234(10, 0);
					}
					break;
				}
				case sf::Keyboard::E:
				{
					if (ptr_trapeze->getCoordinateX3() <= ptr_trapeze->getCoordinateX4())
					{
						ptr_trapeze->changeTopBase(1);
					}
					break;
				}
				case sf::Keyboard::Q:
				{
					if ((ptr_trapeze->getCoordinateX4() - ptr_trapeze->getCoordinateX3() - 1 <= 50))
					{
						ptr_trapeze->changeTopBase(-1);
					}
					break;
				}
				case sf::Keyboard::C:
				{
					if ((ptr_trapeze->getCoordinateX4() + 1) <= 1415 && (ptr_trapeze->getCoordinateX4() + 1) <= (ptr_trapeze->getCoordinateX3() + 60))
					{
						ptr_trapeze->changeBottomBase(1);
					}
					break;
				}
				case sf::Keyboard::Z:
				{
					if ((ptr_trapeze->getCoordinateX4() - 1 >= ptr_trapeze->getCoordinateX3()))
					{
						ptr_trapeze->changeBottomBase(-1);
					}
					break;
				}
				case sf::Keyboard::F:
				{
					if ((ptr_trapeze->getCoordinateY2() - 1) >= 115 && (ptr_trapeze->getCoordinateY() - ptr_trapeze->getCoordinateY2() + 1) <= 100)
					{
						ptr_trapeze->changeHeight(-1);
					}
					break;
				}
				case sf::Keyboard::R:
				{
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
		}
		break;
	}
	case 3:
	{
		for (unsigned i{}; i < count_size_mass_figures;i++)
		{
			TRhombus* ptr_rhombus{ dynamic_cast<TRhombus*>(ptr_figures_mass[i]) };
			if (ptr_rhombus)
			{
				switch (event_click.key.code)
				{
				case sf::Keyboard::W:
				{
					if ((ptr_rhombus->getCoordinateY2() - 10) >= 115)
					{
						ptr_rhombus->MoveTo(0, -10);
						ptr_rhombus->changeCoordinateX234_Y234(0, -10);
					}
					break;
				}
				case sf::Keyboard::A:
				{
					if ((ptr_rhombus->getCoordinateX() - 10) >= 465)
					{
						ptr_rhombus->MoveTo(-10, 0);
						ptr_rhombus->changeCoordinateX234_Y234(-10, 0);
					}
					break;
				}
				case sf::Keyboard::S:
				{
					if ((ptr_rhombus->getCoordinateY4() + 10) <= 715)
					{
						ptr_rhombus->MoveTo(0, 10);
						ptr_rhombus->changeCoordinateX234_Y234(0, 10);
					}
					break;
				}
				case sf::Keyboard::D:
				{
					if ((ptr_rhombus->getCoordinateX3() + 10) <= 1415)
					{
						ptr_rhombus->MoveTo(10, 0);
						ptr_rhombus->changeCoordinateX234_Y234(10, 0);
					}
					break;
				}
				case sf::Keyboard::E:
				{
					if ((ptr_rhombus->getDegree() + 1 <= 60) && ptr_rhombus->getCoordinateY2() >= 115 &&
						ptr_rhombus->getCoordinateY4() <= 715)
					{
						ptr_rhombus->changeDegree(1);
					}
					break;
				}
				case sf::Keyboard::Q:
				{
					if ((ptr_rhombus->getDegree() - 1 >= 15) && ptr_rhombus->getCoordinateX3() <= 1415)
					{
						ptr_rhombus->changeDegree(-1);
					}
					break;
				}
				case sf::Keyboard::C:
				{
					if ((ptr_rhombus->getCoordinateY2() >= 115) && ptr_rhombus->getCoordinateY4() <= 715 &&
						ptr_rhombus->getCoordinateX3() <= 1415)
					{
						ptr_rhombus->changeLength(1);
					}
					break;
				}
				case sf::Keyboard::Z:
				{
					if ((ptr_rhombus->getLength() - 1 >= 30))
					{
						ptr_rhombus->changeLength(-1);
					}
					break;
				}
				default:
				{
					break;
				}
				}
			}
		}
		break;
	}
	default:
	{
		break;
	}
	}
}

int stage_1_work_with_mass(sf::RenderWindow& window)
{
	/*Кнопка Array of polymorphic pointers*/
	User_Text_Button use_array_text_button{ "Comic_Sans_MS.TTF", "Array of polymorphic pointers", 28, 15, 15 };
	User_Rect_Button use_array_rect_button{ 10, 10, 5, 435, 60 };

	/*Кнопка Create array*/
	User_Text_Button create_array_text_button{ "Comic_Sans_MS.TTF", "Create array", 25, 20, 110 };
	User_Rect_Button create_array_rect_button{ 10, 100, 5, 200, 60 };

	/*Кнопка Destroy array*/
	User_Text_Button delete_array_text_button{ "Comic_Sans_MS.TTF", "Delete array", 25, 20, 200 };
	User_Rect_Button delete_array_rect_button{ 10, 190, 5, 200, 60 };

	/*Кнопка Erase*/
	User_Text_Button erase_text_button{ "Comic_Sans_MS.TTF", "Erase", 25, 60, 295 };
	User_Rect_Button erase_rect_button{ 10, 280, 5, 200, 60 };

	/*Кнопка Show*/
	User_Text_Button show_text_button{ "Comic_Sans_MS.TTF", "Show", 25, 60, 385 };
	User_Rect_Button show_rect_button{ 10, 370, 5, 200, 60 };

	/*Кнопка Move*/
	User_Text_Button move_text_button{ "Comic_Sans_MS.TTF", "Move", 25, 60, 475 };
	User_Rect_Button move_rect_button{ 10, 460, 5, 200, 60 };

	/*Текст IMAGE*/
	User_Text_Button image_text{ "Comic_Sans_MS.TTF", "Image", 60, 850, 10 };
	User_Rect_Button image_rect{ 465, 115, 0, 950, 600 }; image_rect.m_setColor(178, 143, 252);

	/*Кнопка BACK*/
	User_Text_Button back_text_button{ "Comic_Sans_MS.TTF", "Back", 28, 1350, 740 };
	User_Rect_Button back_rect_button{ 1290, 730, 5, 200, 60 };

	/*Кнопка under circle hierarchy*/
	User_Text_Button circle_hierarchy_text_button{ "Comic_Sans_MS.TTF", "Under circle hierarchy", 28, 20, 560 };
	User_Rect_Button circle_hierarchy_rect_button{ 10, 550, 5, 440, 60 };

	/*Кнопка under quadrilateral hierarchy*/
	User_Text_Button quadrilateral_hierarchy_text_button{ "Comic_Sans_MS.TTF", "Under quadrilateral hierarchy", 28, 20, 650 };
	User_Rect_Button quadrilateral_hierarchy_rect_button{ 10, 640, 5, 440, 60 };

	/*Текст выбора конкретного класса*/
	User_Text_Button switch_mode_text{ "Comic_Sans_MS.TTF", "M - switch mode of work with class: ", 20, 20, 720 };

	/*Текст выбора конкретного класса*/
	User_Text_Button select_specific_class_text{ "Comic_Sans_MS.TTF", "Space - select a specific class: ", 20, 20, 750 };

	/*Текст выборанного режима*/
	User_Text_Button usually_mode_text{ "Comic_Sans_MS.TTF", "Usually ", 20, 410, 720 };
	User_Text_Button specific_mode_text{ "Comic_Sans_MS.TTF", "Specific ", 20, 410, 720 };

	/*Текст выборанного режима*/
	User_Text_Button ellipse_text{ "Comic_Sans_MS.TTF", "Ellipse ", 20, 410, 750 };
	User_Text_Button rectangle_text{ "Comic_Sans_MS.TTF", "Rectangle ", 20, 410, 750 };
	User_Text_Button rhombus_text{ "Comic_Sans_MS.TTF", "Rhombus ", 20, 410, 750 };
	User_Text_Button trapeze_text{ "Comic_Sans_MS.TTF", "Trapeze ", 20, 410, 750 };

	//Тексты управления фигурами
	User_Text_Button move_shapes{ "Comic_Sans_MS.TTF", "Move up shape (W)    Move down shape (S)   Move left shape (A)    Move right shape (D)", 15, 500, 770 };
	User_Text_Button special_movement_circle{ "Comic_Sans_MS.TTF", "Decrease radius(Q)           Increase radius(E)", 15, 500, 730 };
	User_Text_Button special_movement_ellipse{ "Comic_Sans_MS.TTF",
		"Decrease vertical axis(Q) Increase vertical axis(E) Rotate90degrees (R)\n Decrease horizontal axis(Z) Increase horizontal axis(C)", 15, 500, 730 };
	User_Text_Button special_movement_rectangle{ "Comic_Sans_MS.TTF", "Decrease length(Q)    Increase length(E)    Decrease width(Z)    Increase width(C)", 15, 500, 730 };
	User_Text_Button special_movement_trapeze{ "Comic_Sans_MS.TTF",
		"Decrease top base length(Q) Increase top base length(E) Decrease bottom base length(Z) \n Increase bottom base length(C) Decrease height(R) Increase height(F)",
		15, 500, 715 };
	User_Text_Button special_movement_rhombus{ "Comic_Sans_MS.TTF", "Decrease degree(Q)  Increase degree(E)  Decrease length of side(Z)  Increase length of side(C)", 15, 500, 730 };

	int is_stage{};

	//Работа с полиморфным массивом указателей класса TFigure
	int count_size_mass_figures{}; //кол-во элементов в массиве
	TFigure** ptr_figures_mass = new TFigure * [count_size_mass_figures]; //массив фигур

	//Вспомогательные переменные для регулирования работы программы
	bool submenu_array{ false }; //развернуть или нет подменю массива
	bool draw_figures{ true }; //рисовать фигуры или нет
	bool move_figures{ false }; //перемещать фигуры или нет
	bool under_circle_hierarchy{ false }; //работа с подиерархией окружностей или нет
	bool under_quadrilateral_hierarchy{ false }; //работа с подиерархией четырехугольников или нет
	int specific_counter{ -1 }; //счетчик для определения возможности работы с конкретным классом
	bool specific_work{false}; //работать со всеми классами или с определенными

	while (window.isOpen())
	{
		is_stage = 0;
		window.clear(sf::Color(137, 20, 190));

		if (submenu_array) use_array_rect_button.m_setOutlineColor(247, 30, 241);
		else use_array_rect_button.m_setOutlineColorDefault();
		use_array_text_button.m_setFillColorDefault();

		create_array_rect_button.m_setOutlineColorDefault(); create_array_text_button.m_setFillColorDefault();
		delete_array_rect_button.m_setOutlineColorDefault(); delete_array_text_button.m_setFillColorDefault();

		if (!draw_figures) erase_rect_button.m_setOutlineColor(247, 30, 241);
		else erase_rect_button.m_setOutlineColorDefault();
		erase_text_button.m_setFillColorDefault();

		if (draw_figures && count_size_mass_figures != 0) show_rect_button.m_setOutlineColor(247, 30, 241);
		else show_rect_button.m_setOutlineColorDefault();
		show_text_button.m_setFillColorDefault();

		if (move_figures)move_rect_button.m_setOutlineColor(247, 30, 241);
		else move_rect_button.m_setOutlineColorDefault(); 
		move_text_button.m_setFillColorDefault();

		back_rect_button.m_setOutlineColorDefault(); back_text_button.m_setFillColorDefault();

		if (under_circle_hierarchy) circle_hierarchy_rect_button.m_setOutlineColor(247, 30, 241);
		else circle_hierarchy_rect_button.m_setOutlineColorDefault(); 
		circle_hierarchy_text_button.m_setFillColorDefault();

		if (under_quadrilateral_hierarchy) quadrilateral_hierarchy_rect_button.m_setOutlineColor(241, 30, 241);
		else quadrilateral_hierarchy_rect_button.m_setOutlineColorDefault(); 
		quadrilateral_hierarchy_text_button.m_setFillColorDefault();

		if (sf::IntRect(5, 0, 445, 80).contains(sf::Mouse::getPosition(window))) //array tab
		{
			use_array_rect_button.m_setOutlineColor(165, 15, 203);
			use_array_text_button.m_setFillColor(255, 127, 39);
			is_stage = 1;
		}

		if (sf::IntRect(5, 90, 210, 80).contains(sf::Mouse::getPosition(window))) //create
		{
			create_array_rect_button.m_setOutlineColor(165, 15, 203);
			create_array_text_button.m_setFillColor(255, 127, 39);
			is_stage = 2;
		}

		if (sf::IntRect(5, 180, 210, 80).contains(sf::Mouse::getPosition(window))) //destroy
		{
			delete_array_rect_button.m_setOutlineColor(165, 15, 203);
			delete_array_text_button.m_setFillColor(255, 127, 39);
			is_stage = 3;
		}

		if (sf::IntRect(5, 270, 210, 80).contains(sf::Mouse::getPosition(window))) //erase
		{
			erase_rect_button.m_setOutlineColor(165, 15, 203);
			erase_text_button.m_setFillColor(255, 127, 39);
			is_stage = 4;
		}

		if (sf::IntRect(5, 360, 210, 80).contains(sf::Mouse::getPosition(window))) //show
		{
			show_rect_button.m_setOutlineColor(165, 15, 203);
			show_text_button.m_setFillColor(255, 127, 39);
			is_stage = 5;
		}

		if (sf::IntRect(5, 450, 210, 80).contains(sf::Mouse::getPosition(window))) //move
		{
			move_rect_button.m_setOutlineColor(165, 15, 203);
			move_text_button.m_setFillColor(255, 127, 39);
			is_stage = 6;
		}

		if (sf::IntRect(1285, 720, 210, 80).contains(sf::Mouse::getPosition(window))) //back
		{
			back_rect_button.m_setOutlineColor(165, 15, 203);
			back_text_button.m_setFillColor(255, 127, 39);
			is_stage = 7;
		}

		if (sf::IntRect(5, 540, 450, 80).contains(sf::Mouse::getPosition(window))) //under circle hierarchy
		{
			circle_hierarchy_rect_button.m_setOutlineColor(165, 15, 203);
			circle_hierarchy_text_button.m_setFillColor(255, 127, 39);
			is_stage = 8;
		}

		if (sf::IntRect(5, 630, 450, 80).contains(sf::Mouse::getPosition(window))) //under quadrilateral hierarchy
		{
			quadrilateral_hierarchy_rect_button.m_setOutlineColor(165, 15, 203);
			quadrilateral_hierarchy_text_button.m_setFillColor(255, 127, 39);
			is_stage = 9;
		}

		sf::Event event_click;
		while (window.pollEvent(event_click))
		{
			if (event_click.type == sf::Event::Closed)
			{
				delete_mass_objects<TFigure>(ptr_figures_mass, count_size_mass_figures);
				std::cout << "Все массивы примитивов были удалены из кучи. Окно закрыто." << std::endl;
				window.close();
				return 0;
			}
			else if (event_click.type == event_click.MouseButtonReleased && event_click.mouseButton.button == sf::Mouse::Left)
			{
				//sf::Vector2i position = sf::Mouse::getPosition(window);
				//std::cout << position.x << "\t" << position.y << std::endl;

				if (is_stage == 1)
				{
					submenu_array = !submenu_array;
					if (submenu_array) std::cout << "Возможности полиморфного класса для демонстрации возможнотей стали доступны." << std::endl;
					else std::cout << "Возможности полиморфного класса для демонстрации возможнотей были закрыты." << std::endl;
				}
				if (is_stage == 2 && count_size_mass_figures == 0)
				{
					int iterator_for_mass{ static_cast<int>(getRandomNumber(20, 30)) };
					for (unsigned i{};i < iterator_for_mass;i++)
					{
						int choice_figure{ static_cast<int>(getRandomNumber(0, 5)) };
						switch (choice_figure)
						{
						case 0:
						{
							AddCircleToMass(ptr_figures_mass, count_size_mass_figures);
							break;
						}
						case 1:
						{
							AddEllipseToMass(ptr_figures_mass, count_size_mass_figures);
							break;
						}
						case 2:
						{
							AddQuadrilateralToMass(ptr_figures_mass, count_size_mass_figures);
							break;
						}
						case 3:
						{
							AddRectangleToMass(ptr_figures_mass, count_size_mass_figures);
							break;
						}
						case 4:
						{
							AddRhombusToMass(ptr_figures_mass, count_size_mass_figures);
							break;
						}
						case 5:
						{
							AddTrapezeToMass(ptr_figures_mass, count_size_mass_figures);
							break;
						}
						default:
						{
							break;
						}
						}
					}
					std::cout << "Массив полиморфных указателей был создан со случайными объектами, созданными конструкторами со случайными параметрами." << std::endl;
					std::cout << "На экране находится " << count_size_mass_figures << "объектов(-а)." << std::endl;
				}
				if (is_stage == 3 && draw_figures && count_size_mass_figures != 0)
				{
					int iterator_for_mass{ count_size_mass_figures };
					for (unsigned i{}; i < iterator_for_mass;i++)
					{
						int choice_figure{ getChoiceFigureForMethods(ptr_figures_mass, count_size_mass_figures - 1) };
						switch (choice_figure)
						{
						case 0:
						{
							TCircle* ptr_circle{ dynamic_cast<TCircle*>(ptr_figures_mass[count_size_mass_figures - 1]) };
							ptr_circle->Free(ptr_figures_mass, count_size_mass_figures);
							break;
						}
						case 1:
						{
							TEllipse* ptr_ellipse{ dynamic_cast<TEllipse*>(ptr_figures_mass[count_size_mass_figures - 1]) };
							ptr_ellipse->Free(ptr_figures_mass, count_size_mass_figures);
							break;
						}
						case 2:
						{
							TQuadrilateral* ptr_quadrilateral{ dynamic_cast<TQuadrilateral*>(ptr_figures_mass[count_size_mass_figures - 1]) };
							ptr_quadrilateral->Free(ptr_figures_mass, count_size_mass_figures);
							break;
						}
						case 3:
						{
							TRectangle* ptr_rectangle{ dynamic_cast<TRectangle*>(ptr_figures_mass[count_size_mass_figures - 1]) };
							ptr_rectangle->Free(ptr_figures_mass, count_size_mass_figures);
							break;
						}
						case 4:
						{
							TRhombus* ptr_rhombus{ dynamic_cast<TRhombus*>(ptr_figures_mass[count_size_mass_figures - 1]) };
							ptr_rhombus->Free(ptr_figures_mass, count_size_mass_figures);
							break;
						}
						case 5:
						{
							TTrapeze* ptr_trapeze{ dynamic_cast<TTrapeze*>(ptr_figures_mass[count_size_mass_figures - 1]) };
							ptr_trapeze->Free(ptr_figures_mass, count_size_mass_figures);
							break;
						}
						default:
						{
							break;
						}
						}
					}
					delete_elements_shape<TFigure>(ptr_figures_mass, count_size_mass_figures);
					std::cout << "Массив полиморфных указателей был очищен." << std::endl;
				};
				if (is_stage == 4 && draw_figures && count_size_mass_figures != 0)
				{
					draw_figures = !draw_figures;
					std::cout << "Фигуры в массиве были стерты." << std::endl;
					if (move_figures)
					{
						std::cout << "Возможность передвижения фигур была выключена." << std::endl;
						move_figures = !move_figures;
					}
					
				}
				if (is_stage == 5 && !draw_figures)
				{
					draw_figures = !draw_figures;
					std::cout << "Фигуры массива были показаны на экране." << std::endl;
				}
				if (is_stage == 6 && draw_figures && count_size_mass_figures != 0)
				{
					move_figures = !move_figures;
					if (move_figures) std::cout << "Возможность передвижения фигур была включена." << std::endl;
					else std::cout << "Возможность передвижения фигур была выключена." << std::endl;
				}
				if (is_stage == 7)
				{
					std::cout << "Вы вернулись в MENU" << std::endl;
					return 0;
				}
				if (is_stage == 8 && draw_figures && !specific_work)
				{
					under_circle_hierarchy = !under_circle_hierarchy;
					under_quadrilateral_hierarchy = false;
					std::cout << "Была выбрана работа с подиерархией окружностей. Работа с подиерархией четырехугольников была выключена." << std::endl;
				}
				if (is_stage == 9 && draw_figures && !specific_work)
				{
					under_quadrilateral_hierarchy = !under_quadrilateral_hierarchy;
					under_circle_hierarchy = false;
					std::cout << "Была выбрана работа с подиерархией четырехугольников. Работа с подиерархией окружнсотей была выключена." << std::endl;
				}
			}
			else if (event_click.type == sf::Event::KeyPressed && move_figures)
			{
				//sf::Vector2i position = sf::Mouse::getPosition(window);
				//std::cout << position.x << "\t" << position.y << std::endl;
				if (event_click.key.code == sf::Keyboard::M)
				{
					specific_work = !specific_work;
					if (under_circle_hierarchy) under_circle_hierarchy = false;
					if (under_quadrilateral_hierarchy) under_quadrilateral_hierarchy = false;
				}
				else if (!under_circle_hierarchy && !under_quadrilateral_hierarchy && !specific_work)
				{
					switch (event_click.key.code)
					{
					case sf::Keyboard::W:
					{
						for (unsigned i{}; i < count_size_mass_figures;i++)
						{
							move_figures_W(ptr_figures_mass, i);
						}
						break;
					}
					case sf::Keyboard::A:
					{
						for (unsigned i{}; i < count_size_mass_figures;i++)
						{
							move_figures_A(ptr_figures_mass, i);
						}
						break;
					}
					case sf::Keyboard::S:
					{
						for (unsigned i{}; i < count_size_mass_figures;i++)
						{
							move_figures_S(ptr_figures_mass, i);
						}
						break;
					}
					case sf::Keyboard::D:
					{
						for (unsigned i{}; i < count_size_mass_figures;i++)
						{
							move_figures_D(ptr_figures_mass, i);
						}
						break;
					}
					default:
					{
						break;
					}
					}
				}
				else if (under_circle_hierarchy && !specific_work)
				{
					work_with_under_circle_hierarchy(ptr_figures_mass, count_size_mass_figures, event_click);
				}
				else if (under_quadrilateral_hierarchy && !specific_work)
				{
					work_with_under_quadrilateral_hierarchy(ptr_figures_mass, count_size_mass_figures, event_click);
				}
				else if (event_click.key.code == sf::Keyboard::Space && specific_work)
				{
					specific_counter += 1;
				}
				else if (specific_work)
				{
					work_with_specific_class(ptr_figures_mass, count_size_mass_figures, specific_counter, event_click);
				}
			}
		}

		use_array_rect_button.Show(window); use_array_text_button.Show(window);
		if (submenu_array)
		{
			create_array_rect_button.Show(window); create_array_text_button.Show(window);
			delete_array_rect_button.Show(window); delete_array_text_button.Show(window);
			erase_rect_button.Show(window); erase_text_button.Show(window);
			show_rect_button.Show(window); show_text_button.Show(window);
			move_rect_button.Show(window); move_text_button.Show(window);
		}
		back_rect_button.Show(window); back_text_button.Show(window);
		image_rect.Show(window); image_text.Show(window);
		switch_mode_text.Show(window);
		select_specific_class_text.Show(window);
		move_shapes.Show(window);

		if (count_size_mass_figures != 0)
		{
			circle_hierarchy_rect_button.Show(window); circle_hierarchy_text_button.Show(window);
			quadrilateral_hierarchy_rect_button.Show(window); quadrilateral_hierarchy_text_button.Show(window);
		}

		if (under_circle_hierarchy)
		{
			special_movement_circle.Show(window);
		}
		
		if (specific_work)
		{
			switch (specific_counter % 4)
			{
			case 0:
				special_movement_ellipse.Show(window);
				ellipse_text.Show(window);
				break;
			case 1:
				special_movement_rectangle.Show(window);
				rectangle_text.Show(window);
				break;
			case 2:
				special_movement_trapeze.Show(window);
				trapeze_text.Show(window);
				break;
			case 3:
				special_movement_rhombus.Show(window);
				rhombus_text.Show(window);
				break;
			default:
				break;
			}
		}

		if (specific_work) specific_mode_text.Show(window);
		else usually_mode_text.Show(window);

		if (draw_figures)
		{
			for (unsigned i{}; i < count_size_mass_figures;i++)
			{
				ptr_figures_mass[i]->Show(window);
			}
		}

		window.display();
	}
	return 0;
}


bool stage_0_menu(sf::RenderWindow& window)
{
	std::cout << "Нажмите MENU или выйдите из программы." << std::endl;
	int is_stage{};

	/*Кнопка меню*/
	//Текст MENU
	User_Text_Button menu_text{ "Comic_Sans_MS.TTF", "MENU", 50, 685, 340 };
	//Прямоугольник MENU
	User_Rect_Button menu_rect{ 625, 330, 5, 300, 80 };

	/*Кнопка выход*/
	//Текст EXIT
	User_Text_Button exit_text{ "Comic_Sans_MS.TTF", "EXIT", 50, 685, 440 };
	//Прямоугольник EXIT
	User_Rect_Button exit_rect{ 625, 430, 5, 300, 80 };

	while (window.isOpen())
	{
		//Переменная для перехода между меню и подменю
		is_stage = 0;

		window.clear(sf::Color(137, 20, 190));
		menu_text.m_setFillColorDefault(); menu_rect.m_setOutlineColorDefault();
		exit_text.m_setFillColorDefault(); exit_rect.m_setOutlineColorDefault();

		if (sf::IntRect(610, 320, 320, 100).contains(sf::Mouse::getPosition(window)))
		{
			menu_text.m_setFillColor(255, 127, 39);
			menu_rect.m_setOutlineColor(165, 15, 203);
			is_stage = 1;
		}

		if (sf::IntRect(610, 420, 320, 100).contains(sf::Mouse::getPosition(window)))
		{
			exit_text.m_setFillColor(255, 127, 39);
			exit_rect.m_setOutlineColor(165, 15, 203);
			is_stage = 2;
		}

		sf::Event event_click;
		while (window.pollEvent(event_click))
		{
			if (event_click.type == event_click.MouseButtonReleased && event_click.mouseButton.button == sf::Mouse::Left && is_stage == 1)
			{
				std::cout << "Вы перешли в функциональную часть программы." << std::endl;
				stage_1_work_with_mass(window);
			}
			if (event_click.type == event_click.MouseButtonReleased && event_click.mouseButton.button == sf::Mouse::Left && is_stage == 2)
			{
				std::cout << "Вы вышли из программы. Окно закрыто." << std::endl;
				window.close();
			}
			else if (event_click.type == sf::Event::Closed)
			{
				std::cout << "Окно было закрыто." << std::endl;
				window.close();
			}
		};

		menu_rect.Show(window); menu_text.Show(window);
		exit_rect.Show(window); exit_text.Show(window);

		window.display();
	}

	return false;
}

