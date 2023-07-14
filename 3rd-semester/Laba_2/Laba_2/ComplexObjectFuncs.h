#ifndef COMPLEXOBJECTS_H_
#define COMPLEXOBJECTS_H_

#include "Circle.h"
#include "Rectangle.h"
#include "Linesegment.h"
#include "Ring.h"
#include "ComplexObject.h"

void random_move_complex_objects(ComplexObject** ptr_complex_objects_mass, int num_element);
void create_random_complex_object(ComplexObject**& ptr_complex_objects_mass, int& count_size_mass_complex_objects);
int work_with_complex_objects(sf::RenderWindow& window, ComplexObject**& ptr_complex_objects_mass, int& count_size_mass_complex_objects, 
	Circle** ptr_circles_mass, int count_size_mass_circles, Rectangle** ptr_rectangles_mass, int count_size_mass_rectangles, 
	Line_Segment** ptr_linesegments_mass, int count_size_mass_linesegments,	Ring** ptr_rings_mass, int count_size_mass_rings);

#endif /*COMPLEXOBJECTS_H_*/