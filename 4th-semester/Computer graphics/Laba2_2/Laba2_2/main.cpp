#include <GL/glut.h>
#include <stdlib.h>
#include <windows.h>

GLfloat R{ 640.0 / 480 }; //Форматное соотношение.
GLfloat w{ 40 };  //Ширина мирового окна.
GLfloat h{}; //Высота мирового окна.
GLfloat l{}, r{}, b{}, t{}; //Параметры мирового окна.
GLfloat f{ 45.0 }; //Угол вращения.
GLfloat trans{ 10.0 }; //Для матрицы смещения.

void init(void)
{
	//h = 30, l = - 40, r = 40, b = -30, t = 30.
	h = w / R; l = -w; r = w; b = -h; t = h; //Расчет параметров мирового окна.
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

void showAxisFig1(void) //Прорисовка осей Fig1.
{
	glColor3f(1.0, 1.0, 0.0);
	glBegin(GL_LINES);
	glVertex2f(0, 0);
	glVertex2f(0, 10);
	glVertex2f(0, 0);
	glVertex2f(15, 0);
	glEnd();
}

void fig0(void)
{
	//Прорисовка начального квадрата.
	glColor3f(0.0, 1.0, 0.0);
	glBegin(GL_LINE_LOOP);
	glVertex2f(-10.0, 10.0);
	glVertex2f(10.0, 10.0);
	glVertex2f(10.0, -10.0);
	glVertex2f(-10.0, -10.0);
	glEnd();
}

void fig1(void)
{
	//Прорисовка смещающегося прямоугольника.
	glColor3f(0.0, 1.0, 0.0);
	glBegin(GL_LINE_LOOP);
	glVertex2f(0.0, 0.0);
	glVertex2f(10.0, 0.0);
	glVertex2f(10.0, 5.0);
	glVertex2f(0.0, 5.0);
	glEnd();
}

void scene(void) //Вращение фигуры с прорисовкой Fig1.
{
	glClear(GL_COLOR_BUFFER_BIT);
	showAxis();

	fig0();

	glPushMatrix();
	if (f == 45.0) glTranslatef(trans, trans, 0.0);
	else if (f == 135) glTranslatef(-trans, trans, 0.0);
	else if (f == 225) glTranslatef(-trans, -trans, 0.0);
	else glTranslatef(trans, -trans, 0.0);

	glRotatef(f, 0.0, 0.0, 1.0);
	if (f == 45 || f == 315) glScalef(1.0, 1.0, 1.0);
	else glScalef(1.0, -1.0, 1.0);

	fig1();
	showAxisFig1();
	
	glPopMatrix();

	glFlush();
	glutSwapBuffers();
	
	f += 90; if (f > 360) f = 45;
	Sleep(400);
}

void main(int argc, char** argv) //Работа программы.
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(640, 480);
	glutInitWindowPosition(20, 20);
	glutCreateWindow("OpenGL_Lab2_2");
	glutReshapeFunc(reshape);
	glutDisplayFunc(scene);
	glutIdleFunc(scene);
	init();
	glutMainLoop();
}
