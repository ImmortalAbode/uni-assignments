#include "TFigure.h"
#include "MyFuncs.h"
#include "SFML_EllipseShape.h"

//Класс фигур
TFigure::TFigure()
{
	std::cout << "Объект-точка был успешно создан." << std::endl;
}

TFigure::TFigure(float base_point_coordinate_x, float base_point_coordinate_y)
	:
	m_base_point_coordinate_x{ base_point_coordinate_x },
	m_base_point_coordinate_y{ base_point_coordinate_y }
{
	std::cout << "Объект-точка был успешно создан." << std::endl;
}

void TFigure::Show(sf::RenderWindow& window) {}

void TFigure::MoveTo(float change_coordinate_x, float change_coordinate_y) {}

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
	//std::cout << "Объект-точка был уничтожен." << std::endl;
}

//Класс окружностей
TCircle::TCircle()
	:TFigure(), m_radius{ 50 }
{
	std::cout << "Объект-окружность был успешно создан." << std::endl;
}

TCircle::TCircle(float radius, float base_point_coordinate_x, float base_point_coordinate_y)
	:TFigure(base_point_coordinate_x, base_point_coordinate_y), m_radius{ radius }
{
	while (getCoordinateX() - m_radius < 465 || getCoordinateX() + m_radius > 1415 ||
		getCoordinateY() - m_radius < 115 || getCoordinateY() + m_radius > 715)
	{
		m_radius -= 1;
	}
	std::cout << "Объект-окружность был успешно создан." << std::endl;
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

void TCircle::MoveTo(float change_coordinate_x, float change_coordinate_y) 
{
	setCoordinateX(getCoordinateX() + change_coordinate_x);
	setCoordinateY(getCoordinateY() + change_coordinate_y);
}

void TCircle::Free(TCircle**& ptr_circles_mass, int& count_size_mass_circles)
{
	delete_element_shape<TCircle>(ptr_circles_mass, count_size_mass_circles);
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
	//std::cout << "Объект-окружность был уничтожен." << std::endl;
}

//Класс эллипсов
TEllipse::TEllipse()
	:TCircle{}
{
	std::cout << "Объект-эллипс был успешно создан." << std::endl;
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
	std::cout << "Объект-эллипс был успешно создан." << std::endl;
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

void TEllipse::MoveTo(float change_coordinate_x, float change_coordinate_y) 
{
	setCoordinateX(getCoordinateX() + change_coordinate_x);
	setCoordinateY(getCoordinateY() + change_coordinate_y);
}

void TEllipse::Free(TEllipse**& ptr_ellipses_mass, int& count_size_mass_ellipses)
{
	delete_element_shape<TEllipse>(ptr_ellipses_mass, count_size_mass_ellipses);
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
	//std::cout << "Объект-эллипс был уничтожен." << std::endl;
}

//Класс четырехугольников
TQuadrilateral::TQuadrilateral()
	:TFigure()
{
	std::cout << "Объект-четырехугольник был успешно создан." << std::endl;
}

TQuadrilateral::TQuadrilateral(float base_point_coordinate_x1, float base_point_coordinate_y1, float base_point_coordinate_x2, float base_point_coordinate_y2,
	float base_point_coordinate_x3, float base_point_coordinate_y3, float base_point_coordinate_x4, float base_point_coordinate_y4)
	:TFigure(base_point_coordinate_x1, base_point_coordinate_y1), m_base_point_coordinate_x2{base_point_coordinate_x2}, m_base_point_coordinate_y2{base_point_coordinate_y2},
	m_base_point_coordinate_x3{base_point_coordinate_x3}, m_base_point_coordinate_y3{base_point_coordinate_y3}, 
	m_base_point_coordinate_x4{ base_point_coordinate_x4 }, m_base_point_coordinate_y4{ base_point_coordinate_y4 }
{

	std::cout << "Объект-четырехугольник был успешно создан." << std::endl;
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

void TQuadrilateral::MoveTo(float change_coordinate_x, float change_coordinate_y) 
{
	setCoordinateX(getCoordinateX() + change_coordinate_x);
	setCoordinateY(getCoordinateY() + change_coordinate_y);
	changeCoordinateX234_Y234(change_coordinate_x, change_coordinate_y);
}

void TQuadrilateral::Free(TQuadrilateral**& ptr_quadrilaterals_mass, int& count_size_mass_quadrilaterals)
{
	delete_element_shape<TQuadrilateral>(ptr_quadrilaterals_mass, count_size_mass_quadrilaterals);
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

void TQuadrilateral::changeSize(float dsize)
{
	setCoordinateX(getCoordinateX() - dsize); setCoordinateY(getCoordinateY() - dsize);
	m_base_point_coordinate_x2 += dsize; m_base_point_coordinate_y2 -= dsize;
	m_base_point_coordinate_x3 += dsize; m_base_point_coordinate_y3 += dsize;
	m_base_point_coordinate_x4 -= dsize; m_base_point_coordinate_y4 += dsize;
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
	//std::cout << "Объект-четырехугольник был уничтожен." << std::endl;
}

//Класс трапеций
TTrapeze::TTrapeze()
	:TQuadrilateral()
{
	BalanceSides();
	std::cout << "Объект-трапеция был успешно создан." << std::endl;
}

TTrapeze::TTrapeze(float base_point_coordinate_x1, float base_point_coordinate_y1, int degree, float bottom_base_length, float top_base_length, float height)
	: TQuadrilateral(base_point_coordinate_x1, base_point_coordinate_y1, base_point_coordinate_x1 + height / tan(m_degree * acos(-1.0f) / 180),
		base_point_coordinate_y1 - height, base_point_coordinate_x1 + height / tan(m_degree * acos(-1.0f) / 180) + top_base_length,
		base_point_coordinate_y1 - height, base_point_coordinate_x1 + bottom_base_length, base_point_coordinate_y1),
	m_degree{ degree }, m_bottom_base_length{ bottom_base_length }, m_top_base_length{ top_base_length }, m_height{ height }
{
	BalanceSides();
	std::cout << "Объект-трапеция был успешно создан." << std::endl;
}
void TTrapeze::Show(sf::RenderWindow& window) 
{
	TQuadrilateral::Show(window);
}
void TTrapeze::MoveTo(float change_coordinate_x, float change_coordinate_y) 
{
	TQuadrilateral::MoveTo(change_coordinate_x, change_coordinate_y);
}

void TTrapeze::Free(TTrapeze**& ptr_trapezes_mass, int& count_size_mass_trapezes)
{
	delete_element_shape<TTrapeze>(ptr_trapezes_mass, count_size_mass_trapezes);
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
	//std::cout << "Объект-трапеция был уничтожен." << std::endl;
}

//Класс прямоугольников
TRectangle::TRectangle()
	:TQuadrilateral()
{
	BalanceSides();
	std::cout << "Объект-прямоугольник был успешно создан." << std::endl;
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
	std::cout << "Объект-прямоугольник был успешно создан." << std::endl;
}
void TRectangle::Show(sf::RenderWindow& window)  
{
	BalanceSides();
	TQuadrilateral::Show(window);
}
void TRectangle::MoveTo(float change_coordinate_x, float change_coordinate_y) 
{
	TQuadrilateral::MoveTo(change_coordinate_x, change_coordinate_y);
}
void TRectangle::Free(TRectangle**& ptr_rectangles_mass, int& count_size_mass_rectangles)
{
	delete_element_shape<TRectangle>(ptr_rectangles_mass, count_size_mass_rectangles);
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
	//std::cout << "Объект-прямоугольник был уничтожен." << std::endl;
}

//Класс ромбов
TRhombus::TRhombus()
	:TQuadrilateral()
{
	BalanceSides();
	std::cout << "Объект-ромб был успешно создан." << std::endl;
}
TRhombus::TRhombus(float base_point_coordinate_x1, float base_point_coordinate_y1, float length, int degree)
	: TQuadrilateral(base_point_coordinate_x1, base_point_coordinate_y1, getCoordinateX() + length * cos(degree * acos(-1.0f) / 180),
		getCoordinateY() - length * sin(degree * acos(-1.0f) / 180), getCoordinateX() + 2 * length * cos(degree * acos(-1.0f) / 180), getCoordinateY(),
		getCoordinateX() + length * cos(degree * acos(-1.0f) / 180), getCoordinateY() + length * sin(degree * acos(-1.0f) / 180)), m_length{ length }, m_degree{ degree }
{
	std::cout << "Объект-ромб был успешно создан." << std::endl;
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
void TRhombus::MoveTo(float change_coordinate_x, float change_coordinate_y) 
{
	TQuadrilateral::MoveTo(change_coordinate_x, change_coordinate_y);
}
void TRhombus::Free(TRhombus**& ptr_rhombuses_mass, int& count_size_mass_rhombuses)
{
	delete_element_shape<TRhombus>(ptr_rhombuses_mass, count_size_mass_rhombuses);
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
	//std::cout << "Объект-ромб был уничтожен." << std::endl;
}

//Класс отрезков
TLinesegment::TLinesegment()
	:TFigure()
{
	std::cout << "Объект-отрезок был успешно создан." << std::endl;
}
TLinesegment::TLinesegment(float base_point_coordinate_x, float base_point_coordinate_y, float length, int degree)
	: TFigure{ base_point_coordinate_x, base_point_coordinate_y }, m_length{ length }, m_degree{ degree }
{
	if (m_degree >= 0 && m_degree <= 90)
	{
		while (getCoordinateX() + m_length * cos(m_degree * acos(-1.0f) / 180) > 1415 ||
			getCoordinateY() + m_length * sin(m_degree * acos(-1.0f) / 180) > 715)
		{
			m_length -= 1;
		}
	}
	else if (m_degree >= 90 && m_degree <= 180)
	{
		while (getCoordinateX() + m_length * cos(m_degree * acos(-1.0f) / 180) < 465 ||
			getCoordinateY() + m_length * sin(m_degree * acos(-1.0f) / 180) > 715)
		{
			m_length -= 1;
		}
	}
	else if (m_degree >= 180 && m_degree <= 270)
	{
		while (getCoordinateX() + m_length * cos(m_degree * acos(-1.0f) / 180) < 465 ||
			getCoordinateY() + m_length * sin(m_degree * acos(-1.0f) / 180) < 115)
		{
			m_length -= 1;
		}
	}
	else if (degree >= 270 && degree <= 360)
	{
		while (getCoordinateX() + m_length * cos(m_degree * acos(-1.0f) / 180) > 1415 ||
			getCoordinateY() + m_length * sin(m_degree * acos(-1.0f) / 180) < 115)
		{
			m_length -= 1;
		}
	}
	std::cout << "Объект-отрезок был успешно создан." << std::endl;

}
void TLinesegment::Show(sf::RenderWindow& window) 
{
	line_segment.setSize(sf::Vector2f(m_length, m_width));
	line_segment.setFillColor(sf::Color(m_red, m_green, m_blue, m_visibility));
	line_segment.setPosition(getCoordinateX(), getCoordinateY());
	line_segment.setRotation(m_degree);
	window.draw(line_segment);
}
void TLinesegment::Free(TLinesegment**& ptr_linesegments_mass, int& count_size_mass_linesegments)
{
	delete_element_shape<TLinesegment>(ptr_linesegments_mass, count_size_mass_linesegments);
}
void TLinesegment::MoveTo(float change_coordinate_x, float change_coordinate_y) 
{
	setCoordinateX(getCoordinateX() + change_coordinate_x);
	setCoordinateY(getCoordinateY() + change_coordinate_y);
}
float TLinesegment::getDegree()
{
	return m_degree;
}
float TLinesegment::getLength()
{
	return m_length;
}
float TLinesegment::getWidth()
{
	return m_width;
}
void TLinesegment::changeLength(int dlength)
{
	m_length += dlength;
}
void TLinesegment::changeDegree(int ddegree)
{
	m_degree += ddegree;
}
TLinesegment::~TLinesegment()
{
	//std::cout << "Объект-отрезок был уничтожен." << std::endl;
}