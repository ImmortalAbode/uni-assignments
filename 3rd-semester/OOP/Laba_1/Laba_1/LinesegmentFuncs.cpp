#include <SFML/Graphics.hpp>
#include <iostream>

#include "MyFuncs.h"
#include "LinesegmentFuncs.h"
#include "UserButton.h"
#include "Linesegment.h"
#include "Circle.h"
#include "Rectangle.h"

void create_random_linesegment(Line_Segment**& ptr_linesegments_mass, int& count_size_mass_linesegments)
{
	Line_Segment* ptr_obj_linesegment{ nullptr };
	float restrict_length{ getRandomNumber(100, 250) };
	int restrict_degree{ static_cast<int>(getRandomNumber(0, 360)) };
	float restrict_x{};
	float restrict_y{};
	getRandomX_Y(restrict_x, restrict_y, restrict_length, restrict_degree);
	ptr_obj_linesegment = new Line_Segment{ restrict_x, restrict_y, restrict_length, restrict_degree };
	ptr_obj_linesegment->setColor(getRandomNumber(0, 255), getRandomNumber(0, 255), getRandomNumber(0, 255));
	ptr_obj_linesegment->setVisibility(getRandomNumber(50, 255));
	push_back_shape<Line_Segment>(ptr_linesegments_mass, count_size_mass_linesegments, ptr_obj_linesegment);
}

void random_move_linesegment(Line_Segment** ptr_linesegments_mass, int num_element)
{
	while (true)
	{
		float dx{ getRandomNumber(-50,50) }, dy{ getRandomNumber(-50,50) };
		int degree_linesegment{ static_cast<int>(ptr_linesegments_mass[num_element]->getDegree()) };
		float coordinateX_linesegment{ ptr_linesegments_mass[num_element]->getCoordinateX() };
		float coordinateY_linesegment{ ptr_linesegments_mass[num_element]->getCoordinateY() };
		float length_linesegment{ ptr_linesegments_mass[num_element]->getLength() };
		float pi{ acos(-1.0f) }; float gradus_linesegment{ degree_linesegment * pi / 180 };
		if (degree_linesegment % 360 >= 0 && degree_linesegment % 360 <= 90 || degree_linesegment % 360 >= -360 && degree_linesegment % 360 <= -270)
		{
			if (coordinateX_linesegment + dx >= 465 && coordinateY_linesegment + dy >= 115 && coordinateX_linesegment + length_linesegment * cos(gradus_linesegment) + 
				dx <= 1415 && coordinateY_linesegment + length_linesegment * sin(gradus_linesegment) + dy <= 715)
			{
				ptr_linesegments_mass[num_element]->MoveTo(dx, dy);
				break;
			}
		}
		else if (degree_linesegment % 360 >= 90 && degree_linesegment % 360 <= 180 || degree_linesegment % 360 >= -270 && degree_linesegment % 360 <= -180)
		{
			if (coordinateX_linesegment + dx <= 1415 && coordinateY_linesegment + dy >= 115 && coordinateX_linesegment + length_linesegment * cos(gradus_linesegment) + 
				dx >= 465 && coordinateY_linesegment + length_linesegment * sin(gradus_linesegment) + dy <= 715)
			{
				ptr_linesegments_mass[num_element]->MoveTo(dx, dy);
				break;
			}
		}
		else if (degree_linesegment % 360 >= 180 && degree_linesegment % 360 <= 270 || degree_linesegment % 360 >= -180 && degree_linesegment % 360 <= -90)
		{
			if (coordinateX_linesegment + dx <= 1415 && coordinateY_linesegment + dy <= 715 && coordinateX_linesegment + length_linesegment * cos(gradus_linesegment) + 
				dx >= 465 && coordinateY_linesegment + length_linesegment * sin(gradus_linesegment) + dy >= 115)
			{
				ptr_linesegments_mass[num_element]->MoveTo(dx, dy);
				break;
			}
		}
		else if (degree_linesegment % 360 >= 270 && degree_linesegment % 360 <= 360 || degree_linesegment % 360 >= -90 && degree_linesegment % 360 <= 0)
		{
			if (coordinateX_linesegment + dx >= 465 && coordinateY_linesegment + dy <= 715 && coordinateX_linesegment + length_linesegment * cos(gradus_linesegment) + 
				dx <= 1415 && coordinateY_linesegment + length_linesegment * sin(gradus_linesegment) + dy >= 115)
			{
				ptr_linesegments_mass[num_element]->MoveTo(dx, dy);
				break;
			}
		}
	}
}

