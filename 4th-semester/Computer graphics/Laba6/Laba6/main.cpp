#include <gl\glut.h>
#include <cstdio>
#include <iostream>

#include <C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Tools\\MSVC\\14.31.31103\\include\\GL\\glaux.h>
#pragma comment(lib, "C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Tools\\MSVC\\14.31.31103\\lib\\x64\\GLAUX.lib")
#pragma comment(lib, "legacy_stdio_definitions.lib")

//Структура для хранения заголовка файла изображения.
struct Header
{
	GLint width{}; //Высота
	GLint height{}; //Ширина
	GLenum colorFormat{}; //Формат представления цвета
	GLenum colorComponentDataFormat{}; //Формат данных компоненты цвета
	int colorComponentCount{}; //Количество компонент цвета
};
//Структура для хранения изображения
struct Picture
{
	unsigned char* pixels{ nullptr };
	Header header{};
};

Picture* ReadPictureFromFile(const char* szFileName)
{
	FILE* pFile{ nullptr };
	Picture* picture = (Picture*)malloc(sizeof(Picture));

	fopen_s(&pFile, szFileName, "rb");
	if (pFile == nullptr) return nullptr;
	if (picture != nullptr)
	{
		fread(&(picture->header), sizeof(Header), 1, pFile);

		picture->pixels = (unsigned char*)malloc(picture->header.width * picture->header.height * picture->header.colorComponentCount * 4);
		if (picture->pixels != nullptr) fread(picture->pixels, picture->header.width * picture->header.height * picture->header.colorComponentCount * 4, 1, pFile);
	}
	fclose(pFile);

	return picture;
}
GLint SavePictureInFile(const char* szFileName)
{
	FILE* pFile{ nullptr };
	Picture* picture = (Picture*)malloc(sizeof(Picture));
	GLint iViewport[4]{};
	glGetIntegerv(GL_VIEWPORT, iViewport);
	glPixelStorei(GL_PACK_ALIGNMENT, 1);
	glPixelStorei(GL_PACK_ROW_LENGTH, 512);
	glPixelStorei(GL_PACK_SKIP_ROWS, 0);
	glPixelStorei(GL_PACK_SKIP_PIXELS, 0);
	glReadBuffer(GL_FRONT);
	fopen_s(&pFile, szFileName, "wb");
	if (picture != nullptr && pFile != nullptr)
	{
		picture->header.width = iViewport[2];
		picture->header.height = iViewport[3];
		picture->header.colorFormat = GL_RGB;
		picture->header.colorComponentDataFormat = GL_UNSIGNED_BYTE;
		picture->header.colorComponentCount = 2;
		picture->pixels = (unsigned char*)malloc(picture->header.width * picture->header.height * picture->header.colorComponentCount * 4);
		glReadPixels(0, 0, picture->header.width, picture->header.height, picture->header.colorFormat, picture->header.colorComponentDataFormat, picture->pixels);
		fwrite(&(picture->header), sizeof(Header), 1, pFile);
		if (picture->pixels != nullptr)
			fwrite(picture->pixels, picture->header.width * picture->header.height * picture->header.colorComponentCount * 4, 1, pFile);
		fclose(pFile);
	}
	return 1;
}
Picture* current_picture{ nullptr }; //Текущее изображение
AUX_RGBImageRec* pImage{ nullptr }; //Изображение AUX_RGB
Picture* picture_bmp{ nullptr }; //Изображение .bmp
Picture* picture_save{ nullptr }; //Сохраненное изображение в файл
Picture* picture_RB{ nullptr }; //Изображение с красным и синим компонентами
static GLint choice{ 1 }; //Переменная для хранения выбора меню
bool mirror_image_Y{ false }; //Переменная для учета отзеркаленности изображения относительно оси Y
bool saving_image{ false }; //Переменная для учета, что изображение из сохраненного файла, где уже присутсвует масштаб пикселей
bool invert{ false }; //Переменная для учета, что изображение имеет инвертированный R и B цвета
//Обновляем переменную относитель текущего выбора меню
void MenuProcessing(int pointMenu)
{
	//Меняем индекс режима визуализации на индекс, соответствующий позиции меню
	choice = pointMenu;
	//Активизируем перерисовку окна glutPostRedisplay()
	glutPostRedisplay();
}
void Redrawing(void)
{
	//GLint iViewport[4]{};
	//GLbyte *pModifiedBytes = nullptr;
	GLfloat invertMap[256]{}; //Инверсная карта цветов
	GLfloat defaultMap[256]{}; //Стандартная карта цветов
	GLint i{};
	//Очищаем окно текущим цветом очистки
	glClear(GL_COLOR_BUFFER_BIT);
	//Текущее растровое положение всегда соответствует левому нижнему углу окна
	glRasterPos2i(0, 0);
	//Текущий размер пикселя всегда соответствует 1 пикселю на экране
	glPixelZoom(1, 1);
	//В зависимости от индекса режима визуализации выполняются необходимые операции с изображением
	switch (choice)
	{
	case 0: //Очистка экрана
		//Сброс преобразованного изображения до первоначального с освобождением соответсвующей динамически выделенной памяти
		if (current_picture != nullptr)
		{
			defaultMap[0] = 0.0f;
			for (i = 1; i < 256; i++)
				defaultMap[i] = 1.0f / 255.0f * (GLfloat)i;
			glPixelMapfv(GL_PIXEL_MAP_R_TO_R, 255, defaultMap);
			glPixelMapfv(GL_PIXEL_MAP_G_TO_G, 255, defaultMap);
			glPixelMapfv(GL_PIXEL_MAP_B_TO_B, 255, defaultMap);
			glPixelTransferi(GL_MAP_COLOR, GL_TRUE);
			current_picture = nullptr;
		}
		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
		break;
	case 1: //Загрузка изображения из файла .bmp
		if (current_picture == nullptr)
		{
			pImage = auxDIBImageLoad(L"My_pictures\\photo.bmp");
			picture_bmp = (Picture*)malloc(sizeof(Picture));
			if (picture_bmp != nullptr && pImage != nullptr)
			{
				picture_bmp->header.width = pImage->sizeX * 3 / 8;
				picture_bmp->header.height = pImage->sizeY;
				picture_bmp->pixels = pImage->data;
				picture_bmp->header.colorFormat = GL_LUMINANCE_ALPHA;
				picture_bmp->header.colorComponentDataFormat = GL_UNSIGNED_INT;
				picture_bmp->header.colorComponentCount = 2;
				mirror_image_Y = false;
				invert = false;
				saving_image = false;
				current_picture = picture_bmp;
			}
			else
			{
				std::cout << "Не удалось выделить динамическую память из кучи. Куча переполнена!" << std::endl;
				free(current_picture);
				free(pImage);
				free(picture_bmp);
				free(picture_save);
				free(picture_RB);
				exit(-1);
			}
		}
		break;
	case 2: //Сохранение текущего изображения в файл
		if (current_picture != nullptr)
		{
			SavePictureInFile("Saved_pictures\\save_photo.bmp");
		}
		break;
	case 3: //Загрузка сохраненного в файл изображения 
		picture_save = ReadPictureFromFile("Saved_pictures\\save_photo.bmp");
		saving_image = true;
		current_picture = picture_save;
		break;
	case 4: //Отражениe изображения относительно оси Y
		if (current_picture != nullptr)
			mirror_image_Y = !mirror_image_Y;
		break;
	case 5: //Отображение только компонентов R и B
		if (current_picture != nullptr)
		{
			//Вначале рисуем изображение в буфере цвета.
			glDrawPixels(current_picture->header.width, current_picture->header.height, current_picture->header.colorFormat, current_picture->header.colorComponentDataFormat, current_picture->pixels);
			//Распределяем память для карты яркости.
			picture_RB = (Picture*)malloc(sizeof(Picture));
			if (picture_RB != nullptr)
			{
				picture_RB->header.width = current_picture->header.width;
				picture_RB->header.height = current_picture->header.height;
				picture_RB->header.colorFormat = GL_LUMINANCE_ALPHA;
				picture_RB->header.colorComponentDataFormat = GL_UNSIGNED_INT;
				picture_RB->header.colorComponentCount = 2;
				picture_RB->pixels = (unsigned char*)malloc(picture_RB->header.width * picture_RB->header.height * picture_RB->header.colorComponentCount * 4);
				//Масштабируем цвета согласно заданному условию.
				glPixelTransferf(GL_RED_SCALE, 1.0f);
				glPixelTransferf(GL_GREEN_SCALE, 0.0f);
				glPixelTransferf(GL_BLUE_SCALE, 1.0f);
				//Считываем пиксели в буфер.
				glReadPixels(0, 0, picture_RB->header.width, picture_RB->header.height, picture_RB->header.colorFormat, picture_RB->header.colorComponentDataFormat, picture_RB->pixels);
				current_picture = picture_RB;
				//Масштабирование цвета возвращается в норму.
				glPixelTransferf(GL_RED_SCALE, 1.0f);
				glPixelTransferf(GL_GREEN_SCALE, 1.0f);
				glPixelTransferf(GL_BLUE_SCALE, 1.0f);
			}
			else
			{
				std::cout << "Не удалось выделить динамическую память из кучи! Куча переполнена." << std::endl;
				free(current_picture);
				free(pImage);
				free(picture_bmp);
				free(picture_save);
				free(picture_RB);
				exit(-1);
			}
		}
		break;
	case 6: //Инверсия компонент R и B
		if (current_picture != nullptr)
		{
			invert = true;
			defaultMap[0] = 0.0f;
			invertMap[0] = 1.0f;
			for (i = 1; i < 256; i++)
			{
				defaultMap[i] = 1.0f / 255.0f * (GLfloat)i;
				invertMap[i] = 1.0f - (1.0f / 255.0f * (GLfloat)i);
			}
			glPixelMapfv(GL_PIXEL_MAP_R_TO_R, 255, invertMap);
			glPixelMapfv(GL_PIXEL_MAP_G_TO_G, 255, defaultMap);
			glPixelMapfv(GL_PIXEL_MAP_B_TO_B, 255, invertMap);
			glPixelTransferi(GL_MAP_COLOR, GL_TRUE);
		}
		break;
	case 7:
		std::cout << "Завершение программы..." << std::endl;
		free(current_picture);
		free(pImage);
		free(picture_save);
		exit(0);
	default:
		break;
	}
	if (choice != 0 && current_picture != nullptr)
	{
		//Рисуются пиксели
		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
		//В зависимости от формата изображения выводим на каждый пиксель экрана нужный размер пикселя изображения
		if (!saving_image)
			if (mirror_image_Y)
			{
				glRasterPos2i(current_picture->header.width * 8 / 3, 0);
				glPixelZoom(static_cast<GLfloat>(-(2 + 59.0f / 90.0f)), 1);
			}
			else
				glPixelZoom(static_cast<GLfloat>(2 + 59.0f / 90.0f), 1);
		else
		{
			if (mirror_image_Y)
			{
				glRasterPos2i(current_picture->header.width, 0);
				glPixelZoom(-1, 1);
			}
			else
				glPixelZoom(1, 1);
			if (invert && saving_image)
			{
				defaultMap[0] = 0.0f;
				invertMap[0] = 1.0f;
				for (i = 1; i < 256; i++)
				{
					defaultMap[i] = 1.0f / 255.0f * (GLfloat)i;
					invertMap[i] = 1.0f - (1.0f / 255.0f * (GLfloat)i);
				}
				glPixelMapfv(GL_PIXEL_MAP_R_TO_R, 255, invertMap);
				glPixelMapfv(GL_PIXEL_MAP_G_TO_G, 255, defaultMap);
				glPixelMapfv(GL_PIXEL_MAP_B_TO_B, 255, invertMap);
				glPixelTransferi(GL_MAP_COLOR, GL_TRUE);
			}
		}
		glDrawPixels(current_picture->header.width, current_picture->header.height, current_picture->header.colorFormat, current_picture->header.colorComponentDataFormat,
			current_picture->pixels);
	}
	//Переключает буферы
	glutSwapBuffers();
}
void ResizeWindow(int w, int h)
{
	//Предотвращает деление на ноль, когда окно слишком маленькое
	if (h == 0)
		h = 1;
	glViewport(0, 0, w, h);
	//Система координат обновляется перед модификацией
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
}
int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	setlocale(LC_ALL, "Rus");
	glutInitDisplayMode(GLUT_RGB | GL_DOUBLE);
	glutInitWindowSize(512, 512);
	glutCreateWindow("Lab_6");
	glutReshapeFunc(ResizeWindow);
	glutDisplayFunc(Redrawing);
	//Создается меню и добавляются опции выбора
	GLint submenu = glutCreateMenu(MenuProcessing);
	glutAddMenuEntry("Загрузить изображение .bmp", 1);
	glutAddMenuEntry("Сохранить текущее изображение в файл", 2);
	glutAddMenuEntry("Загрузить изображение из файла", 3);

	glutCreateMenu(MenuProcessing);
	glutAddMenuEntry("Очистить экран", 0);
	glutAddSubMenu("Чтение/запись изображения", submenu);
	glutAddMenuEntry("Отразить изображение относительно оси Y", 4);
	glutAddMenuEntry("Отображение только компонент цвета R и B", 5);
	glutAddMenuEntry("Инверсия компонент цвета R и B", 6);
	glutAddMenuEntry("Выход", 7);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
	gluOrtho2D(0, 512, 0, 512);
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	choice = 0;
	glutMainLoop();
	//Освобождаем указатели на изображения
	free(current_picture);
	free(pImage);
	free(picture_bmp);
	free(picture_save);
	free(picture_RB);
	return 0;
}