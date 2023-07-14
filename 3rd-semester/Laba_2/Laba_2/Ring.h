#ifndef RING_H_
#define RING_H_

#include "Circle.h"

class Ring
{
private:
	Circle m_inner_circle{};
	Circle m_outer_circle{};

public:
	Ring();
	Ring(Circle inner_circle, Circle outer_circle);
	void Show(sf::RenderWindow& window);
	void MoveTo(float change_base_point_coordinate_x, float change_base_point_coordinate_y);
	Circle& getInnerCircle();
	Circle& getOuterCircle();
	~Ring();
};

#endif /*RING_H_*/