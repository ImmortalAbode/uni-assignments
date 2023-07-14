#include <SFML/Graphics.hpp>

#include "Rectangle.h"
#include "Circle.h"
#include "Linesegment.h"
#include "ComplexObject.h"

ComplexObject::ComplexObject()
{
	m_circle.setCoordinateX_Y(m_rectangle.getCoordinateX() + m_rectangle.getLength(), m_rectangle.getCoordinateY() + m_rectangle.getWidth() / 2);
	if (m_circle.getRadius() > m_rectangle.getWidth())
	{
		m_circle.changeRadius(-(m_circle.getRadius() - m_rectangle.getWidth() / 2));
	}
	else
	{
		m_circle.changeRadius(m_rectangle.getWidth() / 2 - m_circle.getRadius());
	}
	m_line_segment_left.setCoordinateX_Y(m_rectangle.getCoordinateX() + m_rectangle.getLength() / 2, m_rectangle.getCoordinateY() + m_rectangle.getWidth() + 2);
	m_line_segment_right.setCoordinateX_Y(m_rectangle.getCoordinateX() + m_rectangle.getLength() / 2, m_rectangle.getCoordinateY() + m_rectangle.getWidth() + 2);
	m_line_segment_left.changeDegree(135), m_line_segment_right.changeDegree(45);
	m_line_segment_left.changeLength(-80), m_line_segment_right.changeLength(-80);
	std::cout << "Объект-составной объект был успешно создан." << std::endl;
}

ComplexObject::ComplexObject(Rectangle rectangle, Circle circle, Line_Segment line_segment_left, Line_Segment line_segment_right)
	:m_rectangle{ rectangle }, m_circle{ circle }, m_line_segment_left{ line_segment_left }, m_line_segment_right{ line_segment_right }
{
	std::cout << "Объект-составной объект был успешно создан." << std::endl;
}

void ComplexObject::Show(sf::RenderWindow& window)
{
	m_rectangle.Show(window);
	m_circle.Show(window);
	m_line_segment_left.Show(window);
	m_line_segment_right.Show(window);
}

void ComplexObject::MoveTo(float change_base_point_coordinate_x, float change_base_point_coordinate_y)
{
	m_rectangle.MoveTo(change_base_point_coordinate_x, change_base_point_coordinate_y);
	m_circle.MoveTo(change_base_point_coordinate_x, change_base_point_coordinate_y);
	m_line_segment_left.MoveTo(change_base_point_coordinate_x, change_base_point_coordinate_y);
	m_line_segment_right.MoveTo(change_base_point_coordinate_x, change_base_point_coordinate_y);
}

Rectangle& ComplexObject::getRectangle()
{
	return m_rectangle;
}

Circle& ComplexObject::getCircle()
{
	return m_circle;
}

Line_Segment& ComplexObject::getLineSegmentLeft()
{
	return m_line_segment_left;
}

Line_Segment& ComplexObject::getLineSegmentRight()
{
	return m_line_segment_right;
}

ComplexObject::~ComplexObject()
{
	//std::cout << "Объект-составной объект был уничтожен." << std::endl;
}