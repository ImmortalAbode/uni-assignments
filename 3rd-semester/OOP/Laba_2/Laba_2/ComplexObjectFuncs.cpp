#include <SFML/Graphics.hpp>
#include <iostream>

#include "MyFuncs.h"
#include "UserButton.h"
#include "ComplexObjectFuncs.h"
#include "Ring.h"
#include "Circle.h"
#include "Rectangle.h"
#include "LineSegment.h"
#include "ComplexObject.h"

void random_move_complex_objects(ComplexObject** ptr_complex_objects_mass, int num_element)
{
	while (true)
	{
		float dx{ getRandomNumber(-50,50) }, dy{ getRandomNumber(-50,50) };
		if ((ptr_complex_objects_mass[num_element]->getRectangle().getCoordinateX() + dx) >= 465 &&
			(ptr_complex_objects_mass[num_element]->getLineSegmentLeft().getCoordinateX() + ptr_complex_objects_mass[num_element]->getLineSegmentLeft().getLength() *
				cos(135 * acos(-1.0f) / 180) + dx) >= 465 &&
			(ptr_complex_objects_mass[num_element]->getCircle().getCoordinateX() + ptr_complex_objects_mass[num_element]->getCircle().getRadius() + dx) <= 1415 &&
			(ptr_complex_objects_mass[num_element]->getLineSegmentRight().getCoordinateX() + ptr_complex_objects_mass[num_element]->getLineSegmentRight().getLength() *
				cos(45 * acos(-1.0f) / 180) + dx) <= 1415 &&
			(ptr_complex_objects_mass[num_element]->getRectangle().getCoordinateY() + dy) >= 115 &&
			(ptr_complex_objects_mass[num_element]->getLineSegmentLeft().getCoordinateY() +
				ptr_complex_objects_mass[num_element]->getLineSegmentLeft().getLength() * sin(135 * acos(-1.0f) / 180) + dy) <= 715)
		{
			ptr_complex_objects_mass[num_element]->MoveTo(dx, dy);
			break;
		}
	}
}

void create_random_complex_object(ComplexObject**& ptr_complex_objects_mass, int& count_size_mass_complex_objects)
{
	ComplexObject* ptr_obj_complex_object{ nullptr };
	while (true)
	{
		float rectangle_length{ getRandomNumber(30, 400) };
		float rectangle_width{ getRandomNumber(30, 250) };
		float rectangle_x{ getRandomNumber(465, 1415) };
		float rectangle_y{ getRandomNumber(115, 715) };
		float radius_circle{ rectangle_width / 2 };
		float circle_x{ rectangle_x + rectangle_length };
		float circle_y{ rectangle_y + rectangle_width / 2 };
		float line_segments_x{ rectangle_x + rectangle_length / 2 };
		float line_segments_y{ rectangle_y + rectangle_width };
		float line_segments_length{ getRandomNumber(80, 120) };
		Rectangle rectangle{ {rectangle_x, rectangle_y}, rectangle_length, rectangle_width };
		Circle circle{ radius_circle, {circle_x, circle_y} };
		Line_Segment line_segment_left{ {line_segments_x, line_segments_y}, line_segments_length, 45 };
		Line_Segment line_segment_right{ {line_segments_x, line_segments_y}, line_segments_length, 135 };
		if (circle.getRadius() == rectangle.getWidth() / 2 && rectangle.getLength() > circle.getRadius() + 20)
		{
			if (line_segment_left.getLength() > line_segment_right.getLength())
				line_segment_left.changeLength(line_segment_right.getLength() - line_segment_left.getLength());
			else
				line_segment_right.changeLength(line_segment_left.getLength() - line_segment_right.getLength());
			ptr_obj_complex_object = new ComplexObject(rectangle, circle, line_segment_left, line_segment_right);
			break;
		}
		else
		{
			std::cout << "!!!��������� ������ �� ������������ �������� �������� � ���� ������� ����������." << std::endl;
			std::cout << ".......������......." << std::endl;
		}
	}
	ptr_obj_complex_object->getRectangle().setColor(getRandomNumber(0, 255), getRandomNumber(0, 255), getRandomNumber(0, 255));
	ptr_obj_complex_object->getRectangle().setColorOutline(getRandomNumber(0, 255), getRandomNumber(0, 255), getRandomNumber(0, 255));
	ptr_obj_complex_object->getRectangle().setVisibility(getRandomNumber(50, 255));
	ptr_obj_complex_object->getCircle().setColor(getRandomNumber(0, 255), getRandomNumber(0, 255), getRandomNumber(0, 255));
	ptr_obj_complex_object->getCircle().setColorOutline(getRandomNumber(0, 255), getRandomNumber(0, 255), getRandomNumber(0, 255));
	ptr_obj_complex_object->getCircle().setVisibility(getRandomNumber(50, 255));
	ptr_obj_complex_object->getLineSegmentLeft().setColor(getRandomNumber(0, 255), getRandomNumber(0, 255), getRandomNumber(0, 255));
	ptr_obj_complex_object->getLineSegmentRight().setColor(getRandomNumber(0, 255), getRandomNumber(0, 255), getRandomNumber(0, 255));
	push_back_shape<ComplexObject>(ptr_complex_objects_mass, count_size_mass_complex_objects, ptr_obj_complex_object);
}

