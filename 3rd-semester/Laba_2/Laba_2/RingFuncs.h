#ifndef RINGFUNCS_H_
#define RINGFUNCS_H_

#include "Circle.h"
#include "Rectangle.h"
#include "Linesegment.h"
#include "Ring.h"
#include "ComplexObject.h"

void random_move_rings(Ring** ptr_rings_mass, int num_element);
void create_random_ring(Ring**& ptr_rings_mass, int& count_size_mass_rings);
int work_with_rings(sf::RenderWindow& window, Ring**& ptr_rings_mass, int& count_size_mass_rings, Circle** ptr_circles_mass, int count_size_mass_circles,
	Rectangle** ptr_rectangles_mass, int count_size_mass_rectangles, Line_Segment** ptr_linesegments_mass, int count_size_mass_linesegments, 
	ComplexObject** ptr_complex_objects_mass, int count_size_mass_complex_objects);

#endif /*RINGFUNCS_H_*/