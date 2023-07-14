#ifndef TRAPEZE_H_
#define TRAPEZE_H_

#include "TFigure.h"

void random_move_trapezes(TTrapeze** ptr_trapezes_mass, int num_element);
void create_random_trapeze(TTrapeze**& ptr_trapezes_mass, int& count_size_mass_trapezes);
int work_with_trapezes(sf::RenderWindow& window, TTrapeze** ptr_trapezes_mass, int count_size_mass_trapezes, TCircle** ptr_circles_mass, int count_size_mass_circles,
	TRectangle** ptr_rectangles_mass, int count_size_mass_rectangles, TLinesegment** ptr_linesegments_mass, int count_size_mass_linesegments,
	TEllipse** ptr_ellipses_mass, int count_size_mass_ellipses, TRhombus** ptr_rhombuses_mass, int count_size_mass_rhombuses, TQuadrilateral** ptr_quadrilaterals_mass,
	int count_size_mass_quadrilaterals);


#endif /*TRAPEZE_H_*/
