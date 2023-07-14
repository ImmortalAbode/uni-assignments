#ifndef DYNAMICARRAYCONTAINER_H_
#define DYNAMICARRAYCONTAINER_H_

#include "SFML/Graphics.hpp"
#include "TFigure.h"

class DynamicArrayContainer
{
private:
	int m_size{};
	TFigure** m_data_figures{};

protected:
	void move_figures_W(int i);
	void move_figures_A(int i);
	void move_figures_S(int i);
	void move_figures_D(int i);
	void move_figures_Q(int i);
	void move_figures_E(int i);
	void move_figures_C(int i);
	void move_figures_Z(int i);
	void move_figures_F(int i);
	void move_figures_R(int i);

	void removeElement();

public:
	DynamicArrayContainer();
	void addElement(TFigure* ptr_obj_shape);
	int getChoiceFigureForMethods(int index);
	void iterator(int choice, int index_of_element, sf::RenderWindow& window);
	void Free();
	int getSize();
	TFigure* getElement(int index_element);
	~DynamicArrayContainer();
};

#endif /*DYNAMICARRAYCONTAINER_H_*/
