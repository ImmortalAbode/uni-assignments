#ifndef Circle_H_
#define Circle_H_

class Circle
{
private:
	float m_base_point_coordinate_x{ 700 };
	float m_base_point_coordinate_y{ 400 };
	float m_radius{ 50 };
	float m_OutlineThickness{ 5 };
	int m_red{ 180 }, m_green{ 68 }, m_blue{ 212 };
	int m_r_color{ 233 }, m_g_color{ 179 }, m_b_color{ 248 };
	int m_visibility{ 255 };

	sf::CircleShape shape_circle{};

public:
	Circle();
	Circle(float radius, float base_point_coordinate_x, float base_point_coordinate_y);
	void Show(sf::RenderWindow& window);
	void MoveTo(float change_base_point_coordinate_x, float change_base_point_coordinate_y);
	void Free(Circle**& ptr_circles_mass, int& count_size_mass_circles);
	float getCoordinateY();
	float getCoordinateX();
	float getRadius();
	float getOutlineThickness();
	void setVisibility(int visibility);
	void setColorOutline(int red, int green, int blue);
	void setColor(int r_color, int g_color, int b_color);
	void setRadius(int dradius);
	~Circle();
};

#endif /*Circle_H_*/
