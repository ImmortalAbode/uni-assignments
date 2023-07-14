#ifndef MYFUNCS_H_
#define MYFUNCS_H_

void CloseWindow(sf::RenderWindow& window, bool& exit_console);
bool MenuGame(sf::RenderWindow& window);
void FirstFrameProgram(sf::RenderWindow& window, int& lift_pos_sending, int& lift_pos_arrival, bool& close_programOut);
void SecondFrameProgram(sf::RenderWindow& window, int& lift_pos_sending, bool& close_programOut);

#endif /*MYFUNCS_H_*/
