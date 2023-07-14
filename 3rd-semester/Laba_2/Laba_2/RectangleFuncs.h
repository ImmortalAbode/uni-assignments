#ifndef RECTANGLEFUNCS_H_
#define RECTANGLEFUNCS_H_

#include "Rectangle.h"
#include "Circle.h"
#include "LineSegment.h"
#include "Ring.h"
#include "ComplexObject.h"

void create_random_rectangle(Rectangle**& ptr_rectangles_mass, int& count_size_mass_rectangles);
void random_move_rectangles(Rectangle** ptr_rectangles_mass, int num_element);
int work_with_rectangles(sf::RenderWindow& window, Rectangle**& ptr_rectangles_mass, int& count_size_mass_rectangles,
	Circle** ptr_circles_mass, int count_size_mass_circles, Line_Segment** ptr_linesegments_mass, int count_size_mass_linesegments, Ring** ptr_rings_mass, int count_size_mass_rings,
	ComplexObject** ptr_complex_objects_mass, int count_size_mass_complex_objects);


#endif /*RECTANGLEFUNCS_H_*/

