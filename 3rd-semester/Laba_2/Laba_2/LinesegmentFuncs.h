#ifndef LINESEGMENTS_H_
#define LINESEGMENTS_H_

#include "LineSegment.h"
#include "Circle.h"
#include "Rectangle.h"
#include "Ring.h"
#include "ComplexObject.h"

void create_random_linesegment(Line_Segment**& ptr_linesegments_mass, int& count_size_mass_linesegments);
void random_move_linesegment(Line_Segment** ptr_linesegments_mass, int num_element);
int work_with_linesegment(sf::RenderWindow& window, Line_Segment**& ptr_linesegments_mass, int& count_size_mass_linesegments, Circle** ptr_circles_mass, int count_size_mass_circles,
	Rectangle** ptr_rectangles_mass, int count_size_mass_rectangles, Ring** ptr_rings_mass, int count_size_mass_rings,
	ComplexObject** ptr_complex_objects_mass, int count_size_mass_complex_objects);

#endif /*LINESEGMENTS_H_*/
