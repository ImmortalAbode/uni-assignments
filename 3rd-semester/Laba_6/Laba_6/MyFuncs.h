#ifndef MYFUNCS_H_
#define MYFUNCS_H_

#include "TFigure.h"
#include "DynamicArrayContainer.h"

float getRandomNumber(float min, float max);
TFigure* CreateCircle();
TFigure* CreateEllipse();
TFigure* CreateQuadrilateral();
TFigure* CreateRectangle();
TFigure* CreateRhombus();
TFigure* CreateTrapeze();
int stage_1_work_with_mass(sf::RenderWindow& window);
bool stage_0_menu(sf::RenderWindow& window);

#endif /*MYFUNCS_H_*/
