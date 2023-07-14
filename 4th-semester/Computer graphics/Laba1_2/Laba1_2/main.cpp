#include <GL/glut.h>
#include <cstdlib> //Для rand() и srand()
#include <ctime> //Для time()
void init();
void draw();
float getRandomNumber(float min, float max);

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
	gluOrtho2D(0.0, 40.0, 0.0, 40.0);
}
void draw() //Функция рисования
{
	//Привязка rand() к календарному времени для создания неповторяющихся последовательностей случайных чисел
	srand(static_cast<unsigned int>(time(0)));

	//Размер порта просмотра, организующего мозаику
	GLint w = 40, h = 40;
	//Экран
	glClear(GL_COLOR_BUFFER_BIT);

	//Реализация мозаики
	for (GLint x{}; x <= 640; x += w)
		for (GLint y{}; y <= 480; y += h)
		{
			glViewport(x, y, w, h);

			//Большой полигон
			glBegin(GL_POLYGON);
			for (GLint i{}; i < 4;i++)
			{
				if ((x / 40 % 2 + y / 40 % 2) == (0 || 2)) glColor3f(getRandomNumber(0.0, 1.0), getRandomNumber(0.0, 1.0), getRandomNumber(0.0, 1.0));
				else  glColor3f(getRandomNumber(0.0, 1.0), getRandomNumber(0.0, 1.0), getRandomNumber(0.0, 1.0));
				glVertex2f(0.0, 0.0); glVertex2f(0.0, 40.0);
				glVertex2f(40.0, 40.0); glVertex2f(40.0, 0.0);
			}
			glEnd();

			//Маленький полигон внутри большого
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

float getRandomNumber(float min, float max) //Генерация случайного числа между заданными min и max
{
	static const float fraction = 1.0 / (static_cast<float>(RAND_MAX) + 1.0);
	return (rand() * fraction * (max - min + 1) + min);
}
