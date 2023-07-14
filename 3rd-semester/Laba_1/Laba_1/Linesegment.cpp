#include <SFML/Graphics.hpp>

#include "MyFuncs.h"
#include "LineSegment.h"

Line_Segment::Line_Segment() = default;

Line_Segment::Line_Segment(float base_point_coordinate_x, float base_point_coordinate_y, float length, int degree)
	: m_base_point_coordinate_x{ base_point_coordinate_x }, m_base_point_coordinate_y{ base_point_coordinate_y }, m_length{ length }, m_degree{ degree }
{}

void Line_Segment::Show(sf::RenderWindow & window)
{
	line_segment.setSize(sf::Vector2f(m_length, m_width));
	line_segment.setFillColor(sf::Color(m_red, m_green, m_blue, m_visibility));
	line_segment.setPosition(m_base_point_coordinate_x, m_base_point_coordinate_y);
	line_segment.setRotation(m_degree);
	window.draw(line_segment);
}

void Line_Segment::Free(Line_Segment * *&ptr_linesegments_mass, int& count_size_mass_linesegments)
{
	delete_element_shape<Line_Segment>(ptr_linesegments_mass, count_size_mass_linesegments);
}

void Line_Segment::MoveTo(float base_point_coordinate_x, float base_point_coordinate_y)
{
	m_base_point_coordinate_x += base_point_coordinate_x;
	m_base_point_coordinate_y += base_point_coordinate_y;
}

float Line_Segment::getDegree()
{
	return m_degree;
}

float Line_Segment::getCoordinateX()
{
	return m_base_point_coordinate_x;
}

float Line_Segment::getCoordinateY()
{
	return m_base_point_coordinate_y;
}

float Line_Segment::getLength()
{
	return m_length;
}

float Line_Segment::getWidth()
{
	return m_width;
}

void Line_Segment::setLength(int dlength)
{
	m_length += dlength;
}

void Line_Segment::setVisibility(int visibility)
{
	m_visibility = visibility;
}

void Line_Segment::setColor(int red, int green, int blue)
{
	m_red = red;
	m_green = green;
	m_blue = blue;
}

void Line_Segment::setDegree(int ddegree)
{
	m_degree += ddegree;
}

Line_Segment::~Line_Segment() {};