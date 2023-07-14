#include <SFML/Graphics.hpp>

#include "MyFuncs.h"
#include "Constants.h"

int main()
{
	setlocale(LC_ALL, "Russian");
	sf::RenderWindow window(sf::VideoMode(WIDTH_window, HEIGHT_window), "Lab_1", sf::Style::Close);
	window.setPosition(sf::Vector2i(x_position_window, y_position_window));

	//Привязка ГПСЧ к календарному времени
	srand(static_cast<unsigned int>(time(0)));

	bool flag_of_end{ stage_0_menu(window) };
	if (flag_of_end == false)
	{
		return 0;
	}
}