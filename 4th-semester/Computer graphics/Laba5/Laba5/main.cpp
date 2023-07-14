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

GLboolean rotate_object{ false }, rotate_light{ false };
GLfloat angle_rotate_y_obj{}, angle_rotate_y_light{};

//GLboolean front_face{ true }, back_face{ false };

GLuint list{};
void figure()
{
	AUX_RGBImageRec* image_1{ auxDIBImageLoad(L"texture_1.bmp") };
	AUX_RGBImageRec* image_2{ auxDIBImageLoad(L"texture_2.bmp") };
	AUX_RGBImageRec* image_3{ auxDIBImageLoad(L"texture_3.bmp") };

	GLuint textures[3]{};
	GLuint texture_1{};
	GLuint texture_2{ 1 };
	GLuint texture_3{ 2 };

	glGenTextures(3, textures);

	glBindTexture(GL_TEXTURE_2D, texture_1);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image_1->sizeX, image_1->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, image_1->data);

	glBindTexture(GL_TEXTURE_2D, texture_2);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image_2->sizeX, image_2->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, image_2->data);

	glBindTexture(GL_TEXTURE_2D, texture_3);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image_3->sizeX, image_3->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, image_3->data);

	list = glGenLists(1);
	glNewList(list, GL_COMPILE);

	GLfloat MyAmbient[] = { 0.2125, 0.1275, 0.054, 1 };
	GLfloat MyDiffuse[] = { 0.714, 0.4284, 0.18144, 1 };
	GLfloat MySpecular[] = { 0.393548, 0.271906, 0.166721, 1 };
	GLfloat MyShininess[] = { 25.6 };
	glMaterialfv(GL_FRONT, GL_AMBIENT, MyAmbient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, MyDiffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, MySpecular);
	glMaterialfv(GL_FRONT, GL_SHININESS, MySpecular);

	glBindTexture(GL_TEXTURE_2D, texture_1);
	glBegin(GL_POLYGON);
	glNormal3f(0, -1, 0);
	glTexCoord2f(0, 0); glVertex3f(0, 0, 0);
	glTexCoord2f(1, 0); glVertex3f(1, 0, 0);
	glTexCoord2f(1, 1); glVertex3f(1, 0, 1);
	glTexCoord2f(0, 1); glVertex3f(0, 0, 1);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, texture_2);
	glBegin(GL_POLYGON);
	glNormal3f(0, 0, -1);
	glTexCoord2f(0, 0); glVertex3f(0, 0, 0);
	glTexCoord2f(0, 1); glVertex3f(1, 1, 0);
	glTexCoord2f(1, 1); glVertex3f(1, 0, 0);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, texture_2);
	glBegin(GL_POLYGON);
	glNormal3f(0, 0, 1);
	glTexCoord2f(1, 0); glVertex3f(0, 0, 1);
	glTexCoord2f(1, 1); glVertex3f(1, 0, 1);
	glTexCoord2f(0, 1); glVertex3f(1, 1, 1);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, texture_3);
	glBegin(GL_POLYGON);
	glNormal3f(1, 0, 0);
	glTexCoord2f(0, 0); glVertex3f(1, 0, 0);
	glTexCoord2f(0, 1); glVertex3f(1, 1, 0);
	glTexCoord2f(1, 1); glVertex3f(1, 1, 1);
	glTexCoord2f(1, 0); glVertex3f(1, 0, 1);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, texture_1);
	glBegin(GL_POLYGON);
	glNormal3f(-0.707, 0.707, 0);
	glTexCoord2f(0, 0); glVertex3f(0, 0, 0);
	glTexCoord2f(1, 0); glVertex3f(0, 0, 1);
	glTexCoord2f(1, 1); glVertex3f(1, 1, 1);
	glTexCoord2f(0, 1); glVertex3f(1, 1, 0);
	glEnd();

	glEndList();
}
void init(void)
{
	glClearColor(0.93, 0.44, 0.91, 0.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60, 1, 1, 10);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	figure();
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_NORMALIZE);
}
void KeyBoardEvents(unsigned char key, int x, int y)
{
	if (key == static_cast<unsigned char>('o'))
		rotate_object == true ? rotate_object = false : rotate_object = true;
	if (key == static_cast<unsigned char>('l'))
		rotate_light == true ? rotate_light = false : rotate_light = true;
	if (key == static_cast<unsigned char>('f'))
	{
		glCullFace(GL_BACK);
		glEnable(GL_CULL_FACE);
	}
	if (key == static_cast<unsigned char>('b'))
	{
		glCullFace(GL_FRONT);
		glEnable(GL_CULL_FACE);
	}
} 
void MouseEvents(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_UP)
	{
		glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	}
	if (button == GLUT_RIGHT_BUTTON && state == GLUT_UP)
	{
		glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	}
}
void myDisplay()
{
	glPushMatrix();

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	gluLookAt(5, 3, 3, 0, 0, 0, 0, 1, 0);

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


	glPushMatrix();

	glEnable(GL_TEXTURE_2D);
	glRotatef(angle_rotate_y_obj, 0.0, 1.0, 0.0);
	glCallList(list);

	glPopMatrix();

	glDisable(GL_LIGHTING);
	glDisable(GL_TEXTURE_2D);

	glBegin(GL_LINES);
	glColor3f(1, 0, 0); glVertex3f(0, 0, 0); glVertex3f(3, 0, 0);
	glColor3f(0, 1, 0); glVertex3f(0, 0, 0); glVertex3f(0, 3, 0);
	glColor3f(0, 0, 1); glVertex3f(0, 0, 0); glVertex3f(0, 0, 3);
	glEnd();

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
	if (rotate_light)
	{
		angle_rotate_y_light += 1;
		if (angle_rotate_y_light > 360) angle_rotate_y_light = 0;
	}
	if (rotate_object)
	{
		angle_rotate_y_obj += 1;
		if (angle_rotate_y_obj > 360) angle_rotate_y_obj = 0;
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
	glutCreateWindow("Lab_5");
	glutDisplayFunc(myDisplay);
	glutReshapeFunc(myReshape);
	glutKeyboardFunc(KeyBoardEvents);
	glutMouseFunc(MouseEvents);
	glutIdleFunc(myIdle);
	init();
	glutMainLoop();
	return 0;
}
