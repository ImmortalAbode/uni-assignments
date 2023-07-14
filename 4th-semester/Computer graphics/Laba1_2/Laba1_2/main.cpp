#include <GL/glut.h>
#include <cstdlib> //��� rand() � srand()
#include <ctime> //��� time()
void init();
void draw();
float getRandomNumber(float min, float max);

void main(int argc, char** argv) //������� �������
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

void init() //������� �������������
{
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, 40.0, 0.0, 40.0);
}
void draw() //������� ���������
{
	//�������� rand() � ������������ ������� ��� �������� ��������������� ������������������� ��������� �����
	srand(static_cast<unsigned int>(time(0)));

	//������ ����� ���������, ������������� �������
	GLint w = 40, h = 40;
	//�����
	glClear(GL_COLOR_BUFFER_BIT);

	//���������� �������
	for (GLint x{}; x <= 640; x += w)
		for (GLint y{}; y <= 480; y += h)
		{
			glViewport(x, y, w, h);

			//������� �������
			glBegin(GL_POLYGON);
			for (GLint i{}; i < 4;i++)
			{
				if ((x / 40 % 2 + y / 40 % 2) == (0 || 2)) glColor3f(getRandomNumber(0.0, 1.0), getRandomNumber(0.0, 1.0), getRandomNumber(0.0, 1.0));
				else  glColor3f(getRandomNumber(0.0, 1.0), getRandomNumber(0.0, 1.0), getRandomNumber(0.0, 1.0));
				glVertex2f(0.0, 0.0); glVertex2f(0.0, 40.0);
				glVertex2f(40.0, 40.0); glVertex2f(40.0, 0.0);
			}
			glEnd();

			//��������� ������� ������ ��������
			glBegin(GL_POLYGON);
			for (GLint i{}; i < 4;i++)
			{
				if ((x / 40 % 2 + y / 40 % 2) == (0 || 2)) glColor3f(getRandomNumber(0.0, 1.0), getRandomNumber(0.0, 1.0), getRandomNumber(0.0, 1.0));
				else glColor3f(getRandomNumber(0.0, 1.0), getRandomNumber(0.0, 1.0), getRandomNumber(0.0, 1.0));
				glVertex2f(10.0, 10.0); glVertex2f(10.0, 30.0);
				glVertex2f(30.0, 30.0); glVertex2f(30.0, 10.0);
			}
			glEnd();
		}

	glFlush();
}

float getRandomNumber(float min, float max) //��������� ���������� ����� ����� ��������� min � max
{
	static const float fraction = 1.0 / (static_cast<float>(RAND_MAX) + 1.0);
	return (rand() * fraction * (max - min + 1) + min);
}
