#include <SFML/Graphics.hpp>
#include <iostream>

#include "MyFuncs.h"
#include "CircleFuncs.h"
#include "UserButton.h"
#include "Circle.h"
#include "Rectangle.h"
#include "LineSegment.h"

void random_move_circles(Circle** ptr_circles_mass, int num_element)
{
	while (true)
	{
		float dx{ getRandomNumber(-50,50) }, dy{ getRandomNumber(-50,50) };
		if ((ptr_circles_mass[num_element]->getCoordinateX() - ptr_circles_mass[num_element]->getRadius() + dx) >= 465 &&
			(ptr_circles_mass[num_element]->getCoordinateX() + ptr_circles_mass[num_element]->getRadius() + dx) <= 1415 &&
			(ptr_circles_mass[num_element]->getCoordinateY() - ptr_circles_mass[num_element]->getRadius() + dy) >= 115 &&
			(ptr_circles_mass[num_element]->getCoordinateY() + ptr_circles_mass[num_element]->getRadius() + dy) <= 715)
		{
			ptr_circles_mass[num_element]->MoveTo(dx, dy);
			break;
		}
	}
}

void create_random_circle(Circle**& ptr_circles_mass, int& count_size_mass_circles)
{
	Circle* ptr_obj_circle{ nullptr };
	float restrict_radius{ getRandomNumber(10, 90) };
	float restrict_x{ getRandomNumber(465 + restrict_radius, 1415 - restrict_radius) };
	float restrict_y{ getRandomNumber(115 + restrict_radius, 715 - restrict_radius) };
	ptr_obj_circle = new Circle{ restrict_radius, restrict_x, restrict_y };
	ptr_obj_circle->setColorOutline(getRandomNumber(0, 255), getRandomNumber(0, 255), getRandomNumber(0, 255));
	ptr_obj_circle->setColor(getRandomNumber(0, 255), getRandomNumber(0, 255), getRandomNumber(0, 255));
	ptr_obj_circle->setVisibility(getRandomNumber(50, 255));
	push_back_shape<Circle>(ptr_circles_mass, count_size_mass_circles, ptr_obj_circle);
}

