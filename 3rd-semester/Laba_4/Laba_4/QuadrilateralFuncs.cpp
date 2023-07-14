#include <SFML/Graphics.hpp>
#include <iostream>

#include "MyFuncs.h"
#include "UserButton.h"
#include "QuadrilateralFuncs.h"
#include "TFigure.h"

void random_move_quadrilaterals(TQuadrilateral** ptr_quadrilaterals_mass, int num_element)
{
	while (true)
	{
		float dx{ getRandomNumber(-50,50) }, dy{ getRandomNumber(-50,50) };
		if ((ptr_quadrilaterals_mass[num_element]->getCoordinateX() + dx) >= 465 &&
			(ptr_quadrilaterals_mass[num_element]->getCoordinateY() + dy) >= 115 &&
			(ptr_quadrilaterals_mass[num_element]->getCoordinateX2() + dx) <= 1415 &&
			(ptr_quadrilaterals_mass[num_element]->getCoordinateY2() + dy) >= 115 &&
			(ptr_quadrilaterals_mass[num_element]->getCoordinateX3() + dx) <= 1415 &&
			(ptr_quadrilaterals_mass[num_element]->getCoordinateY3() + dy) <= 715 &&
			(ptr_quadrilaterals_mass[num_element]->getCoordinateX4() + dx) >= 465 &&
			(ptr_quadrilaterals_mass[num_element]->getCoordinateY4() + dy) <= 715)
		{
			ptr_quadrilaterals_mass[num_element]->MoveTo(dx, dy);
			ptr_quadrilaterals_mass[num_element]->changeCoordinateX234_Y234(dx, dy);
			break;
		}
	}
}

void create_random_quadrilateral(TQuadrilateral**& ptr_quadrilaterals_mass, int& count_size_mass_quadrilaterals)
{
	TQuadrilateral* ptr_obj_quadrilateral{ nullptr };
	float restrict_x1{ getRandomNumber(480, 1315) };
	float restrict_x2{ getRandomNumber(restrict_x1 + 50, restrict_x1 + 100) };
	float restrict_x3{ getRandomNumber(restrict_x1 + 50, restrict_x1 + 100) };
	float restrict_x4{ getRandomNumber(restrict_x1 - 25, restrict_x3 - 50) };
	float restrict_y1{ getRandomNumber(140, 590) };
	float restrict_y2{ getRandomNumber(restrict_y1 - 25, restrict_y1 + 25) };
	float restrict_y3{ getRandomNumber(restrict_y2 + 50, restrict_y2 + 100) };
	float restrict_y4{ getRandomNumber(restrict_y1 + 50, restrict_y1 + 100) };
	ptr_obj_quadrilateral = new TQuadrilateral{ restrict_x1, restrict_y1,restrict_x2,restrict_y2, restrict_x3,restrict_y3, restrict_x4, restrict_y4 };
	ptr_obj_quadrilateral->setOutlineColor(getRandomNumber(0, 255), getRandomNumber(0, 255), getRandomNumber(0, 255));
	ptr_obj_quadrilateral->setFillColor(getRandomNumber(0, 255), getRandomNumber(0, 255), getRandomNumber(0, 255));
	ptr_obj_quadrilateral->setVisibility(getRandomNumber(50, 255));
	push_back_shape<TQuadrilateral>(ptr_quadrilaterals_mass, count_size_mass_quadrilaterals, ptr_obj_quadrilateral);
}

