#include "TFigure.h"
#include "SFML_EllipseShape.h"

//����� �����
TFigure::TFigure()
{
	std::cout << "������-����� ��� ������� ������." << std::endl;
}

TFigure::TFigure(float base_point_coordinate_x, float base_point_coordinate_y)
	:
	m_base_point_coordinate_x{ base_point_coordinate_x },
	m_base_point_coordinate_y{ base_point_coordinate_y }
{
	std::cout << "������-����� ��� ������� ������." << std::endl;
}

void TFigure::Show(sf::RenderWindow& window) {}

void TFigure::MoveTo(float change_coordinate_x, float change_coordinate_y)
{
	setCoordinateX(getCoordinateX() + change_coordinate_x);
	setCoordinateY(getCoordinateY() + change_coordinate_y);
}

void TFigure::setCoordinateX(float base_point_coordinate_x)
{
	m_base_point_coordinate_x = base_point_coordinate_x;
}

void TFigure::setCoordinateY(float base_point_coordinate_y)
{
	m_base_point_coordinate_y = base_point_coordinate_y;
}

float TFigure::getCoordinateX()
{
	return m_base_point_coordinate_x;
}

float TFigure::getCoordinateY()
{
	return m_base_point_coordinate_y;
}

void TFigure::setFillColor(int red, int green, int blue)
{
	m_red = red;
	m_green = green;
	m_blue = blue;
}

void TFigure::setOutlineColor(int out_red, int out_green, int out_blue)
{
	m_out_red = out_red;
	m_out_green = out_green;
	m_out_blue = out_blue;
}

void TFigure::setThickness(int thickness)
{
	m_thickness = thickness;
}

void TFigure::setVisibility(int visibility)
{
	m_visibility = visibility;
}

TFigure::~TFigure()
{
	//std::cout << "������-����� ��� ���������." << std::endl;
}

//����� �����������
TCircle::TCircle()
	:TFigure(), m_radius{ 50 }
{
	std::cout << "������-���������� ��� ������� ������." << std::endl;
}

TCircle::TCircle(float radius, float base_point_coordinate_x, float base_point_coordinate_y)
	: TFigure(base_point_coordinate_x, base_point_coordinate_y), m_radius{ radius }
{
	while (getCoordinateX() - m_radius < 465 || getCoordinateX() + m_radius > 1415 ||
		getCoordinateY() - m_radius < 115 || getCoordinateY() + m_radius > 715)
	{
		m_radius -= 1;
	}
	std::cout << "������-���������� ��� ������� ������." << std::endl;
}

void TCircle::Show(sf::RenderWindow& window)
{
	m_circle.setRadius(m_radius);
	m_circle.setPosition(getCoordinateX() - m_radius, getCoordinateY() - m_radius);
	m_circle.setFillColor(sf::Color(m_red, m_green, m_blue, m_visibility));
	m_circle.setOutlineColor(sf::Color(m_out_red, m_out_green, m_out_blue));
	m_circle.setOutlineThickness(m_thickness);
	window.draw(m_circle);
}

void TCircle::Free(TCircle* ptr_circle)
{
	delete ptr_circle;
}

void TCircle::setRadius(float radius)
{
	m_radius = radius;
}

void TCircle::ChangeRadius(float dradius)
{
	m_radius += dradius;
}

float TCircle::getRadius()
{
	return m_radius;
}

TCircle::~TCircle()
{
	//std::cout << "������-���������� ��� ���������." << std::endl;
}

//����� ��������
TEllipse::TEllipse()
	:TCircle{}
{
	std::cout << "������-������ ��� ������� ������." << std::endl;
}

