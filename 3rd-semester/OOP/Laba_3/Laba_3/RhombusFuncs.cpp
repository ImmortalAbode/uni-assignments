#include <SFML/Graphics.hpp>
#include <iostream>

#include "MyFuncs.h"
#include "UserButton.h"
#include "RhombusFuncs.h"
#include "TFigure.h"

void random_move_rhombuses(TRhombus** ptr_rhombuses_mass, int num_element)
{
	while (true)
	{
		float dx{ getRandomNumber(-50,50) }, dy{ getRandomNumber(-50,50) };
		if ((ptr_rhombuses_mass[num_element]->getCoordinateX() + dx) >= 465 &&
			(ptr_rhombuses_mass[num_element]->getCoordinateY2() + dy) >= 115 &&
			(ptr_rhombuses_mass[num_element]->getCoordinateX3() + dx) <= 1415 &&
			(ptr_rhombuses_mass[num_element]->getCoordinateY4() + dy) <= 715)
		{
			ptr_rhombuses_mass[num_element]->MoveTo(dx, dy);
			break;
		}
	}
}

void create_random_rhombus(TRhombus**& ptr_rhombuses_mass, int& count_size_mass_rhombuses)
{
	TRhombus* ptr_obj_rhombus{ nullptr };
	float length{ getRandomNumber(50, 100) };
	int degree{ static_cast<int>(getRandomNumber(15, 60)) };
	float restrict_x{ getRandomNumber(465, 1415 - 2 * length * cos(degree * acos(-1.0f) / 180)) };
	float restrict_y{ getRandomNumber(115 + length * sin(degree * acos(-1.0f) / 180), 715 - length * sin(degree * acos(-1.0f) / 180)) };
	ptr_obj_rhombus = new TRhombus{ restrict_x, restrict_y, length, degree };
	ptr_obj_rhombus->setOutlineColor(getRandomNumber(0, 255), getRandomNumber(0, 255), getRandomNumber(0, 255));
	ptr_obj_rhombus->setFillColor(getRandomNumber(0, 255), getRandomNumber(0, 255), getRandomNumber(0, 255));
	ptr_obj_rhombus->setVisibility(getRandomNumber(50, 255));
	push_back_shape<TRhombus>(ptr_rhombuses_mass, count_size_mass_rhombuses, ptr_obj_rhombus);
}

