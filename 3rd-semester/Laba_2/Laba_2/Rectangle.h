#ifndef RECTANGLE_H_
#define RECTANGLE_H_

#include "Point2D.h"

class Rectangle
{
private:
	Point2D m_basepoint{ 700,400 };
	float m_length{ 200 };
	float m_width{ 60 };
	float m_outline_thickness{ 5 };
	int m_r_color{ 233 }, m_g_color{ 179 }, m_b_color{ 248 };
	int m_red{ 180 }, m_green{ 68 }, m_blue{ 212 };
	int m_visibility{ 255 };

	sf::RectangleShape shape_rectangle{};

public:
	Rectangle();
	Rectangle(Point2D basepoint, float length, float width);
	void Show(sf::RenderWindow& window);
	void MoveTo(float base_point_coordinate_x, float base_point_coordinate_y);
	void Free(Rectangle**& ptr_rectangles_mass, int& count_size_mass_rectangles);
	float getLength();
	float getWidth();
	float getOutlineThickness();
	float getCoordinateY();
	float getCoordinateX();
	void setVisibility(int visibility);
	void setColor(int r_color, int g_color, int b_color);
	void setColorOutline(int red, int green, int blue);
	void changeLength(int dlength);
	void changeWidth(int dwidth);
	~Rectangle();
};

#endif /*RECTANGLE_H_*/