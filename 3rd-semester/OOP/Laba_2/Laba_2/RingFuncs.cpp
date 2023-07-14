#include <SFML/Graphics.hpp>
#include <iostream>

#include "MyFuncs.h"
#include "UserButton.h"
#include "RingFuncs.h"
#include "Ring.h"
#include "Circle.h"
#include "Rectangle.h"
#include "LineSegment.h"
#include "ComplexObject.h"

void random_move_rings(Ring** ptr_rings_mass, int num_element)
{
	while (true)
	{
		float dx{ getRandomNumber(-50,50) }, dy{ getRandomNumber(-50,50) };
		if ((ptr_rings_mass[num_element]->getOuterCircle().getCoordinateX() - ptr_rings_mass[num_element]->getOuterCircle().getRadius() + dx) >= 465 &&
			(ptr_rings_mass[num_element]->getOuterCircle().getCoordinateX() + ptr_rings_mass[num_element]->getOuterCircle().getRadius() + dx) <= 1415 &&
			(ptr_rings_mass[num_element]->getOuterCircle().getCoordinateY() - ptr_rings_mass[num_element]->getOuterCircle().getRadius() + dy) >= 115 &&
			(ptr_rings_mass[num_element]->getOuterCircle().getCoordinateY() + ptr_rings_mass[num_element]->getOuterCircle().getRadius() + dy) <= 715)
		{
			ptr_rings_mass[num_element]->MoveTo(dx, dy);
			break;
		}
	}
}

void create_random_ring(Ring**& ptr_rings_mass, int& count_size_mass_rings)
{
	Ring* ptr_obj_ring{ nullptr };
	while (true)
	{
		float radius_outer_circle{ getRandomNumber(40, 90) };
		float radius_inner_circle{ getRandomNumber(10, radius_outer_circle - 10) };
		float x_ring{ getRandomNumber(465, 1415) };
		float y_ring{ getRandomNumber(115, 715) };
		Circle inner_circle{ radius_inner_circle, {x_ring, y_ring} };
		Circle outer_circle{ radius_outer_circle, {x_ring, y_ring} };
		if (outer_circle.getRadius() - inner_circle.getRadius() > 10)
		{
			ptr_obj_ring = new Ring{ inner_circle, outer_circle };
			break;
		}
		else
		{
			std::cout << "!!!Созданный объект не удовлетворил условиям создания в ходе попытке реализации." << std::endl;
			std::cout << ".......Заново......." << std::endl;
		}
		
	}
	ptr_obj_ring->getInnerCircle().setColorOutline(getRandomNumber(0, 255), getRandomNumber(0, 255), getRandomNumber(0, 255));
	ptr_obj_ring->getInnerCircle().setColor(178, 143, 252);
	ptr_obj_ring->getInnerCircle().setVisibility(255);
	ptr_obj_ring->getOuterCircle().setColorOutline(getRandomNumber(0, 255), getRandomNumber(0, 255), getRandomNumber(0, 255));
	ptr_obj_ring->getOuterCircle().setColor(getRandomNumber(0, 255), getRandomNumber(0, 255), getRandomNumber(0, 255));
	ptr_obj_ring->getOuterCircle().setVisibility(getRandomNumber(50, 255));
	push_back_shape<Ring>(ptr_rings_mass, count_size_mass_rings, ptr_obj_ring);
}

