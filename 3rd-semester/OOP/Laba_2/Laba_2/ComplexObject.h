#ifndef COMPLEXOBJECT_H_
#define COMPLEXOBJECT_H_

#include "Rectangle.h"
#include "Circle.h"
#include "Linesegment.h"

class ComplexObject
{
private:
	Rectangle m_rectangle{};
	Circle m_circle{};
	Line_Segment m_line_segment_left{};
	Line_Segment m_line_segment_right{};
public:
	ComplexObject();
	ComplexObject(Rectangle rectangle, Circle circle, Line_Segment line_segment_left, Line_Segment line_segment_right);
	void Show(sf::RenderWindow& window);
	void MoveTo(float change_base_point_coordinate_x, float change_base_point_coordinate_y);
	Rectangle& getRectangle();
	Circle& getCircle();
	Line_Segment& getLineSegmentLeft();
	Line_Segment& getLineSegmentRight();
	~ComplexObject();
};

#endif /*COMPLEXOBJECT_H_*/
