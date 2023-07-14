#ifndef RHOMBUSFUNCS_H_
#define RHOMBUSFUNCS_H_

#include "TFigure.h"

void random_move_rhombuses(TRhombus** ptr_rhombuses_mass, int num_element);
void create_random_rhombus(TRhombus**& ptr_rhombuses_mass, int& count_size_mass_rhombuses);
int work_with_rhombuses(sf::RenderWindow& window, TRhombus**& ptr_rhombuses_mass, int& count_size_mass_rhombuses, TCircle** ptr_circles_mass, int count_size_mass_circles,
	TRectangle** ptr_rectangles_mass, int count_size_mass_rectangles, TLinesegment** ptr_linesegments_mass, int count_size_mass_linesegments, TEllipse** ptr_ellipses_mass,
	int count_size_mass_ellipses, TTrapeze** ptr_trapezes_mass, int count_size_mass_trapezes, TQuadrilateral** ptr_quadrilaterals_mass, int count_size_mass_quadrilaterals);


#endif /*RHOMBUSFUNCS_H_*/
