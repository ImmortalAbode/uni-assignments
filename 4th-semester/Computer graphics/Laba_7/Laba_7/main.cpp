#include <stdlib.h>
#include <GL/glut.h>
#include <stdio.h>
#include <cmath>

void drawEvaluationFunctionMethod_1st_quater(const int& x1, const int& y1, const int& x2, const int& y2)
{
	//Число ячеек сетки растра по оси X = A = 99.
	//Число ячеек сетки растра по оси Y = B = 99.
	GLint A{ abs(x2 - x1) }, B{ abs(y2 - y1) };
	//F(x,y) = xy, где F(x,y) = 100 при а = 200; (x, y) - координаты изображающей точки (ИТ).
	GLint x{ x1 }, y{ y1 };
	GLint Fxy{};
	//Построение заданной линии методом оценочной функции.
	while (x <= x2 && y >= y2)
	{
		glVertex2i(x, y);
		Fxy = x * y;
		if (Fxy < 100)
			x++;
		else if (Fxy > 100)
			y--;
		else
			if (A >= B)
				x++;
			else
				y--;
	}
}
void drawEvaluationFunctionMethod_3rd_quater(const int& x1, const int& y1, const int& x2, const int& y2)
{
	//Число ячеек сетки растра по оси X = A = 99.
	//Число ячеек сетки растра по оси Y = B = 99.
	GLint A{ abs(x2 - x1) }, B{ abs(y2 - y1) };
	//F(x,y) = xy, где F(x,y) = 100 при а = 200; (x, y) - координаты изображающей точки (ИТ).
	GLint x{ x1 }, y{ y1 };
	GLint Fxy{};
	//Построение заданной линии методом оценочной функции.
	while (x >= x2 && y <= y2)
	{
		glVertex2i(x, y);
		Fxy = x * y;
		if (Fxy < 100)
			x--;
		else if (Fxy > 100)
			y++;
		else
			if (A >= B)
				x--;
			else
				y++;
	}
}
/*Построение гиперболы по методу цифровых дифференциальных анализаторов (ЦДА).
 *Вычисления (по методическому пособию):
 *F(x,y) = a/(2*x) - y.
 * F'x = -a/(2*x^2) и F'y = -1 => sqrt((F'x)^2 + (F'y)^2) = sqrt(a^2/(4*x^4) + 1) = sqrt(a^2+4*x^4)/(2*x^2).
 * k*dt = 1/sqrt((F'x)^2 + (F'y)^2) = (2*x^2)/sqrt(a^2+4*x^4).
 * dxi = -k*F'y*dt = (2*x^2)/sqrt(a^2+4*x^4).
 * dyi = k*F'x*dt = -a/sqrt(a^2+4*x^4).
 * x(i+1) = xi + dxi = xi + (2*x^2)/sqrt(a^2+4*x^4).
 * y(i+1) = yi + dyi = yi - a/sqrt(a^2+4*x^4).
 */
