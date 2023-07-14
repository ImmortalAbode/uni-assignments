#include <gl\glut.h>
#include <math.h>
#include <windows.h>

//���������� ��� ��������������� ����������.
GLfloat x_size_last{ 1 }, x_size_next{ 1 };
//���������� ��� �������� ���������� � ����������� ������������ ���� ��� ����� ����������.
GLboolean flag_rotate_xy{ false }, no_rotate{ true };
//���������� ��� �������������� ���������� ����� ��� �.
GLboolean inc_size_x{ false }, dec_size_x{ false };
//���� �������� ����������.
GLfloat angle_rotate_xy{};

void init(void)
{
	glClearColor(0.86, 0.58, 0.98, 0.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(90, 1, 1, 10);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}
//������� ��� "������" ������� ���������� (������������ �������).
void KeyBoardEvents(unsigned char key, int x, int y)
{
	if (key == static_cast<unsigned char>('x') && (x_size_next + 0.1) <= 1.7)
	{
		inc_size_x = true;
	}
	else if (key == static_cast<unsigned char>('X') && (x_size_next - 0.1) >= 0.3)
	{
		dec_size_x = true;
	}
}
//������� ��� "������" ������� ���� ("�������" �������).
void MouseEvents(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_UP)
	{
		flag_rotate_xy = true;
		no_rotate = false;
	}
	else if (button == GLUT_RIGHT_BUTTON && state == GLUT_UP)
	{
		flag_rotate_xy = false;
		no_rotate = true;
	}
}
void myDisplay()
{
	glPushMatrix(); //��������� VM = 1.
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);//�������� �������� ������� ��� ���������� �����������.
	//������ VM = Fwe * (������� ��� ���������� �����, ������� �����������, ����).
	gluLookAt(6, 2, 3, 0, 0, 0, 0, 1, 0);
	GLfloat myLightPosition[] = { 3.0, 3.0, 3.0, 1.0 }; //�������� ����� � CKw.
	glLightfv(GL_LIGHT0, GL_POSITION, myLightPosition); //������� ��������� ����� ����� ������������� � CKe.
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	glPushMatrix(); //��������� VM=Fwe.

	//�������� ����� �� VM=Fwe �� ������� ������ ���� ��� ���������� ���������� ����������.
	if (no_rotate)
	{
		glRotatef(angle_rotate_xy, 1.0, 1.0, 0.0);
	}
	if (flag_rotate_xy)
	{
		angle_rotate_xy += 15;
		if (angle_rotate_xy > 360) angle_rotate_xy = 0;
		glRotatef(angle_rotate_xy, 1.0, 1.0, 0.0);
	}
	//��������������� �� � � � VM=Fwe �� ������� ������ ����������.
	glScalef(x_size_next, 1.0, 1.0);
	if (inc_size_x)
	{
		x_size_last = x_size_next;
		x_size_next += 0.05;
		glScalef(x_size_next / x_size_last, 1.0, 1.0);
		inc_size_x = false;
	}
	if (dec_size_x)
	{
		x_size_last = x_size_next;
		x_size_next -= 0.05;
		glScalef(x_size_next / x_size_last, 1.0, 1.0);
		dec_size_x = false;
	}
	//���������� ���������� � ��� ������� ��������������.
	glutSolidDodecahedron();
	glutWireDodecahedron();

	glPopMatrix();//��������������� VM=Fwe.

	glDisable(GL_LIGHTING);//��������� ��������� ��� ����������� ��������� � �����.

	//������������� ������������ ��� ������� ����� � ���.
	glBegin(GL_LINES);
	glColor3f(1, 0, 0); glVertex3f(0, 0, 0); glVertex3f(3, 0, 0);
	glColor3f(0, 1, 0); glVertex3f(0, 0, 0); glVertex3f(0, 3, 0);
	glColor3f(0, 0, 1); glVertex3f(0, 0, 0); glVertex3f(0, 0, 3);
	glEnd();
	//������������� ����������� � ��������� ����� � ���.
	glBegin(GL_LINES);
	glColor3f(1, 1, 1); glVertex3f(3, 3, 3); glVertex3f(0.0, 0.0, 0.0);
	glEnd();
	//������������ ��� �������� ����� � ���� ����� �������� 20.0.
	//������������ ��������� ����� ��� ����������� � ���.
	glPointSize(20.0);
	glBegin(GL_POINTS);
	glColor3f(1.0, 1.0, 1.0);
	glVertex3f(3.0, 3.0, 3.0);
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
	glutPostRedisplay();
	Sleep(25);
}
int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(800, 800);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Lab_3");
	glutDisplayFunc(myDisplay);
	glutReshapeFunc(myReshape);
	glutKeyboardFunc(KeyBoardEvents);
	glutMouseFunc(MouseEvents);
	glutIdleFunc(myIdle);
	init();
	glutMainLoop();
}
