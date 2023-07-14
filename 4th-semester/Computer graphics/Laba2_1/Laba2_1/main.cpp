#include <GL/glut.h>
#include <stdlib.h>
#include <windows.h>

GLfloat R{ 640.0 / 480 }; //Форматное соотношение.
GLfloat w{ 40 };  //Ширина мирового окна.
GLfloat h{}; //Высота мирового окна.
GLfloat l{}, r{}, b{}, t{}; //Параметры мирового окна.
GLfloat f{ 30.0 }; //Угол вращения.
GLfloat scale{ 1.0 }; //Для пульсации изменение размера прорисовки.
bool flag{ false }; //Пульсация.

void init(void)
{
	//h = 30, l = - 26 2/3, r = 26 2/3, b = -20, t = 20.
	h = w / R; l = -w / 1.5; r = w / 1.5; b = -h / 1.5; t = h / 1.5; //Расчет параметров мирового окна.
	glClearColor(0.66, 0.38, 0.72, 0.0);
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(l, r, b, t);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void reshape(GLsizei W, GLsizei H) //Сохранение масштаба работы программы.
{
	if (R > static_cast<float>(W / H)) glViewport(0, 0, W, W / R); //0, 0, 640, 480.
	else glViewport(0, 0, H * R, H); //0, 0, 640, 480.
}

void showAxis(void) //Прорисовка осей.
{
	glColor3f(0.1, 0.04, 0.78);
	glBegin(GL_LINES);
	glVertex2f(0, 0);
	glVertex2f(0, t);
	glVertex2f(0, 0);
	glVertex2f(r, 0);
	glEnd();
}

void showAxisFig1(void) //Прорисовка осей вращающегося прямоугольника.
{
	glColor3f(1.0, 1.0, 0.0);
	glBegin(GL_LINES);
	glVertex2f(0, 0);
	glVertex2f(0, 15 / scale);
	glVertex2f(0, 0);
	glVertex2f(15 / scale, 0);
	glEnd();
}

void fig0(void)
{
	//Прорисовка начальной точки.
	glColor3f(0.0, 1.0, 0.0);
	glPointSize(4);
	glBegin(GL_POINTS);
	glVertex2f(0.0, 0.0);
	glEnd();

	//Прорисовка начального прямоугольника.
	glColor3f(0.0, 1.0, 0.0);
	glBegin(GL_LINE_LOOP);
	if (scale == 1) //В зависимости от масштаба приводим координаты фигуры в правильное значение.
	{
		glVertex2f(5.0, 0.0);
		glVertex2f(5.0, 5.0);
		glVertex2f(7.5, 5.0);
		glVertex2f(7.5, 0.0);
	}
	else if (scale == 2)
	{
		glVertex2f(4.5 / scale, -0.5 / scale);
		glVertex2f(8.0 / scale, -0.5 / scale);
		glVertex2f(8.0 / scale, 5.5 / scale);
		glVertex2f(4.5 / scale, 5.5 / scale);
	}
	else
	{
		glVertex2f(2.5 / scale, -2.5 / scale);
		glVertex2f(2.5 / scale, 7.5 / scale);
		glVertex2f(10.0 / scale, 7.5 / scale);
		glVertex2f(10 / scale, -2.5 / scale);
	}
	glEnd();
}

void scene(void) //Вращение фигуры с прорисовкой Fig0.
{
	glClear(GL_COLOR_BUFFER_BIT);
	showAxis();

	glPushMatrix();

	glTranslatef(4.5, 8.0, 0.0);
	glRotatef(f, 0.0, 0.0, 1.0);
	glScalef(scale, -scale, 1.0);
	fig0();
	showAxisFig1();

	glPopMatrix();

	glFlush();
	glutSwapBuffers();

	f += 15; if (f == 360) f = 0;
	if (!flag) scale += 1;
	else scale -= 1;
	if (scale == 1 || scale == 3) flag = !flag;
	Sleep(200);
}

void main(int argc, char** argv) //Работа программы.
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(640, 480);
	glutInitWindowPosition(20, 20);
	glutCreateWindow("OpenGL_Lab2_1");
	glutReshapeFunc(reshape);
	glutDisplayFunc(scene);
	glutIdleFunc(scene);
	init();
	glutMainLoop();
}
