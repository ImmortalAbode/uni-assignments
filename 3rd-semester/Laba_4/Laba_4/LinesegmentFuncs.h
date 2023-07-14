#ifndef LINESEGMENTS_H_
#define LINESEGMENTS_H_

#include "TFigure.h"

void create_random_linesegment(TLinesegment**& ptr_linesegments_mass, int& count_size_mass_linesegments);
void random_move_linesegment(TLinesegment** ptr_linesegments_mass, int num_element);
int work_with_linesegment(sf::RenderWindow& window, TLinesegment**& ptr_linesegments_mass, int& count_size_mass_linesegments, TCircle** ptr_circles_mass,
	int count_size_mass_circles, TRectangle** ptr_rectangles_mass, int count_size_mass_rectangles, TEllipse** ptr_ellipses_mass, int count_size_mass_ellipses, TTrapeze** ptr_trapezes_mass,
	int count_size_mass_trapezes, TRhombus** ptr_rhombuses_mass, int count_size_mass_rhombuses, TQuadrilateral** ptr_quadrilaterals_mass, int count_size_mass_quadrilaterals);

#endif /*LINESEGMENTS_H_*/