TEllipse::TEllipse(float semi_minor_axis, float semi_major_axis, float base_point_coordinate_x, float base_point_coordinate_y)
	: TCircle{ semi_major_axis, base_point_coordinate_x, base_point_coordinate_y }, m_semi_minor_axis{ semi_minor_axis }
{
	while (getCoordinateX() - getRadius() < 465 || getCoordinateX() + getRadius() > 1415)
	{
		ChangeRadius(-1);
	}
	while (getCoordinateY() - m_semi_minor_axis < 115 || getCoordinateY() + m_semi_minor_axis > 715)
	{
		m_semi_minor_axis -= 1;
	}
	std::cout << "������-������ ��� ������� ������." << std::endl;
}

void TEllipse::Show(sf::RenderWindow& window)
{
	EllipseShape m_ellipse{ {getRadius(), m_semi_minor_axis} };
	m_ellipse.setPosition(getCoordinateX() - getRadius(), getCoordinateY() - m_semi_minor_axis);
	m_ellipse.setFillColor(sf::Color(m_red, m_green, m_blue, m_visibility));
	m_ellipse.setOutlineColor(sf::Color(m_out_red, m_out_green, m_out_blue));
	m_ellipse.setOutlineThickness(m_thickness);
	window.draw(m_ellipse);
}

void TEllipse::Free(TEllipse* ptr_ellipse)
{
	delete ptr_ellipse;
}

void TEllipse::changeSemiMinorAxis(float dsemi_minor_axis)
{
	m_semi_minor_axis += dsemi_minor_axis;
}

float TEllipse::getSemiMinorAxis()
{
	return m_semi_minor_axis;
}

void TEllipse::Rotate90degrees()
{
	float temp = m_semi_minor_axis;
	m_semi_minor_axis = getRadius();
	setRadius(temp);
}

TEllipse::~TEllipse()
{
	//std::cout << "������-������ ��� ���������." << std::endl;
}

//����� �����������������
TQuadrilateral::TQuadrilateral()
	:TFigure()
{
	std::cout << "������-��������������� ��� ������� ������." << std::endl;
}

TQuadrilateral::TQuadrilateral(float base_point_coordinate_x1, float base_point_coordinate_y1, float base_point_coordinate_x2, float base_point_coordinate_y2,
	float base_point_coordinate_x3, float base_point_coordinate_y3, float base_point_coordinate_x4, float base_point_coordinate_y4)
	: TFigure(base_point_coordinate_x1, base_point_coordinate_y1), m_base_point_coordinate_x2{ base_point_coordinate_x2 }, m_base_point_coordinate_y2{ base_point_coordinate_y2 },
	m_base_point_coordinate_x3{ base_point_coordinate_x3 }, m_base_point_coordinate_y3{ base_point_coordinate_y3 },
	m_base_point_coordinate_x4{ base_point_coordinate_x4 }, m_base_point_coordinate_y4{ base_point_coordinate_y4 }
{

	std::cout << "������-��������������� ��� ������� ������." << std::endl;
}

void TQuadrilateral::Show(sf::RenderWindow& window)
{
	quadrilateral.setPointCount(4);
	quadrilateral.setPoint(0, sf::Vector2f(getCoordinateX(), getCoordinateY()));
	quadrilateral.setPoint(1, sf::Vector2f(m_base_point_coordinate_x2, m_base_point_coordinate_y2));
	quadrilateral.setPoint(2, sf::Vector2f(m_base_point_coordinate_x3, m_base_point_coordinate_y3));
	quadrilateral.setPoint(3, sf::Vector2f(m_base_point_coordinate_x4, m_base_point_coordinate_y4));
	quadrilateral.setFillColor(sf::Color(m_red, m_green, m_blue, m_visibility));
	quadrilateral.setOutlineColor(sf::Color(m_out_red, m_out_green, m_out_blue));
	quadrilateral.setOutlineThickness(m_thickness);
	window.draw(quadrilateral);
}

void TQuadrilateral::Free(TQuadrilateral* ptr_quadrilateral)
{
	delete ptr_quadrilateral;
}

