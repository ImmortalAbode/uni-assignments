#include <SFML/Graphics.hpp>

#include "MyFuncs.h"
#include "Circle.h"

Circle::Circle() = default;

Circle::Circle(float radius, float base_point_coordinate_x, float base_point_coordinate_y)
	: m_radius{ radius }, m_base_point_coordinate_x{ base_point_coordinate_x }, m_base_point_coordinate_y{ base_point_coordinate_y }
{}

void Circle::Show(sf::RenderWindow & window)
{
	shape_circle.setRadius(m_radius);
	shape_circle.setFillColor(sf::Color(m_r_color, m_g_color, m_b_color, m_visibility));
	shape_circle.setOutlineThickness(m_OutlineThickness);
	shape_circle.setOutlineColor(sf::Color(m_red, m_green, m_blue));
	shape_circle.setPosition(m_base_point_coordinate_x - m_radius, m_base_point_coordinate_y - m_radius);
	window.draw(shape_circle);
}

void Circle::MoveTo(float change_base_point_coordinate_x, float change_base_point_coordinate_y)
{
	m_base_point_coordinate_x += change_base_point_coordinate_x;
	m_base_point_coordinate_y += change_base_point_coordinate_y;
}

void Circle::Free(Circle * *&ptr_circles_mass, int& count_size_mass_circles)
{
	delete_element_shape<Circle>(ptr_circles_mass, count_size_mass_circles);
}

float Circle::getCoordinateY()
{
	return m_base_point_coordinate_y;
}

float Circle::getCoordinateX()
{
	return m_base_point_coordinate_x;
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

void Circle::setRadius(int dradius)
{
	m_radius += dradius;
}

Circle::~Circle() {};