#include <SFML/Graphics.hpp>
#include <iostream>

#include "MyFuncs.h"
#include "TFigure.h"
#include "UserButton.h"
#include "DynamicArrayContainer.h"
#include "LinearDynamicListContainer.h"

float getRandomNumber(float min, float max)
{
	static const float fraction = 1.0 / (static_cast<float>(RAND_MAX) + 1.0);
	return (rand() * fraction * (max - min + 1) + min);
}

TFigure* CreateCircle()
{
	float restrict_radius{ getRandomNumber(10, 90) };
	float restrict_x{ getRandomNumber(465, 1415) };
	float restrict_y{ getRandomNumber(115, 715) };
	TFigure* ptr_new_figure{ new TCircle{restrict_radius,restrict_x,restrict_y} };
	ptr_new_figure->setOutlineColor(getRandomNumber(0, 255), getRandomNumber(0, 255), getRandomNumber(0, 255));
	ptr_new_figure->setFillColor(getRandomNumber(0, 255), getRandomNumber(0, 255), getRandomNumber(0, 255));
	ptr_new_figure->setVisibility(getRandomNumber(50, 255));
	return ptr_new_figure;
} 

TFigure* CreateEllipse()
{
	TFigure* ptr_new_figure{ nullptr };
	while (true)
	{
		float restrict_semi_minor_axis{ getRandomNumber(10, 90) };
		float restrict_semi_major_axis{ getRandomNumber(90, 130) };
		float restrict_x{ getRandomNumber(465, 1415) };
		float restrict_y{ getRandomNumber(115, 715) };
		TEllipse ellipse{ restrict_semi_minor_axis, restrict_semi_major_axis, restrict_x, restrict_y };
		if (ellipse.getSemiMinorAxis() >= 15 && ellipse.getRadius() >= 40)
		{
			ptr_new_figure = new TEllipse{ ellipse.getSemiMinorAxis(), ellipse.getRadius(), restrict_x, restrict_y };
			break;
		}
		else
		{
			std::cout << "!!!Созданный эллипс не удовлетворил условиям создания в ходе попытки реализации." << std::endl;
			std::cout << ".......Заново......." << std::endl;
		}
	}
	ptr_new_figure->setOutlineColor(getRandomNumber(0, 255), getRandomNumber(0, 255), getRandomNumber(0, 255));
	ptr_new_figure->setFillColor(getRandomNumber(0, 255), getRandomNumber(0, 255), getRandomNumber(0, 255));
	ptr_new_figure->setVisibility(getRandomNumber(50, 255));
	return ptr_new_figure;
}

TFigure* CreateQuadrilateral()
{
	float restrict_x1{ getRandomNumber(480, 1315) };
	float restrict_x2{ getRandomNumber(restrict_x1 + 50, restrict_x1 + 100) };
	float restrict_x3{ getRandomNumber(restrict_x1 + 50, restrict_x1 + 100) };
	float restrict_x4{ getRandomNumber(restrict_x1 - 25, restrict_x3 - 50) };
	float restrict_y1{ getRandomNumber(140, 590) };
	float restrict_y2{ getRandomNumber(restrict_y1 - 25, restrict_y1 + 25) };
	float restrict_y3{ getRandomNumber(restrict_y2 + 50, restrict_y2 + 100) };
	float restrict_y4{ getRandomNumber(restrict_y1 + 50, restrict_y1 + 100) };
	TFigure* ptr_new_figure{ new TQuadrilateral{ restrict_x1, restrict_y1,restrict_x2,restrict_y2, restrict_x3,
		restrict_y3, restrict_x4, restrict_y4 } };
	ptr_new_figure->setOutlineColor(getRandomNumber(0, 255), getRandomNumber(0, 255), getRandomNumber(0, 255));
	ptr_new_figure->setFillColor(getRandomNumber(0, 255), getRandomNumber(0, 255), getRandomNumber(0, 255));
	ptr_new_figure->setVisibility(getRandomNumber(50, 255));
	return ptr_new_figure;
}

TFigure* CreateRectangle()
{
	float restrict_length{ getRandomNumber(30, 400) };
	float restrict_width{ getRandomNumber(30, 250) };
	float restrict_x{ getRandomNumber(465, 1415) };
	float restrict_y{ getRandomNumber(115, 715) };
	TFigure* ptr_new_figure{ new TRectangle{ restrict_x, restrict_y, restrict_length, restrict_width } };
	ptr_new_figure->setOutlineColor(getRandomNumber(0, 255), getRandomNumber(0, 255), getRandomNumber(0, 255));
	ptr_new_figure->setFillColor(getRandomNumber(0, 255), getRandomNumber(0, 255), getRandomNumber(0, 255));
	ptr_new_figure->setVisibility(getRandomNumber(50, 255));
	return ptr_new_figure;
}

TFigure* CreateRhombus()
{
	float length{ getRandomNumber(50, 100) };
	int degree{ static_cast<int>(getRandomNumber(15, 60)) };
	float restrict_x{ getRandomNumber(465, 1415 - 2 * length * cos(degree * acos(-1.0f) / 180)) };
	float restrict_y{ getRandomNumber(115 + length * sin(degree * acos(-1.0f) / 180), 715 - length * sin(degree * acos(-1.0f) / 180)) };
	TFigure* ptr_new_figure{ new TRhombus{ restrict_x, restrict_y, length, degree } };
	ptr_new_figure->setOutlineColor(getRandomNumber(0, 255), getRandomNumber(0, 255), getRandomNumber(0, 255));
	ptr_new_figure->setFillColor(getRandomNumber(0, 255), getRandomNumber(0, 255), getRandomNumber(0, 255));
	ptr_new_figure->setVisibility(getRandomNumber(50, 255));
	return ptr_new_figure;
}

TFigure* CreateTrapeze()
{
	int degree{ static_cast<int>(getRandomNumber(30, 90)) };
	float height{ getRandomNumber(50, 80) };
	float bottom_base_length{ getRandomNumber(150, 300) };
	float top_base_length{ getRandomNumber(60, bottom_base_length - height / tan(degree * acos(-1.0f) / 180)) };
	float restrict_x{ getRandomNumber(465, 1415 - bottom_base_length) };
	float restrict_y{ getRandomNumber(115 + height, 715) };
	TFigure* ptr_new_figure{ new TTrapeze{ restrict_x, restrict_y, degree, bottom_base_length, top_base_length, height } };
	ptr_new_figure->setOutlineColor(getRandomNumber(0, 255), getRandomNumber(0, 255), getRandomNumber(0, 255));
	ptr_new_figure->setFillColor(getRandomNumber(0, 255), getRandomNumber(0, 255), getRandomNumber(0, 255));
	ptr_new_figure->setVisibility(getRandomNumber(50, 255));
	return ptr_new_figure;
}