int work_with_quadrilaterals(sf::RenderWindow& window, TQuadrilateral**& ptr_quadrilaterals_mass, int& count_size_mass_quadrilaterals, TCircle** ptr_circles_mass,
	int count_size_mass_circles, TRectangle** ptr_rectangles_mass, int count_size_mass_rectangles, TLinesegment** ptr_linesegments_mass, int count_size_mass_linesegments,
	TEllipse** ptr_ellipses_mass, int count_size_mass_ellipses, TTrapeze** ptr_trapezes_mass, int count_size_mass_trapezes, TRhombus** ptr_rhombuses_mass,
	int count_size_mass_rhombuses)
{
	/*Кнопка CREATE*/
	User_Text_Button create_text_button{ "Comic_Sans_MS.TTF", "Create element of quadrilaterals", 25, 15, 20 };
	User_Rect_Button create_rect_button{ 10, 10, 5, 430, 60 };

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
	User_Text_Button show_text_button{ "Comic_Sans_MS.TTF", "Show quadrilateral", 30, 15, 200 };
	User_Rect_Button show_rect_button{ 10, 190, 5, 300, 60 };

	//Тексты управления фигурами
	User_Text_Button move_shapes{ "Comic_Sans_MS.TTF", "Move up shape (W)    Move down shape (S)   Move left shape (A)    Move right shape (D)", 20, 260, 770 };
	User_Text_Button special_movements{ "Comic_Sans_MS.TTF", "Decrease size(Q)           Increase size(E)", 20, 260, 730 };

	/*Кнопка удаления элемента*/
	User_Text_Button delete_element_text_button{ "Comic_Sans_MS.TTF", "Delete element", 30, 15, 290 };
	User_Rect_Button delete_element_rect_button{ 10, 280, 5, 240, 60 };

	/*Кнопка удаления всех элементов*/
	User_Text_Button delete_all_elements_text_button{ "Comic_Sans_MS.TTF", "Delete all elements", 30, 15, 380 };
	User_Rect_Button delete_all_elements_rect_button{ 10, 370, 5, 300, 60 };

	/*Кнопка создания 30 элементов*/
	User_Text_Button create_30_elements_text_button{ "Comic_Sans_MS.TTF", "Create array of quadrilaterals", 25, 15, 470 };
	User_Rect_Button create_30_elements_rect_button{ 10, 460, 5, 400, 60 };

	int is_stage{};

	bool show_quadrilateral{ true }; //рисовать четырехугольник или удалить объект, освободив память
	bool move_quadrilateral{ false }; //позволить четырехугольнику двигаться или нет
	bool combine_objects{ false }; //есть ли работа с массивом объектов
	bool save_size_mass_quadrilaterals{ true };//сохранить размер массива для SHOW кнопки или нет
	bool create_30_quadrilaterals{ false }; //создать массив из 30 четырехугольников, добавив его к основному
	int iteration_counter_combine_objs{}; //итератор для кнопки SHOW при работе с массивом

	while (window.isOpen())
	{
		is_stage = 0;
		window.clear(sf::Color(137, 20, 190));

		create_text_button.m_setFillColorDefault(); create_rect_button.m_setOutlineColorDefault();

		moveTo_text_button.m_setFillColorDefault();
		if (move_quadrilateral) moveTo_rect_button.m_setOutlineColor(247, 30, 241);
		else moveTo_rect_button.m_setOutlineColorDefault();

		back_text_button.m_setFillColorDefault(); back_rect_button.m_setOutlineColorDefault();

		combine_objects_text_button.m_setFillColorDefault();
		if (combine_objects && count_size_mass_quadrilaterals != 0) combine_objects_rect_button.m_setOutlineColor(247, 30, 241);
		else combine_objects_rect_button.m_setOutlineColorDefault();

		random_move_text_button.m_setFillColorDefault(); random_move_rect_button.m_setOutlineColorDefault();
		delete_element_text_button.m_setFillColorDefault(); delete_element_rect_button.m_setOutlineColorDefault();

		show_text_button.m_setFillColorDefault();
		if (show_quadrilateral && count_size_mass_quadrilaterals != 0) show_rect_button.m_setOutlineColor(247, 30, 241);
		else show_rect_button.m_setOutlineColorDefault();

		create_30_elements_text_button.m_setFillColorDefault();
		if (create_30_quadrilaterals) create_30_elements_rect_button.m_setOutlineColor(247, 30, 241);
		else create_30_elements_rect_button.m_setOutlineColorDefault();

		delete_all_elements_text_button.m_setFillColorDefault(); delete_all_elements_rect_button.m_setOutlineColorDefault();

		if (sf::IntRect(5, 0, 440, 80).contains(sf::Mouse::getPosition(window))) //create
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

		if (sf::IntRect(5, 180, 310, 80).contains(sf::Mouse::getPosition(window))) // show
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

		if (sf::IntRect(5, 430, 410, 80).contains(sf::Mouse::getPosition(window))) //create 30 elements
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
					if (create_30_quadrilaterals)
					{
						show_quadrilateral = true;
						save_size_mass_quadrilaterals = true;
						for (unsigned i{}; i < 30;i++)
						{
							if (count_size_mass_quadrilaterals == 0)
							{
								TQuadrilateral* ptr_obj_quadrilateral{ nullptr };
								ptr_obj_quadrilateral = new TQuadrilateral{};
								push_back_shape<TQuadrilateral>(ptr_quadrilaterals_mass, count_size_mass_quadrilaterals, ptr_obj_quadrilateral);
							}
							else
							{
								create_random_quadrilateral(ptr_quadrilaterals_mass, count_size_mass_quadrilaterals);
							}
						}
						if (count_size_mass_quadrilaterals - 30 != 0)
							std::cout << "Массив четырехугольников был создан конструктором со случайными параметрами." << std::endl;
						else
							std::cout << "Массив четырехугольников был создан конструктором со случайными параметрами. " <<
							"Первый четырехугольник - конструктором по умолчанию." << std::endl;
						std::cout << "На окне SFML находится " << count_size_mass_quadrilaterals << " четырехугольник(-ов/-a)." << std::endl;
					}
					else if (count_size_mass_quadrilaterals == 0)
					{
						TQuadrilateral* ptr_obj_quadrilateral{ nullptr };
						ptr_obj_quadrilateral = new TQuadrilateral{};
						push_back_shape<TQuadrilateral>(ptr_quadrilaterals_mass, count_size_mass_quadrilaterals, ptr_obj_quadrilateral);
						show_quadrilateral = true;
						save_size_mass_quadrilaterals = true;
						std::cout << "Четырехугольник " << count_size_mass_quadrilaterals << " был создан конструктором по умолчанию." << std::endl;
					}
					else
					{
						create_random_quadrilateral(ptr_quadrilaterals_mass, count_size_mass_quadrilaterals);
						show_quadrilateral = true;
						save_size_mass_quadrilaterals = true;
						std::cout << "Четырехугольник " << count_size_mass_quadrilaterals << " был создан конструктором со случайными параметрами." << std::endl;
					}
				}
				if (is_stage == 2 && count_size_mass_quadrilaterals != 0)
				{
					move_quadrilateral = !move_quadrilateral;

					if (!combine_objects)
					{
						if (move_quadrilateral) std::cout << "Передвижение последней созданной фигуры включено." << std::endl;
						else std::cout << "Передвижение последней созданной фигуры выключено." << std::endl;
					}
					else
					{
						if (move_quadrilateral) std::cout << "Передвижение всех созданных фигур включено." << std::endl;
						else std::cout << "Передвижение всех созданных фигур выключено." << std::endl;
					}
				}
				if (is_stage == 3 && (count_size_mass_quadrilaterals != 0 || count_size_mass_quadrilaterals == 0 && !show_quadrilateral))
				{
					if (save_size_mass_quadrilaterals) iteration_counter_combine_objs = count_size_mass_quadrilaterals;
					show_quadrilateral = !show_quadrilateral;
					if (!show_quadrilateral)
					{
						if (!combine_objects)
						{
							std::cout << "Последний созданный четырехугольник был стерт." << std::endl;
							ptr_quadrilaterals_mass[count_size_mass_quadrilaterals - 1]->Free(ptr_quadrilaterals_mass, count_size_mass_quadrilaterals);
							move_quadrilateral = false;
						}
						else
						{
							std::cout << "Все четырехугольники были стерты." << std::endl;
							save_size_mass_quadrilaterals = false;
							for (unsigned i{}; i < iteration_counter_combine_objs;i++)
							{
								ptr_quadrilaterals_mass[i]->Free(ptr_quadrilaterals_mass, count_size_mass_quadrilaterals);
							}
							move_quadrilateral = false;
						}
					}
					else
					{
						if (!combine_objects)
						{
							create_random_quadrilateral(ptr_quadrilaterals_mass, count_size_mass_quadrilaterals);
							std::cout << "Четырехугольник " << count_size_mass_quadrilaterals << " был создан конструктором со случайными параметрами." << std::endl;
							move_quadrilateral = true;
						}
						else
						{
							for (unsigned i{}; i < iteration_counter_combine_objs; i++)
							{
								create_random_quadrilateral(ptr_quadrilaterals_mass, count_size_mass_quadrilaterals);
								std::cout << "Четырехугольник " << count_size_mass_quadrilaterals << " был создан конструктором со случайными параметрами." << std::endl;
							}
							move_quadrilateral = true;
						}
					}
				}
				if (is_stage == 4)
				{
					std::cout << "Выберите следующий примитив или вернитесь в MENU." << std::endl;
					return 0;
				}
				if (is_stage == 5 && count_size_mass_quadrilaterals >= 2)
				{
					show_quadrilateral = true; move_quadrilateral = false;
					combine_objects = !combine_objects;
					if (combine_objects && count_size_mass_quadrilaterals != 0)
						std::cout << "Режим группового изменения свойств объектов был включен. Возможность передвижения объектов выключена." << std::endl;
					else if (!combine_objects && count_size_mass_quadrilaterals != 0)
						std::cout << "Режим группового изменения свойств объектов был выключен. Возможность передвижения объектов выключена." << std::endl;
				};
				if (is_stage == 6 && move_quadrilateral && count_size_mass_quadrilaterals != 0)
				{
					if (!combine_objects)
					{
						std::cout << "Последний созданный четырехугольник был перемещен на случайные координаты [-50; 50]." << std::endl;
						random_move_quadrilaterals(ptr_quadrilaterals_mass, count_size_mass_quadrilaterals - 1);
					}
					else
					{
						for (unsigned i{}; i < count_size_mass_quadrilaterals;i++)
						{
							random_move_quadrilaterals(ptr_quadrilaterals_mass, i);
						}
						std::cout << "Все четырехугольники были перемещены на случайные координаты[-50; 50]." << std::endl;
					}
				}
				if (is_stage == 7 && count_size_mass_quadrilaterals != 0)
				{
					std::cout << "Четырехугольник " << count_size_mass_quadrilaterals << " был удален." << std::endl;
					save_size_mass_quadrilaterals = true;
					delete_element_shape<TQuadrilateral>(ptr_quadrilaterals_mass, count_size_mass_quadrilaterals);
					if (count_size_mass_quadrilaterals < 2)
					{
						if (combine_objects)
							std::cout << "Режим группового изменения свойств объектов был выключен. Возможность передвижения объектов выключена." << std::endl;
						combine_objects = false;
					}
					move_quadrilateral = false;
				}
				if (is_stage == 8)
				{
					std::cout << "Все четырехугольники были стерты." << std::endl;
					delete_elements_shape<TQuadrilateral>(ptr_quadrilaterals_mass, count_size_mass_quadrilaterals);
					combine_objects = false;
					move_quadrilateral = false;
					std::cout << "Режим группового изменения свойств объектов был выключен. Возможность передвижения объектов выключена." << std::endl;
				}
				if (is_stage == 9)
				{
					create_30_quadrilaterals = !create_30_quadrilaterals;
					if (create_30_quadrilaterals)
						std::cout << "Режим создания объектов целым массивом был включен." << std::endl;
					else if (!create_30_quadrilaterals)
						std::cout << "Режим создания объектов целым массивом был выключен." << std::endl;
				}
			}
			else if (event_click.type == sf::Event::KeyPressed && move_quadrilateral)
			{

				if (!combine_objects)
				{
					if (event_click.key.code == sf::Keyboard::W && (ptr_quadrilaterals_mass[count_size_mass_quadrilaterals - 1]->getCoordinateY() - 10) >= 115 &&
						(ptr_quadrilaterals_mass[count_size_mass_quadrilaterals - 1]->getCoordinateY2() - 10) >= 115)
					{
						ptr_quadrilaterals_mass[count_size_mass_quadrilaterals - 1]->MoveTo(0, -10);
						ptr_quadrilaterals_mass[count_size_mass_quadrilaterals - 1]->changeCoordinateX234_Y234(0, -10);
					}
					if (event_click.key.code == sf::Keyboard::A && (ptr_quadrilaterals_mass[count_size_mass_quadrilaterals - 1]->getCoordinateX() - 10) >= 465 &&
						(ptr_quadrilaterals_mass[count_size_mass_quadrilaterals - 1]->getCoordinateX4() - 10) >= 465)
					{
						ptr_quadrilaterals_mass[count_size_mass_quadrilaterals - 1]->MoveTo(-10, 0);
						ptr_quadrilaterals_mass[count_size_mass_quadrilaterals - 1]->changeCoordinateX234_Y234(-10, 0);
					}
					if (event_click.key.code == sf::Keyboard::S && (ptr_quadrilaterals_mass[count_size_mass_quadrilaterals - 1]->getCoordinateY3() + 10) <= 715 &&
						(ptr_quadrilaterals_mass[count_size_mass_quadrilaterals - 1]->getCoordinateY4() + 10) <= 715)
					{
						ptr_quadrilaterals_mass[count_size_mass_quadrilaterals - 1]->MoveTo(0, 10);
						ptr_quadrilaterals_mass[count_size_mass_quadrilaterals - 1]->changeCoordinateX234_Y234(0, 10);
					}
					if (event_click.key.code == sf::Keyboard::D && (ptr_quadrilaterals_mass[count_size_mass_quadrilaterals - 1]->getCoordinateX2() + 10) <= 1415 &&
						(ptr_quadrilaterals_mass[count_size_mass_quadrilaterals - 1]->getCoordinateX3() + 10) <= 1415)
					{
						ptr_quadrilaterals_mass[count_size_mass_quadrilaterals - 1]->MoveTo(10, 0);
						ptr_quadrilaterals_mass[count_size_mass_quadrilaterals - 1]->changeCoordinateX234_Y234(10, 0);
					}
					if (event_click.key.code == sf::Keyboard::E &&
						(ptr_quadrilaterals_mass[count_size_mass_quadrilaterals - 1]->getCoordinateX() - 1) >= 465 &&
						(ptr_quadrilaterals_mass[count_size_mass_quadrilaterals - 1]->getCoordinateY() - 1) >= 115 &&
						(ptr_quadrilaterals_mass[count_size_mass_quadrilaterals - 1]->getCoordinateX2() + 1) <= 1415 &&
						(ptr_quadrilaterals_mass[count_size_mass_quadrilaterals - 1]->getCoordinateY2() - 1) >= 115 &&
						(ptr_quadrilaterals_mass[count_size_mass_quadrilaterals - 1]->getCoordinateX3() + 1) <= 1415 &&
						(ptr_quadrilaterals_mass[count_size_mass_quadrilaterals - 1]->getCoordinateY3() + 1) <= 715 &&
						(ptr_quadrilaterals_mass[count_size_mass_quadrilaterals - 1]->getCoordinateX4() - 1) >= 465 &&
						(ptr_quadrilaterals_mass[count_size_mass_quadrilaterals - 1]->getCoordinateY4() + 1) <= 715)
					{
						ptr_quadrilaterals_mass[count_size_mass_quadrilaterals - 1]->changeSize(1);
					}
					if (event_click.key.code == sf::Keyboard::Q &&
						(ptr_quadrilaterals_mass[count_size_mass_quadrilaterals - 1]->getCoordinateX2() -
							ptr_quadrilaterals_mass[count_size_mass_quadrilaterals - 1]->getCoordinateX() - 2) >= 40 &&
						(ptr_quadrilaterals_mass[count_size_mass_quadrilaterals - 1]->getCoordinateY3() -
							ptr_quadrilaterals_mass[count_size_mass_quadrilaterals - 1]->getCoordinateY2() - 2) >= 40 &&
						(ptr_quadrilaterals_mass[count_size_mass_quadrilaterals - 1]->getCoordinateX3() -
							ptr_quadrilaterals_mass[count_size_mass_quadrilaterals - 1]->getCoordinateX4() - 2) >= 40 &&
						(ptr_quadrilaterals_mass[count_size_mass_quadrilaterals - 1]->getCoordinateY4() -
							ptr_quadrilaterals_mass[count_size_mass_quadrilaterals - 1]->getCoordinateY() - 2) >= 40)
					{
						ptr_quadrilaterals_mass[count_size_mass_quadrilaterals - 1]->changeSize(-1);
					}
				}
				else
				{
					if (event_click.key.code == sf::Keyboard::W)
					{
						for (unsigned i{}; i < count_size_mass_quadrilaterals;i++)
						{
							if ((ptr_quadrilaterals_mass[i]->getCoordinateY() - 10) >= 115 && (ptr_quadrilaterals_mass[i]->getCoordinateY2() - 10) >= 115)
							{
								ptr_quadrilaterals_mass[i]->MoveTo(0, -10);
								ptr_quadrilaterals_mass[i]->changeCoordinateX234_Y234(0, -10);
							}
						}
					}
					if (event_click.key.code == sf::Keyboard::A)
					{
						for (unsigned i{}; i < count_size_mass_quadrilaterals;i++)
						{
							if ((ptr_quadrilaterals_mass[i]->getCoordinateX() - 10) >= 465 && (ptr_quadrilaterals_mass[i]->getCoordinateX4() - 10) >= 465)
							{
								ptr_quadrilaterals_mass[i]->MoveTo(-10, 0);
								ptr_quadrilaterals_mass[i]->changeCoordinateX234_Y234(-10, 0);
							}
						}
					}
					if (event_click.key.code == sf::Keyboard::S)
					{
						for (unsigned i{}; i < count_size_mass_quadrilaterals;i++)
						{
							if ((ptr_quadrilaterals_mass[i]->getCoordinateY3() + 10) <= 715 && (ptr_quadrilaterals_mass[i]->getCoordinateY4() + 10) <= 715)
							{
								ptr_quadrilaterals_mass[i]->MoveTo(0, 10);
								ptr_quadrilaterals_mass[i]->changeCoordinateX234_Y234(0, 10);
							}
						}
					}
					if (event_click.key.code == sf::Keyboard::D)
					{
						for (unsigned i{}; i < count_size_mass_quadrilaterals;i++)
						{
							if ((ptr_quadrilaterals_mass[i]->getCoordinateX2() + 10) <= 1415 && (ptr_quadrilaterals_mass[i]->getCoordinateX3() + 10) <= 1415)
							{
								ptr_quadrilaterals_mass[i]->MoveTo(10, 0);
								ptr_quadrilaterals_mass[i]->changeCoordinateX234_Y234(10, 0);
							}
						}
					}
					if (event_click.key.code == sf::Keyboard::E)
					{
						for (unsigned i{}; i < count_size_mass_quadrilaterals;i++)
						{
							if ((ptr_quadrilaterals_mass[i]->getCoordinateX() - 1) >= 465 && (ptr_quadrilaterals_mass[i]->getCoordinateY() - 1) >= 115 &&
								(ptr_quadrilaterals_mass[i]->getCoordinateX2() + 1) <= 1415 && (ptr_quadrilaterals_mass[i]->getCoordinateY2() - 1) >= 115 &&
								(ptr_quadrilaterals_mass[i]->getCoordinateX3() + 1) <= 1415 && (ptr_quadrilaterals_mass[i]->getCoordinateY3() + 1) <= 715 &&
								(ptr_quadrilaterals_mass[i]->getCoordinateX4() - 1) >= 465 && (ptr_quadrilaterals_mass[i]->getCoordinateY4() + 1) <= 715)
							{
								ptr_quadrilaterals_mass[i]->changeSize(1);
							}
						}
					}
					if (event_click.key.code == sf::Keyboard::Q)
					{
						for (unsigned i{}; i < count_size_mass_quadrilaterals;i++)
						{
							if ((ptr_quadrilaterals_mass[i]->getCoordinateX2() - ptr_quadrilaterals_mass[i]->getCoordinateX() - 2) >= 40 &&
								(ptr_quadrilaterals_mass[i]->getCoordinateY3() - ptr_quadrilaterals_mass[i]->getCoordinateY2() - 2) >= 40 &&
								(ptr_quadrilaterals_mass[i]->getCoordinateX3() - ptr_quadrilaterals_mass[i]->getCoordinateX4() - 2) >= 40 &&
								(ptr_quadrilaterals_mass[i]->getCoordinateY4() - ptr_quadrilaterals_mass[i]->getCoordinateY() - 2) >= 40)
							{
								ptr_quadrilaterals_mass[i]->changeSize(-1);
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

		for (unsigned i{}; i < count_size_mass_rhombuses;i++)
		{
			ptr_rhombuses_mass[i]->Show(window);
		}

		for (unsigned i{}; i < count_size_mass_quadrilaterals;i++)
		{
			ptr_quadrilaterals_mass[i]->Show(window);
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