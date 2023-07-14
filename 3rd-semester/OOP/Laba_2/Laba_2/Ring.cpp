#include <SFML/Graphics.hpp>

#include "Circle.h"
#include "Ring.h"

Ring::Ring()
{
	m_inner_circle.changeRadius(-10);
	m_inner_circle.setColor(178, 143, 252);
	std::cout << "Объект-кольцо был успешно создан." << std::endl;
}

Ring::Ring(Circle inner_circle, Circle outer_circle)
	:m_inner_circle{ inner_circle }, m_outer_circle{ outer_circle }
{
	std::cout << "Объект-кольцо был успешно создан." << std::endl;
}

void Ring::Show(sf::RenderWindow& window)
{
	m_outer_circle.Show(window);
	m_inner_circle.Show(window);
}

void Ring::MoveTo(float change_base_point_coordinate_x, float change_base_point_coordinate_y)
{
	m_outer_circle.MoveTo(change_base_point_coordinate_x, change_base_point_coordinate_y);
	m_inner_circle.MoveTo(change_base_point_coordinate_x, change_base_point_coordinate_y);
}

Circle& Ring::getInnerCircle()
{
	return m_inner_circle;
}

Circle& Ring::getOuterCircle()
{
	return m_outer_circle;
}
Ring::~Ring()
{
	//std::cout << "Объект-кольцо был уничтожен." << std::endl;
}