void getRandomX_Y(float& restrict_x, float& restrict_y, float restrict_length, int restrict_degree)
{
	float pi{ acos(-1.0f) }; float restrict_gradus{ restrict_degree * pi / 180 };
	if (restrict_degree >= 0 && restrict_degree <= 90)
	{
	restrict_x = getRandomNumber(465, 1415 - restrict_length * cos(restrict_gradus));
	restrict_y = getRandomNumber(115, 715 - restrict_length * sin(restrict_gradus));
	}
	else if (restrict_degree >= 90 && restrict_degree <= 180)
	{
		restrict_x = getRandomNumber(465 - restrict_length * cos(restrict_gradus), 1415);
		restrict_y = getRandomNumber(115, 715 - restrict_length * sin(restrict_gradus));
	}
	else if (restrict_degree >= 180 && restrict_degree <= 270)
	{
	restrict_x = getRandomNumber(465 - restrict_length * cos(restrict_gradus), 1415);
	restrict_y = getRandomNumber(115 - restrict_length * sin(restrict_gradus), 715);
	}
	else if (restrict_degree >= 270 && restrict_degree <= 360)
	{
		restrict_x = getRandomNumber(465, 1415 - restrict_length * cos(restrict_gradus));
		restrict_y = getRandomNumber(115 - restrict_length * sin(restrict_gradus), 715);
	}
}