void TQuadrilateral::changeCoordinateX234_Y234(float change_coordinate_x, float change_coordinate_y)
{
	m_base_point_coordinate_x2 += change_coordinate_x;
	m_base_point_coordinate_x3 += change_coordinate_x;
	m_base_point_coordinate_x4 += change_coordinate_x;
	m_base_point_coordinate_y2 += change_coordinate_y;
	m_base_point_coordinate_y3 += change_coordinate_y;
	m_base_point_coordinate_y4 += change_coordinate_y;
}

float TQuadrilateral::getCoordinateX2()
{
	return m_base_point_coordinate_x2;
}
float TQuadrilateral::getCoordinateX3()
{
	return m_base_point_coordinate_x3;
}
float TQuadrilateral::getCoordinateX4()
{
	return m_base_point_coordinate_x4;
}
float TQuadrilateral::getCoordinateY2()
{
	return m_base_point_coordinate_y2;
}
float TQuadrilateral::getCoordinateY3()
{
	return m_base_point_coordinate_y3;
}
float TQuadrilateral::getCoordinateY4()
{
	return m_base_point_coordinate_y4;
}

TQuadrilateral::~TQuadrilateral()
{
	//std::cout << "������-��������������� ��� ���������." << std::endl;
}

//����� ��������
TTrapeze::TTrapeze()
	:TQuadrilateral()
{
	BalanceSides();
	std::cout << "������-�������� ��� ������� ������." << std::endl;
}

TTrapeze::TTrapeze(float base_point_coordinate_x1, float base_point_coordinate_y1, int degree, float bottom_base_length, float top_base_length, float height)
	: TQuadrilateral(base_point_coordinate_x1, base_point_coordinate_y1, base_point_coordinate_x1 + height / tan(m_degree * acos(-1.0f) / 180),
		base_point_coordinate_y1 - height, base_point_coordinate_x1 + height / tan(m_degree * acos(-1.0f) / 180) + top_base_length,
		base_point_coordinate_y1 - height, base_point_coordinate_x1 + bottom_base_length, base_point_coordinate_y1),
	m_degree{ degree }, m_bottom_base_length{ bottom_base_length }, m_top_base_length{ top_base_length }, m_height{ height }
{
	BalanceSides();
	std::cout << "������-�������� ��� ������� ������." << std::endl;
}
void TTrapeze::Show(sf::RenderWindow& window)
{
	TQuadrilateral::Show(window);
}

void TTrapeze::Free(TTrapeze* ptr_trapeze)
{
	delete ptr_trapeze;
}

void TTrapeze::BalanceSides()
{
	m_base_point_coordinate_x2 = getCoordinateX() + m_height / tan(m_degree * acos(-1.0f) / 180);
	m_base_point_coordinate_y2 = getCoordinateY() - m_height;
	m_base_point_coordinate_x3 = m_base_point_coordinate_x2 + m_top_base_length;
	m_base_point_coordinate_y3 = m_base_point_coordinate_y2;
	m_base_point_coordinate_x4 = getCoordinateX() + m_bottom_base_length;
	m_base_point_coordinate_y4 = getCoordinateY();
}

void TTrapeze::changeTopBase(float change_top_base)
{
	m_base_point_coordinate_x3 += change_top_base;
}
void TTrapeze::changeBottomBase(float change_bottom_base)
{
	m_base_point_coordinate_x4 += change_bottom_base;
}

void TTrapeze::changeHeight(int dheight)
{
	m_base_point_coordinate_y2 += dheight;
	m_base_point_coordinate_y3 = m_base_point_coordinate_y2;
}

TTrapeze::~TTrapeze()
{
	//std::cout << "������-�������� ��� ���������." << std::endl;
}