int work_with_circles(sf::RenderWindow& window, Circle**& ptr_circles_mass, int& count_size_mass_circles, 
	Rectangle** ptr_rectangles_mass, int count_size_mass_rectangles,Line_Segment** ptr_linesegments_mass, int count_size_mass_linesegments)
{
	/*Кнопка CREATE*/
	User_Text_Button create_text_button{ "Comic_Sans_MS.TTF", "Create element of circles", 30, 15, 20 };
	User_Rect_Button create_rect_button{ 10, 10, 5, 390, 60 };

	/*Кнопка MOVETO*/
	User_Text_Button moveTo_text_button{ "Comic_Sans_MS.TTF", "Move to...", 30, 15, 110 };
	User_Rect_Button moveTo_rect_button{ 10, 100, 5, 200, 60 };

	/*Кнопка BACK*/
	User_Text_Button back_text_button{ "Comic_Sans_MS.TTF", "Back", 30, 50, 740 };
	User_Rect_Button back_rect_button{ 10, 730, 5, 200, 60 };

	//Текст IMAGE
	User_Text_Button image_text{ "Comic_Sans_MS.TTF", "Image", 60, 850, 10 };
	User_Rect_Button image_rect(465, 115, 0, 950, 600); image_rect.m_setColor(178, 143, 252);

	/*Кнопка COMBINE OBJECTS*/
	User_Text_Button combine_objects_text_button{ "Comic_Sans_MS.TTF", "Combine objects", 30, 478, 25 };
	User_Rect_Button combine_objects_rect_button{ 470, 10, 5, 250, 60 };

	/*Кнопка RANDOM MOVE*/
	User_Text_Button random_move_text_button{ "Comic_Sans_MS.TTF", "Random move", 30, 1230, 25 };
	User_Rect_Button random_move_rect_button{ 1200, 10, 5, 250, 60 };

	/*Кнопка SHOW CIRCLE*/
	User_Text_Button show_text_button{ "Comic_Sans_MS.TTF", "Show circle", 30, 15, 200 };
	User_Rect_Button show_rect_button{ 10, 190, 5, 200, 60 };

	//Тексты управления фигурами
	User_Text_Button move_shapes{ "Comic_Sans_MS.TTF", "Move up shape (W)    Move down shape (S)   Move left shape (A)    Move right shape (D)", 20, 260, 770 };
	User_Text_Button special_movements{ "Comic_Sans_MS.TTF", "Decrease radius(Q)           Increase radius(E)", 20, 260, 730 };

	/*Кнопка удаления элемента*/
	User_Text_Button delete_element_text_button{ "Comic_Sans_MS.TTF", "Delete element", 30, 15, 290 };
	User_Rect_Button delete_element_rect_button{ 10, 280, 5, 240, 60 };

	/*Кнопка удаления всех элементов*/
	User_Text_Button delete_all_elements_text_button{ "Comic_Sans_MS.TTF", "Delete all elements", 30, 15, 380 };
	User_Rect_Button delete_all_elements_rect_button{ 10, 370, 5, 300, 60 };

	/*Кнопка создания 30 элементов*/
	User_Text_Button create_30_elements_text_button{ "Comic_Sans_MS.TTF", "Create array of circles", 30, 15, 470 };
	User_Rect_Button create_30_elements_rect_button{ 10, 460, 5, 350, 60 };

	int is_stage{};

	bool show_circle{ true }; //рисовать круг или удалить объект, освободив память
	bool move_circle{ false }; //позволить кругу двигаться или нет
	bool combine_objects{ false }; //есть ли работа с массивом объектов
	bool save_size_mass_circles{ true };//сохранить размер массива для SHOW кнопки или нет
	bool create_30_circles{ false }; //создать массив из 30 кругов, добавив его к основному
	int iteration_counter_combine_objs{}; //итератор для кнопки SHOW при работе с массивом

	while (window.isOpen())
	{
		is_stage = 0;
		window.clear(sf::Color(137, 20, 190));

		create_text_button.m_setFillColorDefault(); create_rect_button.m_setOutlineColorDefault();

		moveTo_text_button.m_setFillColorDefault();
		if (move_circle) moveTo_rect_button.m_setOutlineColor(247, 30, 241);
		else moveTo_rect_button.m_setOutlineColorDefault();

		back_text_button.m_setFillColorDefault(); back_rect_button.m_setOutlineColorDefault();

		combine_objects_text_button.m_setFillColorDefault();
		if (combine_objects && count_size_mass_circles != 0) combine_objects_rect_button.m_setOutlineColor(247, 30, 241);
		else combine_objects_rect_button.m_setOutlineColorDefault();

		random_move_text_button.m_setFillColorDefault(); random_move_rect_button.m_setOutlineColorDefault();
		delete_element_text_button.m_setFillColorDefault(); delete_element_rect_button.m_setOutlineColorDefault();

		show_text_button.m_setFillColorDefault();
		if (show_circle && count_size_mass_circles != 0) show_rect_button.m_setOutlineColor(247, 30, 241);
		else show_rect_button.m_setOutlineColorDefault();

		create_30_elements_text_button.m_setFillColorDefault();
		if (create_30_circles) create_30_elements_rect_button.m_setOutlineColor(247, 30, 241);
		else create_30_elements_rect_button.m_setOutlineColorDefault();

		delete_all_elements_text_button.m_setFillColorDefault(); delete_all_elements_rect_button.m_setOutlineColorDefault();

		if (sf::IntRect(5, 0, 400, 80).contains(sf::Mouse::getPosition(window))) //create
		{
			create_text_button.m_setFillColor(255, 127, 39);
			create_rect_button.m_setOutlineColor(165, 15, 203);
			is_stage = 1;
		}

		if (sf::IntRect(5, 90, 210, 80).contains(sf::Mouse::getPosition(window))) //moveto
		{
			moveTo_text_button.m_setFillColor(255, 127, 39);
			moveTo_rect_button.m_setOutlineColor(165, 15, 203);
			is_stage = 2;
		}

		if (sf::IntRect(5, 180, 210, 80).contains(sf::Mouse::getPosition(window))) // show
		{
			show_text_button.m_setFillColor(255, 127, 39);
			show_rect_button.m_setOutlineColor(165, 15, 203);
			is_stage = 3;
		}

		if (sf::IntRect(5, 720, 210, 80).contains(sf::Mouse::getPosition(window))) //back
		{
			back_text_button.m_setFillColor(255, 127, 39);
			back_rect_button.m_setOutlineColor(165, 15, 203);
			is_stage = 4;
		}

		if (sf::IntRect(465, 0, 260, 80).contains(sf::Mouse::getPosition(window))) //combine
		{
			combine_objects_text_button.m_setFillColor(255, 127, 39);
			combine_objects_rect_button.m_setOutlineColor(165, 15, 203);
			is_stage = 5;
		}

		if (sf::IntRect(1195, 0, 260, 80).contains(sf::Mouse::getPosition(window))) //random move
		{
			random_move_text_button.m_setFillColor(255, 127, 39);
			random_move_rect_button.m_setOutlineColor(165, 15, 203);
			is_stage = 6;
		}

		if (sf::IntRect(5, 270, 250, 80).contains(sf::Mouse::getPosition(window))) //delete element
		{
			delete_element_text_button.m_setFillColor(255, 127, 39);
			delete_element_rect_button.m_setOutlineColor(165, 15, 203);
			is_stage = 7;
		}

		if (sf::IntRect(5, 360, 310, 80).contains(sf::Mouse::getPosition(window))) //delete elements
		{
			delete_all_elements_text_button.m_setFillColor(255, 127, 39);
			delete_all_elements_rect_button.m_setOutlineColor(165, 15, 203);
			is_stage = 8;
		}

		if (sf::IntRect(5, 430, 360, 80).contains(sf::Mouse::getPosition(window))) //create 30 elements
		{
			create_30_elements_text_button.m_setFillColor(255, 127, 39);
			create_30_elements_rect_button.m_setOutlineColor(165, 15, 203);
			is_stage = 9;
		}

		sf::Event event_click;
		while (window.pollEvent(event_click))
		{
			if (event_click.type == sf::Event::Closed) 
			{ 
				delete_mass_objects<Circle>(ptr_circles_mass, count_size_mass_circles);
				delete_mass_objects<Rectangle>(ptr_rectangles_mass, count_size_mass_rectangles);
				delete_mass_objects<Line_Segment>(ptr_linesegments_mass, count_size_mass_linesegments);
				std::cout << "Все массивы примитивов были удалены из кучи. Окно закрыто." << std::endl;
				window.close(); 
				return 0;
			}
			else if (event_click.type == event_click.MouseButtonReleased && event_click.mouseButton.button == sf::Mouse::Left)
			{
				//sf::Vector2i position = sf::Mouse::getPosition(window);
				//std::cout << position.x << "\t" << position.y << std::endl;

				if (is_stage == 1)
				{
					if (create_30_circles)
					{
						show_circle = true;
						save_size_mass_circles = true;
						for (unsigned i{}; i < 30;i++)
						{
							if (count_size_mass_circles == 0)
							{
								Circle* ptr_obj_circle{ nullptr };
								ptr_obj_circle = new Circle{};
								push_back_shape<Circle>(ptr_circles_mass, count_size_mass_circles, ptr_obj_circle);
							}
							else
							{
								create_random_circle(ptr_circles_mass, count_size_mass_circles);
							}
						}
						if (count_size_mass_circles - 30 != 0) std::cout << "Массив кругов был создан конструктором со случайными параметрами." << std::endl;
						else std::cout << "Массив кругов был создан конструктором со случайными параметрами. Первый круг - конструктором по умолчанию." << std::endl;
						std::cout << "На окне SFML находится " << count_size_mass_circles << " кругов." << std::endl;
					}
					else if (count_size_mass_circles == 0)
					{
						Circle* ptr_obj_circle{ nullptr };
						ptr_obj_circle = new Circle{};
						push_back_shape<Circle>(ptr_circles_mass, count_size_mass_circles, ptr_obj_circle);
						show_circle = true;
						save_size_mass_circles = true;
						std::cout << "Круг " << count_size_mass_circles << " был создан конструктором по умолчанию." << std::endl;
					}
					else
					{
						create_random_circle(ptr_circles_mass, count_size_mass_circles);
						show_circle = true;
						save_size_mass_circles = true;
						std::cout << "Круг " << count_size_mass_circles << " был создан конструктором со случайными параметрами." << std::endl;
					}
				}
				if (is_stage == 2 && count_size_mass_circles != 0)
				{
					move_circle = !move_circle;

					if (!combine_objects)
					{
						if (move_circle) std::cout << "Передвижение последней созданной фигуры включено." << std::endl;
						else std::cout << "Передвижение последней созданной фигуры выключено." << std::endl;
					}
					else
					{
						if (move_circle) std::cout << "Передвижение всех созданных фигур включено." << std::endl;
						else std::cout << "Передвижение всех созданных фигур выключено." << std::endl;
					}
				}
				if (is_stage == 3 && (count_size_mass_circles != 0 || count_size_mass_circles == 0 && !show_circle))
				{
					if (save_size_mass_circles) iteration_counter_combine_objs = count_size_mass_circles;
					show_circle = !show_circle;
					if (!show_circle)
					{
						if (!combine_objects)
						{
							std::cout << "Последняя созданная окружность была стерта." << std::endl;
							ptr_circles_mass[count_size_mass_circles - 1]->Free(ptr_circles_mass, count_size_mass_circles);
							move_circle = false;
						}
						else
						{
							std::cout << "Все окружности были стерты." << std::endl;
							save_size_mass_circles = false;
							for (unsigned i{}; i < iteration_counter_combine_objs;i++)
							{
								ptr_circles_mass[i]->Free(ptr_circles_mass, count_size_mass_circles);
							}
							move_circle = false;
						}
					}
					else
					{
						if (!combine_objects)
						{
							create_random_circle(ptr_circles_mass, count_size_mass_circles);
							std::cout << "Круг " << count_size_mass_circles << " был создан конструктором со случайными параметрами." << std::endl;
							move_circle = true;
						}
						else
						{
							for (unsigned i{}; i < iteration_counter_combine_objs; i++)
							{
								create_random_circle(ptr_circles_mass, count_size_mass_circles);
								std::cout << "Круг " << count_size_mass_circles << " был создан конструктором со случайными параметрами." << std::endl;
							}
							move_circle = true;
						}
					}
				}
				if (is_stage == 4)
				{
					std::cout << "Выберите следующий примитив или вернитесь в MENU." << std::endl;
					return 0;
				}
				if (is_stage == 5 && count_size_mass_circles >= 2)
				{
					show_circle = true; move_circle = false;
					combine_objects = !combine_objects;
					if (combine_objects && count_size_mass_circles != 0)
						std::cout << "Режим группового изменения свойств объектов был включен. Возможность передвижения объектов выключена." << std::endl;
					else if (!combine_objects && count_size_mass_circles != 0)
						std::cout << "Режим группового изменения свойств объектов был выключен. Возможность передвижения объектов выключена." << std::endl;
				};
				if (is_stage == 6 && move_circle && count_size_mass_circles != 0)
				{
					if (!combine_objects)
					{
						std::cout << "Последняя созданная окружность была перемещена на случайные координаты [-50; 50]." << std::endl;
						random_move_circles(ptr_circles_mass, count_size_mass_circles - 1);
					}
					else
					{
						for (unsigned i{}; i < count_size_mass_circles;i++)
						{
							random_move_circles(ptr_circles_mass, i);
						}
						std::cout << "Все окружности были перемещены на случайные координаты[-50; 50]." << std::endl;
					}
				}
				if (is_stage == 7 && count_size_mass_circles != 0)
				{
					std::cout << "Окружность " << count_size_mass_circles << " была удалена." << std::endl;
					save_size_mass_circles = true;
					delete_element_shape<Circle>(ptr_circles_mass, count_size_mass_circles);
					if (count_size_mass_circles < 2)
					{
						if (combine_objects)
							std::cout << "Режим группового изменения свойств объектов был выключен. Возможность передвижения объектов выключена." << std::endl;
						combine_objects = false;
					}
					move_circle = false;
				}
				if (is_stage == 8)
				{
					std::cout << "Все окружности были стерты." << std::endl;
					delete_elements_shape<Circle>(ptr_circles_mass, count_size_mass_circles);
					combine_objects = false;
					move_circle = false;
					std::cout << "Режим группового изменения свойств объектов был выключен. Возможность передвижения объектов выключена." << std::endl;
				}
				if (is_stage == 9)
				{
					create_30_circles = !create_30_circles;
					if (create_30_circles)
						std::cout << "Режим создания объектов целым массивом был включен." << std::endl;
					else if (!create_30_circles)
						std::cout << "Режим создания объектов целым массивом был выключен." << std::endl;
				}
			}
			else if (event_click.type == sf::Event::KeyPressed && move_circle)
			{
				
				if (!combine_objects)
				{
					if (event_click.key.code == sf::Keyboard::W && (ptr_circles_mass[count_size_mass_circles - 1]->getCoordinateY() - 
						ptr_circles_mass[count_size_mass_circles - 1]->getRadius() - 10) >= 115)
					{
						ptr_circles_mass[count_size_mass_circles - 1]->MoveTo(0, -10);
					}
					if (event_click.key.code == sf::Keyboard::A && (ptr_circles_mass[count_size_mass_circles - 1]->getCoordinateX() - 
						ptr_circles_mass[count_size_mass_circles - 1]->getRadius() - 10) >= 465)
					{
						ptr_circles_mass[count_size_mass_circles - 1]->MoveTo(-10, 0);
					}
					if (event_click.key.code == sf::Keyboard::S && (ptr_circles_mass[count_size_mass_circles - 1]->getCoordinateY() + 10 +
						ptr_circles_mass[count_size_mass_circles - 1]->getRadius()) <= 715)
					{
						ptr_circles_mass[count_size_mass_circles - 1]->MoveTo(0, 10);
					}
					if (event_click.key.code == sf::Keyboard::D && (ptr_circles_mass[count_size_mass_circles - 1]->getCoordinateX() + 10 +
						ptr_circles_mass[count_size_mass_circles - 1]->getRadius()) <= 1415)
					{
						ptr_circles_mass[count_size_mass_circles - 1]->MoveTo(10, 0);
					}
					if (event_click.key.code == sf::Keyboard::E && 
						((ptr_circles_mass[count_size_mass_circles - 1]->getCoordinateX() -	ptr_circles_mass[count_size_mass_circles - 1]->getRadius() - 1) >= 465 && 
						(ptr_circles_mass[count_size_mass_circles - 1]->getCoordinateX() + ptr_circles_mass[count_size_mass_circles - 1]->getRadius() + 1) <= 1415 &&
						(ptr_circles_mass[count_size_mass_circles - 1]->getCoordinateY() - ptr_circles_mass[count_size_mass_circles - 1]->getRadius() - 1) >= 115 &&
						(ptr_circles_mass[count_size_mass_circles - 1]->getCoordinateY() + ptr_circles_mass[count_size_mass_circles - 1]->getRadius() + 1) <= 715))
					{
						ptr_circles_mass[count_size_mass_circles - 1]->setRadius(1);
					}
					if (event_click.key.code == sf::Keyboard::Q && (ptr_circles_mass[count_size_mass_circles - 1]->getRadius() - 1 >= 15))
					{
						ptr_circles_mass[count_size_mass_circles - 1]->setRadius(-1);
					}
				}
				else
				{
					if (event_click.key.code == sf::Keyboard::W)
					{
						for (unsigned i{}; i < count_size_mass_circles;i++)
						{
							if (ptr_circles_mass[i]->getCoordinateY() - ptr_circles_mass[i]->getRadius() - 10 >= 115)
							{
								ptr_circles_mass[i]->MoveTo(0, -10);
							}
						}
					}
					if (event_click.key.code == sf::Keyboard::A)
					{
						for (unsigned i{}; i < count_size_mass_circles;i++)
						{
							if (ptr_circles_mass[i]->getCoordinateX() - ptr_circles_mass[i]->getRadius() - 10 >= 465)
								ptr_circles_mass[i]->MoveTo(-10, 0);
						}
					}
					if (event_click.key.code == sf::Keyboard::S)
					{
						for (unsigned i{}; i < count_size_mass_circles;i++)
						{
							if (ptr_circles_mass[i]->getCoordinateY() + ptr_circles_mass[i]->getRadius() + 10 <= 715)
								ptr_circles_mass[i]->MoveTo(0, 10);
						}
					}
					if (event_click.key.code == sf::Keyboard::D)
					{
						for (unsigned i{}; i < count_size_mass_circles;i++)
						{
							if (ptr_circles_mass[i]->getCoordinateX() + ptr_circles_mass[i]->getRadius() + 10 <= 1415)
								ptr_circles_mass[i]->MoveTo(10, 0);
						}
					}
					if (event_click.key.code == sf::Keyboard::E)
					{
						for (unsigned i{}; i < count_size_mass_circles;i++)
						{
							if (((ptr_circles_mass[i]->getCoordinateX() - ptr_circles_mass[i]->getRadius() - 1) >= 465 &&
								(ptr_circles_mass[i]->getCoordinateX() + ptr_circles_mass[i]->getRadius() + 1) <= 1415 &&
								(ptr_circles_mass[i]->getCoordinateY() - ptr_circles_mass[i]->getRadius() - 1) >= 115 &&
								(ptr_circles_mass[i]->getCoordinateY() + ptr_circles_mass[i]->getRadius() + 1) <= 715))
							{
								ptr_circles_mass[i]->setRadius(1);
							}
						}
					}
					if (event_click.key.code == sf::Keyboard::Q)
					{
						for (unsigned i{}; i < count_size_mass_circles;i++)
						{
							if ((ptr_circles_mass[i]->getRadius() - 1) >= 15)
							{
								ptr_circles_mass[i]->setRadius(-1);
							}
						}
					}
				}
			}
		}
		image_rect.Show(window);

		for (unsigned i{}; i < count_size_mass_rectangles;i++)
		{
			ptr_rectangles_mass[i]->Show(window);
		}

		for (unsigned i{}; i < count_size_mass_linesegments;i++)
		{
			ptr_linesegments_mass[i]->Show(window);
		}

		for (unsigned i{}; i < count_size_mass_circles;i++)
		{
			ptr_circles_mass[i]->Show(window);
		}


		create_rect_button.Show(window); create_text_button.Show(window);
		moveTo_rect_button.Show(window); moveTo_text_button.Show(window);
		show_rect_button.Show(window); show_text_button.Show(window);
		back_rect_button.Show(window); back_text_button.Show(window);
		combine_objects_rect_button.Show(window); combine_objects_text_button.Show(window);
		random_move_rect_button.Show(window); random_move_text_button.Show(window);
		delete_element_rect_button.Show(window); delete_element_text_button.Show(window);
		create_30_elements_rect_button.Show(window); create_30_elements_text_button.Show(window);
		if (combine_objects)
		{
			delete_all_elements_rect_button.Show(window);
			delete_all_elements_text_button.Show(window);
		}

		image_text.Show(window); special_movements.Show(window); move_shapes.Show(window);

		window.display();
	}

	return 0;
}