int work_with_rhombuses(sf::RenderWindow& window, TRhombus**& ptr_rhombuses_mass, int& count_size_mass_rhombuses, TCircle** ptr_circles_mass, int count_size_mass_circles,
	TRectangle** ptr_rectangles_mass, int count_size_mass_rectangles, TLinesegment** ptr_linesegments_mass, int count_size_mass_linesegments, TEllipse** ptr_ellipses_mass,
	int count_size_mass_ellipses, TTrapeze** ptr_trapezes_mass, int count_size_mass_trapezes, TQuadrilateral** ptr_quadrilaterals_mass, int count_size_mass_quadrilaterals)
{
	/*Кнопка CREATE*/
	User_Text_Button create_text_button{ "Comic_Sans_MS.TTF", "Create element of rhombuses", 25, 15, 20 };
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
	User_Text_Button show_text_button{ "Comic_Sans_MS.TTF", "Show rhombus", 30, 15, 200 };
	User_Rect_Button show_rect_button{ 10, 190, 5, 220, 60 };

	//Тексты управления фигурами
	User_Text_Button move_shapes{ "Comic_Sans_MS.TTF", "Move up shape (W)    Move down shape (S)   Move left shape (A)    Move right shape (D)", 20, 260, 770 };
	User_Text_Button special_movements{ "Comic_Sans_MS.TTF", "Decrease degree(Q)  Increase degree(E)  Decrease length of side(Z)  Increase length of side(C)", 20, 260, 730 };

	/*Кнопка удаления элемента*/
	User_Text_Button delete_element_text_button{ "Comic_Sans_MS.TTF", "Delete element", 30, 15, 290 };
	User_Rect_Button delete_element_rect_button{ 10, 280, 5, 240, 60 };

	/*Кнопка удаления всех элементов*/
	User_Text_Button delete_all_elements_text_button{ "Comic_Sans_MS.TTF", "Delete all elements", 30, 15, 380 };
	User_Rect_Button delete_all_elements_rect_button{ 10, 370, 5, 300, 60 };

	/*Кнопка создания 30 элементов*/
	User_Text_Button create_30_elements_text_button{ "Comic_Sans_MS.TTF", "Create array of rhombuses", 30, 15, 470 };
	User_Rect_Button create_30_elements_rect_button{ 10, 460, 5, 430, 60 };

	int is_stage{};

	bool show_rhombus{ true }; //рисовать ромб или удалить объект, освободив память
	bool move_rhombus{ false }; //позволить ромбу двигаться или нет
	bool combine_objects{ false }; //есть ли работа с массивом объектов
	bool save_size_mass_rhombuses{ true };//сохранить размер массива для SHOW кнопки или нет
	bool create_30_rhombuses{ false }; //создать массив из 30 ромбов, добавив его к основному
	int iteration_counter_combine_objs{}; //итератор для кнопки SHOW при работе с массивом

	while (window.isOpen())
	{
		is_stage = 0;
		window.clear(sf::Color(137, 20, 190));

		create_text_button.m_setFillColorDefault(); create_rect_button.m_setOutlineColorDefault();

		moveTo_text_button.m_setFillColorDefault();
		if (move_rhombus) moveTo_rect_button.m_setOutlineColor(247, 30, 241);
		else moveTo_rect_button.m_setOutlineColorDefault();

		back_text_button.m_setFillColorDefault(); back_rect_button.m_setOutlineColorDefault();

		combine_objects_text_button.m_setFillColorDefault();
		if (combine_objects && count_size_mass_rhombuses != 0) combine_objects_rect_button.m_setOutlineColor(247, 30, 241);
		else combine_objects_rect_button.m_setOutlineColorDefault();

		random_move_text_button.m_setFillColorDefault(); random_move_rect_button.m_setOutlineColorDefault();
		delete_element_text_button.m_setFillColorDefault(); delete_element_rect_button.m_setOutlineColorDefault();

		show_text_button.m_setFillColorDefault();
		if (show_rhombus && count_size_mass_rhombuses != 0) show_rect_button.m_setOutlineColor(247, 30, 241);
		else show_rect_button.m_setOutlineColorDefault();

		create_30_elements_text_button.m_setFillColorDefault();
		if (create_30_rhombuses) create_30_elements_rect_button.m_setOutlineColor(247, 30, 241);
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

		if (sf::IntRect(5, 180, 230, 80).contains(sf::Mouse::getPosition(window))) // show
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

		if (sf::IntRect(5, 430, 440, 80).contains(sf::Mouse::getPosition(window))) //create 30 elements
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
				delete_mass_objects<TCircle>(ptr_circles_mass, count_size_mass_circles);
				delete_mass_objects<TRectangle>(ptr_rectangles_mass, count_size_mass_rectangles);
				delete_mass_objects<TLinesegment>(ptr_linesegments_mass, count_size_mass_linesegments);
				delete_mass_objects<TEllipse>(ptr_ellipses_mass, count_size_mass_ellipses);
				delete_mass_objects<TTrapeze>(ptr_trapezes_mass, count_size_mass_trapezes);
				delete_mass_objects<TRhombus>(ptr_rhombuses_mass, count_size_mass_rhombuses);
				delete_mass_objects<TQuadrilateral>(ptr_quadrilaterals_mass, count_size_mass_quadrilaterals);
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
					if (create_30_rhombuses)
					{
						show_rhombus = true;
						save_size_mass_rhombuses = true;
						for (unsigned i{}; i < 30;i++)
						{
							if (count_size_mass_rhombuses == 0)
							{
								TRhombus* ptr_obj_rhombus{ nullptr };
								ptr_obj_rhombus = new TRhombus{};
								push_back_shape<TRhombus>(ptr_rhombuses_mass, count_size_mass_rhombuses, ptr_obj_rhombus);
							}
							else
							{
								create_random_rhombus(ptr_rhombuses_mass, count_size_mass_rhombuses);
							}
						}
						if (count_size_mass_rhombuses - 30 != 0) std::cout << "Массив ромбов был создан конструктором со случайными параметрами." << std::endl;
						else std::cout << "Массив ромбов был создан конструктором со случайными параметрами. Первый ромб - конструктором по умолчанию." << std::endl;
						std::cout << "На окне SFML находится " << count_size_mass_rhombuses << " ромб(-ов/-а)." << std::endl;
					}
					else if (count_size_mass_rhombuses == 0)
					{
						TRhombus* ptr_obj_rhombus{ nullptr };
						ptr_obj_rhombus = new TRhombus{};
						push_back_shape<TRhombus>(ptr_rhombuses_mass, count_size_mass_rhombuses, ptr_obj_rhombus);
						show_rhombus = true;
						save_size_mass_rhombuses = true;
						std::cout << "Ромб " << count_size_mass_rhombuses << " был создан конструктором по умолчанию." << std::endl;
					}
					else
					{
						create_random_rhombus(ptr_rhombuses_mass, count_size_mass_rhombuses);
						show_rhombus = true;
						save_size_mass_rhombuses = true;
						std::cout << "Ромб " << count_size_mass_rhombuses << " был создан конструктором со случайными параметрами." << std::endl;
					}
				}
				if (is_stage == 2 && count_size_mass_rhombuses != 0)
				{
					move_rhombus = !move_rhombus;

					if (!combine_objects)
					{
						if (move_rhombus) std::cout << "Передвижение последней созданной фигуры включено." << std::endl;
						else std::cout << "Передвижение последней созданной фигуры выключено." << std::endl;
					}
					else
					{
						if (move_rhombus) std::cout << "Передвижение всех созданных фигур включено." << std::endl;
						else std::cout << "Передвижение всех созданных фигур выключено." << std::endl;
					}
				}
				if (is_stage == 3 && (count_size_mass_rhombuses != 0 || count_size_mass_rhombuses == 0 && !show_rhombus))
				{
					if (save_size_mass_rhombuses) iteration_counter_combine_objs = count_size_mass_rhombuses;
					show_rhombus = !show_rhombus;
					if (!show_rhombus)
					{
						if (!combine_objects)
						{
							std::cout << "Последний созданный ромб был стерт." << std::endl;
							ptr_rhombuses_mass[count_size_mass_rhombuses - 1]->Free(ptr_rhombuses_mass, count_size_mass_rhombuses);
							move_rhombus = false;
						}
						else
						{
							std::cout << "Все ромбы были стерты." << std::endl;
							save_size_mass_rhombuses = false;
							for (unsigned i{}; i < iteration_counter_combine_objs;i++)
							{
								ptr_rhombuses_mass[i]->Free(ptr_rhombuses_mass, count_size_mass_rhombuses);
							}
							move_rhombus = false;
						}
					}
					else
					{
						if (!combine_objects)
						{
							create_random_rhombus(ptr_rhombuses_mass, count_size_mass_rhombuses);
							std::cout << "Ромб " << count_size_mass_rhombuses << " был создан конструктором со случайными параметрами." << std::endl;
							move_rhombus = true;
						}
						else
						{
							for (unsigned i{}; i < iteration_counter_combine_objs; i++)
							{
								create_random_rhombus(ptr_rhombuses_mass, count_size_mass_rhombuses);
								std::cout << "Ромб " << count_size_mass_rhombuses << " был создан конструктором со случайными параметрами." << std::endl;
							}
							move_rhombus = true;
						}
					}
				}
				if (is_stage == 4)
				{
					std::cout << "Выберите следующий примитив или вернитесь в MENU." << std::endl;
					return 0;
				}
				if (is_stage == 5 && count_size_mass_rhombuses >= 2)
				{
					show_rhombus = true; move_rhombus = false;
					combine_objects = !combine_objects;
					if (combine_objects && count_size_mass_rhombuses != 0)
						std::cout << "Режим группового изменения свойств объектов был включен. Возможность передвижения объектов выключена." << std::endl;
					else if (!combine_objects && count_size_mass_rhombuses != 0)
						std::cout << "Режим группового изменения свойств объектов был выключен. Возможность передвижения объектов выключена." << std::endl;
				};
				if (is_stage == 6 && move_rhombus && count_size_mass_rhombuses != 0)
				{
					if (!combine_objects)
					{
						std::cout << "Последний созданный ромб был перемещен на случайные координаты [-50; 50]." << std::endl;
						random_move_rhombuses(ptr_rhombuses_mass, count_size_mass_rhombuses - 1);
					}
					else
					{
						for (unsigned i{}; i < count_size_mass_rhombuses;i++)
						{
							random_move_rhombuses(ptr_rhombuses_mass, i);
						}
						std::cout << "Все ромбы были перемещены на случайные координаты[-50; 50]." << std::endl;
					}
				}
				if (is_stage == 7 && count_size_mass_rhombuses != 0)
				{
					std::cout << "Ромб " << count_size_mass_rhombuses << " был удален." << std::endl;
					save_size_mass_rhombuses = true;
					delete_element_shape<TRhombus>(ptr_rhombuses_mass, count_size_mass_rhombuses);
					if (count_size_mass_rhombuses < 2)
					{
						if (combine_objects)
							std::cout << "Режим группового изменения свойств объектов был выключен. Возможность передвижения объектов выключена." << std::endl;
						combine_objects = false;
					}
					move_rhombus = false;
				}
				if (is_stage == 8)
				{
					std::cout << "Все ромбы были стерты." << std::endl;
					delete_elements_shape<TRhombus>(ptr_rhombuses_mass, count_size_mass_rhombuses);
					combine_objects = false;
					move_rhombus = false;
					std::cout << "Режим группового изменения свойств объектов был выключен. Возможность передвижения объектов выключена." << std::endl;
				}
				if (is_stage == 9)
				{
					create_30_rhombuses = !create_30_rhombuses;
					if (create_30_rhombuses)
						std::cout << "Режим создания объектов целым массивом был включен." << std::endl;
					else if (!create_30_rhombuses)
						std::cout << "Режим создания объектов целым массивом был выключен." << std::endl;
				}
			}
			else if (event_click.type == sf::Event::KeyPressed && move_rhombus)
			{

				if (!combine_objects) 
				{
					if (event_click.key.code == sf::Keyboard::W && (ptr_rhombuses_mass[count_size_mass_rhombuses - 1]->getCoordinateY2() - 10) >= 115)
					{
						ptr_rhombuses_mass[count_size_mass_rhombuses - 1]->MoveTo(0, -10);
					}
					if (event_click.key.code == sf::Keyboard::A && (ptr_rhombuses_mass[count_size_mass_rhombuses - 1]->getCoordinateX() - 10) >= 465)
					{
						ptr_rhombuses_mass[count_size_mass_rhombuses - 1]->MoveTo(-10, 0);
					}
					if (event_click.key.code == sf::Keyboard::S && (ptr_rhombuses_mass[count_size_mass_rhombuses - 1]->getCoordinateY4() + 10) <= 715)
					{
						ptr_rhombuses_mass[count_size_mass_rhombuses - 1]->MoveTo(0, 10);
					}
					if (event_click.key.code == sf::Keyboard::D && (ptr_rhombuses_mass[count_size_mass_rhombuses - 1]->getCoordinateX3() + 10) <= 1415)
					{
						ptr_rhombuses_mass[count_size_mass_rhombuses - 1]->MoveTo(10, 0);
					}
					if (event_click.key.code == sf::Keyboard::E && (ptr_rhombuses_mass[count_size_mass_rhombuses - 1]->getDegree() + 1 <= 60) &&
						ptr_rhombuses_mass[count_size_mass_rhombuses - 1]->getCoordinateY2() >= 115 && 
						ptr_rhombuses_mass[count_size_mass_rhombuses - 1]->getCoordinateY4() <= 715)
					{
						ptr_rhombuses_mass[count_size_mass_rhombuses - 1]->changeDegree(1);
					}
					if (event_click.key.code == sf::Keyboard::Q && (ptr_rhombuses_mass[count_size_mass_rhombuses - 1]->getDegree() - 1 >= 15) &&
						ptr_rhombuses_mass[count_size_mass_rhombuses - 1]->getCoordinateX3() <= 1415)
					{
						ptr_rhombuses_mass[count_size_mass_rhombuses - 1]->changeDegree(-1);
					}
					if (event_click.key.code == sf::Keyboard::C && (ptr_rhombuses_mass[count_size_mass_rhombuses - 1]->getCoordinateY2() >= 115) &&
						ptr_rhombuses_mass[count_size_mass_rhombuses - 1]->getCoordinateY4() <= 715 &&
						ptr_rhombuses_mass[count_size_mass_rhombuses - 1]->getCoordinateX3() <= 1415)
					{
						ptr_rhombuses_mass[count_size_mass_rhombuses - 1]->changeLength(1);
					}
					if (event_click.key.code == sf::Keyboard::Z && (ptr_rhombuses_mass[count_size_mass_rhombuses - 1]->getLength() - 1 >= 30))
					{
						ptr_rhombuses_mass[count_size_mass_rhombuses - 1]->changeLength(-1);
					}
				}
				else
				{
					if (event_click.key.code == sf::Keyboard::W)
					{
						for (unsigned i{}; i < count_size_mass_rhombuses;i++)
						{
							if ((ptr_rhombuses_mass[i]->getCoordinateY2() - 10) >= 115)
							{
								ptr_rhombuses_mass[i]->MoveTo(0, -10);
							}
						}
					}
					if (event_click.key.code == sf::Keyboard::A)
					{
						for (unsigned i{}; i < count_size_mass_rhombuses;i++)
						{
							if ((ptr_rhombuses_mass[i]->getCoordinateX() - 10) >= 465)
								ptr_rhombuses_mass[i]->MoveTo(-10, 0);
						}
					}
					if (event_click.key.code == sf::Keyboard::S)
					{
						for (unsigned i{}; i < count_size_mass_rhombuses;i++)
						{
							if ((ptr_rhombuses_mass[i]->getCoordinateY4() + 10) <= 715)
								ptr_rhombuses_mass[i]->MoveTo(0, 10);
						}
					}
					if (event_click.key.code == sf::Keyboard::D)
					{
						for (unsigned i{}; i < count_size_mass_rhombuses;i++)
						{
							if ((ptr_rhombuses_mass[i]->getCoordinateX3() + 10) <= 1415)
								ptr_rhombuses_mass[i]->MoveTo(10, 0);
						}
					}
					if (event_click.key.code == sf::Keyboard::E)
					{
						for (unsigned i{}; i < count_size_mass_rhombuses;i++)
						{
							if ((ptr_rhombuses_mass[i]->getDegree() + 1 <= 60) && ptr_rhombuses_mass[i]->getCoordinateY2() >= 115 && 
								ptr_rhombuses_mass[i]->getCoordinateY4() <= 715)
							{
								ptr_rhombuses_mass[i]->changeDegree(1);
							}
						}
					}
					if (event_click.key.code == sf::Keyboard::Q)
					{
						for (unsigned i{}; i < count_size_mass_rhombuses;i++)
						{
							if ((ptr_rhombuses_mass[i]->getDegree() - 1 >= 15) && ptr_rhombuses_mass[i]->getCoordinateX3() <= 1415)
							{
								ptr_rhombuses_mass[i]->changeDegree(-1);
							}
						}
					}
					if (event_click.key.code == sf::Keyboard::C)
					{
						for (unsigned i{}; i < count_size_mass_rhombuses;i++)
						{
							if ((ptr_rhombuses_mass[i]->getCoordinateY2() >= 115) && ptr_rhombuses_mass[i]->getCoordinateY4() <= 715 && 
								ptr_rhombuses_mass[i]->getCoordinateX3() <= 1415)
							{
								ptr_rhombuses_mass[i]->changeLength(1);
							}
						}
					}
					if (event_click.key.code == sf::Keyboard::Z)
					{
						for (unsigned i{}; i < count_size_mass_rhombuses;i++)
						{
							if ((ptr_rhombuses_mass[i]->getLength() - 1 >= 30))
							{
								ptr_rhombuses_mass[i]->changeLength(-1);
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

		for (unsigned i{}; i < count_size_mass_linesegments;i++)
		{
			ptr_linesegments_mass[i]->Show(window);
		}

		for (unsigned i{}; i < count_size_mass_ellipses;i++)
		{
			ptr_ellipses_mass[i]->Show(window);
		}

		for (unsigned i{}; i < count_size_mass_trapezes;i++)
		{
			ptr_trapezes_mass[i]->Show(window);
		}

		for (unsigned i{}; i < count_size_mass_quadrilaterals;i++)
		{
			ptr_quadrilaterals_mass[i]->Show(window);
		}

		for (unsigned i{}; i < count_size_mass_rhombuses;i++)
		{
			ptr_rhombuses_mass[i]->Show(window);
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