//����� ���������������
TRectangle::TRectangle()
	:TQuadrilateral()
{
	BalanceSides();
	std::cout << "������-������������� ��� ������� ������." << std::endl;
}
TRectangle::TRectangle(float base_point_coordinate_x1, float base_point_coordinate_y1, float length, float width)
	: TQuadrilateral{ base_point_coordinate_x1, base_point_coordinate_y1, base_point_coordinate_x1 + length, base_point_coordinate_y1,
	base_point_coordinate_x1 + length, base_point_coordinate_y1 + width, base_point_coordinate_x1, base_point_coordinate_y1 + width }, m_length{ length }, m_width{ width }
{
	while (getCoordinateX() + m_length > 1415)
	{
		m_length -= 1;
	}
	while (getCoordinateY() + m_width > 715)
	{
		m_width -= 1;
	}
	std::cout << "������-������������� ��� ������� ������." << std::endl;
}
void TRectangle::Show(sf::RenderWindow& window)
{
	BalanceSides();
	TQuadrilateral::Show(window);
}

void TRectangle::Free(TRectangle* ptr_rectangle)
{
	delete ptr_rectangle;
}

void TRectangle::BalanceSides()
{
	m_base_point_coordinate_x2 = getCoordinateX() + m_length; m_base_point_coordinate_y2 = getCoordinateY();
	m_base_point_coordinate_x3 = getCoordinateX() + m_length; m_base_point_coordinate_y3 = getCoordinateY() + m_width;
	m_base_point_coordinate_x4 = getCoordinateX(); m_base_point_coordinate_y4 = getCoordinateY() + m_width;
}
float TRectangle::getLength()
{
	return m_length;
}
float TRectangle::getWidth()
{
	return m_width;
}
void TRectangle::changeLength(int dlength)
{
	m_length += dlength;
}
void TRectangle::changeWidth(int dwidth)
{
	m_width += dwidth;
}
TRectangle::~TRectangle()
{
	//std::cout << "������-������������� ��� ���������." << std::endl;
}

//����� ������
TRhombus::TRhombus()
	:TQuadrilateral()
{
	BalanceSides();
	std::cout << "������-���� ��� ������� ������." << std::endl;
}
TRhombus::TRhombus(float base_point_coordinate_x1, float base_point_coordinate_y1, float length, int degree)
	: TQuadrilateral(base_point_coordinate_x1, base_point_coordinate_y1, getCoordinateX() + length * cos(degree * acos(-1.0f) / 180),
		getCoordinateY() - length * sin(degree * acos(-1.0f) / 180), getCoordinateX() + 2 * length * cos(degree * acos(-1.0f) / 180), getCoordinateY(),
		getCoordinateX() + length * cos(degree * acos(-1.0f) / 180), getCoordinateY() + length * sin(degree * acos(-1.0f) / 180)), m_length{ length }, m_degree{ degree }
{
	std::cout << "������-���� ��� ������� ������." << std::endl;
}
void TRhombus::BalanceSides()
{
	m_base_point_coordinate_x2 = getCoordinateX() + m_length * cos(m_degree * acos(-1.0f) / 180);
	m_base_point_coordinate_y2 = getCoordinateY() - m_length * sin(m_degree * acos(-1.0f) / 180);
	m_base_point_coordinate_x3 = getCoordinateX() + 2 * m_length * cos(m_degree * acos(-1.0f) / 180);
	m_base_point_coordinate_y3 = getCoordinateY();
	m_base_point_coordinate_x4 = m_base_point_coordinate_x2;
	m_base_point_coordinate_y4 = getCoordinateY() + m_length * sin(m_degree * acos(-1.0f) / 180);
}
void TRhombus::Show(sf::RenderWindow& window)
{
	BalanceSides();
	TQuadrilateral::Show(window);
}

void TRhombus::Free(TRhombus* ptr_rhombus)
{
	delete ptr_rhombus;
}
float TRhombus::getLength()
{
	return m_length;
}
int TRhombus::getDegree()
{
	return m_degree;
}
void TRhombus::changeLength(int dlength)
{
	m_length += dlength;
	BalanceSides();
}
void TRhombus::changeDegree(int ddegree)
{
	m_degree += ddegree;
	BalanceSides();
}
TRhombus::~TRhombus()
{
	//std::cout << "������-���� ��� ���������." << std::endl;
}