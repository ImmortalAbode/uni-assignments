#include <gl\glut.h>
#include <math.h>
#include <windows.h>

GLboolean rotate_object{ false }, rotate_light{ false };
GLfloat angle_rotate_y_obj{}, angle_rotate_y_light{};

GLboolean front_face{ true }, back_face{ false };

void init(void)
{
	glClearColor(0.86, 0.58, 0.98, 0.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60, 1, 1, 10);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
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
void myDisplay()
{
	glPushMatrix();

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	gluLookAt(3, 3, 3, 0, 0, 0, 0, 1, 0);

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

	glRotatef(angle_rotate_y_obj, 0.0, 1.0, 0.0);

	glBegin(GL_POLYGON);
	glNormal3f(0.577, 0.577, 0.577);
	glVertex3f(1, 0, 0);
	glVertex3f(0, 1, 0);
	glVertex3f(0, 0, 1);
	glEnd();

	glBegin(GL_POLYGON);
	glNormal3f(0, 0, -1);
	glVertex3f(0, 0, 0);
	glVertex3f(0, 1, 0);
	glVertex3f(1, 0, 0);
	glEnd();

	glBegin(GL_POLYGON);
	glNormal3f(-1, 0, 0);
	glVertex3f(0, 0, 0);
	glVertex3f(0, 0, 1);
	glVertex3f(0, 1, 0);
	glEnd();

	glBegin(GL_POLYGON);
	glNormal3f(0, -1, 0);
	glVertex3f(1, 0, 0);
	glVertex3f(0, 0, 1);
	glVertex3f(0, 0, 0);
	glEnd();

	glPopMatrix();


	glDisable(GL_LIGHTING);

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
	glutCreateWindow("Lab_4");
	glutDisplayFunc(myDisplay);
	glutReshapeFunc(myReshape);
	glutKeyboardFunc(KeyBoardEvents);
	glutIdleFunc(myIdle);
	init();
	glutMainLoop();
}
