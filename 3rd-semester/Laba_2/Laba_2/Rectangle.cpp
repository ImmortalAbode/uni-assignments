#include <SFML/Graphics.hpp>

#include "MyFuncs.h"
#include "Rectangle.h"
#include "Point2D.h"


Rectangle::Rectangle()
	: m_length{ 200 },
	m_width{ 60 },
	m_outline_thickness{ 5 },
	m_r_color{ 233 }, m_g_color{ 179 }, m_b_color{ 248 },
	m_red{ 180 }, m_green{ 68 }, m_blue{ 212 },
	m_visibility{ 255 },
	m_basepoint{ 700, 400 }
{
	std::cout << "Объект-прямоугольник был успешно создан." << std::endl;
}

Rectangle::Rectangle(Point2D basepoint, float length, float width)
	: m_length{ length }, m_width{ width }, m_basepoint{ basepoint }
{
	while (m_basepoint.getCoordinateX_Point() + m_length > 1415)
	{
		m_length -= 1;
	}
	while (m_basepoint.getCoordinateY_Point() + m_width > 715)
	{
		m_width -= 1;
	}
	std::cout << "Объект-прямоугольник был успешно создан." << std::endl;
}

void Rectangle::Show(sf::RenderWindow& window)
{
	shape_rectangle.setSize(sf::Vector2f(m_length, m_width));
	shape_rectangle.setFillColor(sf::Color(m_r_color, m_g_color, m_b_color, m_visibility));
	shape_rectangle.setOutlineThickness(m_outline_thickness);
	shape_rectangle.setOutlineColor(sf::Color(m_red, m_green, m_blue));
	shape_rectangle.setPosition(m_basepoint.getCoordinateX_Point(), m_basepoint.getCoordinateY_Point());
	window.draw(shape_rectangle);
}

void Rectangle::MoveTo(float base_point_coordinate_x, float base_point_coordinate_y)
{
	m_basepoint.setCoordinateX_Point(m_basepoint.getCoordinateX_Point() + base_point_coordinate_x);
	m_basepoint.setCoordinateY_Point(m_basepoint.getCoordinateY_Point() + base_point_coordinate_y);
}

void Rectangle::Free(Rectangle**& ptr_rectangles_mass, int& count_size_mass_rectangles)
{
	delete_element_shape<Rectangle>(ptr_rectangles_mass, count_size_mass_rectangles);
}

float Rectangle::getLength()
{
	return m_length;
}

float Rectangle::getWidth()
{
	return m_width;
}

float Rectangle::getOutlineThickness()
{
	return m_outline_thickness;
}

float Rectangle::getCoordinateY()
{
	return m_basepoint.getCoordinateY_Point();
}

float Rectangle::getCoordinateX()
{
	return m_basepoint.getCoordinateX_Point();
}

void Rectangle::setVisibility(int visibility)
{
	m_visibility = visibility;
}

void Rectangle::setColor(int r_color, int g_color, int b_color)
{
	m_r_color = r_color;
	m_g_color = g_color;
	m_b_color = b_color;
}

void Rectangle::setColorOutline(int red, int green, int blue)
{
	m_red = red;
	m_green = green;
	m_blue = blue;
}

void Rectangle::changeLength(int dlength)
{
	m_length += dlength;
}

void Rectangle::changeWidth(int dwidth)
{
	m_width += dwidth;
}

Rectangle::~Rectangle()
{
	//std::cout << "Объект-прямоугольник был уничтожен." << std::endl;
}
