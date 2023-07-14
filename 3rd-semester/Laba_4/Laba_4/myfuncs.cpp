#include <SFML/Graphics.hpp>
#include <iostream>

#include "MyFuncs.h"
#include "CircleFuncs.h"
#include "RectangleFuncs.h"
#include "LinesegmentFuncs.h"
#include "EllipseFuncs.h"
#include "QuadrilateralFuncs.h"
#include "TrapezeFuncs.h"
#include "RhombusFuncs.h"
#include "TFigure.h"
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
	/*������ Circle*/
	User_Text_Button circle_text_button{ "Comic_Sans_MS.TTF", "Circle", 30, 660, 110 };
	User_Rect_Button circle_rect_button{ 630, 100, 5, 250, 60 };

	/*������ Rectangle*/
	User_Text_Button rectangle_text_button{ "Comic_Sans_MS.TTF", "Rectangle", 30, 660, 190 };
	User_Rect_Button rectangle_rect_button{ 630, 180, 5, 250, 60 };

	/*������ LineSegment*/
	User_Text_Button linesegment_text_button{ "Comic_Sans_MS.TTF", "Linesegment", 30, 660, 270 };
	User_Rect_Button linesegment_rect_button{ 630, 260, 5, 250, 60 };

	/*������ Ellipse*/
	User_Text_Button ellipse_text_button{ "Comic_Sans_MS.TTF", "Ellipse", 30, 660, 350 };
	User_Rect_Button ellipse_rect_button{ 630, 340, 5, 250, 60 };

	/*������ Trapeze*/
	User_Text_Button trapeze_text_button{ "Comic_Sans_MS.TTF", "Trapeze", 30, 660, 430 };
	User_Rect_Button trapeze_rect_button{ 630, 420, 5, 250, 60 };

	/*������ Rhombus*/
	User_Text_Button rhombus_text_button{ "Comic_Sans_MS.TTF", "Rhombus", 30, 660, 510 };
	User_Rect_Button rhombus_rect_button{ 630, 500, 5, 250, 60 };

	/*������ Quadrilateral*/
	User_Text_Button quadrilateral_text_button{ "Comic_Sans_MS.TTF", "Quadrilateral", 30, 660, 590 };
	User_Rect_Button quadrilateral_rect_button{ 630, 580, 5, 250, 60 };

	/*����� LIST*/
	User_Text_Button list_text{ "Comic_sans_MS.TTF", "L I S T:", 40, 670, 15 };

	/*������ BACK*/
	User_Text_Button back_text_button{ "Comic_Sans_MS.TTF", "Back", 30, 50, 740 };
	User_Rect_Button back_rect_button{ 10, 730, 5, 200, 60 };

	int is_stage{};

	/*������ � �������� ������ TCircle*/
	int count_size_mass_circles{}; //���-�� ��������� � �������
	TCircle** ptr_circles_mass = new TCircle * [count_size_mass_circles]; //������ ������

	/*������ � �������� ������ TRectangle*/
	int count_size_mass_rectangles{}; //���-�� ��������� � �������
	TRectangle** ptr_rectangles_mass = new TRectangle * [count_size_mass_rectangles]; //������ ���������������

	/*������ � �������� ������ TLinesegment*/
	int count_size_mass_linesegments{}; //���-�� ��������� � �������
	TLinesegment** ptr_linesegments_mass = new TLinesegment * [count_size_mass_linesegments]; //������ ��������

	/*������ � �������� ������ TEllipse*/
	int count_size_mass_ellipses{}; //���-�� ��������� � �������
	TEllipse** ptr_ellipses_mass = new TEllipse * [count_size_mass_ellipses]; //������ ��������

	/*������ � �������� ������ TTrapeze*/
	int count_size_mass_trapezes{}; //���-�� ��������� � �������
	TTrapeze** ptr_trapezes_mass = new TTrapeze * [count_size_mass_trapezes]; //������ ��������

	/*������ � �������� ������ TRhombus*/
	int count_size_mass_rhombuses{}; //���-�� ��������� � �������
	TRhombus** ptr_rhombuses_mass = new TRhombus * [count_size_mass_rhombuses]; //������ ������

	/*������ � �������� ������ TQuadrilateral*/
	int count_size_mass_quadrilaterals{}; //���-�� ��������� � �������
	TQuadrilateral** ptr_quadrilaterals_mass = new TQuadrilateral * [count_size_mass_quadrilaterals]; //������ �����������������

	while (window.isOpen())
	{
		is_stage = 0;
		window.clear(sf::Color(137, 20, 190));

		circle_text_button.m_setFillColorDefault(); circle_rect_button.m_setOutlineColorDefault();
		rectangle_text_button.m_setFillColorDefault(); rectangle_rect_button.m_setOutlineColorDefault();
		linesegment_text_button.m_setFillColorDefault(); linesegment_rect_button.m_setOutlineColorDefault();
		ellipse_text_button.m_setFillColorDefault(); ellipse_rect_button.m_setOutlineColorDefault();
		trapeze_text_button.m_setFillColorDefault(); trapeze_rect_button.m_setOutlineColorDefault();
		rhombus_text_button.m_setFillColorDefault(); rhombus_rect_button.m_setOutlineColorDefault();
		quadrilateral_text_button.m_setFillColorDefault(); quadrilateral_rect_button.m_setOutlineColorDefault();
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

		if (sf::IntRect(625, 330, 260, 80).contains(sf::Mouse::getPosition(window)))
		{
			ellipse_text_button.m_setFillColor(255, 127, 39);
			ellipse_rect_button.m_setOutlineColor(165, 15, 203);
			is_stage = 4;
		}

		if (sf::IntRect(625, 410, 260, 80).contains(sf::Mouse::getPosition(window)))
		{
			trapeze_text_button.m_setFillColor(255, 127, 39);
			trapeze_rect_button.m_setOutlineColor(165, 15, 203);
			is_stage = 5;
		}

		if (sf::IntRect(625, 490, 260, 80).contains(sf::Mouse::getPosition(window)))
		{
			rhombus_text_button.m_setFillColor(255, 127, 39);
			rhombus_rect_button.m_setOutlineColor(165, 15, 203);
			is_stage = 6;
		}

		if (sf::IntRect(625, 570, 260, 80).contains(sf::Mouse::getPosition(window)))
		{
			quadrilateral_text_button.m_setFillColor(255, 127, 39);
			quadrilateral_rect_button.m_setOutlineColor(165, 15, 203);
			is_stage = 7;
		}

		if (sf::IntRect(5, 720, 210, 70).contains(sf::Mouse::getPosition(window)))
		{
			back_text_button.m_setFillColor(255, 127, 39);
			back_rect_button.m_setOutlineColor(165, 15, 203);
			is_stage = 8;
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
				std::cout << "��� ������� ���� ������� �� ����. ���� �������." << std::endl;
				window.close();
				return 0;
			}
			else if (event_click.type == event_click.MouseButtonReleased && event_click.mouseButton.button == sf::Mouse::Left)
			{
				//sf::Vector2i position = sf::Mouse::getPosition(window);
				//std::cout << position.x << "\t" << position.y << std::endl;

				if (is_stage == 1)
				{
					std::cout << "�� ������� ����� �������� TCircle." << std::endl;
					work_with_circles(window, ptr_circles_mass, count_size_mass_circles, ptr_rectangles_mass, count_size_mass_rectangles,
						ptr_linesegments_mass, count_size_mass_linesegments, ptr_ellipses_mass, count_size_mass_ellipses, ptr_trapezes_mass, count_size_mass_trapezes,
						ptr_rhombuses_mass, count_size_mass_rhombuses, ptr_quadrilaterals_mass, count_size_mass_quadrilaterals);
				}
				if (is_stage == 2)
				{
					std::cout << "�� ������� ����� �������� TRectangle." << std::endl;
					work_with_rectangles(window, ptr_rectangles_mass, count_size_mass_rectangles, ptr_circles_mass, count_size_mass_circles,
						ptr_linesegments_mass, count_size_mass_linesegments, ptr_ellipses_mass, count_size_mass_ellipses, ptr_trapezes_mass, count_size_mass_trapezes,
						ptr_rhombuses_mass, count_size_mass_rhombuses, ptr_quadrilaterals_mass, count_size_mass_quadrilaterals);
				}
				if (is_stage == 3)
				{
					std::cout << "�� ������� ����� �������� TLinesegment." << std::endl;
					work_with_linesegment(window, ptr_linesegments_mass, count_size_mass_linesegments, ptr_circles_mass, count_size_mass_circles, ptr_rectangles_mass,
						count_size_mass_rectangles, ptr_ellipses_mass, count_size_mass_ellipses, ptr_trapezes_mass, count_size_mass_trapezes,
						ptr_rhombuses_mass, count_size_mass_rhombuses, ptr_quadrilaterals_mass, count_size_mass_quadrilaterals);
				};
				if (is_stage == 4)
				{
					std::cout << "�� ������� ����� �������� TEllipse." << std::endl;
					work_with_ellipses(window, ptr_ellipses_mass, count_size_mass_ellipses, ptr_circles_mass, count_size_mass_circles, ptr_rectangles_mass, count_size_mass_rectangles,
						ptr_linesegments_mass, count_size_mass_linesegments, ptr_trapezes_mass, count_size_mass_trapezes, ptr_rhombuses_mass, count_size_mass_rhombuses,
						ptr_quadrilaterals_mass, count_size_mass_quadrilaterals);
				}
				if (is_stage == 5)
				{
					std::cout << "�� ������� ����� �������� TTrapeze." << std::endl;
					work_with_trapezes(window, ptr_trapezes_mass, count_size_mass_trapezes, ptr_circles_mass, count_size_mass_circles, ptr_rectangles_mass, count_size_mass_rectangles,
						ptr_linesegments_mass, count_size_mass_linesegments, ptr_ellipses_mass, count_size_mass_ellipses,
						ptr_rhombuses_mass, count_size_mass_rhombuses, ptr_quadrilaterals_mass, count_size_mass_quadrilaterals);
				}
				if (is_stage == 6)
				{
					std::cout << "�� ������� ����� �������� TRhombus." << std::endl;
					work_with_rhombuses(window, ptr_rhombuses_mass, count_size_mass_rhombuses, ptr_circles_mass, count_size_mass_circles, ptr_rectangles_mass, count_size_mass_rectangles,
						ptr_linesegments_mass, count_size_mass_linesegments, ptr_ellipses_mass, count_size_mass_ellipses, ptr_trapezes_mass, count_size_mass_trapezes,
						ptr_quadrilaterals_mass, count_size_mass_quadrilaterals);
				}
				if (is_stage == 7)
				{
					std::cout << "�� ������� ����� �������� TQuadrilateral." << std::endl;
					work_with_quadrilaterals(window, ptr_quadrilaterals_mass, count_size_mass_quadrilaterals, ptr_circles_mass, count_size_mass_circles, ptr_rectangles_mass,
						count_size_mass_rectangles, ptr_linesegments_mass, count_size_mass_linesegments, ptr_ellipses_mass, count_size_mass_ellipses, ptr_trapezes_mass,
						count_size_mass_trapezes, ptr_rhombuses_mass, count_size_mass_rhombuses);
				}
				if (is_stage == 8)
				{
					delete_mass_objects<TCircle>(ptr_circles_mass, count_size_mass_circles);
					delete_mass_objects<TRectangle>(ptr_rectangles_mass, count_size_mass_rectangles);
					delete_mass_objects<TLinesegment>(ptr_linesegments_mass, count_size_mass_linesegments);
					delete_mass_objects<TEllipse>(ptr_ellipses_mass, count_size_mass_ellipses);
					delete_mass_objects<TTrapeze>(ptr_trapezes_mass, count_size_mass_trapezes);
					delete_mass_objects<TRhombus>(ptr_rhombuses_mass, count_size_mass_rhombuses);
					delete_mass_objects<TQuadrilateral>(ptr_quadrilaterals_mass, count_size_mass_quadrilaterals);
					std::cout << "��� ������� ���������� ���� ������� �� ����. �� ����� � MENU." << std::endl;
					return 0;
				}
			}
		}

		circle_rect_button.Show(window); circle_text_button.Show(window);
		rectangle_rect_button.Show(window); rectangle_text_button.Show(window);
		linesegment_rect_button.Show(window); linesegment_text_button.Show(window);
		ellipse_rect_button.Show(window); ellipse_text_button.Show(window);
		trapeze_rect_button.Show(window); trapeze_text_button.Show(window);
		rhombus_rect_button.Show(window); rhombus_text_button.Show(window);
		quadrilateral_rect_button.Show(window); quadrilateral_text_button.Show(window);
		back_rect_button.Show(window); back_text_button.Show(window);

		list_text.Show(window);

		window.display();
	}
	return 0;
}


