#include <SFML/Graphics.hpp>

#include "MyFuncs.h"
#include "Linesegment.h"
#include "Point2D.h"

Line_Segment::Line_Segment()
	: m_length{ 200 },
	m_width{ 2 },
	m_degree{},
	m_red{ 180 }, m_green{ 68 }, m_blue{ 212 },
	m_visibility{ 255 },
	m_basepoint{ 700,400 }
{
	std::cout << "Объект-отрезок был успешно создан." << std::endl;
}

Line_Segment::Line_Segment(Point2D basepoint, float length, int degree)
	: m_length{ length }, m_degree{ degree }, m_basepoint{ basepoint }
{
	if (m_degree >= 0 && m_degree <= 90)
	{
		while (m_basepoint.getCoordinateX_Point() + m_length * cos(m_degree * acos(-1.0f) / 180) > 1415 ||
			m_basepoint.getCoordinateY_Point() + m_length * sin(m_degree * acos(-1.0f) / 180) > 715)
		{
			m_length -= 1;
		}
	}
	else if (m_degree >= 90 && m_degree <= 180)
	{
		while (m_basepoint.getCoordinateX_Point() + m_length * cos(m_degree * acos(-1.0f) / 180) < 465 ||
			m_basepoint.getCoordinateY_Point() + m_length * sin(m_degree * acos(-1.0f) / 180) > 715)
		{
			m_length -= 1;
		}
	}
	else if (m_degree >= 180 && m_degree <= 270)
	{
		while (m_basepoint.getCoordinateX_Point() + m_length * cos(m_degree * acos(-1.0f) / 180) < 465 ||
			m_basepoint.getCoordinateY_Point() + m_length * sin(m_degree * acos(-1.0f) / 180) < 115)
		{
			m_length -= 1;
		}
	}
	else if (degree >= 270 && degree <= 360)
	{
		while (m_basepoint.getCoordinateX_Point() + m_length * cos(m_degree * acos(-1.0f) / 180) > 1415 ||
			m_basepoint.getCoordinateY_Point() + m_length * sin(m_degree * acos(-1.0f) / 180) < 115)
		{
			m_length -= 1;
		}
	}
	m_basepoint.setCoordinateX_Point(m_basepoint.getCoordinateX_Point());
	m_basepoint.setCoordinateY_Point(m_basepoint.getCoordinateY_Point());
	std::cout << "Объект-отрезок был успешно создан." << std::endl;
}

void Line_Segment::Show(sf::RenderWindow& window)
{
	line_segment.setSize(sf::Vector2f(m_length, m_width));
	line_segment.setFillColor(sf::Color(m_red, m_green, m_blue, m_visibility));
	line_segment.setPosition(m_basepoint.getCoordinateX_Point(), m_basepoint.getCoordinateY_Point());
	line_segment.setRotation(m_degree);
	window.draw(line_segment);
}

void Line_Segment::Free(Line_Segment**& ptr_linesegments_mass, int& count_size_mass_linesegments)
{
	delete_element_shape<Line_Segment>(ptr_linesegments_mass, count_size_mass_linesegments);
}

void Line_Segment::MoveTo(float base_point_coordinate_x, float base_point_coordinate_y)
{
	m_basepoint.setCoordinateX_Point(m_basepoint.getCoordinateX_Point() + base_point_coordinate_x);
	m_basepoint.setCoordinateY_Point(m_basepoint.getCoordinateY_Point() + base_point_coordinate_y);
}

float Line_Segment::getDegree()
{
	return m_degree;
}

float Line_Segment::getCoordinateX()
{
	return m_basepoint.getCoordinateX_Point();
}

float Line_Segment::getCoordinateY()
{
	return m_basepoint.getCoordinateY_Point();
}

float Line_Segment::getLength()
{
	return m_length;
}

float Line_Segment::getWidth()
{
	return m_width;
}

void Line_Segment::changeLength(int dlength)
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

void Line_Segment::changeDegree(int ddegree)
{
	m_degree += ddegree;
}

void Line_Segment::setCoordinateX_Y(float change_base_point_coordinate_x, float change_base_point_coordinate_y)
{
	m_basepoint.setCoordinateX_Point(change_base_point_coordinate_x);
	m_basepoint.setCoordinateY_Point(change_base_point_coordinate_y);
}

void Line_Segment::changeCoordinateX_Y(float dx, float dy)
{
	m_basepoint.setCoordinateX_Point(m_basepoint.getCoordinateX_Point() + dx);
	m_basepoint.setCoordinateY_Point(m_basepoint.getCoordinateY_Point() + dy);
}

Line_Segment::~Line_Segment()
{
	//std::cout << "Объект-отрезок был уничтожен." << std::endl;
}
