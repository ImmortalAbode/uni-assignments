#ifndef LINESEGMENT_H_
#define LINESEGMENT_H_

#include "Point2D.h"

class Line_Segment
{
private:
	Point2D m_basepoint{ 700,400 };
	float m_length{ 200 };
	float m_width{ 2 };
	int m_degree{};
	int m_red{ 180 }, m_green{ 68 }, m_blue{ 212 };
	int m_visibility{ 255 };

	sf::RectangleShape line_segment{};
public:
	Line_Segment();
	Line_Segment(Point2D basepoint, float length, int degree);
	void Show(sf::RenderWindow& window);
	void Free(Line_Segment**& ptr_linesegments_mass, int& count_size_mass_linesegments);
	void MoveTo(float base_point_coordinate_x, float base_point_coordinate_y);
	float getDegree();
	float getCoordinateX();
	float getCoordinateY();
	float getLength();
	float getWidth();
	void changeLength(int dlength);
	void setVisibility(int visibility);
	void setColor(int red, int green, int blue);
	void changeDegree(int ddegree);
	void setCoordinateX_Y(float change_base_point_coordinate_x, float change_base_point_coordinate_y);
	void changeCoordinateX_Y(float dx, float dy);
	~Line_Segment();
};

#endif /*LINESEGMENT_H_*/

