#include <iostream>
#include <gl\glut.h>
#include <atlbase.h>
#include <atlconv.h>
#include <string>
#include <cmath>
#include <math.h>
#include <windows.h>
#include <stdlib.h>

#include <C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Tools\\MSVC\\14.31.31103\\include\\GL\\glaux.h>
#pragma comment(lib, "C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Tools\\MSVC\\14.31.31103\\lib\\x64\\GLAUX.lib")
#pragma comment(lib, "legacy_stdio_definitions.lib")

GLboolean rotate_object_clockwise{ false }, rotate_light_clockwise{ false };
GLboolean rotate_object_against{ false }, rotate_light_against{ false };
GLfloat angle_rotate_y_obj{}, angle_rotate_y_light{};
GLboolean show_axis{ true };

//Переменные, изменяющие положение наблюдателя в зависимости от соответствующих клавиатурных событий.
GLdouble eye_x{ 4 }, eye_y{ 2 }, eye_z{ 4 };
//Переменные для смещения наблюдателя вдоль сферы вниз, вверх, влево, вправо.
int t_v{ 45 }, t_g{ 45 };//Радианы.
const double M_PI{ acos(-1) }; //Число pi.

//Дисплейный список.
GLuint list{};
//Функции смещения наблюдателя.
double sign_eye(const double& eye_coord) //Знак прибавки к соответствующей координате положения наблюдателя.
{
	return (eye_coord >= 0) ? 1 : -1;
}
//Соотношение координат для сохранения пропорций по координатам положения наблюдателя.
double ratio_coords(const double& first_coord, const double& second_coord)
{
	if (first_coord == second_coord)
		return 1;
	else
		return first_coord / second_coord;
}
/*Учет положения наблюдателя при перемещении вокруг объекта вдоль сферы вниз, вверх.влево, вправо.*/
//По окружности.
void circle_rt(double& a, double& b, int& t, int ord) 
{
	double r{ sqrt(double(a * a) + double(b * b)) };
	if (t == 360 || t == -360) t = 0;
	else t += ord * 5;
	a = r * sin((t * M_PI) / 180);
	b = r * cos((t * M_PI) / 180);
}
//По сфере.
void sphere_rt(double& x, double& y, double& z, int& t_v, int& t_g, int ord) 
{
	double r{ sqrt(double(x * x) + double(z * z)) };
	circle_rt(y, r, t_v, ord);
	x = r * sin((t_g * M_PI) / 180);
	z = r * cos((t_g * M_PI) / 180);
}
//Источник света.
void draw_light()
{
	glPushMatrix();
	glRotatef(angle_rotate_y_light, 0.0, 1.0, 0.0);
	glBegin(GL_LINES);
	glColor3f(1, 1, 1); glVertex3f(1, 2, 2); glVertex3f(0.0, 0.0, 0.0);
	glEnd();
	glPointSize(20.0);
	glBegin(GL_POINTS);
	glColor3f(1.0, 1.0, 1.0);
	glVertex3f(1.0, 2.0, 2.0);
	glEnd();

	GLfloat myLightPosition[] = { 1.0, 2.0, 2.0, 1.0 };
	glLightfv(GL_LIGHT0, GL_POSITION, myLightPosition);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	glPopMatrix();
}
void getNormalForPolygon(const float& x_1, const float& y_1, const float& z_1, const float& x_2, const float& y_2, const float& z_2, const float& x_3, const float& y_3, const float& z_3, const bool& minus)
{
	double ax{ x_2 - x_1 };
	double ay{ y_2 - y_1 };
	double az{ z_2 - z_1 };
	double bx{ x_3 - x_1 };
	double by{ y_3 - y_1 };
	double bz{ z_3 - z_1 };

	if (minus) glNormal3f(ay * bz - az * by, az * bx - ax * bz, -(ax * by - ay * bx));
	else glNormal3f(ay * bz - az * by, az * bx - ax * bz, ax * by - ay * bx);
}
void figure()
{
	AUX_RGBImageRec* image_1{ auxDIBImageLoad(L"texture_background.bmp") };

	GLuint textures[1]{};
	GLuint texture_1{};

	glGenTextures(1, textures);

	glBindTexture(GL_TEXTURE_2D, texture_1);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image_1->sizeX, image_1->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, image_1->data);

	list = glGenLists(1);
	glNewList(list, GL_COMPILE);

	GLfloat MyAmbient_1[] = { 0.19225, 0.19225, 0.19225, 1 };
	GLfloat MyDiffuse_1[] = { 0.50754, 0.50754, 0.50754, 1 };
	GLfloat MySpecular_1[] = { 0.0001, 0.0001, 0.0001, 1 };
	GLfloat MyShininess_1[] = { 51.2 };
	glMaterialfv(GL_FRONT, GL_AMBIENT, MyAmbient_1);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, MyDiffuse_1);
	glMaterialfv(GL_FRONT, GL_SPECULAR, MySpecular_1);
	glMaterialfv(GL_FRONT, GL_SHININESS, MyShininess_1);

	//Кружок с текстурой на зданем фоне.
	//Внутренняя полная окружность.
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture_1);
	glBegin(GL_POLYGON);
	glNormal3f(0, 0, 1);
	glTexCoord2f(0.6f, 0.6f); glVertex3f(0.0f, 0.0f, 0.0f);
	for (GLint angle{}; angle <= 360; angle++)
	{
		double theta{ angle * acos(-1) / 180 };
		if (cos(theta) > 0 && sin(theta) > 0) 
			glTexCoord2f(0.5 + cos(theta) / 2, 0.5 + sin(theta) / 2); 
		else if (cos(theta) < 0 && sin(theta) > 0)
			glTexCoord2f(0.5 - cos(theta) / 2, 0.5 + sin(theta) / 2);
		else if (cos(theta) < 0 && sin(theta) < 0)
			glTexCoord2f(0.5 - cos(theta) / 2, 0.5 - sin(theta) / 2);
		else if (cos(theta) > 0 && sin(theta) < 0)
			glTexCoord2f(0.5 + cos(theta) / 2, 0.5 - sin(theta) / 2);
		glVertex3f(0.8f * cos(theta), 0.8f * sin(theta), 0.0f);
	}
	glEnd();
	glDisable(GL_TEXTURE_2D);

	GLfloat MyAmbient_2[] = { 0.19225, 0.19225, 0.19225, 1 };
	GLfloat MyDiffuse_2[] = { 0.50754, 0.50754, 0.50754, 1 };
	GLfloat MySpecular_2[] = { 0.508273, 0.508273, 0.508273, 1 };
	GLfloat MyShininess_2[] = { 51.2 };
	glMaterialfv(GL_FRONT, GL_AMBIENT, MyAmbient_2);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, MyDiffuse_2);
	glMaterialfv(GL_FRONT, GL_SPECULAR, MySpecular_2);
	glMaterialfv(GL_FRONT, GL_SHININESS, MyShininess_2);

	//Кружок с текстурой на зданем фоне.
	//Связь окружности верхней и внешней боковой.
	for (GLint angle{}; angle <= 359; angle++)
	{
		glBegin(GL_POLYGON);

		double theta_1{ angle * acos(-1) / 180 };
		double theta_2{ (angle + 1) * acos(-1) / 180 };

		getNormalForPolygon(cos(theta_1), sin(theta_1), 0.1f, 1.2f * cos(theta_1), 1.2f * sin(theta_1), -0.1f, 1.2f * cos(theta_2), 1.2f * sin(theta_2), -0.1f, false);
		glVertex3f(cos(theta_1), sin(theta_1), 0.1f);
		glVertex3f(1.2f * cos(theta_1), 1.2f * sin(theta_1), -0.1f);
		glVertex3f(1.2f * cos(theta_2), 1.2f * sin(theta_2), -0.1f);
		glVertex3f(cos(theta_2), sin(theta_2), 0.1f);
		glEnd();
	}

	//Связь окружности внешней боковой и задней.
	for (GLint angle{}; angle <= 359; angle++)
	{
		glBegin(GL_POLYGON);

		double theta_1{ angle * acos(-1) / 180 };
		double theta_2{ (angle + 1) * acos(-1) / 180 };

		getNormalForPolygon(cos(theta_2), sin(theta_2), -0.2f, 1.2 * cos(theta_2), 1.2 * sin(theta_2), -0.1f, cos(theta_1), sin(theta_1), -0.2f, false);
		glVertex3f(cos(theta_2), sin(theta_2), -0.2f);
		glVertex3f(1.2 * cos(theta_2), 1.2 * sin(theta_2), -0.1f);
		glVertex3f(1.2 * cos(theta_1), 1.2 * sin(theta_1), -0.1f);
		glVertex3f(cos(theta_1), sin(theta_1), -0.2f);
		glEnd();
	}

	//Задняя полная окружность.
	glBegin(GL_POLYGON);
	glNormal3f(0, 0, -1);
	for (GLint angle{ 360 }; angle >= 0; angle--)
	{
		double theta{ angle * acos(-1) / 180 };
		glVertex3f(1.0f * cos(theta), 1.0f * sin(theta), -0.2f);
	}
	glEnd();

	GLfloat MyAmbient_3[] = { 0.24725, 0.1995, 0.0745, 1 };
	GLfloat MyDiffuse_3[] = { 0.75164, 0.60648, 0.22648, 1 };
	GLfloat MySpecular_3[] = { 0.628281, 0.555802, 0.366065, 1 };
	GLfloat MyShininess_3[] = { 51.2 };
	glMaterialfv(GL_FRONT, GL_AMBIENT, MyAmbient_3);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, MyDiffuse_3);
	glMaterialfv(GL_FRONT, GL_SPECULAR, MySpecular_3);
	glMaterialfv(GL_FRONT, GL_SHININESS, MyShininess_3);

	//Кружок с текстурой на заднем фоне.
	//Связь окружности верхней и внутренней боковой.
	for (GLint angle{}; angle <= 359; angle++)
	{
		glBegin(GL_POLYGON);

		double theta_1{ angle * acos(-1) / 180 };
		double theta_2{ (angle + 1) * acos(-1) / 180 };

		getNormalForPolygon(0.8 * cos(theta_1), 0.8 * sin(theta_1), 0.0f, cos(theta_1), sin(theta_1), 0.1f, 0.8 * cos(theta_2), 0.8 * sin(theta_2), 0.0f, false);
		glVertex3f(0.8 * cos(theta_1), 0.8 * sin(theta_1), 0.0f);
		glVertex3f(cos(theta_1), sin(theta_1), 0.1f);
		glVertex3f(cos(theta_2), sin(theta_2), 0.1f);
		glVertex3f(0.8 * cos(theta_2), 0.8 * sin(theta_2), 0.0f);
		glEnd();
	}

	/*Буква L.*/
	//Внешняя часть.
	glBegin(GL_POLYGON);
	glNormal3f(0, 0, 10);
	glVertex3f(-0.2, 1.4, 0.3);
	glVertex3f(-1.0, 1.4, 0.3);
	glVertex3f(-0.8, 1.2, 0.3);
	glVertex3f(-0.2, 1.2, 0.3);
	glEnd();

	glBegin(GL_POLYGON);
	glNormal3f(0, 0, 10);
	glVertex3f(-0.2, 1.2, 0.3);
	glVertex3f(-0.8, 1.2, 0.3);
	glVertex3f(-0.8, -1.0, 0.3);
	glVertex3f(-0.2, -1.0, 0.3);
	glEnd();

	glBegin(GL_POLYGON);
	glNormal3f(0, 0, 10);
	glVertex3f(-0.8, -1.0, 0.3);
	glVertex3f(-1.0, -1.4, 0.3);
	glVertex3f(1.0, -1.4, 0.3);
	glVertex3f(1.2, -1.0, 0.3);
	glVertex3f(-0.2, -1.0, 0.3);
	glEnd();

	//Придание толщины.
	//Левый бок.
	glBegin(GL_POLYGON);
	getNormalForPolygon(-1.0, 1.4, 0.3, -0.8, -1.0, 0.1, -1.0, -1.4, 0.1, true);
	glVertex3f(-1.0, -1.4, 0.3);
	glVertex3f(-0.8, -1.0, 0.3);
	glVertex3f(-0.8, -1.0, 0.1);
	glVertex3f(-1.0, -1.4, 0.1);
	glEnd();

	glBegin(GL_POLYGON);
	getNormalForPolygon(-0.8, 1.2, 0.3, -0.8, 1.2, 0.1, -0.8, -1.0, 0.3, false);
	glVertex3f(-0.8, 1.2, 0.3);
	glVertex3f(-0.8, 1.2, 0.1);
	glVertex3f(-0.8, -1.0, 0.1);
	glVertex3f(-0.8, -1.0, 0.3);
	glEnd();

	glBegin(GL_POLYGON);
	getNormalForPolygon(-1.0, 1.4, 0.3, -1.0, 1.4, 0.1, -0.8, 1.2, 0.3, false);
	glVertex3f(-1.0, 1.4, 0.3);
	glVertex3f(-1.0, 1.4, 0.1);
	glVertex3f(-0.8, 1.2, 0.1);
	glVertex3f(-0.8, 1.2, 0.3);
	glEnd();

	//Верх.
	glBegin(GL_POLYGON);
	getNormalForPolygon(-0.2, 1.4, 0.3, -0.2, 1.4, 0.1, -1.0, 1.4, 0.3, false);
	glVertex3f(-0.2, 1.4, 0.3);
	glVertex3f(-0.2, 1.4, 0.1);
	glVertex3f(-1.0, 1.4, 0.1);
	glVertex3f(-1.0, 1.4, 0.3);
	glEnd();

	//Правый бок.
	glBegin(GL_POLYGON);
	//getNormalForPolygon(-0.2, 1.4, 0.1, -0.2, 1.4, 0.3, -0.2, -1.0, 0.1, false);
	glNormal3f(5.0, -3.0, 0.0);
	glVertex3f(-0.2, 1.4, 0.1);
	glVertex3f(-0.2, 1.4, 0.3);
	glVertex3f(-0.2, -1.0, 0.3);
	glVertex3f(-0.2, -1.0, 0.1);
	glEnd();

	glBegin(GL_POLYGON);
	//getNormalForPolygon(-0.2, -1.0, 0.1, -0.2, -1.0, 0.3, 1.2, -1.0, 0.1, false);
	glNormal3f(2.0, 1.0, 10.0);
	glVertex3f(-0.2, -1.0, 0.1);
	glVertex3f(-0.2, -1.0, 0.3);
	glVertex3f(1.2, -1.0, 0.3);
	glVertex3f(1.2, -1.0, 0.1);
	glEnd();

	glBegin(GL_POLYGON);
	getNormalForPolygon(1.2, -1.0, 0.3, 1.0, -1.4, 0.3, 1.2, -1.0, 0.1, false);
	glVertex3f(1.2, -1.0, 0.3);
	glVertex3f(1.0, -1.4, 0.3);
	glVertex3f(1.0, -1.4, 0.1);
	glVertex3f(1.2, -1.0, 0.1);
	glEnd();

	//Низ.
	glBegin(GL_POLYGON);
	getNormalForPolygon(1.0, -1.4, 0.3, -1.0, -1.4, 0.3, 1.0, -1.4, 0.1, true);
	glVertex3f(1.0, -1.4, 0.3);
	glVertex3f(-1.0, -1.4, 0.3);
	glVertex3f(-1.0, -1.4, 0.1);
	glVertex3f(1.0, -1.4, 0.1);
	glEnd();

	//Задняя часть.
	glBegin(GL_POLYGON);
	glNormal3f(0, 0, -10);
	glVertex3f(-0.2, 1.4, 0.1);
	glVertex3f(-0.2, 1.2, 0.1);
	glVertex3f(-0.8, 1.2, 0.1);
	glVertex3f(-1.0, 1.4, 0.1);
	glEnd();

	glBegin(GL_POLYGON);
	glNormal3f(0, 0, -10);
	glVertex3f(-0.2, 1.2, 0.1);
	glVertex3f(-0.2, -1.0, 0.1);
	glVertex3f(-0.8, -1.0, 0.1);
	glVertex3f(-0.8, 1.2, 0.1);
	glEnd();

	glBegin(GL_POLYGON);
	glNormal3f(0, 0, -10);
	glVertex3f(-0.8, -1.0, 0.1);
	glVertex3f(-0.2, -1.0, 0.1);
	glVertex3f(1.2, -1.0, 0.1);
	glVertex3f(1.0, -1.4, 0.1);
	glVertex3f(-1.0, -1.4, 0.1);
	glEnd();


	glEndList();
}
void init(void)
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60, 1, 1, 100);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	figure();
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_NORMALIZE);
}
void KeyBoardEvents(unsigned char key, int x, int y)
{
	if (key == static_cast<unsigned char>('u'))
		show_axis == true ? show_axis = false : show_axis = true;
	if (key == static_cast<unsigned char>('o'))
	{
		rotate_object_clockwise == true ? rotate_object_clockwise = false : rotate_object_clockwise = true;
		rotate_object_against = false;
	}
	if (key == static_cast<unsigned char>('i'))
	{
		rotate_object_against == true ? rotate_object_against = false : rotate_object_against = true;
		rotate_object_clockwise = false;
	}
	if (key == static_cast<unsigned char>('l'))
	{
		rotate_light_clockwise == true ? rotate_light_clockwise = false : rotate_light_clockwise = true;
		rotate_light_against = false;
	}
	if (key == static_cast<unsigned char>('k'))
	{
		rotate_light_against == true ? rotate_light_against = false : rotate_light_against = true;
		rotate_light_clockwise = false;
	}
	//Отдаление.
	if (key == '0' && eye_y != 0) 
	{
		eye_x += 0.1 * sign_eye(eye_x) * abs(ratio_coords(eye_x, eye_y));
		eye_z += 0.1 * sign_eye(eye_z) * abs(ratio_coords(eye_z, eye_y));
		eye_y += 0.1 * sign_eye(eye_y);
	}
	//Приближение (нельзя приблизиться меньше, чем на значение '1' по модулю каждой координаты положения наблюдателя).
	if (key == '1' && eye_y != 0 && !(-1 < eye_x && eye_x < 1 &&
						-1 < eye_y && eye_y < 1 &&
						-1 < eye_z && eye_z < 1))
	{
		eye_x -= 0.1 * sign_eye(eye_x) * abs(ratio_coords(eye_x, eye_y));
		eye_z -= 0.1 * sign_eye(eye_z) * abs(ratio_coords(eye_z, eye_y));
		eye_y -= 0.1 * sign_eye(eye_y);
	}
	//Поворот вниз (нельзя переместиться больше, чем на 90 градусов).
	if (key == '2' && (-90 < t_v))
	{
		sphere_rt(eye_x, eye_y, eye_z, t_v, t_g, -1);
	}
	//Поворот влево.
	if (key == '4') 
	{
		circle_rt(eye_x, eye_z, t_g, -1);
	}
	//Поворот вправо.
	if (key == '6') 
	{
		circle_rt(eye_x, eye_z, t_g, +1);
	}
	//Поворот вверх (нельзя переместиться больше, чем на 90 градусов).
	if (key == '8' && (t_v < 90))
	{
		sphere_rt(eye_x, eye_y, eye_z, t_v, t_g, 1);
	}
}
void myDisplay()
{
	glPushMatrix();

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	gluLookAt(eye_x, eye_y, eye_z, 0, 0, 0, 0, 1, 0);

	draw_light();

	glPushMatrix();
	glRotatef(angle_rotate_y_obj, 0.0, 1.0, 0.0);
	glCallList(list);
	glPopMatrix();

	glDisable(GL_LIGHTING);

	if (show_axis)
	{
		glBegin(GL_LINES);
		glColor3f(1, 0, 0); glVertex3f(0, 0, 0); glVertex3f(3, 0, 0);
		glColor3f(0, 1, 0); glVertex3f(0, 0, 0); glVertex3f(0, 3, 0);
		glColor3f(0, 0, 1); glVertex3f(0, 0, 0); glVertex3f(0, 0, 3);
		glEnd();
	}

	glPopMatrix();

	glutSwapBuffers();
}
void myReshape(int width, int height)
{
	if (width / height < 1) glViewport(0, 0, width, width);
	else glViewport(0, 0, height, height);
}
void myIdle()
{
	if (rotate_object_clockwise)
	{
		angle_rotate_y_obj += 1;
		if (angle_rotate_y_obj > 360) angle_rotate_y_obj = 0;
	}
	if (rotate_object_against)
	{
		angle_rotate_y_obj -= 1;
		if (angle_rotate_y_obj < 0) angle_rotate_y_obj = 360;
	}
	if (rotate_light_clockwise)
	{
		angle_rotate_y_light += 1;
		if (angle_rotate_y_light > 360) angle_rotate_y_light = 0;
	}
	if (rotate_light_against)
	{
		angle_rotate_y_light -= 1;
		if (angle_rotate_y_light < 0) angle_rotate_y_light = 360;
	}
	glutPostRedisplay();
	Sleep(25);
}
int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(800, 800);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Logo_work");
	glutDisplayFunc(myDisplay);
	glutReshapeFunc(myReshape);
	glutKeyboardFunc(KeyBoardEvents);
	glutIdleFunc(myIdle);
	init();
	glutMainLoop();
	return 0;
}
