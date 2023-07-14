#include <SFML/Graphics.hpp>

#include "MyFuncs.h"
#include "Point2D.h"

Point2D::Point2D(float base_point_coordinate_x, float base_point_coordinate_y)
	:m_base_point_coordinate_x{ base_point_coordinate_x }, m_base_point_coordinate_y{ base_point_coordinate_y }
{
	std::cout << "Объект-точка был успешно создан." << std::endl;
}

void Point2D::setCoordinateX_Point(float coordinate_x)
{
	m_base_point_coordinate_x = coordinate_x;
}

void Point2D::setCoordinateY_Point(float coordinate_y)
{
	m_base_point_coordinate_y = coordinate_y;
}

float Point2D::getCoordinateX_Point()
{
	return m_base_point_coordinate_x;
}

float Point2D::getCoordinateY_Point()
{
	return m_base_point_coordinate_y;
}

Point2D::~Point2D()
{
	//std::cout << "Объект-точка данной фигуры был уничтожен." << std::endl;
};