int work_with_linesegment(sf::RenderWindow& window, Line_Segment**& ptr_linesegments_mass, int& count_size_mass_linesegments, 
	Circle** ptr_circles_mass, int count_size_mass_circles, Rectangle** ptr_rectangles_mass, int count_size_mass_rectangles)
{
	/*Кнопка CREATE*/
	User_Text_Button create_text_button{ "Comic_Sans_MS.TTF", "Create array of linesegments", 30, 15, 20 };
	User_Rect_Button create_rect_button{ 10, 10, 5, 440, 60 };

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

	/*Кнопка SHOW LINESEGMENT*/
	User_Text_Button show_text_button{ "Comic_Sans_MS.TTF", "Show linesegmnet", 30, 15, 200 };
	User_Rect_Button show_rect_button{ 10, 190, 5, 270, 60 };

	//Тексты управления фигурами
	User_Text_Button move_shapes{ "Comic_Sans_MS.TTF", "Move up shape (W)    Move down shape (S)   Move left shape (A)    Move right shape (D)", 20, 260, 770 };
	User_Text_Button special_movements{ "Comic_Sans_MS.TTF", "Decrease length(Q)    Increase length(E)    Turn counterclockwise(Z)    Turn clockwise(C)", 20, 260, 730 };

	/*Кнопка удаления элемента*/
	User_Text_Button delete_element_text_button{ "Comic_Sans_MS.TTF", "Delete element", 30, 15, 290 };
	User_Rect_Button delete_element_rect_button{ 10, 280, 5, 240, 60 };

	/*Кнопка удаления всех элементов*/
	User_Text_Button delete_all_elements_text_button{ "Comic_Sans_MS.TTF", "Delete all elements", 30, 15, 380 };
	User_Rect_Button delete_all_elements_rect_button{ 10, 370, 5, 300, 60 };

	/*Кнопка создания 30 элементов*/
	User_Text_Button create_30_elements_text_button{ "Comic_Sans_MS.TTF", "Create array of linesegments", 30, 15, 470 };
	User_Rect_Button create_30_elements_rect_button{ 10, 460, 5, 450, 60 };

	int is_stage{};

	bool show_linesegment{ true }; //рисовать отрезок или удалить объект, освободив память
	bool move_linesegment{ false }; //позволить отрезку двигаться или нет
	bool combine_objects{ false }; //есть ли работа с массивом объектов
	bool save_size_mass_linesegments{ true };//сохранить размер массива для SHOW кнопки или нет
	bool create_30_linesegments{ false }; //создать массив из 30 отрезков, добавив его к основному
	int iteration_counter_combine_objs{}; //итератор для кнопки SHOW при работе с массивом

	while (window.isOpen())
	{
		is_stage = 0;
		window.clear(sf::Color(137, 20, 190));

		create_text_button.m_setFillColorDefault(); create_rect_button.m_setOutlineColorDefault();

		moveTo_text_button.m_setFillColorDefault();
		if (move_linesegment) moveTo_rect_button.m_setOutlineColor(247, 30, 241);
		else moveTo_rect_button.m_setOutlineColorDefault();

		back_text_button.m_setFillColorDefault(); back_rect_button.m_setOutlineColorDefault();

		combine_objects_text_button.m_setFillColorDefault();
		if (combine_objects && count_size_mass_linesegments != 0) combine_objects_rect_button.m_setOutlineColor(247, 30, 241);
		else combine_objects_rect_button.m_setOutlineColorDefault();

		random_move_text_button.m_setFillColorDefault(); random_move_rect_button.m_setOutlineColorDefault();
		delete_element_text_button.m_setFillColorDefault(); delete_element_rect_button.m_setOutlineColorDefault();

		show_text_button.m_setFillColorDefault();
		if (show_linesegment && count_size_mass_linesegments != 0) show_rect_button.m_setOutlineColor(247, 30, 241);
		else show_rect_button.m_setOutlineColorDefault();

		create_30_elements_text_button.m_setFillColorDefault();
		if (create_30_linesegments) create_30_elements_rect_button.m_setOutlineColor(247, 30, 241);
		else create_30_elements_rect_button.m_setOutlineColorDefault();

		delete_all_elements_text_button.m_setFillColorDefault(); delete_all_elements_rect_button.m_setOutlineColorDefault();

		if (sf::IntRect(5, 0, 450, 80).contains(sf::Mouse::getPosition(window))) //create
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

		if (sf::IntRect(5, 180, 280, 80).contains(sf::Mouse::getPosition(window))) // show
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

		if (sf::IntRect(5, 430, 460, 80).contains(sf::Mouse::getPosition(window))) //create 30 elements
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
					if (create_30_linesegments)
					{
						show_linesegment = true;
						save_size_mass_linesegments = true;
						for (unsigned i{}; i < 30;i++)
						{
							if (count_size_mass_linesegments == 0)
							{
								Line_Segment* ptr_obj_linesegment{ nullptr };
								ptr_obj_linesegment = new Line_Segment{};
								push_back_shape<Line_Segment>(ptr_linesegments_mass, count_size_mass_linesegments, ptr_obj_linesegment);
							}
							else
							{
								create_random_linesegment(ptr_linesegments_mass, count_size_mass_linesegments);
							}
						}
						if (count_size_mass_linesegments - 30 != 0) std::cout << "Массив отрезков был создан конструктором со случайными параметрами." << std::endl;
						else std::cout << "Массив отрезков был создан конструктором со случайными параметрами. Первый отрезок - конструктором по умолчанию." << std::endl;
						std::cout << "На окне SFML находится " << count_size_mass_linesegments << " отрезков." << std::endl;
					}
					else if (count_size_mass_linesegments == 0)
					{
						Line_Segment* ptr_obj_linesegment{ nullptr };
						ptr_obj_linesegment = new Line_Segment{};
						push_back_shape<Line_Segment>(ptr_linesegments_mass, count_size_mass_linesegments, ptr_obj_linesegment);
						show_linesegment = true;
						save_size_mass_linesegments = true;
						std::cout << "Отрезок " << count_size_mass_linesegments << " был создан конструктором по умолчанию." << std::endl;
					}
					else
					{
						create_random_linesegment(ptr_linesegments_mass, count_size_mass_linesegments);
						show_linesegment = true;
						save_size_mass_linesegments = true;
						std::cout << "Отрезок " << count_size_mass_linesegments << " был создан конструктором со случайными параметрами." << std::endl;
					}
				}
				if (is_stage == 2 && count_size_mass_linesegments != 0)
				{
					move_linesegment = !move_linesegment;

					if (!combine_objects)
					{
						if (move_linesegment) std::cout << "Передвижение последней созданной фигуры включено." << std::endl;
						else std::cout << "Передвижение последней созданной фигуры выключено." << std::endl;
					}
					else
					{
						if (move_linesegment) std::cout << "Передвижение всех созданных фигур включено." << std::endl;
						else std::cout << "Передвижение всех созданных фигур выключено." << std::endl;
					}
				}
				if (is_stage == 3 && (count_size_mass_linesegments != 0 || count_size_mass_linesegments == 0 && !show_linesegment))
				{
					if (save_size_mass_linesegments) iteration_counter_combine_objs = count_size_mass_linesegments;
					show_linesegment = !show_linesegment;
					if (!show_linesegment)
					{
						if (!combine_objects)
						{
							std::cout << "Последний созданный отрезок был стерт." << std::endl;
							ptr_linesegments_mass[count_size_mass_linesegments]->Free(ptr_linesegments_mass, count_size_mass_linesegments);
							move_linesegment = false;
						}
						else
						{
							std::cout << "Все отрезки были стерты." << std::endl;
							save_size_mass_linesegments = false;
							for (unsigned i{}; i < iteration_counter_combine_objs;i++)
							{
								ptr_linesegments_mass[i]->Free(ptr_linesegments_mass, count_size_mass_linesegments);
							}
							move_linesegment = false;
						}
					}
					else
					{
						if (!combine_objects)
						{
							create_random_linesegment(ptr_linesegments_mass, count_size_mass_linesegments);
							std::cout << "Отрезок " << count_size_mass_linesegments << " был создан конструктором со случайными параметрами." << std::endl;
							move_linesegment = true;
						}
						else
						{
							for (unsigned i{}; i < iteration_counter_combine_objs; i++)
							{
								create_random_linesegment(ptr_linesegments_mass, count_size_mass_linesegments);
								std::cout << "Отрезок " << count_size_mass_linesegments << " был создан конструктором со случайными параметрами." << std::endl;
							}
							move_linesegment = true;
						}
					}
				}
				if (is_stage == 4)
				{
					std::cout << "Выберите следующий примитив или вернитесь в MENU." << std::endl;
					return 0;
				}
				if (is_stage == 5 && count_size_mass_linesegments >= 2)
				{
					show_linesegment = true; move_linesegment = false;
					combine_objects = !combine_objects;
					if (combine_objects && count_size_mass_linesegments != 0)
						std::cout << "Режим группового изменения свойств объектов был включен. Возможность передвижения объектов выключена." << std::endl;
					else if (!combine_objects && count_size_mass_linesegments != 0)
						std::cout << "Режим группового изменения свойств объектов был выключен. Возможность передвижения объектов выключена." << std::endl;
				};
				if (is_stage == 6 && move_linesegment && count_size_mass_linesegments != 0)
				{
					if (!combine_objects)
					{
						std::cout << "Последний созданный отрезок был перемещен на случайные координаты [-50; 50]." << std::endl;
						random_move_linesegment(ptr_linesegments_mass, count_size_mass_linesegments - 1);
					}
					else
					{
						for (unsigned i{}; i < count_size_mass_linesegments;i++)
						{
							random_move_linesegment(ptr_linesegments_mass, i);
						}
						std::cout << "Все отрезки были перемещены на случайные координаты[-50; 50]." << std::endl;
					}
				}
				if (is_stage == 7 && count_size_mass_linesegments != 0)
				{
					std::cout << "Отрезок " << count_size_mass_linesegments << " был удален." << std::endl;
					save_size_mass_linesegments = true;
					delete_element_shape<Line_Segment>(ptr_linesegments_mass, count_size_mass_linesegments);
					if (count_size_mass_linesegments < 2)
					{
						if (combine_objects)
							std::cout << "Режим группового изменения свойств объектов был выключен. Возможность передвижения объектов выключена." << std::endl;
						combine_objects = false;
					}
					move_linesegment = false;
				}
				if (is_stage == 8)
				{
					std::cout << "Все отрезки были стерты." << std::endl;
					delete_elements_shape<Line_Segment>(ptr_linesegments_mass, count_size_mass_linesegments);
					combine_objects = false;
					move_linesegment = false;
					std::cout << "Режим группового изменения свойств объектов был выключен. Возможность передвижения объектов выключена." << std::endl;
				}
				if (is_stage == 9)
				{
					create_30_linesegments = !create_30_linesegments;
					if (create_30_linesegments)
						std::cout << "Режим создания объектов целым массивом был включен." << std::endl;
					else if (!create_30_linesegments)
						std::cout << "Режим создания объектов целым массивом был выключен." << std::endl;
				}
			}
			else if (event_click.type == sf::Event::KeyPressed && move_linesegment)
			{
				if (!combine_objects)
				{
					int degree_linesegment{ static_cast<int>(ptr_linesegments_mass[count_size_mass_linesegments - 1]->getDegree()) };
					float coordinateX_linesegment{ ptr_linesegments_mass[count_size_mass_linesegments - 1]->getCoordinateX() };
					float coordinateY_linesegment{ ptr_linesegments_mass[count_size_mass_linesegments - 1]->getCoordinateY() };
					float length_linesegment{ ptr_linesegments_mass[count_size_mass_linesegments - 1]->getLength() };
					float pi{ acos(-1.0f) }; float gradus_linesegment{ degree_linesegment * pi / 180 };
					if (event_click.key.code == sf::Keyboard::W)
					{
						if (degree_linesegment % 360 >= 180 && degree_linesegment % 360 <= 360 || degree_linesegment % 360 >= -180 && degree_linesegment % 360 <= 0)
						{
							if ((coordinateY_linesegment + length_linesegment * sin(gradus_linesegment) - 10) >= 115)
								ptr_linesegments_mass[count_size_mass_linesegments - 1]->MoveTo(0, -10);
						}
						else if ((coordinateY_linesegment - 10) >= 115)
						{
							ptr_linesegments_mass[count_size_mass_linesegments - 1]->MoveTo(0, -10);
						}				
					}
					if (event_click.key.code == sf::Keyboard::A)
					{
						if (degree_linesegment % 360 >= 90 && degree_linesegment % 360 <= 270 || degree_linesegment % 360 >= -270 && degree_linesegment % 360 <= -90)
						{
							if ((coordinateX_linesegment + length_linesegment * cos(gradus_linesegment) - 10) >= 465)
								ptr_linesegments_mass[count_size_mass_linesegments - 1]->MoveTo(-10, 0);
						}
						else if ((coordinateX_linesegment - 10) >= 465)
						{
							ptr_linesegments_mass[count_size_mass_linesegments - 1]->MoveTo(-10, 0);
						}
					}
					if (event_click.key.code == sf::Keyboard::S)
					{
						if (degree_linesegment % 360 >= 0 && degree_linesegment % 360 <= 180 || degree_linesegment % 360 >= -360 && degree_linesegment % 360 <= -180)
						{
							if ((coordinateY_linesegment + length_linesegment * sin(gradus_linesegment) + 10) <= 715)
								ptr_linesegments_mass[count_size_mass_linesegments - 1]->MoveTo(0, 10);
						}
						else if ((coordinateY_linesegment + 10) <= 715)
						{
							ptr_linesegments_mass[count_size_mass_linesegments - 1]->MoveTo(0, 10);
						}
					}
					if (event_click.key.code == sf::Keyboard::D)
					{
						if (degree_linesegment % 360 >= 90 && degree_linesegment % 360 <= 270 || degree_linesegment % 360 >= -270 && degree_linesegment % 360 <= -90)
						{
							if ((coordinateX_linesegment + 10) <= 1415)
								ptr_linesegments_mass[count_size_mass_linesegments - 1]->MoveTo(10, 0);
						}
						else if ((coordinateX_linesegment + length_linesegment * cos(gradus_linesegment) + 10) <= 1415)
						{
							ptr_linesegments_mass[count_size_mass_linesegments - 1]->MoveTo(10, 0);
						}
					}
					if (event_click.key.code == sf::Keyboard::E)
					{
						if ((coordinateX_linesegment + length_linesegment * cos(gradus_linesegment) + 1) <= 1415 &&
							(coordinateX_linesegment + length_linesegment * cos(gradus_linesegment) + 1) >= 465 &&
							(coordinateY_linesegment + length_linesegment * sin(gradus_linesegment) + 1) <= 715 &&
							(coordinateY_linesegment + length_linesegment * sin(gradus_linesegment) + 1) >= 115)
						{
							ptr_linesegments_mass[count_size_mass_linesegments - 1]->setLength(1);
						}
					}
					if (event_click.key.code == sf::Keyboard::Q)
					{
						if (length_linesegment - 1 >= 30)
						{
							ptr_linesegments_mass[count_size_mass_linesegments - 1]->setLength(-1);
						}
					}
					if (event_click.key.code == sf::Keyboard::C )
					{
						if ((coordinateX_linesegment + length_linesegment * cos(gradus_linesegment + 5 * pi / 180)) <= 1415 &&
							(coordinateX_linesegment + length_linesegment * cos(gradus_linesegment + 5 * pi / 180)) >= 465 &&
							(coordinateY_linesegment + length_linesegment * sin(gradus_linesegment + 5 * pi / 180)) <= 715 &&
							(coordinateY_linesegment + length_linesegment * sin(gradus_linesegment + 5 * pi / 180)) >= 115)
						{
							ptr_linesegments_mass[count_size_mass_linesegments - 1]->setDegree(5);
						}
					}
					if (event_click.key.code == sf::Keyboard::Z )
					{
						if ((coordinateX_linesegment + length_linesegment * cos(gradus_linesegment - 5 * pi / 180)) <= 1415 &&
							(coordinateX_linesegment + length_linesegment * cos(gradus_linesegment - 5 * pi / 180)) >= 465 &&
							(coordinateY_linesegment + length_linesegment * sin(gradus_linesegment - 5 * pi / 180)) <= 715 &&
							(coordinateY_linesegment + length_linesegment * sin(gradus_linesegment - 5 * pi / 180)) >= 115)
						{
							ptr_linesegments_mass[count_size_mass_linesegments - 1]->setDegree(-5);
						}
					}
				}
				else
				{
					float pi{ acos(-1.0f) }; 
					if (event_click.key.code == sf::Keyboard::W)
					{
						for (unsigned i{}; i < count_size_mass_linesegments;i++)
						{
							int degree_linesegment{ static_cast<int>(ptr_linesegments_mass[i]->getDegree()) };
							float coordinateY_linesegment{ ptr_linesegments_mass[i]->getCoordinateY() };
							float length_linesegment{ ptr_linesegments_mass[i]->getLength() };
							float gradus_linesegment{ degree_linesegment * pi / 180 };
							if (degree_linesegment % 360 >= 180 && degree_linesegment % 360 <= 360 || degree_linesegment % 360 >= -180 && degree_linesegment % 360 <= 0)
							{
								if ((coordinateY_linesegment + length_linesegment * sin(gradus_linesegment) - 10) >= 115)
									ptr_linesegments_mass[i]->MoveTo(0, -10);
							}
							else if ((coordinateY_linesegment - 10) >= 115)
							{
								ptr_linesegments_mass[i]->MoveTo(0, -10);
							}
						}
					}

					if (event_click.key.code == sf::Keyboard::A)
					{
						for (unsigned i{}; i < count_size_mass_linesegments;i++)
						{
							int degree_linesegment{ static_cast<int>(ptr_linesegments_mass[i]->getDegree()) };
							float coordinateX_linesegment{ ptr_linesegments_mass[i]->getCoordinateX() };
							float length_linesegment{ ptr_linesegments_mass[i]->getLength() };
							float gradus_linesegment{ degree_linesegment * pi / 180 };
							if (degree_linesegment % 360 >= 90 && degree_linesegment % 360 <= 270 || degree_linesegment % 360 >= -270 && degree_linesegment % 360 <= -90)
							{
								if ((coordinateX_linesegment + length_linesegment * cos(gradus_linesegment) - 10) >= 465)
									ptr_linesegments_mass[i]->MoveTo(-10, 0);
							}
							else if ((coordinateX_linesegment - 10) >= 465)
							{
								ptr_linesegments_mass[i]->MoveTo(-10, 0);
							}
						}
					}
					if (event_click.key.code == sf::Keyboard::S)
					{
						for (unsigned i{}; i < count_size_mass_linesegments;i++)
						{
							int degree_linesegment{ static_cast<int>(ptr_linesegments_mass[i]->getDegree()) };
							float coordinateY_linesegment{ ptr_linesegments_mass[i]->getCoordinateY() };
							float length_linesegment{ ptr_linesegments_mass[i]->getLength() };
							float gradus_linesegment{ degree_linesegment * pi / 180 };
							if (degree_linesegment % 360 >= 0 && degree_linesegment % 360 <= 180 || degree_linesegment % 360 >= -360 && degree_linesegment % 360 <= -180)
							{
								if ((coordinateY_linesegment + length_linesegment * sin(gradus_linesegment) + 10) <= 715)
									ptr_linesegments_mass[i]->MoveTo(0, 10);
							}
							else if ((coordinateY_linesegment + 10) <= 715)
							{
								ptr_linesegments_mass[i]->MoveTo(0, 10);
							}
						}
					}
					if (event_click.key.code == sf::Keyboard::D)
					{
						for (unsigned i{}; i < count_size_mass_linesegments;i++)
						{
							int degree_linesegment{ static_cast<int>(ptr_linesegments_mass[i]->getDegree()) };
							float coordinateX_linesegment{ ptr_linesegments_mass[i]->getCoordinateX() };
							float length_linesegment{ ptr_linesegments_mass[i]->getLength() };
							float gradus_linesegment{ degree_linesegment * pi / 180 };
							if (degree_linesegment % 360 >= 90 && degree_linesegment % 360 <= 270 || degree_linesegment % 360 >= -270 && degree_linesegment % 360 <= -90)
							{
								if ((coordinateX_linesegment + 10) <= 1415)
									ptr_linesegments_mass[i]->MoveTo(10, 0);
							}
							else if ((coordinateX_linesegment + length_linesegment * cos(gradus_linesegment) + 10) <= 1415)
							{
								ptr_linesegments_mass[i]->MoveTo(10, 0);
							}
						}
					}
					if (event_click.key.code == sf::Keyboard::E)
					{
						for (unsigned i{}; i < count_size_mass_linesegments;i++)
						{
							int degree_linesegment{ static_cast<int>(ptr_linesegments_mass[i]->getDegree()) };
							float coordinateY_linesegment{ ptr_linesegments_mass[i]->getCoordinateY() };
							float coordinateX_linesegment{ ptr_linesegments_mass[i]->getCoordinateX() };
							float length_linesegment{ ptr_linesegments_mass[i]->getLength() };
							float gradus_linesegment{ degree_linesegment * pi / 180 };
							if ((coordinateX_linesegment + length_linesegment * cos(gradus_linesegment) + 1) <= 1415 &&
								(coordinateX_linesegment + length_linesegment * cos(gradus_linesegment) + 1) >= 465 &&
								(coordinateY_linesegment + length_linesegment * sin(gradus_linesegment) + 1) <= 715 &&
								(coordinateY_linesegment + length_linesegment * sin(gradus_linesegment) + 1) >= 115)
							{
								ptr_linesegments_mass[i]->setLength(1);
							}
						}
					}
					if (event_click.key.code == sf::Keyboard::Q)
					{
						for (unsigned i{}; i < count_size_mass_linesegments;i++)
						{
							float length_linesegment{ ptr_linesegments_mass[i]->getLength() };
							if (length_linesegment - 1 >= 30)
							{
								ptr_linesegments_mass[i]->setLength(-1);
							}
						}
					}
					if (event_click.key.code == sf::Keyboard::C)
					{
						for (unsigned i{}; i < count_size_mass_linesegments;i++)
						{
							int degree_linesegment{ static_cast<int>(ptr_linesegments_mass[i]->getDegree()) };
							float coordinateY_linesegment{ ptr_linesegments_mass[i]->getCoordinateY() };
							float coordinateX_linesegment{ ptr_linesegments_mass[i]->getCoordinateX() };
							float length_linesegment{ ptr_linesegments_mass[i]->getLength() };
							float gradus_linesegment{ degree_linesegment * pi / 180 };
							if ((coordinateX_linesegment + length_linesegment * cos(gradus_linesegment + 5 * pi / 180)) <= 1415 &&
								(coordinateX_linesegment + length_linesegment * cos(gradus_linesegment + 5 * pi / 180)) >= 465 &&
								(coordinateY_linesegment + length_linesegment * sin(gradus_linesegment + 5 * pi / 180)) <= 715 &&
								(coordinateY_linesegment + length_linesegment * sin(gradus_linesegment + 5 * pi / 180)) >= 115)
							{
								ptr_linesegments_mass[i]->setDegree(5);
							}
						}
					}
					if (event_click.key.code == sf::Keyboard::Z)
					{
						for (unsigned i{}; i < count_size_mass_linesegments;i++)
						{
							int degree_linesegment{ static_cast<int>(ptr_linesegments_mass[i]->getDegree()) };
							float coordinateY_linesegment{ ptr_linesegments_mass[i]->getCoordinateY() };
							float coordinateX_linesegment{ ptr_linesegments_mass[i]->getCoordinateX() };
							float length_linesegment{ ptr_linesegments_mass[i]->getLength() };
							float gradus_linesegment{ degree_linesegment * pi / 180 };
							if ((coordinateX_linesegment + length_linesegment * cos(gradus_linesegment - 5 * pi / 180)) <= 1415 &&
								(coordinateX_linesegment + length_linesegment * cos(gradus_linesegment - 5 * pi / 180)) >= 465 &&
								(coordinateY_linesegment + length_linesegment * sin(gradus_linesegment - 5 * pi / 180)) <= 715 &&
								(coordinateY_linesegment + length_linesegment * sin(gradus_linesegment - 5 * pi / 180)) >= 115)
							{
								ptr_linesegments_mass[i]->setDegree(-5);
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