int work_with_complex_objects(sf::RenderWindow& window, ComplexObject**& ptr_complex_objects_mass, int& count_size_mass_complex_objects,
	Circle** ptr_circles_mass, int count_size_mass_circles, Rectangle** ptr_rectangles_mass, int count_size_mass_rectangles,
	Line_Segment** ptr_linesegments_mass, int count_size_mass_linesegments, Ring** ptr_rings_mass, int count_size_mass_rings)
{
	/*������ CREATE*/
	User_Text_Button create_text_button{ "Comic_Sans_MS.TTF", "Create element of complex objects", 25, 15, 20 };
	User_Rect_Button create_rect_button{ 10, 10, 5, 440, 60 };

	/*������ MOVETO*/
	User_Text_Button moveTo_text_button{ "Comic_Sans_MS.TTF", "Move to...", 30, 15, 110 };
	User_Rect_Button moveTo_rect_button{ 10, 100, 5, 200, 60 };

	/*������ BACK*/
	User_Text_Button back_text_button{ "Comic_Sans_MS.TTF", "Back", 30, 50, 740 };
	User_Rect_Button back_rect_button{ 10, 730, 5, 200, 60 };

	//����� IMAGE
	User_Text_Button image_text{ "Comic_Sans_MS.TTF", "Image", 60, 850, 10 };
	User_Rect_Button image_rect(465, 115, 0, 950, 600); image_rect.m_setColor(178, 143, 252);

	/*������ COMBINE OBJECTS*/
	User_Text_Button combine_objects_text_button{ "Comic_Sans_MS.TTF", "Combine objects", 30, 478, 25 };
	User_Rect_Button combine_objects_rect_button{ 470, 10, 5, 250, 60 };

	/*������ RANDOM MOVE*/
	User_Text_Button random_move_text_button{ "Comic_Sans_MS.TTF", "Random move", 30, 1230, 25 };
	User_Rect_Button random_move_rect_button{ 1200, 10, 5, 250, 60 };

	/*������ SHOW COMPLEX OBJECT*/
	User_Text_Button show_text_button{ "Comic_Sans_MS.TTF", "Show complex object", 30, 15, 200 };
	User_Rect_Button show_rect_button{ 10, 190, 5, 330, 60 };

	//������ ���������� ��������
	User_Text_Button move_shapes{ "Comic_Sans_MS.TTF", "Move up shape (W)    Move down shape (S)   Move left shape (A)    Move right shape (D)", 20, 260, 770 };
	User_Text_Button special_movements{ "Comic_Sans_MS.TTF", "Decrease shape(Q)           Increase shape(E)", 20, 260, 730 };

	/*������ �������� ��������*/
	User_Text_Button delete_element_text_button{ "Comic_Sans_MS.TTF", "Delete element", 30, 15, 290 };
	User_Rect_Button delete_element_rect_button{ 10, 280, 5, 240, 60 };

	/*������ �������� ���� ���������*/
	User_Text_Button delete_all_elements_text_button{ "Comic_Sans_MS.TTF", "Delete all elements", 30, 15, 380 };
	User_Rect_Button delete_all_elements_rect_button{ 10, 370, 5, 300, 60 };

	/*������ �������� 30 ���������*/
	User_Text_Button create_30_elements_text_button{ "Comic_Sans_MS.TTF", "Create array of complex objects", 25, 15, 470 };
	User_Rect_Button create_30_elements_rect_button{ 10, 460, 5, 430, 60 };

	int is_stage{};

	bool show_complex_object{ true }; //�������� ��������� ������ ��� ������� ������, ��������� ������
	bool move_complex_object{ false }; //��������� ��������� ������� ��������� ��� ���
	bool combine_objects{ false }; //���� �� ������ � �������� ��������
	bool save_size_mass_complex_objects{ true };//��������� ������ ������� ��� SHOW ������ ��� ���
	bool create_30_complex_objects{ false }; //������� ������ �� 30 ��������� ��������, ������� ��� � ���������
	int iteration_counter_combine_objs{}; //�������� ��� ������ SHOW ��� ������ � ��������

	while (window.isOpen())
	{
		is_stage = 0;
		window.clear(sf::Color(137, 20, 190));

		create_text_button.m_setFillColorDefault(); create_rect_button.m_setOutlineColorDefault();

		moveTo_text_button.m_setFillColorDefault();
		if (move_complex_object) moveTo_rect_button.m_setOutlineColor(247, 30, 241);
		else moveTo_rect_button.m_setOutlineColorDefault();

		back_text_button.m_setFillColorDefault(); back_rect_button.m_setOutlineColorDefault();

		combine_objects_text_button.m_setFillColorDefault();
		if (combine_objects && count_size_mass_complex_objects != 0) combine_objects_rect_button.m_setOutlineColor(247, 30, 241);
		else combine_objects_rect_button.m_setOutlineColorDefault();

		random_move_text_button.m_setFillColorDefault(); random_move_rect_button.m_setOutlineColorDefault();
		delete_element_text_button.m_setFillColorDefault(); delete_element_rect_button.m_setOutlineColorDefault();

		show_text_button.m_setFillColorDefault();
		if (show_complex_object && count_size_mass_complex_objects != 0) show_rect_button.m_setOutlineColor(247, 30, 241);
		else show_rect_button.m_setOutlineColorDefault();

		create_30_elements_text_button.m_setFillColorDefault();
		if (create_30_complex_objects) create_30_elements_rect_button.m_setOutlineColor(247, 30, 241);
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

		if (sf::IntRect(5, 180, 340, 80).contains(sf::Mouse::getPosition(window))) // show
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
				delete_mass_objects<Ring>(ptr_rings_mass, count_size_mass_rings);
				delete_mass_objects<Circle>(ptr_circles_mass, count_size_mass_circles);
				delete_mass_objects<Rectangle>(ptr_rectangles_mass, count_size_mass_rectangles);
				delete_mass_objects<Line_Segment>(ptr_linesegments_mass, count_size_mass_linesegments);
				delete_mass_objects<ComplexObject>(ptr_complex_objects_mass, count_size_mass_complex_objects);
				std::cout << "��� ������� ���������� ���� ������� �� ����. ���� �������." << std::endl;
				window.close();
				return 0;
			}
			else if (event_click.type == event_click.MouseButtonReleased && event_click.mouseButton.button == sf::Mouse::Left)
			{
				//sf::Vector2i position = sf::Mouse::getPosition(window);
				//std::cout << position.x << "\t" << position.y << std::endl;

				if (is_stage == 1)
				{
					if (create_30_complex_objects)
					{
						show_complex_object = true;
						save_size_mass_complex_objects = true;
						for (unsigned i{}; i < 30;i++)
						{
							if (count_size_mass_complex_objects == 0)
							{
								ComplexObject* ptr_obj_complex_object{ nullptr };
								ptr_obj_complex_object = new ComplexObject{};
								push_back_shape<ComplexObject>(ptr_complex_objects_mass, count_size_mass_complex_objects, ptr_obj_complex_object);
							}
							else
							{
								create_random_complex_object(ptr_complex_objects_mass, count_size_mass_complex_objects);
							}
						}
						if (count_size_mass_complex_objects - 30 != 0) 
							std::cout << "������ ��������� �������� ��� ������ ������������� �� ���������� �����������." << std::endl;
						else 
							std::cout << "������ ��������� �������� ��� ������ ������������� �� ���������� �����������. ������ ������ - ������������� �� ���������." << std::endl;
						std::cout << "�� ���� SFML ��������� " << count_size_mass_complex_objects << " ��������� ��������." << std::endl;
					}
					else if (count_size_mass_complex_objects == 0)
					{
						ComplexObject* ptr_obj_complex_object{ nullptr };
						ptr_obj_complex_object = new ComplexObject{};
						push_back_shape<ComplexObject>(ptr_complex_objects_mass, count_size_mass_complex_objects, ptr_obj_complex_object);
						show_complex_object = true;
						save_size_mass_complex_objects = true;
						std::cout << "��������� ������ " << count_size_mass_complex_objects << " ��� ������ ������������� �� ���������." << std::endl;
					}
					else
					{
						create_random_complex_object(ptr_complex_objects_mass, count_size_mass_complex_objects);
						show_complex_object = true;
						save_size_mass_complex_objects = true;
						std::cout << "��������� ������ " << count_size_mass_complex_objects << " ��� ������ ������������� �� ���������� �����������." << std::endl;
					}
				}
				if (is_stage == 2 && count_size_mass_complex_objects != 0)
				{
					move_complex_object = !move_complex_object;

					if (!combine_objects)
					{
						if (move_complex_object) std::cout << "������������ ��������� ��������� ������ ��������." << std::endl;
						else std::cout << "������������ ��������� ��������� ������ ���������." << std::endl;
					}
					else
					{
						if (move_complex_object) std::cout << "������������ ���� ��������� ����� ��������." << std::endl;
						else std::cout << "������������ ���� ��������� ����� ���������." << std::endl;
					}
				}
				if (is_stage == 3 && (count_size_mass_complex_objects != 0 || count_size_mass_complex_objects == 0 && !show_complex_object))
				{
					if (save_size_mass_complex_objects) iteration_counter_combine_objs = count_size_mass_complex_objects;
					show_complex_object = !show_complex_object;
					if (!show_complex_object)
					{
						if (!combine_objects)
						{
							std::cout << "��������� ��������� ��������� ������ ���� ������." << std::endl;
							delete_element_shape<ComplexObject>(ptr_complex_objects_mass, count_size_mass_complex_objects);
							move_complex_object = false;
						}
						else
						{
							std::cout << "��� ��������� ������� ���� ������." << std::endl;
							save_size_mass_complex_objects = false;
							for (unsigned i{}; i < iteration_counter_combine_objs;i++)
							{
								delete_element_shape<ComplexObject>(ptr_complex_objects_mass, count_size_mass_complex_objects);
							}
							move_complex_object = false;
						}
					}
					else
					{
						if (!combine_objects)
						{
							create_random_complex_object(ptr_complex_objects_mass, count_size_mass_complex_objects);
							std::cout << "��������� ������ " << count_size_mass_complex_objects << " ��� ������ ������������� �� ���������� �����������." << std::endl;
							move_complex_object = true;
						}
						else
						{
							for (unsigned i{}; i < iteration_counter_combine_objs; i++)
							{
								create_random_complex_object(ptr_complex_objects_mass, count_size_mass_complex_objects);
								std::cout << "��������� ������ " << count_size_mass_complex_objects << " ��� ������ ������������� �� ���������� �����������." << std::endl;
							}
							move_complex_object = true;
						}
					}
				}
				if (is_stage == 4)
				{
					std::cout << "�������� ��������� �������� ��� ��������� � MENU." << std::endl;
					return 0;
				}
				if (is_stage == 5 && count_size_mass_complex_objects >= 2)
				{
					show_complex_object = true; move_complex_object = false;
					combine_objects = !combine_objects;
					if (combine_objects && count_size_mass_complex_objects != 0)
						std::cout << "����� ���������� ��������� ������� �������� ��� �������. ����������� ������������ �������� ���������." << std::endl;
					else if (!combine_objects && count_size_mass_complex_objects != 0)
						std::cout << "����� ���������� ��������� ������� �������� ��� ��������. ����������� ������������ �������� ���������." << std::endl;
				};
				if (is_stage == 6 && move_complex_object && count_size_mass_complex_objects != 0)
				{
					if (!combine_objects)
					{
						std::cout << "��������� ��������� ��������� ������ ��� ��������� �� ��������� ���������� [-50; 50]." << std::endl;
						random_move_complex_objects(ptr_complex_objects_mass, count_size_mass_complex_objects - 1);
					}
					else
					{
						for (unsigned i{}; i < count_size_mass_complex_objects;i++)
						{
							random_move_complex_objects(ptr_complex_objects_mass, i);
						}
						std::cout << "��� ��������� ������� ���� ���������� �� ��������� ����������[-50; 50]." << std::endl;
					}
				}
				if (is_stage == 7 && count_size_mass_complex_objects != 0)
				{
					std::cout << "��������� ������ " << count_size_mass_complex_objects << " ��� ������." << std::endl;
					save_size_mass_complex_objects = true;
					delete_element_shape<ComplexObject>(ptr_complex_objects_mass, count_size_mass_complex_objects);
					if (count_size_mass_complex_objects < 2)
					{
						if (combine_objects)
							std::cout << "����� ���������� ��������� ������� �������� ��� ��������. ����������� ������������ �������� ���������." << std::endl;
						combine_objects = false;
					}
					move_complex_object = false;
				}
				if (is_stage == 8)
				{
					std::cout << "��� ��������� ������� ���� ������." << std::endl;
					delete_elements_shape<ComplexObject>(ptr_complex_objects_mass, count_size_mass_complex_objects);
					combine_objects = false;
					move_complex_object = false;
					std::cout << "����� ���������� ��������� ������� �������� ��� ��������. ����������� ������������ �������� ���������." << std::endl;
				}
				if (is_stage == 9)
				{
					create_30_complex_objects = !create_30_complex_objects;
					if (create_30_complex_objects)
						std::cout << "����� �������� �������� ����� �������� ��� �������." << std::endl;
					else if (!create_30_complex_objects)
						std::cout << "����� �������� �������� ����� �������� ��� ��������." << std::endl;
				}
			}
			else if (event_click.type == sf::Event::KeyPressed && move_complex_object)
			{

				if (!combine_objects)
				{
					if (event_click.key.code == sf::Keyboard::W && 
						(ptr_complex_objects_mass[count_size_mass_complex_objects - 1]->getRectangle().getCoordinateY() - 10) >= 115)
					{
						ptr_complex_objects_mass[count_size_mass_complex_objects - 1]->MoveTo(0, -10);
					}
					if (event_click.key.code == sf::Keyboard::A)
					{
						if (ptr_complex_objects_mass[count_size_mass_complex_objects - 1]->getRectangle().getCoordinateX() <
							(ptr_complex_objects_mass[count_size_mass_complex_objects - 1]->getLineSegmentLeft().getCoordinateX() +
								ptr_complex_objects_mass[count_size_mass_complex_objects - 1]->getLineSegmentLeft().getLength() * cos(135 * acos(-1.0f) / 180)))
						{
							if ((ptr_complex_objects_mass[count_size_mass_complex_objects - 1]->getRectangle().getCoordinateX() - 10) >= 465)
								ptr_complex_objects_mass[count_size_mass_complex_objects - 1]->MoveTo(-10, 0);
						}
						else if ((ptr_complex_objects_mass[count_size_mass_complex_objects - 1]->getLineSegmentLeft().getCoordinateX() +
							ptr_complex_objects_mass[count_size_mass_complex_objects - 1]->getLineSegmentLeft().getLength() * cos(135 * acos(-1.0f) / 180) - 10) >= 465)
							ptr_complex_objects_mass[count_size_mass_complex_objects - 1]->MoveTo(-10, 0);
					}
					if (event_click.key.code == sf::Keyboard::S && 
						(ptr_complex_objects_mass[count_size_mass_complex_objects - 1]->getLineSegmentLeft().getCoordinateY() +  
							ptr_complex_objects_mass[count_size_mass_complex_objects - 1]->getLineSegmentLeft().getLength() * sin(135 * acos(-1.0f) / 180) + 10) <= 715)
					{
						ptr_complex_objects_mass[count_size_mass_complex_objects - 1]->MoveTo(0, 10);
					}
					if (event_click.key.code == sf::Keyboard::D)
					{
						if ((ptr_complex_objects_mass[count_size_mass_complex_objects - 1]->getCircle().getCoordinateX() +
							ptr_complex_objects_mass[count_size_mass_complex_objects - 1]->getCircle().getRadius()) >
							(ptr_complex_objects_mass[count_size_mass_complex_objects - 1]->getLineSegmentRight().getCoordinateX() +
								ptr_complex_objects_mass[count_size_mass_complex_objects - 1]->getLineSegmentRight().getLength() * cos(45 * acos(-1.0f) / 180)))
						{
							if ((ptr_complex_objects_mass[count_size_mass_complex_objects - 1]->getCircle().getCoordinateX() + 10 +
								ptr_complex_objects_mass[count_size_mass_complex_objects - 1]->getCircle().getRadius()) <= 1415)
								ptr_complex_objects_mass[count_size_mass_complex_objects - 1]->MoveTo(10, 0);
						}
						else if ((ptr_complex_objects_mass[count_size_mass_complex_objects - 1]->getLineSegmentRight().getCoordinateX() +
							ptr_complex_objects_mass[count_size_mass_complex_objects - 1]->getLineSegmentRight().getLength() * cos(45 * acos(-1.0f) / 180) + 10) <= 1415)
							ptr_complex_objects_mass[count_size_mass_complex_objects - 1]->MoveTo(10, 0);
						
					}
					if (event_click.key.code == sf::Keyboard::E &&
						((ptr_complex_objects_mass[count_size_mass_complex_objects - 1]->getCircle().getCoordinateX() + 
							ptr_complex_objects_mass[count_size_mass_complex_objects - 1]->getCircle().getRadius() + 1 + 1) <= 1415 &&
							(ptr_complex_objects_mass[count_size_mass_complex_objects - 1]->getLineSegmentLeft().getCoordinateY() + 
								ptr_complex_objects_mass[count_size_mass_complex_objects - 1]->getLineSegmentLeft().getLength() * sin(135 * acos(-1.0f) / 180) + 2) <= 715))
					{
						ptr_complex_objects_mass[count_size_mass_complex_objects - 1]->getRectangle().changeLength(2);
						ptr_complex_objects_mass[count_size_mass_complex_objects - 1]->getRectangle().changeWidth(2);
						ptr_complex_objects_mass[count_size_mass_complex_objects - 1]->getCircle().changeRadius(1);
						ptr_complex_objects_mass[count_size_mass_complex_objects - 1]->getCircle().MoveTo(2, 1);
						ptr_complex_objects_mass[count_size_mass_complex_objects - 1]->getLineSegmentLeft().changeLength(2);
						ptr_complex_objects_mass[count_size_mass_complex_objects - 1]->getLineSegmentRight().changeLength(2);
						ptr_complex_objects_mass[count_size_mass_complex_objects - 1]->getLineSegmentLeft().changeCoordinateX_Y(1, 2);
						ptr_complex_objects_mass[count_size_mass_complex_objects - 1]->getLineSegmentRight().changeCoordinateX_Y(1, 2);
					}
					if (event_click.key.code == sf::Keyboard::Q && (ptr_complex_objects_mass[count_size_mass_complex_objects - 1]->getCircle().getRadius() - 1 >= 15) &&
						(ptr_complex_objects_mass[count_size_mass_complex_objects - 1]->getLineSegmentLeft().getLength() - 1 >= 20))
					{
						ptr_complex_objects_mass[count_size_mass_complex_objects - 1]->getRectangle().changeLength(-2);
						ptr_complex_objects_mass[count_size_mass_complex_objects - 1]->getRectangle().changeWidth(-2);
						ptr_complex_objects_mass[count_size_mass_complex_objects - 1]->getCircle().changeRadius(-1);
						ptr_complex_objects_mass[count_size_mass_complex_objects - 1]->getCircle().MoveTo(-2, -1);
						ptr_complex_objects_mass[count_size_mass_complex_objects - 1]->getLineSegmentLeft().changeLength(-2);
						ptr_complex_objects_mass[count_size_mass_complex_objects - 1]->getLineSegmentRight().changeLength(-2);
						ptr_complex_objects_mass[count_size_mass_complex_objects - 1]->getLineSegmentLeft().changeCoordinateX_Y(-1, -2);
						ptr_complex_objects_mass[count_size_mass_complex_objects - 1]->getLineSegmentRight().changeCoordinateX_Y(-1, -2);
					}
				}
				else
				{
					if (event_click.key.code == sf::Keyboard::W)
					{
						for (unsigned i{}; i < count_size_mass_complex_objects;i++)
						{
							if (ptr_complex_objects_mass[i]->getRectangle().getCoordinateY() - 10 >= 115)
							{
								ptr_complex_objects_mass[i]->MoveTo(0, -10);
							}
						}
					}
					if (event_click.key.code == sf::Keyboard::A)
					{
						for (unsigned i{}; i < count_size_mass_complex_objects;i++)
						{
							if (ptr_complex_objects_mass[i]->getRectangle().getCoordinateX() < (ptr_complex_objects_mass[i]->getLineSegmentLeft().getCoordinateX() +
									ptr_complex_objects_mass[i]->getLineSegmentLeft().getLength() * cos(135 * acos(-1.0f) / 180)))
							{
								if ((ptr_complex_objects_mass[i]->getRectangle().getCoordinateX() - 10) >= 465)
									ptr_complex_objects_mass[i]->MoveTo(-10, 0);
							}
							else if ((ptr_complex_objects_mass[i]->getLineSegmentLeft().getCoordinateX() + ptr_complex_objects_mass[i]->getLineSegmentLeft().getLength() * 
								cos(135 * acos(-1.0f) / 180) - 10) >= 465)
								ptr_complex_objects_mass[i]->MoveTo(-10, 0);
						}
					}
					if (event_click.key.code == sf::Keyboard::S)
					{
						for (unsigned i{}; i < count_size_mass_complex_objects;i++)
						{
							if (ptr_complex_objects_mass[i]->getLineSegmentLeft().getCoordinateY() + ptr_complex_objects_mass[i]->getLineSegmentLeft().getLength() *
								sin(135 * acos(-1.0f) / 180) + 10 <= 715)
							{
								ptr_complex_objects_mass[i]->MoveTo(0, 10);
							}
						}
					}
					if (event_click.key.code == sf::Keyboard::D)
					{
						for (unsigned i{}; i < count_size_mass_complex_objects;i++)
						{
							if ((ptr_complex_objects_mass[i]->getCircle().getCoordinateX() + ptr_complex_objects_mass[i]->getCircle().getRadius()) >
								(ptr_complex_objects_mass[i]->getLineSegmentRight().getCoordinateX() + ptr_complex_objects_mass[i]->getLineSegmentRight().getLength() *
									cos(45 * acos(-1.0f) / 180)))
							{
								if ((ptr_complex_objects_mass[i]->getCircle().getCoordinateX() + 10 + ptr_complex_objects_mass[i]->getCircle().getRadius()) <= 1415)
									ptr_complex_objects_mass[i]->MoveTo(10, 0);
							}
							else if ((ptr_complex_objects_mass[i]->getLineSegmentRight().getCoordinateX() + ptr_complex_objects_mass[i]->getLineSegmentRight().getLength() *
								cos(45 * acos(-1.0f) / 180) + 10) <= 1415)
								ptr_complex_objects_mass[i]->MoveTo(10, 0);
						}
					}
					if (event_click.key.code == sf::Keyboard::E)
					{
						for (unsigned i{}; i < count_size_mass_complex_objects;i++)
						{
							if (((ptr_complex_objects_mass[i]->getCircle().getCoordinateX() + ptr_complex_objects_mass[i]->getCircle().getRadius() + 1 + 1) <= 1415 &&
								(ptr_complex_objects_mass[i]->getLineSegmentLeft().getCoordinateY() + ptr_complex_objects_mass[i]->getLineSegmentLeft().getLength() * 
									sin(135 * acos(-1.0f) / 180) + 2) <= 715))
							{
								ptr_complex_objects_mass[i]->getRectangle().changeLength(2);
								ptr_complex_objects_mass[i]->getRectangle().changeWidth(2);
								ptr_complex_objects_mass[i]->getCircle().changeRadius(1);
								ptr_complex_objects_mass[i]->getCircle().MoveTo(2, 1);
								ptr_complex_objects_mass[i]->getLineSegmentLeft().changeLength(2);
								ptr_complex_objects_mass[i]->getLineSegmentRight().changeLength(2);
								ptr_complex_objects_mass[i]->getLineSegmentLeft().changeCoordinateX_Y(1, 2);
								ptr_complex_objects_mass[i]->getLineSegmentRight().changeCoordinateX_Y(1, 2);
							}
						}
					}
					if (event_click.key.code == sf::Keyboard::Q)
					{
						for (unsigned i{}; i < count_size_mass_complex_objects;i++)
						{
							if ((ptr_complex_objects_mass[i]->getCircle().getRadius() - 1 >= 15) && (ptr_complex_objects_mass[i]->getLineSegmentLeft().getLength() - 1 >= 20))
							{
								ptr_complex_objects_mass[i]->getRectangle().changeLength(-2);
								ptr_complex_objects_mass[i]->getRectangle().changeWidth(-2);
								ptr_complex_objects_mass[i]->getCircle().changeRadius(-1);
								ptr_complex_objects_mass[i]->getCircle().MoveTo(-2, -1);
								ptr_complex_objects_mass[i]->getLineSegmentLeft().changeLength(-2);
								ptr_complex_objects_mass[i]->getLineSegmentRight().changeLength(-2);
								ptr_complex_objects_mass[i]->getLineSegmentLeft().changeCoordinateX_Y(-1, -2);
								ptr_complex_objects_mass[i]->getLineSegmentRight().changeCoordinateX_Y(-1, -2);
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

		for (unsigned i{}; i < count_size_mass_rings;i++)
		{
			ptr_rings_mass[i]->Show(window);
		}

		for (unsigned i{}; i < count_size_mass_linesegments;i++)
		{
			ptr_linesegments_mass[i]->Show(window);
		}

		for (unsigned i{}; i < count_size_mass_complex_objects;i++)
		{
			ptr_complex_objects_mass[i]->Show(window);
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