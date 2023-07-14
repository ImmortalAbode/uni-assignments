#ifndef MYFUNCS_H_
#define MYFUNCS_H_

float getRandomNumber(float min, float max);
float getRandomMove();
int stage_1_choice_shape(sf::RenderWindow& window);
bool stage_0_menu(sf::RenderWindow& window);


//Шаблонные функции для работы с примитивами
template <typename Shape >
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

template <typename Shape >
void delete_mass_objects(Shape**& ptr_shapes_mass, int& count_size_mass_shapes)
{
	for (unsigned i{}; i < count_size_mass_shapes;i++)
	{
		delete ptr_shapes_mass[i];
	}
	delete[] ptr_shapes_mass;
}

template <typename Shape >
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

template <typename Shape >
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

