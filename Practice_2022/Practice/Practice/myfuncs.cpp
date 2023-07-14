#include <iostream>
#include <sstream>
#include "cabin.h"
#include "myfuncs.h"
#include "myclass.h"

void FirstFrameProgram(sf::RenderWindow& window, int& lift_pos_sending, int& lift_pos_arrival, bool& close_programOut)
{
	/////////////////Инициализация спрайтов////////////////////
	//Загрузка спрайта лифта
	User_Sprite lift("Lift.png", 10, 10);

	//Загрузка кнопки
	User_Sprite Button("Button.png", 115, 406);

	//Загрузка левой двери
	User_Sprite LeftDoor("Left_Door.png", 204, 213);

	//Загрузка правой двери
	User_Sprite RightDoor("Right_Door.png", 351, 213);

	//BG лифта
	User_Sprite BGlift("Lift_BG.png", 204, 213);

	//Загрузка текста вызова лифта
	sf::Font button_doors_font;
	button_doors_font.loadFromFile("fonts/Comic_Sans_MS.TTF");
	sf::Text button_doors_text("", button_doors_font, 10);
	button_doors_text.setFillColor(sf::Color::Black);
	button_doors_text.setString("Press button\nto call lift:");
	button_doors_text.setPosition(105, 360);

	//Загрузка выбора этажа
	User_Sprite Button_plus("Plus.png", 915, 100);
	User_Sprite Button_minus("Minus.png", 765, 100);

	//Загрузка текста выбора этажа
	sf::Font floor_font;
	floor_font.loadFromFile("fonts/CyrilicOLD.TTF");
	sf::Text floor_text("", floor_font, 20);
	floor_text.setFillColor(sf::Color::Black);
	floor_text.setString("Ваш этаж: 1");
	floor_text.setPosition(800, 100);

	//Время и переменные (для анимации дверей)
	float speed_doors{ 0 };
	float sum_doors{ 0 };

	//Загрузка кнопки готово
	User_Sprite ready_button("Ready_Button.png", 770, 130);

	//Переменные для кнопок выбора этажа у человека
	int floor_num{ 1 };
	std::ostringstream floor_str;
	int isFloor{ 1 };

	//marher_floor загрузка маркера этажа
	User_Sprite marker("marker_floor.png", 277 + 15 * (lift_pos_arrival - 1), 150);

	//Загрузка текста входа
	sf::Font entrance_font;
	entrance_font.loadFromFile("fonts/CyrilicOLD.TTF");
	sf::Text entrance_text("", entrance_font, 30);
	entrance_text.setFillColor(sf::Color::Magenta);
	entrance_text.setString("Войти");
	entrance_text.setPosition(320, 280);

	//Переменная для передвижения маркера
	int dx{ marker.x };

	while (window.isOpen())
	{
		CloseWindow(window, close_programOut);

		///////////////////////////////////////////Кнопки выбора этажа////////////////////////////////////////
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
							if (floor_num > 1) floor_num -= 1;
						}

						if (button_floor == 2)
						{
							if (floor_num < 10) floor_num += 1;
						}
						if (button_floor == 3)
						{
							isFloor = 0;
						}
						floor_str.str("");
						floor_str << floor_num;
						floor_text.setString("Ваш этаж: " + floor_str.str());
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

		//Для положения отправки лифта
		lift_pos_sending = floor_num;

		//////////////////////////////////////////Анимация двери//////////////////////////////////
			if (isFloor == 0)
			{
				Button.sprite.setColor(sf::Color::White);

				if (sf::IntRect(115, 406, 35, 36).contains(sf::Mouse::getPosition(window)))
				{
					Button.sprite.setColor(sf::Color::Green);
					if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
					{
						Button.sprite.setColor(sf::Color::Cyan);

						while (lift_pos_arrival != lift_pos_sending)
						{
							CloseWindow(window, close_programOut);

							sf::Clock clock_marker;
							//Время и переменный (для анимации маркера)
							int wait_marker{ 0 };
							int sum_marker{ 0 };

							while (sum_marker <= 120)
							{
								float time = clock_marker.getElapsedTime().asMilliseconds();
								clock_marker.restart();
								wait_marker += time;//Ожидание маркера для движения на следующий этаж
									sum_marker += 0.005 * wait_marker;//Накапливание ожидания маркера
								std::cout << "Your floor is " << lift_pos_sending << ". Floor of elevator is " << lift_pos_arrival << std::endl;
							}

							if (sum_marker > 120)
							{
								if (lift_pos_sending < lift_pos_arrival)
								{
									lift_pos_arrival -= 1;
									dx -= 15;
									marker.sprite.setPosition(dx, 150);
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
								if (lift_pos_sending > lift_pos_arrival)
								{
									lift_pos_arrival += 1;
									dx += 15;
									marker.sprite.setPosition(dx, 150);
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

								if (lift_pos_sending == lift_pos_arrival) std::cout << "Your floor is " << lift_pos_sending << ". Floor of elevator is " << lift_pos_arrival << std::endl;

							}
						}

						sf::Clock clock_doors; //Чтобы не было мчащих дверей

						while (sum_doors <= 120)
						{
							CloseWindow(window, close_programOut);

							//SFML - время
							float time = clock_doors.getElapsedTime().asMilliseconds();
							clock_doors.restart();
							time = time / 800;
							speed_doors += time;//Скорость дверей (с ускорением)
							sum_doors += 0.04 * speed_doors;//Смещение

							LeftDoor.sprite.move(-0.04 * speed_doors, 0);//Левая дверь
							RightDoor.sprite.move(0.04 * speed_doors, 0);//Правая дверь
							//Покадровый вывод цикла
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

				////Выгрузка всех спрайтов (лифт и кнопка)
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
				if (sum_doors > 120)
				{
					window.draw(entrance_text);
					entrance_text.setFillColor(sf::Color::Magenta);
					if (sf::IntRect(300, 280, 100, 50).contains(sf::Mouse::getPosition(window)))
					{
						entrance_text.setFillColor(sf::Color::Green);
						if ((sf::Mouse::isButtonPressed(sf::Mouse::Left)) && (close_programOut == false))
							SecondFrameProgram(window, lift_pos_sending, close_programOut);
					}

				}
				window.display();
			}
	}
}

void SecondFrameProgram(sf::RenderWindow& window, int& lift_pos_sending, bool& close_programOut)
{
	//Положение лифта на этаже (прибытие)
	int lift_pos_arrival{ 1 };

	//Нажать можно только одну кнопку и контроль
	int isTap{ 1 };

	//Загрузка кабины лифта
	User_Sprite CabinPanel("Cabin_panel.png", 10, 10);

	//Загрузка индикаторов
	User_Sprite Indicators("Indicator_Panel.png", 0, 0);

	//Загрузка спрайта выхода
	User_Sprite exit("Exit.png", 200, 100);

	///////////////////////////////////Загрузка кнопок лифта
	sf::CircleShape circle1;
	circle1.setFillColor(sf::Color(221, 221, 221));
	circle1.setRadius(13);
	circle1.setOutlineColor(sf::Color::Black);
	circle1.setOutlineThickness(5);
	circle1.setPosition(533, 273);

	sf::CircleShape circle2;
	circle2.setFillColor(sf::Color(221, 221, 221));
	circle2.setRadius(13);
	circle2.setOutlineColor(sf::Color::Black);
	circle2.setOutlineThickness(5);
	circle2.setPosition(583, 273);

	sf::CircleShape circle3;
	circle3.setFillColor(sf::Color(221, 221, 221));
	circle3.setRadius(13);
	circle3.setOutlineColor(sf::Color::Black);
	circle3.setOutlineThickness(5);
	circle3.setPosition(633, 273);

	sf::CircleShape circle4;
	circle4.setFillColor(sf::Color(221, 221, 221));
	circle4.setRadius(13);
	circle4.setOutlineColor(sf::Color::Black);
	circle4.setOutlineThickness(5);
	circle4.setPosition(683, 273);

	sf::CircleShape circle5;
	circle5.setFillColor(sf::Color(221, 221, 221));
	circle5.setRadius(13);
	circle5.setOutlineColor(sf::Color::Black);
	circle5.setOutlineThickness(5);
	circle5.setPosition(533, 333);

	sf::CircleShape circle6;
	circle6.setFillColor(sf::Color(221, 221, 221));
	circle6.setRadius(13);
	circle6.setOutlineColor(sf::Color::Black);
	circle6.setOutlineThickness(5);
	circle6.setPosition(583, 333);

	sf::CircleShape circle7;
	circle7.setFillColor(sf::Color(221, 221, 221));
	circle7.setRadius(13);
	circle7.setOutlineColor(sf::Color::Black);
	circle7.setOutlineThickness(5);
	circle7.setPosition(633, 333);

	sf::CircleShape circle8;
	circle8.setFillColor(sf::Color(221, 221, 221));
	circle8.setRadius(13);
	circle8.setOutlineColor(sf::Color::Black);
	circle8.setOutlineThickness(5);
	circle8.setPosition(683, 333);

	sf::CircleShape circle9;
	circle9.setFillColor(sf::Color(221, 221, 221));
	circle9.setRadius(13);
	circle9.setOutlineColor(sf::Color::Black);
	circle9.setOutlineThickness(5);
	circle9.setPosition(583, 403);

	sf::CircleShape circle10;
	circle10.setFillColor(sf::Color(221, 221, 221));
	circle10.setRadius(13);
	circle10.setOutlineColor(sf::Color::Black);
	circle10.setOutlineThickness(5);
	circle10.setPosition(633, 403);

	//////////////////////Загрузка текста для кнопок, чтобы не окрашивались
	sf::Font circles_font;
	circles_font.loadFromFile("fonts/Comic_Sans_MS.TTF");

	sf::Text Digit1("", circles_font, 20);
	Digit1.setFillColor(sf::Color::Black);
	Digit1.setStyle(sf::Text::Bold);
	Digit1.setString("1");
	Digit1.setPosition(540, 273);

	sf::Text Digit2("", circles_font, 20);
	Digit2.setFillColor(sf::Color::Black);
	Digit2.setStyle(sf::Text::Bold);
	Digit2.setString("2");
	Digit2.setPosition(588, 273);

	sf::Text Digit3("", circles_font, 20);
	Digit3.setFillColor(sf::Color::Black);
	Digit3.setStyle(sf::Text::Bold);
	Digit3.setString("3");
	Digit3.setPosition(640, 273);

	sf::Text Digit4("", circles_font, 20);
	Digit4.setFillColor(sf::Color::Black);
	Digit4.setStyle(sf::Text::Bold);
	Digit4.setString("4");
	Digit4.setPosition(688, 273);

	sf::Text Digit5("", circles_font, 20);
	Digit5.setFillColor(sf::Color::Black);
	Digit5.setStyle(sf::Text::Bold);
	Digit5.setString("5");
	Digit5.setPosition(540, 333);

	sf::Text Digit6("", circles_font, 20);
	Digit6.setFillColor(sf::Color::Black);
	Digit6.setStyle(sf::Text::Bold);
	Digit6.setString("6");
	Digit6.setPosition(588, 333);

	sf::Text Digit7("", circles_font, 20);
	Digit7.setFillColor(sf::Color::Black);
	Digit7.setStyle(sf::Text::Bold);
	Digit7.setString("7");
	Digit7.setPosition(640, 333);

	sf::Text Digit8("", circles_font, 20);
	Digit8.setFillColor(sf::Color::Black);
	Digit8.setStyle(sf::Text::Bold);
	Digit8.setString("8");
	Digit8.setPosition(688, 333);

	sf::Text Digit9("", circles_font, 20);
	Digit9.setFillColor(sf::Color::Black);
	Digit9.setStyle(sf::Text::Bold);
	Digit9.setString("9");
	Digit9.setPosition(590, 403);

	sf::Text Digit10("", circles_font, 20);
	Digit10.setFillColor(sf::Color::Black);
	Digit10.setStyle(sf::Text::Bold);
	Digit10.setString("10");
	Digit10.setPosition(635, 403);

	while (window.isOpen())
	{

		CloseWindow(window, close_programOut);
		if (isTap == 1)
		{
			window.clear();
			window.draw(CabinPanel.sprite);

			for (unsigned i = 0; i < HEIGHT_PANEL; i++)
				for (unsigned j = 0; j < WIDTH_PANEL_ARROW; j++)
				{
					Indicators.sprite.setTextureRect(sf::IntRect(0, 0, 16, 16));
					Indicators.sprite.setPosition(j * 16 + 515, i * 16 + 70);

					window.draw(Indicators.sprite);
				}

			for (unsigned i = 0; i < HEIGHT_PANEL; i++)
				for (unsigned j = 0; j < WIDTH_PANEL_DIGIT; j++)
				{
					Indicators.sprite.setTextureRect(sf::IntRect(0, 0, 16, 16));
					Indicators.sprite.setPosition(j * 16 + 610, i * 16 + 70);

					window.draw(Indicators.sprite);
				}

			//Возврат цвета кнопок
			circle1.setFillColor(sf::Color::White);
			circle2.setFillColor(sf::Color::White);
			circle3.setFillColor(sf::Color::White);
			circle4.setFillColor(sf::Color::White);
			circle5.setFillColor(sf::Color::White);
			circle6.setFillColor(sf::Color::White);
			circle7.setFillColor(sf::Color::White);
			circle8.setFillColor(sf::Color::White);
			circle9.setFillColor(sf::Color::White);
			circle10.setFillColor(sf::Color::White);

			if (sf::IntRect(533, 273, 34, 34).contains(sf::Mouse::getPosition(window)))
			{
				circle1.setFillColor(sf::Color::Cyan);
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
				{
					circle1.setOutlineColor(sf::Color::Green);
					lift_pos_arrival = 1;
					isTap = 2;
					circle1.setFillColor(sf::Color::White);
				}
			}

			if (sf::IntRect(583, 273, 34, 34).contains(sf::Mouse::getPosition(window)))
			{
				circle2.setFillColor(sf::Color::Cyan);
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
				{
					circle2.setOutlineColor(sf::Color::Green);
					lift_pos_arrival = 2;
					isTap = 2;
					circle2.setFillColor(sf::Color::White);
				}

			}

			if (sf::IntRect(633, 273, 34, 34).contains(sf::Mouse::getPosition(window)))
			{
				circle3.setFillColor(sf::Color::Cyan);
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
				{
					circle3.setOutlineColor(sf::Color::Green);
					lift_pos_arrival = 3;
					isTap = 2;
					circle3.setFillColor(sf::Color::White);
				}
			}

			if (sf::IntRect(683, 273, 34, 34).contains(sf::Mouse::getPosition(window)))
			{
				circle4.setFillColor(sf::Color::Cyan);
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
				{
					circle4.setOutlineColor(sf::Color::Green);
					lift_pos_arrival = 4;
					isTap = 2;
					circle4.setFillColor(sf::Color::White);
				}
			}

			if (sf::IntRect(533, 333, 34, 34).contains(sf::Mouse::getPosition(window)))
			{
				circle5.setFillColor(sf::Color::Cyan);
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
				{
					circle5.setOutlineColor(sf::Color::Green);
					lift_pos_arrival = 5;
					isTap = 2;
					circle5.setFillColor(sf::Color::White);
				}
			}

			if (sf::IntRect(583, 333, 34, 34).contains(sf::Mouse::getPosition(window)))
			{
				circle6.setFillColor(sf::Color::Cyan);
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
				{
					circle6.setOutlineColor(sf::Color::Green);
					lift_pos_arrival = 6;
					isTap = 2;
					circle6.setFillColor(sf::Color::White);
				}
			}

			if (sf::IntRect(633, 333, 34, 34).contains(sf::Mouse::getPosition(window)))
			{
				circle7.setFillColor(sf::Color::Cyan);
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
				{
					circle7.setOutlineColor(sf::Color::Green);
					lift_pos_arrival = 7;
					isTap = 2;
					circle7.setFillColor(sf::Color::White);
				}
			}

			if (sf::IntRect(683, 333, 34, 34).contains(sf::Mouse::getPosition(window)))
			{
				circle8.setFillColor(sf::Color::Cyan);
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
				{
					circle8.setOutlineColor(sf::Color::Green);
					lift_pos_arrival = 8;
					isTap = 2;
					circle8.setFillColor(sf::Color::White);
				}
			}

			if (sf::IntRect(583, 403, 34, 34).contains(sf::Mouse::getPosition(window)))
			{
				circle9.setFillColor(sf::Color::Cyan);
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
				{
					circle9.setOutlineColor(sf::Color::Green);
					lift_pos_arrival = 9;
					isTap = 2;
					circle9.setFillColor(sf::Color::White);
				}
			}

			if (sf::IntRect(633, 403, 34, 34).contains(sf::Mouse::getPosition(window)))
			{
				circle10.setFillColor(sf::Color::Cyan);
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
				{
					circle10.setOutlineColor(sf::Color::Green);
					lift_pos_arrival = 10;
					isTap = 2;
					circle10.setFillColor(sf::Color::White);
				}
			}

			window.draw(circle1); window.draw(circle2); window.draw(circle3); window.draw(circle4); window.draw(circle5);
			window.draw(circle6); window.draw(circle7); window.draw(circle8); window.draw(circle9); window.draw(circle10);

			window.draw(Digit1); window.draw(Digit2); window.draw(Digit3); window.draw(Digit4); window.draw(Digit5);
			window.draw(Digit6); window.draw(Digit7); window.draw(Digit8); window.draw(Digit9); window.draw(Digit10);

			window.display();
		}

		if (isTap == 2)
		{
			int sending_plus{ 0 }, arrival_plus{ 0 };
			if (lift_pos_sending < lift_pos_arrival) arrival_plus += 1;
			else if (lift_pos_sending > lift_pos_arrival) sending_plus += 1;

			while ((lift_pos_sending + sending_plus) != (lift_pos_arrival + arrival_plus))
			{
				CloseWindow(window, close_programOut);

				//SFML время для задержки смены тайлсета
				sf::Clock clock;
				int wait{ 0 }, sum{ 0 };

				window.clear();
				window.draw(CabinPanel.sprite);

				window.draw(circle1); window.draw(circle2); window.draw(circle3); window.draw(circle4); window.draw(circle5);
				window.draw(circle6); window.draw(circle7); window.draw(circle8); window.draw(circle9); window.draw(circle10);

				window.draw(Digit1); window.draw(Digit2); window.draw(Digit3); window.draw(Digit4); window.draw(Digit5);
				window.draw(Digit6); window.draw(Digit7); window.draw(Digit8); window.draw(Digit9); window.draw(Digit10);

				if (lift_pos_sending < lift_pos_arrival)
				{
					for (unsigned i = 0; i < HEIGHT_PANEL; i++)
						for (unsigned j = 0; j < WIDTH_PANEL_ARROW; j++)
						{
							if (TilePanelArrowUp[i][j] == '0') Indicators.sprite.setTextureRect(sf::IntRect(0, 0, 16, 16));
							if (TilePanelArrowUp[i][j] == '1') Indicators.sprite.setTextureRect(sf::IntRect(16, 0, 16, 16));

							Indicators.sprite.setPosition(j * 16 + 515, i * 16 + 70);

							window.draw(Indicators.sprite);
						}
				}
				else if (lift_pos_sending > lift_pos_arrival)
				{
					for (unsigned i = 0; i < HEIGHT_PANEL; i++)
						for (unsigned j = 0; j < WIDTH_PANEL_ARROW; j++)
						{
							if (TilePanelArrowDown[i][j] == '0') Indicators.sprite.setTextureRect(sf::IntRect(0, 0, 16, 16));
							if (TilePanelArrowDown[i][j] == '1') Indicators.sprite.setTextureRect(sf::IntRect(16, 0, 16, 16));

							Indicators.sprite.setPosition(j * 16 + 515, i * 16 + 70);

							window.draw(Indicators.sprite);
						}
				}

				//Задержка
				while ((sum <= 120) && (close_programOut == false))
				{
					float time = clock.getElapsedTime().asMilliseconds();
					clock.restart();
					wait += time;
					sum += 0.005 * wait;
					std::cout << "TIME_WAIT_TILESET = " << sum << std::endl;
				}

				//После задержки вывод тайлсетов
				if (sum > 120)
				{
					if (lift_pos_sending == 1)
						for (unsigned i = 0; i < HEIGHT_PANEL; i++)
							for (unsigned j = 0; j < WIDTH_PANEL_DIGIT; j++)
							{
								if (TilePanelDigit1[i][j] == '0') Indicators.sprite.setTextureRect(sf::IntRect(0, 0, 16, 16));
								if (TilePanelDigit1[i][j] == '1') Indicators.sprite.setTextureRect(sf::IntRect(16, 0, 16, 16));

								Indicators.sprite.setPosition(j * 16 + 610, i * 16 + 70);

								window.draw(Indicators.sprite);

							}
					if (lift_pos_sending == 2)
						for (unsigned i = 0; i < HEIGHT_PANEL; i++)
							for (unsigned j = 0; j < WIDTH_PANEL_DIGIT; j++)
							{
								if (TilePanelDigit2[i][j] == '0') Indicators.sprite.setTextureRect(sf::IntRect(0, 0, 16, 16));
								if (TilePanelDigit2[i][j] == '1') Indicators.sprite.setTextureRect(sf::IntRect(16, 0, 16, 16));

								Indicators.sprite.setPosition(j * 16 + 610, i * 16 + 70);

								window.draw(Indicators.sprite);
							}
					if (lift_pos_sending == 3)
						for (unsigned i = 0; i < HEIGHT_PANEL; i++)
							for (unsigned j = 0; j < WIDTH_PANEL_DIGIT; j++)
							{
								if (TilePanelDigit3[i][j] == '0') Indicators.sprite.setTextureRect(sf::IntRect(0, 0, 16, 16));
								if (TilePanelDigit3[i][j] == '1') Indicators.sprite.setTextureRect(sf::IntRect(16, 0, 16, 16));

								Indicators.sprite.setPosition(j * 16 + 610, i * 16 + 70);

								window.draw(Indicators.sprite);
							}
					if (lift_pos_sending == 4)
						for (unsigned i = 0; i < HEIGHT_PANEL; i++)
							for (unsigned j = 0; j < WIDTH_PANEL_DIGIT; j++)
							{
								if (TilePanelDigit4[i][j] == '0') Indicators.sprite.setTextureRect(sf::IntRect(0, 0, 16, 16));
								if (TilePanelDigit4[i][j] == '1') Indicators.sprite.setTextureRect(sf::IntRect(16, 0, 16, 16));

								Indicators.sprite.setPosition(j * 16 + 610, i * 16 + 70);

								window.draw(Indicators.sprite);
							}
					if (lift_pos_sending == 5)
						for (unsigned i = 0; i < HEIGHT_PANEL; i++)
							for (unsigned j = 0; j < WIDTH_PANEL_DIGIT; j++)
							{
								if (TilePanelDigit5[i][j] == '0') Indicators.sprite.setTextureRect(sf::IntRect(0, 0, 16, 16));
								if (TilePanelDigit5[i][j] == '1') Indicators.sprite.setTextureRect(sf::IntRect(16, 0, 16, 16));

								Indicators.sprite.setPosition(j * 16 + 610, i * 16 + 70);

								window.draw(Indicators.sprite);
							}
					if (lift_pos_sending == 6)
						for (unsigned i = 0; i < HEIGHT_PANEL; i++)
							for (unsigned j = 0; j < WIDTH_PANEL_DIGIT; j++)
							{
								if (TilePanelDigit6[i][j] == '0') Indicators.sprite.setTextureRect(sf::IntRect(0, 0, 16, 16));
								if (TilePanelDigit6[i][j] == '1') Indicators.sprite.setTextureRect(sf::IntRect(16, 0, 16, 16));

								Indicators.sprite.setPosition(j * 16 + 610, i * 16 + 70);

								window.draw(Indicators.sprite);
							}
					if (lift_pos_sending == 7)
						for (unsigned i = 0; i < HEIGHT_PANEL; i++)
							for (unsigned j = 0; j < WIDTH_PANEL_DIGIT; j++)
							{
								if (TilePanelDigit7[i][j] == '0') Indicators.sprite.setTextureRect(sf::IntRect(0, 0, 16, 16));
								if (TilePanelDigit7[i][j] == '1') Indicators.sprite.setTextureRect(sf::IntRect(16, 0, 16, 16));

								Indicators.sprite.setPosition(j * 16 + 610, i * 16 + 70);

								window.draw(Indicators.sprite);
							}
					if (lift_pos_sending == 8)
						for (unsigned i = 0; i < HEIGHT_PANEL; i++)
							for (unsigned j = 0; j < WIDTH_PANEL_DIGIT; j++)
							{
								if (TilePanelDigit8[i][j] == '0') Indicators.sprite.setTextureRect(sf::IntRect(0, 0, 16, 16));
								if (TilePanelDigit8[i][j] == '1') Indicators.sprite.setTextureRect(sf::IntRect(16, 0, 16, 16));

								Indicators.sprite.setPosition(j * 16 + 610, i * 16 + 70);

								window.draw(Indicators.sprite);
							}
					if (lift_pos_sending == 9)
						for (unsigned i = 0; i < HEIGHT_PANEL; i++)
							for (unsigned j = 0; j < WIDTH_PANEL_DIGIT; j++)
							{
								if (TilePanelDigit9[i][j] == '0') Indicators.sprite.setTextureRect(sf::IntRect(0, 0, 16, 16));
								if (TilePanelDigit9[i][j] == '1') Indicators.sprite.setTextureRect(sf::IntRect(16, 0, 16, 16));

								Indicators.sprite.setPosition(j * 16 + 610, i * 16 + 70);

								window.draw(Indicators.sprite);
							}
					if (lift_pos_sending == 10)
						for (unsigned i = 0; i < HEIGHT_PANEL; i++)
							for (unsigned j = 0; j < WIDTH_PANEL_DIGIT; j++)
							{
								if (TilePanelDigit10[i][j] == '0') Indicators.sprite.setTextureRect(sf::IntRect(0, 0, 16, 16));
								if (TilePanelDigit10[i][j] == '1') Indicators.sprite.setTextureRect(sf::IntRect(16, 0, 16, 16));

								Indicators.sprite.setPosition(j * 16 + 610, i * 16 + 70);

								window.draw(Indicators.sprite);
							}
				}
				//Рисует пустой тайлсет стрелки, так как Вы приехали
				if (lift_pos_sending == lift_pos_arrival)
					for (unsigned i = 0; i < HEIGHT_PANEL; i++)
						for (unsigned j = 0; j < WIDTH_PANEL_ARROW; j++)
						{
							Indicators.sprite.setTextureRect(sf::IntRect(0, 0, 16, 16));
							Indicators.sprite.setPosition(j * 16 + 515, i * 16 + 70);

							window.draw(Indicators.sprite);
						}

				if (lift_pos_sending < (lift_pos_arrival + arrival_plus)) lift_pos_sending += 1;
				else if ((lift_pos_sending + sending_plus) > lift_pos_arrival) lift_pos_sending -= 1;

				window.display();

			}
			if ((lift_pos_sending - arrival_plus) == lift_pos_arrival)
			{
				lift_pos_sending -= 1;
				isTap = 0;
			}
			else isTap = 0;
		}

		if (isTap == 0)
		{
			window.clear();
			window.draw(CabinPanel.sprite);
			exit.sprite.setColor(sf::Color::White);

			if (lift_pos_arrival == 1)
				for (unsigned i = 0; i < HEIGHT_PANEL; i++)
					for (unsigned j = 0; j < WIDTH_PANEL_DIGIT; j++)
					{
						if (TilePanelDigit1[i][j] == '0') Indicators.sprite.setTextureRect(sf::IntRect(0, 0, 16, 16));
						if (TilePanelDigit1[i][j] == '1') Indicators.sprite.setTextureRect(sf::IntRect(16, 0, 16, 16));

						Indicators.sprite.setPosition(j * 16 + 610, i * 16 + 70);

						window.draw(Indicators.sprite);

					}
			if (lift_pos_arrival == 2)
				for (unsigned i = 0; i < HEIGHT_PANEL; i++)
					for (unsigned j = 0; j < WIDTH_PANEL_DIGIT; j++)
					{
						if (TilePanelDigit2[i][j] == '0') Indicators.sprite.setTextureRect(sf::IntRect(0, 0, 16, 16));
						if (TilePanelDigit2[i][j] == '1') Indicators.sprite.setTextureRect(sf::IntRect(16, 0, 16, 16));

						Indicators.sprite.setPosition(j * 16 + 610, i * 16 + 70);

						window.draw(Indicators.sprite);
					}
			if (lift_pos_arrival == 3)
				for (unsigned i = 0; i < HEIGHT_PANEL; i++)
					for (unsigned j = 0; j < WIDTH_PANEL_DIGIT; j++)
					{
						if (TilePanelDigit3[i][j] == '0') Indicators.sprite.setTextureRect(sf::IntRect(0, 0, 16, 16));
						if (TilePanelDigit3[i][j] == '1') Indicators.sprite.setTextureRect(sf::IntRect(16, 0, 16, 16));

						Indicators.sprite.setPosition(j * 16 + 610, i * 16 + 70);

						window.draw(Indicators.sprite);
					}
			if (lift_pos_arrival == 4)
				for (unsigned i = 0; i < HEIGHT_PANEL; i++)
					for (unsigned j = 0; j < WIDTH_PANEL_DIGIT; j++)
					{
						if (TilePanelDigit4[i][j] == '0') Indicators.sprite.setTextureRect(sf::IntRect(0, 0, 16, 16));
						if (TilePanelDigit4[i][j] == '1') Indicators.sprite.setTextureRect(sf::IntRect(16, 0, 16, 16));

						Indicators.sprite.setPosition(j * 16 + 610, i * 16 + 70);

						window.draw(Indicators.sprite);
					}
			if (lift_pos_arrival == 5)
				for (unsigned i = 0; i < HEIGHT_PANEL; i++)
					for (unsigned j = 0; j < WIDTH_PANEL_DIGIT; j++)
					{
						if (TilePanelDigit5[i][j] == '0') Indicators.sprite.setTextureRect(sf::IntRect(0, 0, 16, 16));
						if (TilePanelDigit5[i][j] == '1') Indicators.sprite.setTextureRect(sf::IntRect(16, 0, 16, 16));

						Indicators.sprite.setPosition(j * 16 + 610, i * 16 + 70);

						window.draw(Indicators.sprite);
					}
			if (lift_pos_arrival == 6)
				for (unsigned i = 0; i < HEIGHT_PANEL; i++)
					for (unsigned j = 0; j < WIDTH_PANEL_DIGIT; j++)
					{
						if (TilePanelDigit6[i][j] == '0') Indicators.sprite.setTextureRect(sf::IntRect(0, 0, 16, 16));
						if (TilePanelDigit6[i][j] == '1') Indicators.sprite.setTextureRect(sf::IntRect(16, 0, 16, 16));

						Indicators.sprite.setPosition(j * 16 + 610, i * 16 + 70);

						window.draw(Indicators.sprite);
					}
			if (lift_pos_arrival == 7)
				for (unsigned i = 0; i < HEIGHT_PANEL; i++)
					for (unsigned j = 0; j < WIDTH_PANEL_DIGIT; j++)
					{
						if (TilePanelDigit7[i][j] == '0') Indicators.sprite.setTextureRect(sf::IntRect(0, 0, 16, 16));
						if (TilePanelDigit7[i][j] == '1') Indicators.sprite.setTextureRect(sf::IntRect(16, 0, 16, 16));

						Indicators.sprite.setPosition(j * 16 + 610, i * 16 + 70);

						window.draw(Indicators.sprite);
					}
			if (lift_pos_arrival == 8)
				for (unsigned i = 0; i < HEIGHT_PANEL; i++)
					for (unsigned j = 0; j < WIDTH_PANEL_DIGIT; j++)
					{
						if (TilePanelDigit8[i][j] == '0') Indicators.sprite.setTextureRect(sf::IntRect(0, 0, 16, 16));
						if (TilePanelDigit8[i][j] == '1') Indicators.sprite.setTextureRect(sf::IntRect(16, 0, 16, 16));

						Indicators.sprite.setPosition(j * 16 + 610, i * 16 + 70);

						window.draw(Indicators.sprite);
					}
			if (lift_pos_arrival == 9)
				for (unsigned i = 0; i < HEIGHT_PANEL; i++)
					for (unsigned j = 0; j < WIDTH_PANEL_DIGIT; j++)
					{
						if (TilePanelDigit9[i][j] == '0') Indicators.sprite.setTextureRect(sf::IntRect(0, 0, 16, 16));
						if (TilePanelDigit9[i][j] == '1') Indicators.sprite.setTextureRect(sf::IntRect(16, 0, 16, 16));

						Indicators.sprite.setPosition(j * 16 + 610, i * 16 + 70);

						window.draw(Indicators.sprite);
					}
			if (lift_pos_arrival == 10)
				for (unsigned i = 0; i < HEIGHT_PANEL; i++)
					for (unsigned j = 0; j < WIDTH_PANEL_DIGIT; j++)
					{
						if (TilePanelDigit10[i][j] == '0') Indicators.sprite.setTextureRect(sf::IntRect(0, 0, 16, 16));
						if (TilePanelDigit10[i][j] == '1') Indicators.sprite.setTextureRect(sf::IntRect(16, 0, 16, 16));

						Indicators.sprite.setPosition(j * 16 + 610, i * 16 + 70);

						window.draw(Indicators.sprite);
					}

			for (unsigned i = 0; i < HEIGHT_PANEL; i++)
				for (unsigned j = 0; j < WIDTH_PANEL_ARROW; j++)
				{
					Indicators.sprite.setTextureRect(sf::IntRect(0, 0, 16, 16));
					Indicators.sprite.setPosition(j * 16 + 515, i * 16 + 70);

					window.draw(Indicators.sprite);
				}

			circle1.setOutlineColor(sf::Color::Black);
			circle2.setOutlineColor(sf::Color::Black);
			circle3.setOutlineColor(sf::Color::Black);
			circle4.setOutlineColor(sf::Color::Black);
			circle5.setOutlineColor(sf::Color::Black);
			circle6.setOutlineColor(sf::Color::Black);
			circle7.setOutlineColor(sf::Color::Black);
			circle8.setOutlineColor(sf::Color::Black);
			circle9.setOutlineColor(sf::Color::Black);
			circle10.setOutlineColor(sf::Color::Black);

			window.draw(circle1); window.draw(circle2); window.draw(circle3); window.draw(circle4); window.draw(circle5);
			window.draw(circle6); window.draw(circle7); window.draw(circle8); window.draw(circle9); window.draw(circle10);

			window.draw(Digit1); window.draw(Digit2); window.draw(Digit3); window.draw(Digit4); window.draw(Digit5);
			window.draw(Digit6); window.draw(Digit7); window.draw(Digit8); window.draw(Digit9); window.draw(Digit10);

			if (sf::IntRect(200, 120, 200, 50).contains(sf::Mouse::getPosition(window)))
			{
				exit.sprite.setColor(sf::Color::Magenta);
				if ((sf::Mouse::isButtonPressed(sf::Mouse::Left)) && (close_programOut == false))
					FirstFrameProgram(window, lift_pos_sending, lift_pos_arrival, close_programOut);
			}

			window.draw(exit.sprite);
			window.display();
		}
	}
}

void CloseWindow(sf::RenderWindow& window, bool& exit_console)
{
	sf::Event event;
	while (window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			window.close();
			exit_console = true;
		}

	}
}

bool MenuGame(sf::RenderWindow& window)
{
	sf::Font menu_font;
	menu_font.loadFromFile("fonts/Comic_Sans_MS.TTF");
	sf::Text menu_text("", menu_font, 100);
	menu_text.setFillColor(sf::Color::Black);
	menu_text.setStyle(sf::Text::Bold);
	menu_text.setString("L  I  F  T");
	menu_text.setPosition(10, 0);

	sf::Texture menuTexture1, menuTexture2, menuTexture3, aboutTexture, menuBackground;
	menuTexture1.loadFromFile("images/menu111.png");
	menuTexture2.loadFromFile("images/menu222.png");
	menuBackground.loadFromFile("images/Menu_BG.png");
	sf::Sprite menu1(menuTexture1), menu2(menuTexture2), menuBG(menuBackground);
	bool isMenu{ true };
	int menuNum{ 0 };
	menu1.setPosition(10, 160);
	menu2.setPosition(6, 220);

	//////////////////////////МЕНЮ//////////////////////////
	while (isMenu)
	{
		menu1.setColor(sf::Color::White);
		menu2.setColor(sf::Color::White);
		menuNum = 0;

		window.clear();

		if (sf::IntRect(10, 160, 380, 40).contains(sf::Mouse::getPosition(window)))
		{
			menu1.setColor(sf::Color::Blue);
			menuNum = 1;
		}
		if (sf::IntRect(6, 220, 160, 40).contains(sf::Mouse::getPosition(window)))
		{
			menu2.setColor(sf::Color::Blue);
			menuNum = 2;
		}

		sf::Event event_click;
		while (window.pollEvent(event_click))
		{
			if (event_click.type == sf::Event::Closed)
			{
				window.close();
				return !isMenu;
			}

			if (event_click.type == event_click.MouseButtonReleased && event_click.mouseButton.button == sf::Mouse::Left)
			{
				if (menuNum == 1) isMenu = false;
				if (menuNum == 2)
				{
					window.close();
					isMenu = false;
				}
			}
		}

		window.draw(menuBG);
		window.draw(menu_text);
		window.draw(menu1);
		window.draw(menu2);

		window.display();
	}
	return !isMenu;
}
