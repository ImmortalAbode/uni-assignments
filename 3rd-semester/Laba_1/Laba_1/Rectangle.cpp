#include <SFML/Graphics.hpp>

#include "MyFuncs.h"
#include "Rectangle.h"

Rectangle::Rectangle() = default;

Rectangle::Rectangle(float base_point_coordinate_x, float base_point_coordinate_y, float length, float width)
	: m_base_point_coordinate_x{ base_point_coordinate_x }, m_base_point_coordinate_y{ base_point_coordinate_y }
	, m_length{ length }, m_width{ width }
{}

void Rectangle::Show(sf::RenderWindow & window)
{
	shape_rectangle.setSize(sf::Vector2f(m_length, m_width));
	shape_rectangle.setFillColor(sf::Color(m_r_color, m_g_color, m_b_color, m_visibility));
	shape_rectangle.setOutlineThickness(m_outline_thickness);
	shape_rectangle.setOutlineColor(sf::Color(m_red, m_green, m_blue));
	shape_rectangle.setPosition(m_base_point_coordinate_x, m_base_point_coordinate_y);
	window.draw(shape_rectangle);
}

void Rectangle::MoveTo(float base_point_coordinate_x, float base_point_coordinate_y)
{
	m_base_point_coordinate_x += base_point_coordinate_x;
	m_base_point_coordinate_y += base_point_coordinate_y;
}

void Rectangle::Free(Rectangle * *&ptr_rectangles_mass, int& count_size_mass_rectangles)
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
	return m_base_point_coordinate_y;
}

float Rectangle::getCoordinateX()
{
	return m_base_point_coordinate_x;
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

void Rectangle::setLength(int dlength)
{
	m_length += dlength;
}

void Rectangle::setWidth(int dwidth)
{
	m_width += dwidth;
}

Rectangle::~Rectangle() {};