int stage_1_work_with_mass(sf::RenderWindow& window)
{
	/*Кнопка Work with polymorphic container as*/
	User_Text_Button work_container_text_button{ "Comic_Sans_MS.TTF", "Work with polymorphic pointers as", 25, 15, 15 };
	User_Rect_Button work_container_rect_button{ 10, 10, 5, 450, 60 };

	/*Кнопка Dynamic array*/
	User_Text_Button dynamic_array_text_button{ "Comic_Sans_MS.TTF", "Dynamic array", 25, 15, 105 };
	User_Rect_Button dynamic_array_rect_button{ 10, 90, 5, 200, 60 };

	/*Кнопка Linear dynamic list*/
	User_Text_Button linear_dynamic_list_text_button{ "Comic_Sans_MS.TTF", "Linear dynamic list", 23, 235, 110 };
	User_Rect_Button linear_dynamic_list_rect_button{ 230, 90, 5, 230, 60 };

	/*Кнопка Create container*/
	User_Text_Button create_container_text_button{ "Comic_Sans_MS.TTF", "Create container", 23, 15, 180 };
	User_Rect_Button create_container_rect_button{ 10, 170, 5, 205, 60 };

	/*Кнопка Add element*/
	User_Text_Button add_element_text_button{ "Comic_Sans_MS.TTF", "Add element", 23, 15, 260 };
	User_Rect_Button add_element_rect_button{ 10, 250, 5, 200, 60 };

	/*Кнопка Delete element*/
	User_Text_Button delete_element_text_button{ "Comic_Sans_MS.TTF", "Delete element", 23, 15, 340 };
	User_Rect_Button delete_element_rect_button{ 10, 330, 5, 200, 60 };

	/*Кнопка Show element*/
	User_Text_Button show_elements_text_button{ "Comic_Sans_MS.TTF", "Show elements", 23, 15, 420 };
	User_Rect_Button show_elements_rect_button{ 10, 410, 5, 200, 60 };

	/*Кнопка Erase element*/
	User_Text_Button erase_elements_text_button{ "Comic_Sans_MS.TTF", "Erase elements", 23, 15, 500 };
	User_Rect_Button erase_elements_rect_button{ 10, 490, 5, 200, 60 };

	/*Кнопка Move element*/
	User_Text_Button move_elements_text_button{ "Comic_Sans_MS.TTF", "Move elements", 23, 15, 580 };
	User_Rect_Button move_elements_rect_button{ 10, 570, 5, 200, 60 };

	/*Кнопка Destroy container*/
	User_Text_Button destroy_container_text_button{ "Comic_Sans_MS.TTF", "Destroy container", 23, 15, 660 };
	User_Rect_Button destroy_container_rect_button{ 10, 650, 5, 215, 60 };

	/*Кнопка under circle hierarchy*/
	User_Text_Button circle_hierarchy_text_button{ "Comic_Sans_MS.TTF", "Under circle hierarchy", 23, 15, 740 };
	User_Rect_Button circle_hierarchy_rect_button{ 10, 730, 5, 440, 60 };

	/*Кнопка under quadrilateral hierarchy*/
	User_Text_Button quadrilateral_hierarchy_text_button{ "Comic_Sans_MS.TTF", "Under quadrilateral hierarchy", 23, 15, 820 };
	User_Rect_Button quadrilateral_hierarchy_rect_button{ 10, 810, 5, 440, 60 };

	/*Текст выбора конкретного класса*/
	User_Text_Button switch_mode_text{ "Comic_Sans_MS.TTF", "M - switch mode of work with class: ", 20, 500, 840 };

	/*Текст выбора конкретного класса*/
	User_Text_Button select_specific_class_text{ "Comic_Sans_MS.TTF", "Space - select a specific class: ", 20, 500, 870 };

	/*Текст выборанного режима*/
	User_Text_Button usually_mode_text{ "Comic_Sans_MS.TTF", "Usually ", 20, 890, 840 };
	User_Text_Button specific_mode_text{ "Comic_Sans_MS.TTF", "Specific ", 20, 890, 840 };

	/*Текст выборанного режима*/
	User_Text_Button ellipse_text{ "Comic_Sans_MS.TTF", "Ellipse ", 20, 830, 870 };
	User_Text_Button rectangle_text{ "Comic_Sans_MS.TTF", "Rectangle ", 20, 830, 870 };
	User_Text_Button rhombus_text{ "Comic_Sans_MS.TTF", "Rhombus ", 20, 830, 870 };
	User_Text_Button trapeze_text{ "Comic_Sans_MS.TTF", "Trapeze ", 20, 830, 870 };

	//Тексты управления фигурами
	User_Text_Button move_shapes{ "Comic_Sans_MS.TTF", "Move up shape (W)    Move down shape (S)   Move left shape (A)    Move right shape (D)", 15, 500, 770 };
	User_Text_Button special_movement_circle{ "Comic_Sans_MS.TTF", "Decrease radius(Q)           Increase radius(E)", 15, 500, 730 };
	User_Text_Button special_movement_ellipse{ "Comic_Sans_MS.TTF",
		"Decrease vertical axis(Q) Increase vertical axis(E) Rotate90degrees (R)\n Decrease horizontal axis(Z) Increase horizontal axis(C)", 15, 500, 730 };
	User_Text_Button special_movement_rectangle{ "Comic_Sans_MS.TTF", "Decrease length(Q)    Increase length(E)    Decrease width(Z)    Increase width(C)", 15, 500, 730 };
	User_Text_Button special_movement_trapeze{ "Comic_Sans_MS.TTF",
		"Decrease top base length(Q) Increase top base length(E) Decrease bottom base length(Z) \n Increase bottom base length(C) Decrease height(R) Increase height(F)",
		15, 500, 715 };
	User_Text_Button special_movement_rhombus{ "Comic_Sans_MS.TTF", "Decrease degree(Q)  Increase degree(E)  Decrease length of side(Z)  Increase length of side(C)", 15, 500, 730 };


	/*Текст IMAGE*/
	User_Text_Button image_text{ "Comic_Sans_MS.TTF", "Image", 60, 850, 10 };
	User_Rect_Button image_rect{ 465, 115, 0, 950, 600 }; image_rect.m_setColor(178, 143, 252);

	/*Кнопка BACK*/
	User_Text_Button back_text_button{ "Comic_Sans_MS.TTF", "Back", 28, 1350, 840 };
	User_Rect_Button back_rect_button{ 1290, 830, 5, 200, 60 };
	
	int is_stage{}; //для определения какая кнопка нажата

	//Работа с полиморфным контейнером на основе полиморфного массива указателей класса TFigure
	DynamicArrayContainer* ptr_container_array{ nullptr };
	LinearDynamicListContainer* ptr_container_list{ nullptr };

	//Вспомогательные переменные для регулирования работы программы
	bool submenu_container{ false }; //развернуть или нет подменю массива
	bool container_as_array{ false }; //работа с контейнером на основе динамического массива
	bool container_as_list{ false }; //работа с контейнером на основе линейного динамического списка
	bool draw_figures{ true }; //рисовать фигуры или нет
	bool move_figures{ false }; //перемещать фигуры или нет
	bool under_circle_hierarchy{ false }; //работа с подиерархией окружностей или нет
	bool under_quadrilateral_hierarchy{ false }; //работа с подиерархией четырехугольников или нет
	int specific_counter{ -1 }; //счетчик для определения возможности работы с конкретным классом
	bool specific_work{ false }; //работать со всеми классами или с определенными
	bool create_container{ false }; //создан контейнер или нет

	while (window.isOpen())
	{
		is_stage = 0;
		window.clear(sf::Color(137, 20, 190));

		if (submenu_container) work_container_rect_button.m_setOutlineColor(247, 30, 241);
		else work_container_rect_button.m_setOutlineColorDefault();
		work_container_text_button.m_setFillColorDefault();

		if (container_as_array) dynamic_array_rect_button.m_setOutlineColor(247, 30, 241);
		else dynamic_array_rect_button.m_setOutlineColorDefault(); 
		dynamic_array_text_button.m_setFillColorDefault();

		if (container_as_list) linear_dynamic_list_rect_button.m_setOutlineColor(247, 30, 241);
		else linear_dynamic_list_rect_button.m_setOutlineColorDefault(); 
		linear_dynamic_list_text_button.m_setFillColorDefault();

		create_container_rect_button.m_setOutlineColorDefault(); create_container_text_button.m_setFillColorDefault();
		add_element_rect_button.m_setOutlineColorDefault(); add_element_text_button.m_setFillColorDefault();
		delete_element_rect_button.m_setOutlineColorDefault(); delete_element_text_button.m_setFillColorDefault();

		if (!draw_figures) erase_elements_rect_button.m_setOutlineColor(247, 30, 241);
		else erase_elements_rect_button.m_setOutlineColorDefault();
		erase_elements_text_button.m_setFillColorDefault();

		if (draw_figures && create_container)
		{
			if (container_as_array)
			{
				if (ptr_container_array->getSize() != 0) 
					show_elements_rect_button.m_setOutlineColor(247, 30, 241);
			}
			else if (container_as_list)
			{
				if (ptr_container_list->getSize() != 0)
					show_elements_rect_button.m_setOutlineColor(247, 30, 241);
			}
		}
		else show_elements_rect_button.m_setOutlineColorDefault();
		show_elements_text_button.m_setFillColorDefault();

		if (move_figures)move_elements_rect_button.m_setOutlineColor(247, 30, 241);
		else move_elements_rect_button.m_setOutlineColorDefault();
		move_elements_text_button.m_setFillColorDefault();

		destroy_container_rect_button.m_setOutlineColorDefault(); destroy_container_text_button.m_setFillColorDefault();
		back_rect_button.m_setOutlineColorDefault(); back_text_button.m_setFillColorDefault();

		if (under_circle_hierarchy) circle_hierarchy_rect_button.m_setOutlineColor(247, 30, 241);
		else circle_hierarchy_rect_button.m_setOutlineColorDefault();
		circle_hierarchy_text_button.m_setFillColorDefault();

		if (under_quadrilateral_hierarchy) quadrilateral_hierarchy_rect_button.m_setOutlineColor(241, 30, 241);
		else quadrilateral_hierarchy_rect_button.m_setOutlineColorDefault();
		quadrilateral_hierarchy_text_button.m_setFillColorDefault();

		if (sf::IntRect(5, 0, 465, 80).contains(sf::Mouse::getPosition(window))) //container tab
		{
			work_container_rect_button.m_setOutlineColor(165, 15, 203);
			work_container_text_button.m_setFillColor(255, 127, 39);
			is_stage = 1;
		}

		if (sf::IntRect(5, 80, 210, 80).contains(sf::Mouse::getPosition(window))) //container as array
		{
			dynamic_array_rect_button.m_setOutlineColor(165, 15, 203);
			dynamic_array_text_button.m_setFillColor(255, 127, 39);
			is_stage = 2;
		}

		if (sf::IntRect(225, 80, 240, 80).contains(sf::Mouse::getPosition(window))) //container as list
		{
			linear_dynamic_list_rect_button.m_setOutlineColor(165, 15, 203);
			linear_dynamic_list_text_button.m_setFillColor(255, 127, 39);
			is_stage = 3;
		}

		if (sf::IntRect(5, 160, 215, 80).contains(sf::Mouse::getPosition(window))) //create container
		{
			create_container_rect_button.m_setOutlineColor(165, 15, 203);
			create_container_text_button.m_setFillColor(255, 127, 39);
			is_stage = 4;
		}

		if (sf::IntRect(5, 240, 210, 80).contains(sf::Mouse::getPosition(window))) //add element
		{
			add_element_rect_button.m_setOutlineColor(165, 15, 203);
			add_element_text_button.m_setFillColor(255, 127, 39);
			is_stage = 5;
		}

		if (sf::IntRect(5, 320, 210, 80).contains(sf::Mouse::getPosition(window))) //remove element
		{
			delete_element_rect_button.m_setOutlineColor(165, 15, 203);
			delete_element_text_button.m_setFillColor(255, 127, 39);
			is_stage = 6;
		}

		if (sf::IntRect(5, 400, 210, 80).contains(sf::Mouse::getPosition(window))) //show element
		{
			show_elements_rect_button.m_setOutlineColor(165, 15, 203);
			show_elements_text_button.m_setFillColor(255, 127, 39);
			is_stage = 7;
		}

		if (sf::IntRect(5, 480, 210, 80).contains(sf::Mouse::getPosition(window))) //erase element
		{
			erase_elements_rect_button.m_setOutlineColor(165, 15, 203);
			erase_elements_text_button.m_setFillColor(255, 127, 39);
			is_stage = 8;
		}

		if (sf::IntRect(5, 560, 210, 80).contains(sf::Mouse::getPosition(window))) //move element
		{
			move_elements_rect_button.m_setOutlineColor(165, 15, 203);
			move_elements_text_button.m_setFillColor(255, 127, 39);
			is_stage = 9;
		}

		if (sf::IntRect(5, 640, 225, 80).contains(sf::Mouse::getPosition(window))) //destroy container
		{
			destroy_container_rect_button.m_setOutlineColor(165, 15, 203);
			destroy_container_text_button.m_setFillColor(255, 127, 39);
			is_stage = 10;
		}

		if (sf::IntRect(5, 720, 450, 80).contains(sf::Mouse::getPosition(window))) //under circle hierarchy
		{
			circle_hierarchy_rect_button.m_setOutlineColor(165, 15, 203);
			circle_hierarchy_text_button.m_setFillColor(255, 127, 39);
			is_stage = 11;
		}

		if (sf::IntRect(5, 800, 450, 80).contains(sf::Mouse::getPosition(window))) //under quadrilateral hierarchy
		{
			quadrilateral_hierarchy_rect_button.m_setOutlineColor(165, 15, 203);
			quadrilateral_hierarchy_text_button.m_setFillColor(255, 127, 39);
			is_stage = 12;
		}

		if (sf::IntRect(1285, 820, 210, 80).contains(sf::Mouse::getPosition(window))) //back
		{
			back_rect_button.m_setOutlineColor(165, 15, 203);
			back_text_button.m_setFillColor(255, 127, 39);
			is_stage = 13;
		}
		sf::Event event_click;
		while (window.pollEvent(event_click))
		{
			if (event_click.type == sf::Event::Closed)
			{
				if (container_as_array && ptr_container_array != nullptr)
				{

					for (unsigned i{}; i < ptr_container_array->getSize();i++)
					{
						ptr_container_array->iterator(0, i, window);
					}
					ptr_container_array->Free();
				}
				if (container_as_list && ptr_container_list->get_pHead() != nullptr)
				{
					for (unsigned i{}; i < ptr_container_list->getSize();i++)
					{
						ptr_container_list->iterator(0, i, window);
					}
					ptr_container_list->Free();
				}
				window.close();
				return 0;
			}
			else if (event_click.type == event_click.MouseButtonReleased && event_click.mouseButton.button == sf::Mouse::Left)
			{
				//sf::Vector2i position = sf::Mouse::getPosition(window);
				//std::cout << position.x << "\t" << position.y << std::endl;

				if (is_stage == 1)
				{
					submenu_container = !submenu_container;
					if (submenu_container) std::cout << "Возможности полиморфного класса для демонстрации возможнотей стали доступны." << std::endl;
					else std::cout << "Возможности полиморфного класса для демонстрации возможнотей были закрыты." << std::endl;
				}
				if (is_stage == 2 && submenu_container)
				{
					container_as_array = !container_as_array;
					if (container_as_list)
					{
						container_as_list = false;
						draw_figures = true;
						move_figures = false;
						under_circle_hierarchy = false;
						under_quadrilateral_hierarchy = false;
						specific_work = false;
						create_container = false;
						if (ptr_container_list != nullptr)
						{
							for (unsigned i{}; i < ptr_container_list->getSize();i++)
							{
								ptr_container_list->iterator(0, i, window);
							}
							ptr_container_list->Free();
							delete ptr_container_list;
						}
					}
					if (container_as_array) std::cout << "Была выбрана работа с контейнером на основе динамического массива. " << std::endl;
					else std::cout << "Работа с контейнером на основе динамического массива была отключена. " << std::endl;
				}
				if (is_stage == 3 && submenu_container)
				{
					container_as_list = !container_as_list;
					if (container_as_array)
					{
						container_as_array = false;
						draw_figures = true;
						move_figures = false;
						under_circle_hierarchy = false;
						under_quadrilateral_hierarchy = false;
						specific_work = false;
						create_container = false;
						if (ptr_container_array != nullptr)
						{
							for (unsigned i{}; i < ptr_container_array->getSize();i++)
							{
								ptr_container_array->iterator(0, i, window);
							}
							ptr_container_array->Free();
							delete ptr_container_array;
						}
					}
					if (container_as_list) std::cout << "Была выбрана работа с контейнером на основе линейного динамического списка. " << std::endl;
					else std::cout << "Работа с контейнером на основе линейного динамического списка была отключена. " << std::endl;
				}
				if (is_stage == 4 && !create_container && (container_as_array || container_as_list))
				{
					if (container_as_array)
					{
						create_container = !create_container;
						ptr_container_array = new DynamicArrayContainer{};
					}
					if (container_as_list)
					{
						create_container = !create_container;
						ptr_container_list = new LinearDynamicListContainer{};
					}
				}
				if (is_stage == 5 && create_container && draw_figures && (container_as_array || container_as_list))
				{
					int choice_figure{ static_cast<int>(getRandomNumber(0, 5)) };
					std::cout << choice_figure << std::endl;
					if (container_as_array)
					{
						switch (choice_figure)
						{
						case 0:
						{
							ptr_container_array->addElement(CreateCircle());
							break;
						}
						case 1:
						{
							ptr_container_array->addElement(CreateEllipse());
							break;
						}
						case 2:
						{
							ptr_container_array->addElement(CreateQuadrilateral());
							break;
						}
						case 3:
						{
							ptr_container_array->addElement(CreateRectangle());
							break;
						}
						case 4:
						{
							ptr_container_array->addElement(CreateRhombus());
							break;
						}
						case 5:
						{
							ptr_container_array->addElement(CreateTrapeze());
							break;
						}
						default:
						{
							break;
						}
						}
						std::cout << "В контейнер был добавлен случайный объект со случайными параметрами." << std::endl;
						std::cout << "Сейчас в контейнере " << ptr_container_array->getSize() << " элемент (-a/-ов)." << std::endl;
					}
					else if (container_as_list)
					{
						switch (choice_figure)
						{
						case 0:
						{
							ptr_container_list->addNewNode(CreateCircle());
							break;
						}
						case 1:
						{
							ptr_container_list->addNewNode(CreateEllipse());
							break;
						}
						case 2:
						{
							ptr_container_list->addNewNode(CreateQuadrilateral());
							break;
						}
						case 3:
						{
							ptr_container_list->addNewNode(CreateRectangle());
							break;
						}
						case 4:
						{
							ptr_container_list->addNewNode(CreateRhombus());
							break;
						}
						case 5:
						{
							ptr_container_list->addNewNode(CreateTrapeze());
							break;
						}
						default:
						{
							break;
						}
						}
						std::cout << "В контейнер был добавлен случайный объект со случайными параметрами." << std::endl;
						std::cout << "Сейчас в контейнере " << ptr_container_list->getSize() << " элемент (-a/-ов)." << std::endl;
					}
				}
				if (is_stage == 6 && create_container &&  draw_figures &&
					(container_as_array || container_as_list))
				{
					if (container_as_array)
					{
						if (ptr_container_array->getSize() != 0)
						{
							ptr_container_array->iterator(1, ptr_container_array->getSize() - 1, window);
							std::cout << "Крайний элемент контейнера был удален." << std::endl;
						}
					}
					if (container_as_list)
					{
						if (ptr_container_list->getSize() != 0)
						{
							ptr_container_list->iterator(1, ptr_container_list->getSize() - 1, window);
							std::cout << "Первый элемент контейнера был удален." << std::endl;
						}
					}
				}
				if (is_stage == 7 && !draw_figures && create_container && (container_as_array || container_as_list))
				{
					draw_figures = !draw_figures;
					std::cout << "Фигуры контейнера были показаны на экране." << std::endl;
				}
				if (is_stage == 8 && draw_figures && create_container)
				{
					if (container_as_array)
					{
						if (ptr_container_array->getSize() != 0)
						{
							draw_figures = !draw_figures;
							std::cout << "Фигуры в контейнере были стерты на экране." << std::endl;
							if (move_figures)
							{
								std::cout << "Возможность передвижения фигур была выключена." << std::endl;
								move_figures = !move_figures;
							}
						}
					}
					else if (container_as_list)
					{
						if (ptr_container_list->getSize() != 0)
						{
							draw_figures = !draw_figures;
							std::cout << "Фигуры в контейнере были стерты на экране." << std::endl;
							if (move_figures)
							{
								std::cout << "Возможность передвижения фигур была выключена." << std::endl;
								move_figures = !move_figures;
							}
						}
					}
				}
				if (is_stage == 9 && draw_figures && create_container)
				{
					if (container_as_array)
					{
						if (ptr_container_array->getSize() != 0)
						{
							move_figures = !move_figures;
							if (move_figures) std::cout << "Возможность передвижения фигур была включена." << std::endl;
							else std::cout << "Возможность передвижения фигур была выключена." << std::endl;
						}
					}
					else if (container_as_list)
					{
						if (ptr_container_list->getSize() != 0)
						{
							move_figures = !move_figures;
							if (move_figures) std::cout << "Возможность передвижения фигур была включена." << std::endl;
							else std::cout << "Возможность передвижения фигур была выключена." << std::endl;
						}
					}
				}
				if (is_stage == 10 && draw_figures && create_container && (container_as_array || container_as_list))
				{
					if (container_as_array)
					{
						for (unsigned i{};i < ptr_container_array->getSize();i++)
						{
							ptr_container_array->iterator(0, i, window);
						}
						ptr_container_array->Free();
						delete ptr_container_array; ptr_container_array = nullptr;
					}
					else if (container_as_list)
					{
						for (unsigned i{};i < ptr_container_list->getSize();i++)
						{
							ptr_container_list->iterator(0, i, window);
						}
						ptr_container_list->Free();
						delete ptr_container_list; ptr_container_list = nullptr;
					}
					create_container = !create_container;
				}
				if (is_stage == 11 && draw_figures && !specific_work && create_container && (container_as_array || container_as_list))
				{
					under_circle_hierarchy = !under_circle_hierarchy;
					under_quadrilateral_hierarchy = false;
					std::cout << "Была выбрана работа с подиерархией окружностей. Работа с подиерархией четырехугольников была выключена." << std::endl;
				}
				if (is_stage == 12 && draw_figures && !specific_work && create_container && (container_as_array || container_as_list))
				{
					under_quadrilateral_hierarchy = !under_quadrilateral_hierarchy;
					under_circle_hierarchy = false;
					std::cout << "Была выбрана работа с подиерархией четырехугольников. Работа с подиерархией окружнсотей была выключена." << std::endl;
				}
				if (is_stage == 13)
				{
					if (container_as_array && ptr_container_array != nullptr)
					{
						for (unsigned i{}; i < ptr_container_array->getSize();i++)
						{
							ptr_container_array->iterator(0, i, window);
						}
						delete ptr_container_array;
					}
					else if (container_as_list && ptr_container_list != nullptr)
					{
						for (unsigned i{};i < ptr_container_list->getSize();i++)
						{
							ptr_container_list->iterator(0, i, window);
						}
						delete ptr_container_list;
					}
					std::cout << "Вы вернулись в MENU" << std::endl;
					return 0;
				}
			}
			else if (event_click.type == sf::Event::KeyPressed && move_figures && create_container && draw_figures && (container_as_array || container_as_list))
			{
				//sf::Vector2i position = sf::Mouse::getPosition(window);
				//std::cout << position.x << "\t" << position.y << std::endl;
				if (event_click.key.code == sf::Keyboard::M)
				{
					specific_work = !specific_work;
					if (under_circle_hierarchy) under_circle_hierarchy = false;
					if (under_quadrilateral_hierarchy) under_quadrilateral_hierarchy = false;
				}
				else if (!under_circle_hierarchy && !under_quadrilateral_hierarchy && !specific_work)
				{
					if (container_as_array)
					{
						for (unsigned i{}; i < ptr_container_array->getSize();i++)
						{
							switch (event_click.key.code)
							{
							case sf::Keyboard::W:
							{
								ptr_container_array->iterator(4, i, window);
								break;
							}
							case sf::Keyboard::A:
							{
								ptr_container_array->iterator(5, i, window);
								break;
							}
							case sf::Keyboard::S:
							{
								ptr_container_array->iterator(6, i, window);
								break;
							}
							case sf::Keyboard::D:
							{
								ptr_container_array->iterator(7, i, window);
								break;
							}
							default:
							{
								break;
							}
							}
						}
					}
					else if (container_as_list)
					{
						for (unsigned i{}; i < ptr_container_list->getSize();i++)
						{
							switch (event_click.key.code)
							{
							case sf::Keyboard::W:
							{
								ptr_container_list->iterator(4, i, window);
								break;
							}
							case sf::Keyboard::A:
							{
								ptr_container_list->iterator(5, i, window);
								break;
							}
							case sf::Keyboard::S:
							{
								ptr_container_list->iterator(6, i, window);
								break;
							}
							case sf::Keyboard::D:
							{
								ptr_container_list->iterator(7, i, window);
								break;
							}
							default:
							{
								break;
							}
							}
						}
					}
				}
				else if (under_circle_hierarchy && !specific_work)
				{
					if (container_as_array)
					{
						for (unsigned i{}; i < ptr_container_array->getSize();i++)
						{
							if (dynamic_cast<TCircle*>(ptr_container_array->getElement(i)) != nullptr)
							{
								switch (event_click.key.code)
								{
								case sf::Keyboard::W:
								{
									ptr_container_array->iterator(4, i, window);
									break;
								}
								case sf::Keyboard::A:
								{
									ptr_container_array->iterator(5, i, window);
									break;
								}
								case sf::Keyboard::S:
								{
									ptr_container_array->iterator(6, i, window);
									break;
								}
								case sf::Keyboard::D:
								{
									ptr_container_array->iterator(7, i, window);
									break;
								}
								case sf::Keyboard::Q:
								{
									ptr_container_array->iterator(8, i, window);
									break;
								}
								case sf::Keyboard::E:
								{
									ptr_container_array->iterator(9, i, window);
									break;
								}
								default:
								{
									break;
								}
								}
							}
						}
					}
					else if (container_as_list)
					{
						for (unsigned i{}; i < ptr_container_list->getSize();i++)
						{
							if (dynamic_cast<TCircle*>(ptr_container_list->getNodeData(i)) != nullptr)
							{
								switch (event_click.key.code)
								{
								case sf::Keyboard::W:
								{
									ptr_container_list->iterator(4, i, window);
									break;
								}
								case sf::Keyboard::A:
								{
									ptr_container_list->iterator(5, i, window);
									break;
								}
								case sf::Keyboard::S:
								{
									ptr_container_list->iterator(6, i, window);
									break;
								}
								case sf::Keyboard::D:
								{
									ptr_container_list->iterator(7, i, window);
									break;
								}
								case sf::Keyboard::Q:
								{
									ptr_container_list->iterator(8, i, window);
									break;
								}
								case sf::Keyboard::E:
								{
									ptr_container_list->iterator(9, i, window);
									break;
								}
								default:
								{
									break;
								}
								}
							}
						}
					}
				}
				else if (under_quadrilateral_hierarchy && !specific_work)
				{
					if (container_as_array)
					{
						for (unsigned i{}; i < ptr_container_array->getSize();i++)
						{
							if (dynamic_cast<TQuadrilateral*>(ptr_container_array->getElement(i)) != nullptr)
							{
								switch (event_click.key.code)
								{
								case sf::Keyboard::W:
								{
									ptr_container_array->iterator(4, i, window);
									break;
								}
								case sf::Keyboard::A:
								{
									ptr_container_array->iterator(5, i, window);
									break;
								}
								case sf::Keyboard::S:
								{
									ptr_container_array->iterator(6, i, window);
									break;
								}
								case sf::Keyboard::D:
								{
									ptr_container_array->iterator(7, i, window);
									break;
								}
								default:
								{
									break;
								}
								}
							}
						}
					}
					else if (container_as_list)
					{
						for (unsigned i{}; i < ptr_container_list->getSize();i++)
						{
							if (dynamic_cast<TQuadrilateral*>(ptr_container_list->getNodeData(i)) != nullptr)
							{
								switch (event_click.key.code)
								{
								case sf::Keyboard::W:
								{
									ptr_container_list->iterator(4, i, window);
									break;
								}
								case sf::Keyboard::A:
								{
									ptr_container_list->iterator(5, i, window);
									break;
								}
								case sf::Keyboard::S:
								{
									ptr_container_list->iterator(6, i, window);
									break;
								}
								case sf::Keyboard::D:
								{
									ptr_container_list->iterator(7, i, window);
									break;
								}
								default:
								{
									break;
								}
								}
							}
						}
					}
				}
				else if (event_click.key.code == sf::Keyboard::Space && specific_work)
				{
					specific_counter += 1;
				}
				else if (specific_work)
				{
					if (container_as_array)
					{
						switch (specific_counter % 4)
						{
						case 0:
						{
							for (unsigned i{}; i < ptr_container_array->getSize();i++)
							{
								TEllipse* ptr_ellipse{ dynamic_cast<TEllipse*>(ptr_container_array->getElement(i)) };
								if (ptr_ellipse)
								{
									switch (event_click.key.code)
									{
									case sf::Keyboard::W:
									{
										ptr_container_array->iterator(4, i, window);
										break;
									}
									case sf::Keyboard::A:
									{
										ptr_container_array->iterator(5, i, window);
										break;
									}
									case sf::Keyboard::S:
									{
										ptr_container_array->iterator(6, i, window);
										break;
									}
									case sf::Keyboard::D:
									{
										ptr_container_array->iterator(7, i, window);
										break;
									}
									case sf::Keyboard::E:
									{
										ptr_container_array->iterator(9, i, window);
										break;
									}
									case sf::Keyboard::Q:
									{
										ptr_container_array->iterator(8, i, window);
										break;
									}
									case sf::Keyboard::C:
									{
										ptr_container_array->iterator(11, i, window);
										break;
									}
									case sf::Keyboard::Z:
									{
										ptr_container_array->iterator(10, i, window);
										break;
									}
									case sf::Keyboard::R:
									{
										ptr_container_array->iterator(13, i, window);
										break;
									}
									default:
									{
										break;
									}
									}
								}
							}
							break;
						}
						case 1:
						{
							for (unsigned i{}; i < ptr_container_array->getSize();i++)
							{
								TRectangle* ptr_rectangle{ dynamic_cast<TRectangle*>(ptr_container_array->getElement(i)) };
								if (ptr_rectangle)
								{
									switch (event_click.key.code)
									{
									case sf::Keyboard::W:
									{
										ptr_container_array->iterator(4, i, window);
										break;
									}
									case sf::Keyboard::A:
									{
										ptr_container_array->iterator(5, i, window);
										break;
									}
									case sf::Keyboard::S:
									{
										ptr_container_array->iterator(6, i, window);
										break;
									}
									case sf::Keyboard::D:
									{
										ptr_container_array->iterator(7, i, window);
										break;
									}
									case sf::Keyboard::E:
									{
										ptr_container_array->iterator(9, i, window);
										break;
									}
									case sf::Keyboard::Q:
									{
										ptr_container_array->iterator(8, i, window);
										break;
									}
									case sf::Keyboard::C:
									{
										ptr_container_array->iterator(11, i, window);
										break;
									}
									case sf::Keyboard::Z:
									{
										ptr_container_array->iterator(10, i, window);
										break;
									}
									default:
									{
										break;
									}
									}
								}
							}
							break;
						}
						case 2:
						{
							for (unsigned i{}; i < ptr_container_array->getSize();i++)
							{
								TTrapeze* ptr_trapeze{ dynamic_cast<TTrapeze*>(ptr_container_array->getElement(i)) };
								if (ptr_trapeze)
								{
									switch (event_click.key.code)
									{
									case sf::Keyboard::W:
									{
										ptr_container_array->iterator(4, i, window);
										break;
									}
									case sf::Keyboard::A:
									{
										ptr_container_array->iterator(5, i, window);
										break;
									}
									case sf::Keyboard::S:
									{
										ptr_container_array->iterator(6, i, window);
										break;
									}
									case sf::Keyboard::D:
									{
										ptr_container_array->iterator(7, i, window);
										break;
									}
									case sf::Keyboard::E:
									{
										ptr_container_array->iterator(9, i, window);
										break;
									}
									case sf::Keyboard::Q:
									{
										ptr_container_array->iterator(8, i, window);
										break;
									}
									case sf::Keyboard::C:
									{
										ptr_container_array->iterator(11, i, window);
										break;
									}
									case sf::Keyboard::Z:
									{
										ptr_container_array->iterator(10, i, window);
										break;
									}
									case sf::Keyboard::F:
									{
										ptr_container_array->iterator(12, i, window);
										break;
									}
									case sf::Keyboard::R:
									{
										ptr_container_array->iterator(13, i, window);
										break;
									}
									default:
									{
										break;
									}
									}
								}
							}
							break;
						}
						case 3:
						{
							for (unsigned i{}; i < ptr_container_array->getSize();i++)
							{
								TRhombus* ptr_rhombus{ dynamic_cast<TRhombus*>(ptr_container_array->getElement(i)) };
								if (ptr_rhombus)
								{
									switch (event_click.key.code)
									{
									case sf::Keyboard::W:
									{
										ptr_container_array->iterator(4, i, window);
										break;
									}
									case sf::Keyboard::A:
									{
										ptr_container_array->iterator(5, i, window);
										break;
									}
									case sf::Keyboard::S:
									{
										ptr_container_array->iterator(6, i, window);
										break;
									}
									case sf::Keyboard::D:
									{
										ptr_container_array->iterator(7, i, window);
										break;
									}
									case sf::Keyboard::E:
									{
										ptr_container_array->iterator(9, i, window);
										break;
									}
									case sf::Keyboard::Q:
									{
										ptr_container_array->iterator(8, i, window);
										break;
									}
									case sf::Keyboard::C:
									{
										ptr_container_array->iterator(11, i, window);
										break;
									}
									case sf::Keyboard::Z:
									{
										ptr_container_array->iterator(10, i, window);
										break;
									}
									default:
									{
										break;
									}
									}
								}
							}
							break;
						}
						default:
						{
							break;
						}
						}
					}
					else if (container_as_list)
					{
						switch (specific_counter % 4)
						{
						case 0:
						{
							for (unsigned i{}; i < ptr_container_list->getSize();i++)
							{
								TEllipse* ptr_ellipse{ dynamic_cast<TEllipse*>(ptr_container_list->getNodeData(i)) };
								if (ptr_ellipse)
								{
									switch (event_click.key.code)
									{
									case sf::Keyboard::W:
									{
										ptr_container_list->iterator(4, i, window);
										break;
									}
									case sf::Keyboard::A:
									{
										ptr_container_list->iterator(5, i, window);
										break;
									}
									case sf::Keyboard::S:
									{
										ptr_container_list->iterator(6, i, window);
										break;
									}
									case sf::Keyboard::D:
									{
										ptr_container_list->iterator(7, i, window);
										break;
									}
									case sf::Keyboard::E:
									{
										ptr_container_list->iterator(9, i, window);
										break;
									}
									case sf::Keyboard::Q:
									{
										ptr_container_list->iterator(8, i, window);
										break;
									}
									case sf::Keyboard::C:
									{
										ptr_container_list->iterator(11, i, window);
										break;
									}
									case sf::Keyboard::Z:
									{
										ptr_container_list->iterator(10, i, window);
										break;
									}
									case sf::Keyboard::R:
									{
										ptr_container_list->iterator(13, i, window);
										break;
									}
									default:
									{
										break;
									}
									}
								}
							}
							break;
						}
						case 1:
						{
							for (unsigned i{}; i < ptr_container_list->getSize();i++)
							{
								TRectangle* ptr_rectangle{ dynamic_cast<TRectangle*>(ptr_container_list->getNodeData(i)) };
								if (ptr_rectangle)
								{
									switch (event_click.key.code)
									{
									case sf::Keyboard::W:
									{
										ptr_container_list->iterator(4, i, window);
										break;
									}
									case sf::Keyboard::A:
									{
										ptr_container_list->iterator(5, i, window);
										break;
									}
									case sf::Keyboard::S:
									{
										ptr_container_list->iterator(6, i, window);
										break;
									}
									case sf::Keyboard::D:
									{
										ptr_container_list->iterator(7, i, window);
										break;
									}
									case sf::Keyboard::E:
									{
										ptr_container_list->iterator(9, i, window);
										break;
									}
									case sf::Keyboard::Q:
									{
										ptr_container_list->iterator(8, i, window);
										break;
									}
									case sf::Keyboard::C:
									{
										ptr_container_list->iterator(11, i, window);
										break;
									}
									case sf::Keyboard::Z:
									{
										ptr_container_list->iterator(10, i, window);
										break;
									}
									default:
									{
										break;
									}
									}
								}
							}
							break;
						}
						case 2:
						{
							for (unsigned i{}; i < ptr_container_list->getSize();i++)
							{
								TTrapeze* ptr_trapeze{ dynamic_cast<TTrapeze*>(ptr_container_list->getNodeData(i)) };
								if (ptr_trapeze)
								{
									switch (event_click.key.code)
									{
									case sf::Keyboard::W:
									{
										ptr_container_list->iterator(4, i, window);
										break;
									}
									case sf::Keyboard::A:
									{
										ptr_container_list->iterator(5, i, window);
										break;
									}
									case sf::Keyboard::S:
									{
										ptr_container_list->iterator(6, i, window);
										break;
									}
									case sf::Keyboard::D:
									{
										ptr_container_list->iterator(7, i, window);
										break;
									}
									case sf::Keyboard::E:
									{
										ptr_container_list->iterator(9, i, window);
										break;
									}
									case sf::Keyboard::Q:
									{
										ptr_container_list->iterator(8, i, window);
										break;
									}
									case sf::Keyboard::C:
									{
										ptr_container_list->iterator(11, i, window);
										break;
									}
									case sf::Keyboard::Z:
									{
										ptr_container_list->iterator(10, i, window);
										break;
									}
									case sf::Keyboard::F:
									{
										ptr_container_list->iterator(12, i, window);
										break;
									}
									case sf::Keyboard::R:
									{
										ptr_container_list->iterator(13, i, window);
										break;
									}
									default:
									{
										break;
									}
									}
								}
							}
							break;
						}
						case 3:
						{
							for (unsigned i{}; i < ptr_container_list->getSize();i++)
							{
								TRhombus* ptr_rhombus{ dynamic_cast<TRhombus*>(ptr_container_list->getNodeData(i)) };
								if (ptr_rhombus)
								{
									switch (event_click.key.code)
									{
									case sf::Keyboard::W:
									{
										ptr_container_list->iterator(4, i, window);
										break;
									}
									case sf::Keyboard::A:
									{
										ptr_container_list->iterator(5, i, window);
										break;
									}
									case sf::Keyboard::S:
									{
										ptr_container_list->iterator(6, i, window);
										break;
									}
									case sf::Keyboard::D:
									{
										ptr_container_list->iterator(7, i, window);
										break;
									}
									case sf::Keyboard::E:
									{
										ptr_container_list->iterator(9, i, window);
										break;
									}
									case sf::Keyboard::Q:
									{
										ptr_container_list->iterator(8, i, window);
										break;
									}
									case sf::Keyboard::C:
									{
										ptr_container_list->iterator(11, i, window);
										break;
									}
									case sf::Keyboard::Z:
									{
										ptr_container_list->iterator(10, i, window);
										break;
									}
									default:
									{
										break;
									}
									}
								}
							}
							break;
						}
						default:
						{
							break;
						}
						}
					}
				}
			}
		}

		work_container_rect_button.Show(window); work_container_text_button.Show(window);
		if (submenu_container)
		{
			dynamic_array_rect_button.Show(window); dynamic_array_text_button.Show(window);
			linear_dynamic_list_rect_button.Show(window);linear_dynamic_list_text_button.Show(window);
			if (container_as_array || container_as_list)
			{
				create_container_rect_button.Show(window); create_container_text_button.Show(window);
				add_element_rect_button.Show(window); add_element_text_button.Show(window);
				delete_element_rect_button.Show(window); delete_element_text_button.Show(window);
				show_elements_rect_button.Show(window); show_elements_text_button.Show(window);
				erase_elements_rect_button.Show(window); erase_elements_text_button.Show(window);
				move_elements_rect_button.Show(window); move_elements_text_button.Show(window); 
				destroy_container_rect_button.Show(window); destroy_container_text_button.Show(window);
			}
		}
		back_rect_button.Show(window); back_text_button.Show(window);
		image_rect.Show(window); image_text.Show(window);
		switch_mode_text.Show(window);
		select_specific_class_text.Show(window);
		move_shapes.Show(window);

		if (create_container)
		{
			if (container_as_array)
			{
				if (ptr_container_array->getSize() != 0)
				{
					circle_hierarchy_rect_button.Show(window); circle_hierarchy_text_button.Show(window);
					quadrilateral_hierarchy_rect_button.Show(window); quadrilateral_hierarchy_text_button.Show(window);
				}
			}
			else if (container_as_list)
			{
				if (ptr_container_list->getSize() != 0)
				{
					circle_hierarchy_rect_button.Show(window); circle_hierarchy_text_button.Show(window);
					quadrilateral_hierarchy_rect_button.Show(window); quadrilateral_hierarchy_text_button.Show(window);
				}
			}
		}

		if (under_circle_hierarchy)
		{
			special_movement_circle.Show(window);
		}

		if (specific_work)
		{
			switch (specific_counter % 4)
			{
			case 0:
				special_movement_ellipse.Show(window);
				ellipse_text.Show(window);
				break;
			case 1:
				special_movement_rectangle.Show(window);
				rectangle_text.Show(window);
				break;
			case 2:
				special_movement_trapeze.Show(window);
				trapeze_text.Show(window);
				break;
			case 3:
				special_movement_rhombus.Show(window);
				rhombus_text.Show(window);
				break;
			default:
				break;
			}
		}

		if (specific_work) specific_mode_text.Show(window);
		else usually_mode_text.Show(window);

		if (draw_figures && create_container)
		{
			if (container_as_array)
			{
				for (unsigned i{}; i < ptr_container_array->getSize();i++)
				{
					ptr_container_array->iterator(2, i, window);
				}
			}
			else if (container_as_list)
			{
				for (unsigned i{};i < ptr_container_list->getSize();i++)
				{
					ptr_container_list->iterator(2, i, window);
				}
			}

		}
		window.display();
	}
	return 0;
}


