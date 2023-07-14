#ifndef RECTANGLEFUNCS_H_
#define RECTANGLEFUNCS_H_

#include "TFigure.h"

void create_random_rectangle(TRectangle**& ptr_rectangles_mass, int& count_size_mass_rectangles);
void random_move_rectangles(TRectangle** ptr_rectangles_mass, int num_element);
int work_with_rectangles(sf::RenderWindow& window, TRectangle**& ptr_rectangles_mass, int& count_size_mass_rectangles, TCircle** ptr_circles_mass, int count_size_mass_circles,
	TLinesegment** ptr_linesegments_mass, int count_size_mass_linesegments, TEllipse** ptr_ellipses_mass, int count_size_mass_ellipses, TTrapeze** ptr_trapezes_mass,
	int count_size_mass_trapezes, TRhombus** ptr_rhombuses_mass, int count_size_mass_rhombuses, TQuadrilateral** ptr_quadrilaterals_mass, int count_size_mass_quadrilaterals);


#endif /*RECTANGLEFUNCS_H_*/