void drawDDA_1st_quater(const float& x1, const float& y1, const float& x2, const float& y2)
{
	//Координаты изображающей точки (ИТ).
	double x{ x1 }, y{ y1 };
	//Приращение координат ИТ, вычисленное согласно методическому пособию ( sqrt(((2*x^2)/sqrt(a^2+4*x^4))^2 + (-a/sqrt(a^2+4*x^4))^2) = 1).
	double dxi{ (2 * pow(x,2)) / sqrt(pow(200,2) + 4 * pow(x,4)) }, dyi{ ((-1) * 200) / sqrt(pow(200,2) + 4 * pow(x,4)) };
	//Построение заданной линии по методу ЦДА.
	while (round(x + dxi) <= x2 && round(y + dyi) >= y2)
	{
		dxi = (2 * pow(x, 2)) / sqrt(pow(200, 2) + 4 * pow(x, 4));
		dyi = ((-1) * 200) / sqrt(pow(200, 2) + 4 * pow(x, 4));
		glVertex2i(round(x), round(y));
		x += dxi/10;
		y += dyi/10;
	}
}
void drawDDA_3rd_quater(const float& x1, const float& y1, const float& x2, const float& y2)
{
	//Координаты изображающей точки (ИТ).
	double x{ x1 }, y{ y1 };
	//Приращение координат ИТ, вычисленное согласно методическому пособию ( sqrt((2*x^2)/sqrt(a^2+4*x^4))^2 + (-a/sqrt(a^2+4*x^4))^2) = 1).
	double dxi{ (2 * pow(x,2)) / sqrt(pow(200,2) + 4 * pow(x,4)) }, dyi{ (-1) * 200 / sqrt(pow(200,2) + 4 * pow(x,4)) };
	//Построение заданной линии по методу ЦДА.
	while (round(x - dxi) >= x2 && round(y - dyi) <= y2)
	{
		dxi = (2 * pow(x, 2)) / sqrt(pow(200, 2) + 4 * pow(x, 4));
		dyi = ((-1) * 200) / sqrt(pow(200, 2) + 4 * pow(x, 4));
		glVertex2i(round(x), round(y));
		x -= dxi/10;
		y -= dyi/10;
	}
}
void init()
{
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-110, 110, -110, 110);
}
void myReshape(int width, int height)
{
	if (width / height < 1) glViewport(0, 0, width, width);
	else glViewport(0, 0, height, height);
}
void myDisplay()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glViewport(10, 10, 640, 480);

	//Построение клеточек (сетки растра).
	//GLdouble grid_size{ -110 };
	//glColor3f(0.54, 0.53, 1);
	//glBegin(GL_LINES);
	//glLineWidth(1.0);
	//do
	//{
	//	glVertex2f(grid_size, -110); glVertex2f(grid_size, 110); //Вертикальные линии.
	//	glVertex2f(-110, grid_size); glVertex2f(110, grid_size); //Горизонтальные линии.
	//	grid_size += 1.0;
	//} while (grid_size <= 110);
	//glEnd();

	//Построение координатных осей.
	glBegin(GL_LINES);
	glLineWidth(2.0);
	glColor3f(1.0, 0.0, 0.0);
	glVertex2f(-110.0, 0.0); glVertex2f(110.0, 0.0);
	glColor3f(0.0, 0.0, 1.0);
	glVertex2f(0.0, 110.0); glVertex2f(0.0, -110.0);
	glEnd();

	/*РАСТЕРИЗАЦИЯ ИЗОБРАЖЕНИЯ ВЕКТОРА*/
	//Значение параметра.
	GLint a{ 200 };
	//Работа с 1 координатной четвертью. Крайние точки.
	GLint X1_1{ 1 }, Y1_1{ static_cast<GLint>(round(a / (2 * X1_1))) };
	GLint X2_1{ 100 }, Y2_1{ static_cast<GLint>(round(a / (2 * X2_1))) };
	//Работа с 3 координатной четвертью. Крайние точки.
	GLint X1_2{ -1 }, Y1_2{ static_cast<GLint>(round(a / (2 * X1_2))) };
	GLint X2_2{ -100 }, Y2_2{ static_cast<GLint>(round(a / (2 * X2_2))) };

	//Построение гиперболы методами OpenGL (GL_LINE_STRIP).
	glColor3f(1.0, 0.2, 0.5);
	glBegin(GL_LINE_STRIP);
	for (GLint i{ -100 }; i <= -1; i++)
		glVertex2f(i, static_cast<float>(a / (2 * i)));
	glEnd();

	glBegin(GL_LINE_STRIP);
	for (GLint i{ 1 }; i <= 100; i++)
		glVertex2f(i, static_cast<float>(a / (2 * i)));
	glEnd();

	glLineWidth(1.0);
	//Построение гиперболы по упрощенному методу Брозенхейма (Брезенхема) - метод оценочной функции.
	glColor3f(0.4, 0.75, 0.26);
	glBegin(GL_LINE_STRIP);
	drawEvaluationFunctionMethod_1st_quater(X1_1, Y1_1, X2_1, Y2_1);
	glEnd();

	glColor3f(0.4, 0.75, 0.26);
	glBegin(GL_LINE_STRIP);
	drawEvaluationFunctionMethod_3rd_quater(X1_2, Y1_2, X2_2, Y2_2);
	glEnd();

	//Построение гиперболы по методу цифровых дифференциальных анализаторов (ЦДА).
	glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_LINE_STRIP);
	drawDDA_1st_quater(X1_1, Y1_1, X2_1, Y2_1);
	glEnd();

	glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_LINE_STRIP);
	drawDDA_3rd_quater(X1_2, Y1_2, X2_2, Y2_2);
	glEnd();


	glFlush();
}
int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(640, 480);
	glutInitWindowPosition(50, 50);
	glutCreateWindow("Lab_7");
	glutDisplayFunc(myDisplay);
	glutReshapeFunc(myReshape);
	init();
	glutMainLoop();
	return 0;
}
