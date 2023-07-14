#ifndef POINT2D_H_
#define POINT2D_H_

#include <iostream>

class Point2D
{
private:
	float m_base_point_coordinate_x;
	float m_base_point_coordinate_y;
public:
	Point2D(float base_point_coordinate_x, float base_point_coordinate_y);
	void setCoordinateX_Point(float coordinate_x);
	void setCoordinateY_Point(float coordinate_y);
	float getCoordinateX_Point();
	float getCoordinateY_Point();
	~Point2D();
};

#endif /*POINT2D_H_*/