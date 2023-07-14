#ifndef QUADRILATERALS_H_
#define QUADRILATERALS_H_

#include "TFigure.h"

void random_move_quadrilaterals(TQuadrilateral** ptr_quadrilaterals_mass, int num_element);
void create_random_quadrilateral(TQuadrilateral**& ptr_quadrilaterals_mass, int& count_size_mass_quadrilaterals);
int work_with_quadrilaterals(sf::RenderWindow& window, TQuadrilateral**& ptr_quadrilaterals_mass, int& count_size_mass_quadrilaterals, TCircle** ptr_circles_mass,
	int count_size_mass_circles, TRectangle** ptr_rectangles_mass, int count_size_mass_rectangles, TLinesegment** ptr_linesegments_mass, int count_size_mass_linesegments,
	TEllipse** ptr_ellipses_mass, int count_size_mass_ellipses, TTrapeze** ptr_trapezes_mass, int count_size_mass_trapezes, TRhombus** ptr_rhombuses_mass,
	int count_size_mass_rhombuses);


#endif /*QUADRILATERALS_H_*/
