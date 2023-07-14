#include <SFML\Graphics.hpp>
#include <iostream>
#include <sstream>
#include "myfuncs.h"
#include "constants.h"
#include "myclass.h"

int main()
{
	sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Elevator");

	bool inGame{ MenuGame(window) };

	//���������� ��� �������� ������� ��� ������ �� ��������� � ������� SFML event
	bool close_program{ false };

	if (inGame)
	{
		/////////////////������������� ��������////////////////////
		//�������� ������� �����
		User_Sprite lift("Lift.png", 10, 10);

		//�������� ������
		User_Sprite Button("Button.png", 115, 406);

		//�������� ����� �����
		User_Sprite LeftDoor("Left_Door.png", 204, 213);

		//�������� ������ �����
		User_Sprite RightDoor("Right_Door.png", 351, 213);

		//BG �����
		User_Sprite BGlift("Lift_BG.png", 204, 213);

		//�������� ������ ������ �����
		sf::Font button_doors_font;
		button_doors_font.loadFromFile("fonts/Comic_Sans_MS.TTF");
		sf::Text button_doors_text("", button_doors_font, 10);
		button_doors_text.setFillColor(sf::Color::Black);
		button_doors_text.setString("Press button\nto call lift:");
		button_doors_text.setPosition(105, 360);

		//�������� ������ �����
		User_Sprite Button_plus("Plus.png", 915, 100);
		User_Sprite Button_minus("Minus.png", 765, 100);

		//�������� ������ ������ �����
		sf::Font floor_font;
		floor_font.loadFromFile("fonts/CyrilicOLD.TTF");
		sf::Text floor_text("", floor_font, 20);
		floor_text.setFillColor(sf::Color::Black);
		floor_text.setString("��� ����: 1");
		floor_text.setPosition(800, 100);

		//����� � ���������� (��� �������� ������)
		float speed{ 0 };
		float sum{ 0 };

		//�������� ������ ������
		User_Sprite ready_button("Ready_Button.png", 770, 130);

		//���������� ��� ������ ������ ����� � ��������
		int floor_num{ 1 };
		std::ostringstream floor_str;
		int isFloor{ 1 };

		//marher_floor �������� ������� �����
		User_Sprite marker("marker_floor.png", 277, 150);

		//���������� ��� ��������� ����� (��������)
		int lift_pos_sending{ 1 };

		//�������� ������ �����
		sf::Font entrance_font;
		entrance_font.loadFromFile("fonts/CyrilicOLD.TTF");
		sf::Text entrance_text("", entrance_font, 30);
		entrance_text.setFillColor(sf::Color::Magenta);
		entrance_text.setString("�����");
		entrance_text.setPosition(320, 280);

		//���������� ��� ������ ������� �����
		int dx{ marker.x };

		while (window.isOpen())
		{
			CloseWindow(window, close_program);

			///////////////////////////////////////////������ ������ �����////////////////////////////////////////
				while (isFloor)
				{
					Button_minus.sprite.setColor(sf::Color::White);
					Button_plus.sprite.setColor(sf::Color::White);
					ready_button.sprite.setColor(sf::Color::White);
					int button_floor{ 0 };

					window.clear();

					if (sf::IntRect(765, 100, 25, 25).contains(sf::Mouse::getPosition(window)))
					{
						Button_minus.sprite.setColor(sf::Color(2, 100, 49));
						button_floor = 1;
					}
					if (sf::IntRect(915, 100, 25, 25).contains(sf::Mouse::getPosition(window)))
					{
						Button_plus.sprite.setColor(sf::Color(2, 100, 49));
						button_floor = 2;
					}
					if (sf::IntRect(770, 135, 150, 40).contains(sf::Mouse::getPosition(window)))
					{
						ready_button.sprite.setColor(sf::Color(70, 111, 81));
						button_floor = 3;
					}

					sf::Event event_floor;
					while (window.pollEvent(event_floor))
					{
						if (event_floor.type == sf::Event::Closed) { window.close(); exit(0); }
						if (event_floor.type == event_floor.MouseButtonReleased && event_floor.mouseButton.button == sf::Mouse::Left)
						{
							if (button_floor == 1)
							{
								if (floor_num > 1) { floor_num -= 1; dx -= 15; marker.sprite.setPosition(dx, 150); }
							}

							if (button_floor == 2)
							{
								if (floor_num < 10) { floor_num += 1; dx += 15; marker.sprite.setPosition(dx, 150); }
							}
							if (button_floor == 3)
							{
								isFloor = 0;
							}
							floor_str.str("");
							floor_str << floor_num;
							floor_text.setString("��� ����: " + floor_str.str());
							std::cout << "Your floor is " << floor_str.str() << std::endl;
						}
					}
					window.draw(BGlift.sprite);
					window.draw(LeftDoor.sprite);
					window.draw(RightDoor.sprite);
					window.draw(lift.sprite);
					window.draw(Button.sprite);
					window.draw(Button_minus.sprite);
					window.draw(Button_plus.sprite);
					window.draw(ready_button.sprite);
					window.draw(floor_text);
					window.draw(marker.sprite);
					window.display();

				}

			//��� ��������� �������� �����
			lift_pos_sending = floor_num;

			//////////////////////////////////////////�������� �����//////////////////////////////////
			if (isFloor == 0)
			{

				sf::Clock clock;
				Button.sprite.setColor(sf::Color::White);
				if (sf::IntRect(115, 406, 35, 36).contains(sf::Mouse::getPosition(window)))
				{
					Button.sprite.setColor(sf::Color::Green);
					if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
					{
						Button.sprite.setColor(sf::Color::Cyan);
						while (sum <= 120)
						{
							CloseWindow(window, close_program);

							//SFML - �����
							float time = clock.getElapsedTime().asMilliseconds();
							clock.restart();
							time = time / 800;
							speed += time;//�������� ������ (� ����������)
							sum += 0.04 * speed;//��������

							LeftDoor.sprite.move(-0.04 * speed, 0);//����� �����
							RightDoor.sprite.move(0.04 * speed, 0);//������ �����
							//���������� ����� �����
							window.clear();
							window.draw(BGlift.sprite);
							window.draw(LeftDoor.sprite);
							window.draw(RightDoor.sprite);
							window.draw(lift.sprite);
							window.draw(Button.sprite);
							window.draw(button_doors_text);
							window.draw(marker.sprite);
							window.display();
						}
					}
				}

				////�������� ���� �������� (���� � ������)
				window.clear();
				window.draw(BGlift.sprite);
				window.draw(LeftDoor.sprite);
				window.draw(RightDoor.sprite);
				window.draw(lift.sprite);
				window.draw(Button.sprite);
				window.draw(button_doors_text);
				window.draw(Button_minus.sprite);
				window.draw(Button_plus.sprite);
				window.draw(floor_text);
				window.draw(marker.sprite);
				if (sum > 120)
				{
					window.draw(entrance_text);
					entrance_text.setFillColor(sf::Color::Magenta);
					if (sf::IntRect(300, 280, 100, 50).contains(sf::Mouse::getPosition(window)))
					{
						entrance_text.setFillColor(sf::Color::Green);
						if ((sf::Mouse::isButtonPressed(sf::Mouse::Left)) && (close_program == false))
							SecondFrameProgram(window, lift_pos_sending, close_program);
					}

				}
				window.display();
			}
		}
	}

	return 0;
}
