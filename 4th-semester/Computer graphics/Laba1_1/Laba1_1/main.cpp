#include <GL/glut.h>
#include <math.h>
void init();
void draw();

void main(int argc, char** argv) //Главная функция
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(640, 480);
	glutInitWindowPosition(50, 50);
	glutCreateWindow("MyGlutProgLab1");
	init();
	glutDisplayFunc(draw);
	glutMainLoop();
}

void init() //Функция инициализации
{
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-6.0, 6.0, -6.0, 6.0);
}
void draw() //Функция рисования
{
	glClear(GL_COLOR_BUFFER_BIT);
	glViewport(0, 0, 480, 480);

	//Прорисовка поля клеточек для наглядного графика
	glColor3f(0.5, 0.5, 1.0);
	glLineWidth(1);
	glBegin(GL_LINES);
	for (GLint i{ -6 }; i <= 6; i++)
	{
		glVertex2f(i, 6.0); glVertex2f(i, -6.0);
		glVertex2f(-6.0, i); glVertex2f(6.0, i);
	}
	glEnd();

	//Прорисовка осей координат
	glColor3f(0.0, 0.0, 1.0);
	glLineWidth(2);
	glBegin(GL_LINE_STRIP);
	glVertex2f(0.0, 6.0); glVertex2f(0.0, -6.0);
	glEnd();
	glBegin(GL_LINE_STRIP);
	glVertex2f(-6.0, 0.0); glVertex2f(6.0, 0.0);
	glEnd();

	//Прорисовка самого графика
	glColor3f(0.0, 0.0, 0.0);
	glLineWidth(1);
	glBegin(GL_LINE_STRIP);
	for (GLdouble t{ -6 }; t <= 6; t += 0.05)
	{
		glVertex2f(t, sin(2 * t) * cos(3 * t));
	}
	glEnd();

	glFlush();

}
