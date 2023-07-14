#ifndef LINESEGMENTS_H_
#define LINESEGMENTS_H_

#include "LineSegment.h"
#include "Circle.h"
#include "Rectangle.h"

void create_random_linesegment(Line_Segment**& ptr_linesegments_mass, int& count_size_mass_linesegments);
void random_move_linesegment(Line_Segment** ptr_linesegments_mass, int num_element);
void getRandomX_Y(float& restrict_x, float& restrict_y, float restrict_length, int restrict_degree);
int work_with_linesegment(sf::RenderWindow& window, Line_Segment**& ptr_linesegments_mass, int& count_size_mass_linesegments,
	Circle** ptr_circles_mass, int count_size_mass_circles, Rectangle** ptr_rectangles_mass, int count_size_mass_rectangles);

#endif /*LINESEGMENTS_H_*/
