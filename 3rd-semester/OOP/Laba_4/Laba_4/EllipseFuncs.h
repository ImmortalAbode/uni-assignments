#ifndef ELLIPSEFUNCS_H_
#define ELLIPSEFUNCS_H_

#include "TFigure.h"

void random_move_ellipses(TEllipse** ptr_ellipses_mass, int num_element);
void create_random_ellipse(TEllipse**& ptr_ellipses_mass, int& count_size_mass_ellipses);
int work_with_ellipses(sf::RenderWindow& window, TEllipse**& ptr_ellipses_mass, int& count_size_mass_ellipses, TCircle** ptr_circles_mass, int count_size_mass_circles,
	TRectangle** ptr_rectangles_mass, int count_size_mass_rectangles, TLinesegment** ptr_linesegments_mass, int count_size_mass_linesegments, TTrapeze** ptr_trapezes_mass,
	int count_size_mass_trapezes, TRhombus** ptr_rhombuses_mass, int count_size_mass_rhombuses, TQuadrilateral** ptr_quadrilaterals_mass, int count_size_mass_quadrilaterals);


#endif /*ELLIPSEFUNCS_H_*/