int work_with_rings(sf::RenderWindow& window, Ring**& ptr_rings_mass, int& count_size_mass_rings, Circle** ptr_circles_mass, int count_size_mass_circles,
	Rectangle** ptr_rectangles_mass, int count_size_mass_rectangles, Line_Segment** ptr_linesegments_mass, int count_size_mass_linesegments,
	ComplexObject** ptr_complex_objects_mass, int count_size_mass_complex_objects)
{
	/*Кнопка CREATE*/
	User_Text_Button create_text_button{ "Comic_Sans_MS.TTF", "Create element of rings", 30, 15, 20 };
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

	/*Кнопка SHOW RING*/
	User_Text_Button show_text_button{ "Comic_Sans_MS.TTF", "Show ring", 30, 15, 200 };
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
	User_Text_Button create_30_elements_text_button{ "Comic_Sans_MS.TTF", "Create array of rings", 30, 15, 470 };
	User_Rect_Button create_30_elements_rect_button{ 10, 460, 5, 350, 60 };

	int is_stage{};

	bool show_ring{ true }; //рисовать кольцо или удалить объект, освободив память
	bool move_ring{ false }; //позволить кольцу двигаться или нет
	bool combine_objects{ false }; //есть ли работа с массивом объектов
	bool save_size_mass_rings{ true };//сохранить размер массива для SHOW кнопки или нет
	bool create_30_rings{ false }; //создать массив из 30 колец, добавив его к основному
	int iteration_counter_combine_objs{}; //итератор для кнопки SHOW при работе с массивом

	while (window.isOpen())
	{
		is_stage = 0;
		window.clear(sf::Color(137, 20, 190));

		create_text_button.m_setFillColorDefault(); create_rect_button.m_setOutlineColorDefault();

		moveTo_text_button.m_setFillColorDefault();
		if (move_ring) moveTo_rect_button.m_setOutlineColor(247, 30, 241);
		else moveTo_rect_button.m_setOutlineColorDefault();

		back_text_button.m_setFillColorDefault(); back_rect_button.m_setOutlineColorDefault();

		combine_objects_text_button.m_setFillColorDefault();
		if (combine_objects && count_size_mass_rings != 0) combine_objects_rect_button.m_setOutlineColor(247, 30, 241);
		else combine_objects_rect_button.m_setOutlineColorDefault();

		random_move_text_button.m_setFillColorDefault(); random_move_rect_button.m_setOutlineColorDefault();
		delete_element_text_button.m_setFillColorDefault(); delete_element_rect_button.m_setOutlineColorDefault();

		show_text_button.m_setFillColorDefault();
		if (show_ring && count_size_mass_rings != 0) show_rect_button.m_setOutlineColor(247, 30, 241);
		else show_rect_button.m_setOutlineColorDefault();

		create_30_elements_text_button.m_setFillColorDefault();
		if (create_30_rings) create_30_elements_rect_button.m_setOutlineColor(247, 30, 241);
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
				delete_mass_objects<Ring>(ptr_rings_mass, count_size_mass_rings);
				delete_mass_objects<Circle>(ptr_circles_mass, count_size_mass_circles);
				delete_mass_objects<Rectangle>(ptr_rectangles_mass, count_size_mass_rectangles);
				delete_mass_objects<Line_Segment>(ptr_linesegments_mass, count_size_mass_linesegments);
				delete_mass_objects<ComplexObject>(ptr_complex_objects_mass, count_size_mass_complex_objects);
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
					if (create_30_rings)
					{
						show_ring = true;
						save_size_mass_rings = true;
						for (unsigned i{}; i < 30;i++)
						{
							if (count_size_mass_rings == 0)
							{
								Ring* ptr_obj_ring{ nullptr };
								ptr_obj_ring = new Ring{};
								push_back_shape<Ring>(ptr_rings_mass, count_size_mass_rings, ptr_obj_ring);
							}
							else
							{
								create_random_ring(ptr_rings_mass, count_size_mass_rings);
							}
						}
						if (count_size_mass_rings - 30 != 0) std::cout << "Массив колец был создан конструктором со случайными параметрами." << std::endl;
						else std::cout << "Массив колец был создан конструктором со случайными параметрами. Первое кольцо - конструктором по умолчанию." << std::endl;
						std::cout << "На окне SFML находится " << count_size_mass_rings << " колец." << std::endl;
					}
					else if (count_size_mass_rings == 0)
					{
						Ring* ptr_obj_ring{ nullptr };
						ptr_obj_ring = new Ring{};
						push_back_shape<Ring>(ptr_rings_mass, count_size_mass_rings, ptr_obj_ring);
						show_ring = true;
						save_size_mass_rings = true;
						std::cout << "Кольцо " << count_size_mass_rings << " было создано конструктором по умолчанию." << std::endl;
					}
					else
					{
						create_random_ring(ptr_rings_mass, count_size_mass_rings);
						show_ring = true;
						save_size_mass_rings = true;
						std::cout << "Кольцо " << count_size_mass_rings << " было создано конструктором со случайными параметрами." << std::endl;
					}
				}
				if (is_stage == 2 && count_size_mass_rings != 0)
				{
					move_ring = !move_ring;

					if (!combine_objects)
					{
						if (move_ring) std::cout << "Передвижение последней созданной фигуры включено." << std::endl;
						else std::cout << "Передвижение последней созданной фигуры выключено." << std::endl;
					}
					else
					{
						if (move_ring) std::cout << "Передвижение всех созданных фигур включено." << std::endl;
						else std::cout << "Передвижение всех созданных фигур выключено." << std::endl;
					}
				}
				if (is_stage == 3 && (count_size_mass_rings != 0 || count_size_mass_rings == 0 && !show_ring))
				{
					if (save_size_mass_rings) iteration_counter_combine_objs = count_size_mass_rings;
					show_ring = !show_ring;
					if (!show_ring)
					{
						if (!combine_objects)
						{
							std::cout << "Последнее созданное кольцо было стерто." << std::endl;
							delete_element_shape<Ring>(ptr_rings_mass, count_size_mass_rings);
							move_ring = false;
						}
						else
						{
							std::cout << "Все кольца были стерты." << std::endl;
							save_size_mass_rings = false;
							for (unsigned i{}; i < iteration_counter_combine_objs;i++)
							{
								delete_element_shape<Ring>(ptr_rings_mass, count_size_mass_rings);
							}
							move_ring = false;
						}
					}
					else
					{
						if (!combine_objects)
						{
							create_random_ring(ptr_rings_mass, count_size_mass_rings);
							std::cout << "Кольцо " << count_size_mass_rings << " было создано конструктором со случайными параметрами." << std::endl;
							move_ring = true;
						}
						else
						{
							for (unsigned i{}; i < iteration_counter_combine_objs; i++)
							{
								create_random_ring(ptr_rings_mass, count_size_mass_rings);
								std::cout << "Кольцо " << count_size_mass_rings << " было создано конструктором со случайными параметрами." << std::endl;
							}
							move_ring = true;
						}
					}
				}
				if (is_stage == 4)
				{
					std::cout << "Выберите следующий примитив или вернитесь в MENU." << std::endl;
					return 0;
				}
				if (is_stage == 5 && count_size_mass_rings >= 2)
				{
					show_ring = true; move_ring = false;
					combine_objects = !combine_objects;
					if (combine_objects && count_size_mass_rings != 0)
						std::cout << "Режим группового изменения свойств объектов был включен. Возможность передвижения объектов выключена." << std::endl;
					else if (!combine_objects && count_size_mass_rings != 0)
						std::cout << "Режим группового изменения свойств объектов был выключен. Возможность передвижения объектов выключена." << std::endl;
				};
				if (is_stage == 6 && move_ring && count_size_mass_rings != 0)
				{
					if (!combine_objects)
					{
						std::cout << "Последнее созданное кольцо было перемещено на случайные координаты [-50; 50]." << std::endl;
						random_move_rings(ptr_rings_mass, count_size_mass_rings - 1);
					}
					else
					{
						for (unsigned i{}; i < count_size_mass_rings;i++)
						{
							random_move_rings(ptr_rings_mass, i);
						}
						std::cout << "Все кольца были перемещены на случайные координаты[-50; 50]." << std::endl;
					}
				}
				if (is_stage == 7 && count_size_mass_rings != 0)
				{
					std::cout << "Кольцо " << count_size_mass_rings << " было удалено." << std::endl;
					save_size_mass_rings = true;
					delete_element_shape<Ring>(ptr_rings_mass, count_size_mass_rings);
					if (count_size_mass_rings < 2)
					{
						if (combine_objects)
							std::cout << "Режим группового изменения свойств объектов был выключен. Возможность передвижения объектов выключена." << std::endl;
						combine_objects = false;
					}
					move_ring = false;
				}
				if (is_stage == 8)
				{
					std::cout << "Все кольца были стерты." << std::endl;
					delete_elements_shape<Ring>(ptr_rings_mass, count_size_mass_rings);
					combine_objects = false;
					move_ring = false;
					std::cout << "Режим группового изменения свойств объектов был выключен. Возможность передвижения объектов выключена." << std::endl;
				}
				if (is_stage == 9)
				{
					create_30_rings = !create_30_rings;
					if (create_30_rings)
						std::cout << "Режим создания объектов целым массивом был включен." << std::endl;
					else if (!create_30_rings)
						std::cout << "Режим создания объектов целым массивом был выключен." << std::endl;
				}
			}
			else if (event_click.type == sf::Event::KeyPressed && move_ring)
			{

				if (!combine_objects)
				{
					if (event_click.key.code == sf::Keyboard::W && (ptr_rings_mass[count_size_mass_rings - 1]->getOuterCircle().getCoordinateY() -
						ptr_rings_mass[count_size_mass_rings - 1]->getOuterCircle().getRadius() - 10) >= 115)
					{
						ptr_rings_mass[count_size_mass_rings - 1]->MoveTo(0, -10);
					}
					if (event_click.key.code == sf::Keyboard::A && (ptr_rings_mass[count_size_mass_rings - 1]->getOuterCircle().getCoordinateX() -
						ptr_rings_mass[count_size_mass_rings - 1]->getOuterCircle().getRadius() - 10) >= 465)
					{
						ptr_rings_mass[count_size_mass_rings - 1]->MoveTo(-10, 0);
					}
					if (event_click.key.code == sf::Keyboard::S && (ptr_rings_mass[count_size_mass_rings - 1]->getOuterCircle().getCoordinateY() + 10 +
						ptr_rings_mass[count_size_mass_rings - 1]->getOuterCircle().getRadius()) <= 715)
					{
						ptr_rings_mass[count_size_mass_rings - 1]->MoveTo(0, 10);
					}
					if (event_click.key.code == sf::Keyboard::D && (ptr_rings_mass[count_size_mass_rings - 1]->getOuterCircle().getCoordinateX() + 10 +
						ptr_rings_mass[count_size_mass_rings - 1]->getOuterCircle().getRadius()) <= 1415)
					{
						ptr_rings_mass[count_size_mass_rings - 1]->MoveTo(10, 0);
					}
					if (event_click.key.code == sf::Keyboard::E &&
						((ptr_rings_mass[count_size_mass_rings - 1]->getOuterCircle().getCoordinateX() -
							ptr_rings_mass[count_size_mass_rings - 1]->getOuterCircle().getRadius() - 1) >= 465 &&
							(ptr_rings_mass[count_size_mass_rings - 1]->getOuterCircle().getCoordinateX() +
								ptr_rings_mass[count_size_mass_rings - 1]->getOuterCircle().getRadius() + 1) <= 1415 &&
							(ptr_rings_mass[count_size_mass_rings - 1]->getOuterCircle().getCoordinateY() -
								ptr_rings_mass[count_size_mass_rings - 1]->getOuterCircle().getRadius() - 1) >= 115 &&
							(ptr_rings_mass[count_size_mass_rings - 1]->getOuterCircle().getCoordinateY() +
								ptr_rings_mass[count_size_mass_rings - 1]->getOuterCircle().getRadius() + 1) <= 715))
					{
						ptr_rings_mass[count_size_mass_rings - 1]->getOuterCircle().changeRadius(1);
						ptr_rings_mass[count_size_mass_rings - 1]->getInnerCircle().changeRadius(1);
					}
					if (event_click.key.code == sf::Keyboard::Q && (ptr_rings_mass[count_size_mass_rings - 1]->getInnerCircle().getRadius() - 1 >= 15))
					{
						ptr_rings_mass[count_size_mass_rings - 1]->getOuterCircle().changeRadius(-1);
						ptr_rings_mass[count_size_mass_rings - 1]->getInnerCircle().changeRadius(-1);
					}
				}
				else
				{
					if (event_click.key.code == sf::Keyboard::W)
					{
						for (unsigned i{}; i < count_size_mass_rings;i++)
						{
							if (ptr_rings_mass[i]->getOuterCircle().getCoordinateY() - ptr_rings_mass[i]->getOuterCircle().getRadius() - 10 >= 115)
							{
								ptr_rings_mass[i]->MoveTo(0, -10);
							}
						}
					}
					if (event_click.key.code == sf::Keyboard::A)
					{
						for (unsigned i{}; i < count_size_mass_rings;i++)
						{
							if (ptr_rings_mass[i]->getOuterCircle().getCoordinateX() - ptr_rings_mass[i]->getOuterCircle().getRadius() - 10 >= 465)
								ptr_rings_mass[i]->MoveTo(-10, 0);
						}
					}
					if (event_click.key.code == sf::Keyboard::S)
					{
						for (unsigned i{}; i < count_size_mass_rings;i++)
						{
							if (ptr_rings_mass[i]->getOuterCircle().getCoordinateY() + ptr_rings_mass[i]->getOuterCircle().getRadius() + 10 <= 715)
								ptr_rings_mass[i]->MoveTo(0, 10);
						}
					}
					if (event_click.key.code == sf::Keyboard::D)
					{
						for (unsigned i{}; i < count_size_mass_rings;i++)
						{
							if (ptr_rings_mass[i]->getOuterCircle().getCoordinateX() + ptr_rings_mass[i]->getOuterCircle().getRadius() + 10 <= 1415)
								ptr_rings_mass[i]->MoveTo(10, 0);
						}
					}
					if (event_click.key.code == sf::Keyboard::E)
					{
						for (unsigned i{}; i < count_size_mass_rings;i++)
						{
							if (((ptr_rings_mass[i]->getOuterCircle().getCoordinateX() - ptr_rings_mass[i]->getOuterCircle().getRadius() - 1) >= 465 &&
								(ptr_rings_mass[i]->getOuterCircle().getCoordinateX() + ptr_rings_mass[i]->getOuterCircle().getRadius() + 1) <= 1415 &&
								(ptr_rings_mass[i]->getOuterCircle().getCoordinateY() - ptr_rings_mass[i]->getOuterCircle().getRadius() - 1) >= 115 &&
								(ptr_rings_mass[i]->getOuterCircle().getCoordinateY() + ptr_rings_mass[i]->getOuterCircle().getRadius() + 1) <= 715))
							{
								ptr_rings_mass[i]->getOuterCircle().changeRadius(1);
								ptr_rings_mass[i]->getInnerCircle().changeRadius(1);
							}
						}
					}
					if (event_click.key.code == sf::Keyboard::Q)
					{
						for (unsigned i{}; i < count_size_mass_rings;i++)
						{
							if ((ptr_rings_mass[i]->getInnerCircle().getRadius() - 1) >= 15)
							{
								ptr_rings_mass[i]->getOuterCircle().changeRadius(-1);
								ptr_rings_mass[i]->getInnerCircle().changeRadius(-1);
							}
						}
					}
				}
			}
		}
		image_rect.Show(window);

		for (unsigned i{}; i < count_size_mass_circles;i++)
		{
			ptr_circles_mass[i]->Show(window);
		}

		for (unsigned i{}; i < count_size_mass_rectangles;i++)
		{
			ptr_rectangles_mass[i]->Show(window);
		}

		for (unsigned i{}; i < count_size_mass_complex_objects;i++)
		{
			ptr_complex_objects_mass[i]->Show(window);
		}

		for (unsigned i{}; i < count_size_mass_linesegments;i++)
		{
			ptr_linesegments_mass[i]->Show(window);
		}

		for (unsigned i{}; i < count_size_mass_rings;i++)
		{
			ptr_rings_mass[i]->Show(window);
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