bool stage_0_menu(sf::RenderWindow& window)
{
	std::cout << "������� MENU ��� ������� �� ���������." << std::endl;
	int is_stage{};

	/*������ ����*/
	//����� MENU
	User_Text_Button menu_text{ "Comic_Sans_MS.TTF", "MENU", 50, 685, 340 };
	//������������� MENU
	User_Rect_Button menu_rect{ 625, 330, 5, 300, 80 };

	/*������ �����*/
	//����� EXIT
	User_Text_Button exit_text{ "Comic_Sans_MS.TTF", "EXIT", 50, 685, 440 };
	//������������� EXIT
	User_Rect_Button exit_rect{ 625, 430, 5, 300, 80 };

	while (window.isOpen())
	{
		//���������� ��� �������� ����� ���� � �������
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

		//�������, ����� ��������, ���� ������� ���� ��� ���
		sf::Event event_click;
		while (window.pollEvent(event_click))
		{
			if (event_click.type == event_click.MouseButtonReleased && event_click.mouseButton.button == sf::Mouse::Left && is_stage == 1)
			{
				std::cout << "�������� ����� ���������� ��� ��������� � MENU." << std::endl;
				stage_1_choice_shape(window);
			}
			if (event_click.type == event_click.MouseButtonReleased && event_click.mouseButton.button == sf::Mouse::Left && is_stage == 2)
			{
				std::cout << "�� ����� �� ���������. ���� �������." << std::endl;
				window.close();
			}
			else if (event_click.type == sf::Event::Closed)
			{
				std::cout << "���� ���� �������." << std::endl;
				window.close();
			}
		};

		menu_rect.Show(window); menu_text.Show(window);
		exit_rect.Show(window); exit_text.Show(window);

		window.display();
	}

	return false;
}

