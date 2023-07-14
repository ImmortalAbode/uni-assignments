#ifndef CIRCLEFUNCS_H_
#define CIRCLEFUNCS_H_

#include "TFigure.h"

void random_move_circles(TCircle** ptr_circles_mass, int num_element);
void create_random_circle(TCircle**& ptr_circles_mass, int& count_size_mass_circles);
int work_with_circles(sf::RenderWindow& window, TCircle**& ptr_circles_mass, int& count_size_mass_circles, TRectangle** ptr_rectangles_mass, int count_size_mass_rectangles,
	TLinesegment** ptr_linesegments_mass, int count_size_mass_linesegments, TEllipse** ptr_ellipses_mass, int count_size_mass_ellipses, TTrapeze** ptr_trapezes_mass, 
	int count_size_mass_trapezes, TRhombus** ptr_rhombuses_mass, int count_size_mass_rhombuses, TQuadrilateral** ptr_quadrilaterals_mass, int count_size_mass_quadrilaterals);


#endif /*CIRCLEFUNCS_H_*/
