#ifndef USER_BUTTON_
#define USER_BUTTON_

class User_Text_Button
{
private:
	float m_x{}, m_y{};
	int m_size{ 50 };
	int m_red{}, m_green{}, m_blue{};

	sf::Font m_user_font{};
	sf::Text m_user_text{};
	sf::String m_file, m_str{ "" };
public:
	User_Text_Button() = default;

	User_Text_Button(sf::String f, sf::String t, int size, float x, float y)
	{
		m_x = x; m_y = y;
		m_user_font.loadFromFile("fonts/" + f);
		m_user_text.setFont(m_user_font);
		m_user_text.setString(t);
		m_user_text.setCharacterSize(size);
		m_user_text.setFillColor(sf::Color::Cyan);
		m_user_text.setStyle(sf::Text::Bold);
		m_user_text.setPosition(x, y);
	}

	void m_setFillColor(int red, int green, int blue)
	{
		m_red = red; m_green = green; m_blue = blue;
		m_user_text.setFillColor(sf::Color(red, green, blue));
	}

	void m_setFillColorDefault()
	{
		m_user_text.setFillColor(sf::Color::Cyan);
	}

	void Show(sf::RenderWindow& window)
	{
		window.draw(m_user_text);
	}

	~User_Text_Button() {};
};

class User_Rect_Button
{
private:
	float m_x{}, m_y{};
	int m_red{}, m_green{}, m_blue{};
	int m_r_color{}, m_g_color{}, m_b_color{};
	float m_rect_width{ 160 }, m_rect_height{ 60 };
	float m_outline_thickness{ 5 };

	sf::RectangleShape m_user_rect{};
public:
	User_Rect_Button() = default;

	User_Rect_Button(float x, float y, float outline_thickness, float width, float height)
	{
		m_rect_width = width; m_rect_height = height; m_outline_thickness = outline_thickness;
		m_x = x; m_y = y;
		m_user_rect.setSize(sf::Vector2f(m_rect_width, m_rect_height));
		m_user_rect.setFillColor(sf::Color::Black);
		m_user_rect.setOutlineThickness(m_outline_thickness);
		m_user_rect.setOutlineColor(sf::Color::Blue);
		m_user_rect.setPosition(m_x, m_y);
	}

	void m_setColor(int r_color, int g_color, int b_color)
	{
		m_r_color = r_color; m_g_color = g_color; m_b_color = b_color;
		m_user_rect.setFillColor(sf::Color(m_r_color, m_g_color, m_b_color));
	}

	void m_setOutlineColor(int red, int green, int blue)
	{
		m_red = red; m_green = green; m_blue = blue;
		m_user_rect.setOutlineColor(sf::Color(red, green, blue));
	}

	void m_setOutlineColorDefault()
	{
		m_user_rect.setOutlineColor(sf::Color::Blue);
	}

	void Show(sf::RenderWindow& window)
	{
		window.draw(m_user_rect);
	}

	~User_Rect_Button() {};
};

#endif /*USER_BUTTON_*/