#include <SFML/Graphics.hpp>

#include "MyFuncs.h"
#include "Circle.h"
#include "Point2D.h"

Circle::Circle()
	: m_radius{ 50 },
	m_OutlineThickness{ 5 },
	m_red{ 180 },
	m_green{ 68 },
	m_blue{ 212 },
	m_r_color{ 233 },
	m_g_color{ 179 },
	m_b_color{ 248 },
	m_visibility{ 255 },
	m_basepoint{ 700, 400 }
{
	std::cout << "Объект-окружность был успешно создан." << std::endl;
}

Circle::Circle(float radius, Point2D basepoint)
	:m_radius{ radius }, m_basepoint{ basepoint }
{
	while (m_basepoint.getCoordinateX_Point() - m_radius < 465 || m_basepoint.getCoordinateX_Point() + m_radius > 1415 ||
		m_basepoint.getCoordinateY_Point() - m_radius < 115 || m_basepoint.getCoordinateY_Point() + m_radius > 715)
	{
		m_radius -= 1;
	}
	std::cout << "Объект-окружность был успешно создан." << std::endl;
}

void Circle::Show(sf::RenderWindow& window)
{
	shape_circle.setRadius(m_radius);
	shape_circle.setFillColor(sf::Color(m_r_color, m_g_color, m_b_color, m_visibility));
	shape_circle.setOutlineThickness(m_OutlineThickness);
	shape_circle.setOutlineColor(sf::Color(m_red, m_green, m_blue));
	shape_circle.setPosition(m_basepoint.getCoordinateX_Point() - m_radius, m_basepoint.getCoordinateY_Point() - m_radius);
	window.draw(shape_circle);
}

void Circle::MoveTo(float change_base_point_coordinate_x, float change_base_point_coordinate_y)
{
	m_basepoint.setCoordinateX_Point(m_basepoint.getCoordinateX_Point() + change_base_point_coordinate_x);
	m_basepoint.setCoordinateY_Point(m_basepoint.getCoordinateY_Point() + change_base_point_coordinate_y);
}

void Circle::Free(Circle**& ptr_circles_mass, int& count_size_mass_circles)
{
	delete_element_shape<Circle>(ptr_circles_mass, count_size_mass_circles);
}

float Circle::getCoordinateY()
{
	return m_basepoint.getCoordinateY_Point();
}

float Circle::getCoordinateX()
{
	return m_basepoint.getCoordinateX_Point();
}

float Circle::getRadius()
{
	return m_radius;
}

float Circle::getOutlineThickness()
{
	return m_OutlineThickness;
}

void Circle::setVisibility(int visibility)
{
	m_visibility = visibility;
}

void Circle::setColorOutline(int red, int green, int blue)
{
	m_red = red;
	m_green = green;
	m_blue = blue;
}

void Circle::setColor(int r_color, int g_color, int b_color)
{
	m_r_color = r_color;
	m_g_color = g_color;
	m_b_color = b_color;
}

void Circle::changeRadius(int dradius)
{
	m_radius += dradius;
}

void Circle::setCoordinateX_Y(int base_point_coordinate_x, int base_point_coordinate_y)
{
	m_basepoint.setCoordinateX_Point(base_point_coordinate_x);
	m_basepoint.setCoordinateY_Point(base_point_coordinate_y);
}

Circle::~Circle()
{
	//std::cout << "Объект-окружность был уничтожен." << std::endl;
}
