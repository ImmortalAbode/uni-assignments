#ifndef CIRCLEFUNCS_H_
#define CIRCLEFUNCS_H_

#include "Circle.h"
#include "Rectangle.h"
#include "LineSegment.h"
#include "Ring.h"
#include "ComplexObject.h"

void random_move_circles(Circle** ptr_circles_mass, int num_element);
void create_random_circle(Circle**& ptr_circles_mass, int& count_size_mass_circles);
int work_with_circles(sf::RenderWindow& window, Circle**& ptr_circles_mass, int& count_size_mass_circles,
	Rectangle** ptr_rectangles_mass, int count_size_mass_rectangles, Line_Segment** ptr_linesegments_mass, int count_size_mass_linesegments, Ring** ptr_rings_mass, int count_size_mass_rings,
	ComplexObject** ptr_complex_objects_mass, int count_size_mass_complex_objects);


#endif /*CIRCLEFUNCS_H_*/

