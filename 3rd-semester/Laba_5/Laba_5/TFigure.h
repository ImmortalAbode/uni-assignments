#ifndef TFIGURE_H_
#define TFIGURE_H_

#include <iostream>
#include "SFML/Graphics.hpp"

class TFigure
{
private:
	float m_base_point_coordinate_x{ 700 };
	float m_base_point_coordinate_y{ 400 };

protected:
	int m_red{ 180 }, m_green{ 68 }, m_blue{ 212 };
	int m_out_red{ 233 }, m_out_green{ 179 }, m_out_blue{ 248 };
	int m_thickness{ 5 };
	int m_visibility{ 255 };

protected:
	TFigure();
	TFigure(float base_point_coordinate_x, float base_point_coordinate_y);

public:
	virtual void Show(sf::RenderWindow& window);
	void MoveTo(float change_coordinate_x, float change_coordinate_y);
	void setCoordinateX(float base_point_coordinate_x);
	void setCoordinateY(float base_point_coordinate_y);
	float getCoordinateX();
	float getCoordinateY();
	void setFillColor(int red, int green, int blue);
	void setOutlineColor(int out_red, int out_green, int out_blue);
	void setThickness(int thickness);
	void setVisibility(int visibility);

	~TFigure();
};

class TCircle :public TFigure
{
private:
	float m_radius{ 50 };
	sf::CircleShape m_circle{};

public:
	TCircle();
	TCircle(float radius, float base_point_coordinate_x, float base_point_coordinate_y);
	void Show(sf::RenderWindow& window) override;
	void Free(TFigure**& ptr_circles_mass, int& count_size_mass_circles);
	void setRadius(float radius);
	void ChangeRadius(float dradius);
	float getRadius();

	~TCircle();
};

class TEllipse :public TCircle
{
private:
	float m_semi_minor_axis{ 25 };

public:
	TEllipse();
	TEllipse(float semi_minor_axis, float semi_major_axis, float base_point_coordinate_x, float base_point_coordinate_y);
	void Show(sf::RenderWindow& window) override;
	void Free(TFigure**& ptr_ellipses_mass, int& count_size_mass_ellipses);
	void changeSemiMinorAxis(float dsemi_minor_axis);
	float getSemiMinorAxis();
	void Rotate90degrees();
	~TEllipse();
};

class TQuadrilateral :public TFigure
{
private:
	sf::ConvexShape quadrilateral{};

protected:
	float m_base_point_coordinate_x2{ 745 }, m_base_point_coordinate_y2{ 415 }, m_base_point_coordinate_x3{ 720 }, m_base_point_coordinate_y3{ 520 },
		m_base_point_coordinate_x4{ 670 }, m_base_point_coordinate_y4{ 480 };
public:
	TQuadrilateral();
	TQuadrilateral(float base_point_coordinate_x1, float base_point_coordinate_y1, float base_point_coordinate_x2, float base_point_coordinate_y2,
		float base_point_coordinate_x3, float base_point_coordinate_y3, float base_point_coordinate_x4, float base_point_coordinate_y4);
	void Show(sf::RenderWindow& window) override;
	void Free(TFigure**& ptr_quadrilaterals_mass, int& count_size_mass_quadrilaterals);
	void changeCoordinateX234_Y234(float change_coordinate_x, float change_coordinate_y);
	float getCoordinateX2();
	float getCoordinateX3();
	float getCoordinateX4();
	float getCoordinateY2();
	float getCoordinateY3();
	float getCoordinateY4();

	~TQuadrilateral();
};

class TTrapeze :public TQuadrilateral
{
private:
	float m_bottom_base_length{ 200 };
	float m_top_base_length{ 100 };
	float m_height{ 80 };
	int m_degree{ 50 };
private:
	void BalanceSides();
public:
	TTrapeze();
	TTrapeze(float base_point_coordinate_x1, float base_point_coordinate_y1, int degree, float bottom_base_length, float top_base_length, float height);
	void Show(sf::RenderWindow& window) override;
	void Free(TFigure**& ptr_trapezes_mass, int& count_size_mass_trapezes);
	void changeTopBase(float change_top_base);
	void changeBottomBase(float change_bottom_base);
	void changeHeight(int dheight);
	~TTrapeze();
};

class TRectangle :public TQuadrilateral
{
private:
	float m_length{ 200 };
	float m_width{ 60 };
private:
	void BalanceSides();
public:
	TRectangle();
	TRectangle(float base_point_coordinate_x1, float base_point_coordinate_y1, float m_length, float m_width);
	void Show(sf::RenderWindow& window) override;
	void Free(TFigure**& ptr_rectangles_mass, int& count_size_mass_rectangles);
	float getLength();
	float getWidth();
	void changeLength(int dlength);
	void changeWidth(int dwidth);
	~TRectangle();
};

class TRhombus :public TQuadrilateral
{
private:
	float m_length{ 100 };
	int m_degree{ 15 };
private:
	void BalanceSides();
public:
	TRhombus();
	TRhombus(float base_point_coordinate_x1, float base_point_coordinate_y1, float length, int degree);
	void Show(sf::RenderWindow& window) override;
	void Free(TFigure**& ptr_rhombuses_mass, int& count_size_mass_rhombuses);
	float getLength();
	int getDegree();
	void changeLength(int dlength);
	void changeDegree(int ddegree);
	~TRhombus();
};
#endif /*TFIGURE_H_*/

