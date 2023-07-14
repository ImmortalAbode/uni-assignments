#include <SFML/Graphics.hpp>
#include <iostream>

#include "MyFuncs.h"
#include "CircleFuncs.h"
#include "RectangleFuncs.h"
#include "LinesegmentFuncs.h"
#include "Circle.h"
#include "Rectangle.h"
#include "LineSegment.h"
#include "UserButton.h"

float getRandomNumber(float min, float max)
{
	static const float fraction = 1.0 / (static_cast<float>(RAND_MAX) + 1.0);
	return (rand() * fraction * (max - min + 1) + min);
}


float getRandomMove()
{
	int min{ -50 }, max{ 50 };
	static const float fraction = 1.0 / (static_cast<float>(RAND_MAX) + 1.0);
	return (rand() * fraction * (max - min + 1) + min);
}


int stage_1_choice_shape(sf::RenderWindow& window)
{
	/*Кнопка Circle*/
	User_Text_Button circle_text_button{ "Comic_Sans_MS.TTF", "Circle", 30, 660, 110 };
	User_Rect_Button circle_rect_button{ 630, 100, 5, 250, 60 };

	/*Кнопка Rectangle*/
	User_Text_Button rectangle_text_button{ "Comic_Sans_MS.TTF", "Rectangle", 30, 660, 190 };
	User_Rect_Button rectangle_rect_button{ 630, 180, 5, 250, 60 };

	/*Кнопка LineSegment*/
	User_Text_Button linesegment_text_button{ "Comic_Sans_MS.TTF", "Linesegment", 30, 660, 270 };
	User_Rect_Button linesegment_rect_button{ 630, 260, 5, 250, 60 };

	/*Текст LIST*/
	User_Text_Button list_text{ "Comic_sans_MS.TTF", "L I S T:", 40, 670, 15 };

	/*Кнопка BACK*/
	User_Text_Button back_text_button{ "Comic_Sans_MS.TTF", "Back", 30, 50, 740 };
	User_Rect_Button back_rect_button{ 10, 730, 5, 200, 60 };

	int is_stage{};

	/*Работа с массивом класса Circle*/
	int count_size_mass_circles{}; //кол-во элементов в массиве
	Circle** ptr_circles_mass = new Circle * [count_size_mass_circles]; //массив кругов

	/*Работа с массивом класса Rectangle*/
	int count_size_mass_rectangles{}; //кол-во элементов в массиве
	Rectangle** ptr_rectangles_mass = new Rectangle * [count_size_mass_rectangles]; //массив прямоугольников

	/*Работа с массивом класса Linesegment*/
	int count_size_mass_linesegments{}; //кол-во элементов в массиве
	Line_Segment** ptr_linesegments_mass = new Line_Segment * [count_size_mass_linesegments]; //массив отрезков

	while (window.isOpen())
	{
		is_stage = 0;
		window.clear(sf::Color(137, 20, 190));

		circle_text_button.m_setFillColorDefault(); circle_rect_button.m_setOutlineColorDefault();
		rectangle_text_button.m_setFillColorDefault(); rectangle_rect_button.m_setOutlineColorDefault();
		linesegment_text_button.m_setFillColorDefault(); linesegment_rect_button.m_setOutlineColorDefault();
		back_text_button.m_setFillColorDefault(); back_rect_button.m_setOutlineColorDefault();

		if (sf::IntRect(625, 90, 260, 80).contains(sf::Mouse::getPosition(window)))
		{
			circle_text_button.m_setFillColor(255, 127, 39);
			circle_rect_button.m_setOutlineColor(165, 15, 203);
			is_stage = 1;
		}

		if (sf::IntRect(625, 170, 260, 80).contains(sf::Mouse::getPosition(window)))
		{
			rectangle_text_button.m_setFillColor(255, 127, 39);
			rectangle_rect_button.m_setOutlineColor(165, 15, 203);
			is_stage = 2;
		}

		if (sf::IntRect(625, 250, 260, 80).contains(sf::Mouse::getPosition(window)))
		{
			linesegment_text_button.m_setFillColor(255, 127, 39);
			linesegment_rect_button.m_setOutlineColor(165, 15, 203);
			is_stage = 3;
		}

		if (sf::IntRect(5, 720, 210, 70).contains(sf::Mouse::getPosition(window)))
		{
			back_text_button.m_setFillColor(255, 127, 39);
			back_rect_button.m_setOutlineColor(165, 15, 203);
			is_stage = 4;
		}

		sf::Event event_click;
		while (window.pollEvent(event_click))
		{
			if (event_click.type == sf::Event::Closed) 
			{ 
				delete_mass_objects<Circle>(ptr_circles_mass, count_size_mass_circles);
				delete_mass_objects<Rectangle>(ptr_rectangles_mass, count_size_mass_rectangles);
				delete_mass_objects<Line_Segment>(ptr_linesegments_mass, count_size_mass_linesegments);
				std::cout << "Все массивы были удалены из кучи. Окно закрыто." << std::endl;
				window.close(); 
				return 0;
			}
			else if (event_click.type == event_click.MouseButtonReleased && event_click.mouseButton.button == sf::Mouse::Left)
			{
				//sf::Vector2i position = sf::Mouse::getPosition(window);
				//std::cout << position.x << "\t" << position.y << std::endl;

				if (is_stage == 1) 
				{ 
					std::cout << "Вы выбрали класс объектов Circle." << std::endl;
					work_with_circles(window, ptr_circles_mass, count_size_mass_circles, ptr_rectangles_mass, count_size_mass_rectangles, 
						ptr_linesegments_mass, count_size_mass_linesegments); 
				}
				if (is_stage == 2) 
				{ 
					std::cout << "Вы выбрали класс объектов Rectangle." << std::endl;
					work_with_rectangles(window, ptr_rectangles_mass, count_size_mass_rectangles, ptr_circles_mass, count_size_mass_circles,
						ptr_linesegments_mass, count_size_mass_linesegments); 
				}
				if (is_stage == 3) 
				{
					std::cout << "Вы выбрали класс объектов Linesegment." << std::endl;
					work_with_linesegment(window, ptr_linesegments_mass, count_size_mass_linesegments, ptr_circles_mass, count_size_mass_circles,
						ptr_rectangles_mass, count_size_mass_rectangles);
				};
				if (is_stage == 4) 
				{ 
					delete_mass_objects<Circle>(ptr_circles_mass, count_size_mass_circles);
					delete_mass_objects<Rectangle>(ptr_rectangles_mass, count_size_mass_rectangles);
					delete_mass_objects<Line_Segment>(ptr_linesegments_mass, count_size_mass_linesegments);
					std::cout << "Все массивы примитивов были удалены из кучи. Вы вышли в MENU." << std::endl;
					return 0; 
				}
			}
		}

		circle_rect_button.Show(window); circle_text_button.Show(window);
		rectangle_rect_button.Show(window); rectangle_text_button.Show(window);
		linesegment_rect_button.Show(window); linesegment_text_button.Show(window);
		back_rect_button.Show(window); back_text_button.Show(window);

		list_text.Show(window);

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

		//Событие, чтобы понимать, есть нажатие мыши или нет
		sf::Event event_click;
		while (window.pollEvent(event_click))
		{
			if (event_click.type == event_click.MouseButtonReleased && event_click.mouseButton.button == sf::Mouse::Left && is_stage == 1)
			{
				std::cout << "Выберите класс примитивов или вернитесь в MENU." << std::endl;
				stage_1_choice_shape(window);
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