bool stage_0_menu(sf::RenderWindow& window)
{
	std::cout << "Нажмите MENU или выйдите из программы." << std::endl;
	int is_stage{};

	/*Кнопка меню*/
	//Текст MENU
	User_Text_Button menu_text{ "Comic_Sans_MS.TTF", "MENU", 50, 685, 340 };
	//Прямоугольник MENU
	User_Rect_Button menu_rect{ 625, 330, 5, 300, 80 };

	/*Кнопка выход*/
	//Текст EXIT
	User_Text_Button exit_text{ "Comic_Sans_MS.TTF", "EXIT", 50, 685, 440 };
	//Прямоугольник EXIT
	User_Rect_Button exit_rect{ 625, 430, 5, 300, 80 };

	while (window.isOpen())
	{
		//Переменная для перехода между меню и подменю
		is_stage = 0;

		window.clear(sf::Color(137, 20, 190));
		menu_text.m_setFillColorDefault(); menu_rect.m_setOutlineColorDefault();
		exit_text.m_setFillColorDefault(); exit_rect.m_setOutlineColorDefault();

		if (sf::IntRect(610, 320, 320, 100).contains(sf::Mouse::getPosition(window)))
		{
			menu_text.m_setFillColor(255, 127, 39);
			menu_rect.m_setOutlineColor(165, 15, 203);
			is_stage = 1;
		}

		if (sf::IntRect(610, 420, 320, 100).contains(sf::Mouse::getPosition(window)))
		{
			exit_text.m_setFillColor(255, 127, 39);
			exit_rect.m_setOutlineColor(165, 15, 203);
			is_stage = 2;
		}

		sf::Event event_click;
		while (window.pollEvent(event_click))
		{
			if (event_click.type == event_click.MouseButtonReleased && event_click.mouseButton.button == sf::Mouse::Left && is_stage == 1)
			{
				std::cout << "Вы перешли в функциональную часть программы." << std::endl;
				stage_1_work_with_mass(window);
			}
			if (event_click.type == event_click.MouseButtonReleased && event_click.mouseButton.button == sf::Mouse::Left && is_stage == 2)
			{
				std::cout << "Вы вышли из программы. Окно закрыто." << std::endl;
				window.close();
			}
			else if (event_click.type == sf::Event::Closed)
			{
				std::cout << "Окно было закрыто." << std::endl;
				window.close();
			}
		};

		menu_rect.Show(window); menu_text.Show(window);
		exit_rect.Show(window); exit_text.Show(window);

		window.display();
	}

	return false;
}

