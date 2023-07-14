#ifndef MYFUNCS_H_
#define MYFUNCS_H_

#include "TFigure.h"

float getRandomNumber(float min, float max);
void AddCircleToMass(TFigure**& ptr_figures_mass, int& count_size_mass_figures);
void AddEllipseToMass(TFigure**& ptr_figures_mass, int& count_size_mass_figures);
void AddQuadrilateralToMass(TFigure**& ptr_figures_mass, int& count_size_mass_figures);
void AddRectangleToMass(TFigure**& ptr_figures_mass, int& count_size_mass_figures);
void AddRhombusToMass(TFigure**& ptr_figures_mass, int& count_size_mass_figures);
void AddTrapezeToMass(TFigure**& ptr_figures_mass, int& count_size_mass_figures);
int getChoiceFigureForMethods(TFigure** ptr_figures_mass, int index_of_element);
void move_figures_W(TFigure** ptr_figures_mass, int index_of_element);
void move_figures_A(TFigure** ptr_figures_mass, int index_of_element);
void move_figures_S(TFigure** ptr_figures_mass, int index_of_element);
void move_figures_D(TFigure** ptr_figures_mass, int index_of_element);
void work_with_under_circle_hierarchy(TFigure** ptr_figures_mass, int count_size_mass_figures, sf::Event event_click);
void work_with_under_quadrilateral_hierarchy(TFigure** ptr_figures_mass, int count_size_mass_figures, sf::Event event_click);
void work_with_specific_class(TFigure** ptr_figures_mass, int count_size_mass_figures, int specific_counter, sf::Event event_click);
int stage_1_work_with_mass(sf::RenderWindow& window);
bool stage_0_menu(sf::RenderWindow& window);


//Шаблонные функции для работы с примитивами
template <typename Shape > //для добавления элемента в массив
void push_back_shape(Shape**& old_ptr_shapes_mass, int& old_count_size_mass_shapes, Shape* ptr_obj_shape)
{
	Shape** new_ptr_shapes_mass = new Shape * [old_count_size_mass_shapes + 1];
	for (unsigned i{};i < old_count_size_mass_shapes; i++)
	{
		new_ptr_shapes_mass[i] = old_ptr_shapes_mass[i];
	}

	new_ptr_shapes_mass[old_count_size_mass_shapes] = ptr_obj_shape;
	old_count_size_mass_shapes += 1;
	delete[] old_ptr_shapes_mass;
	old_ptr_shapes_mass = new_ptr_shapes_mass;

}

template <typename Shape > //для полного удаления массива, включая указатель на него, в случае закрытия программы
void delete_mass_objects(Shape**& ptr_shapes_mass, int& count_size_mass_shapes)
{
	for (unsigned i{}; i < count_size_mass_shapes;i++)
	{
		delete ptr_shapes_mass[i];
	}
	delete[] ptr_shapes_mass;
}

template <typename Shape > //для удаления одного элемента массива при проходе по полиморфному массиву
void delete_element_shape(Shape**& old_ptr_shapes_mass, int& old_count_size_mass_shapes)
{
	Shape** new_ptr_shapes_mass = new Shape * [old_count_size_mass_shapes - 1];
	for (unsigned i{};i < old_count_size_mass_shapes - 1;i++)
	{
		new_ptr_shapes_mass[i] = old_ptr_shapes_mass[i];
	}
	old_count_size_mass_shapes -= 1;
	delete old_ptr_shapes_mass[old_count_size_mass_shapes];
	delete[] old_ptr_shapes_mass;
	old_ptr_shapes_mass = new_ptr_shapes_mass;
}

template <typename Shape > //для удаления всего массива кроме указателя на него, в данном случае для удаления указателя на полиморфные указатели
void delete_elements_shape(Shape**& old_ptr_shapes_mass, int& old_count_size_mass_shapes)
{
	for (unsigned i{}; i < old_count_size_mass_shapes;i++)
	{
		delete old_ptr_shapes_mass[i];
	}
	old_count_size_mass_shapes = 0;
	Shape** new_ptr_shapes_mass = new Shape * [old_count_size_mass_shapes];
	delete[] old_ptr_shapes_mass;
	old_ptr_shapes_mass = new_ptr_shapes_mass;
}

#endif /*MYFUNCS_H_*/
