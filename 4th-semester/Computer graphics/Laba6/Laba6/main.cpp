#include <gl\glut.h>
#include <cstdio>
#include <iostream>

#include <C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Tools\\MSVC\\14.31.31103\\include\\GL\\glaux.h>
#pragma comment(lib, "C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Tools\\MSVC\\14.31.31103\\lib\\x64\\GLAUX.lib")
#pragma comment(lib, "legacy_stdio_definitions.lib")

//��������� ��� �������� ��������� ����� �����������.
struct Header
{
	GLint width{}; //������
	GLint height{}; //������
	GLenum colorFormat{}; //������ ������������� �����
	GLenum colorComponentDataFormat{}; //������ ������ ���������� �����
	int colorComponentCount{}; //���������� ��������� �����
};
//��������� ��� �������� �����������
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
Picture* current_picture{ nullptr }; //������� �����������
AUX_RGBImageRec* pImage{ nullptr }; //����������� AUX_RGB
Picture* picture_bmp{ nullptr }; //����������� .bmp
Picture* picture_save{ nullptr }; //����������� ����������� � ����
Picture* picture_RB{ nullptr }; //����������� � ������� � ����� ������������
static GLint choice{ 1 }; //���������� ��� �������� ������ ����
bool mirror_image_Y{ false }; //���������� ��� ����� ��������������� ����������� ������������ ��� Y
bool saving_image{ false }; //���������� ��� �����, ��� ����������� �� ������������ �����, ��� ��� ����������� ������� ��������
bool invert{ false }; //���������� ��� �����, ��� ����������� ����� ��������������� R � B �����
//��������� ���������� ���������� �������� ������ ����
void MenuProcessing(int pointMenu)
{
	//������ ������ ������ ������������ �� ������, ��������������� ������� ����
	choice = pointMenu;
	//������������ ����������� ���� glutPostRedisplay()
	glutPostRedisplay();
}
void Redrawing(void)
{
	//GLint iViewport[4]{};
	//GLbyte *pModifiedBytes = nullptr;
	GLfloat invertMap[256]{}; //��������� ����� ������
	GLfloat defaultMap[256]{}; //����������� ����� ������
	GLint i{};
	//������� ���� ������� ������ �������
	glClear(GL_COLOR_BUFFER_BIT);
	//������� ��������� ��������� ������ ������������� ������ ������� ���� ����
	glRasterPos2i(0, 0);
	//������� ������ ������� ������ ������������� 1 ������� �� ������
	glPixelZoom(1, 1);
	//� ����������� �� ������� ������ ������������ ����������� ����������� �������� � ������������
	switch (choice)
	{
	case 0: //������� ������
		//����� ���������������� ����������� �� ��������������� � ������������� �������������� ����������� ���������� ������
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
	case 1: //�������� ����������� �� ����� .bmp
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
				std::cout << "�� ������� �������� ������������ ������ �� ����. ���� �����������!" << std::endl;
				free(current_picture);
				free(pImage);
				free(picture_bmp);
				free(picture_save);
				free(picture_RB);
				exit(-1);
			}
		}
		break;
	case 2: //���������� �������� ����������� � ����
		if (current_picture != nullptr)
		{
			SavePictureInFile("Saved_pictures\\save_photo.bmp");
		}
		break;
	case 3: //�������� ������������ � ���� ����������� 
		picture_save = ReadPictureFromFile("Saved_pictures\\save_photo.bmp");
		saving_image = true;
		current_picture = picture_save;
		break;
	case 4: //��������e ����������� ������������ ��� Y
		if (current_picture != nullptr)
			mirror_image_Y = !mirror_image_Y;
		break;
	case 5: //����������� ������ ����������� R � B
		if (current_picture != nullptr)
		{
			//������� ������ ����������� � ������ �����.
			glDrawPixels(current_picture->header.width, current_picture->header.height, current_picture->header.colorFormat, current_picture->header.colorComponentDataFormat, current_picture->pixels);
			//������������ ������ ��� ����� �������.
			picture_RB = (Picture*)malloc(sizeof(Picture));
			if (picture_RB != nullptr)
			{
				picture_RB->header.width = current_picture->header.width;
				picture_RB->header.height = current_picture->header.height;
				picture_RB->header.colorFormat = GL_LUMINANCE_ALPHA;
				picture_RB->header.colorComponentDataFormat = GL_UNSIGNED_INT;
				picture_RB->header.colorComponentCount = 2;
				picture_RB->pixels = (unsigned char*)malloc(picture_RB->header.width * picture_RB->header.height * picture_RB->header.colorComponentCount * 4);
				//������������ ����� �������� ��������� �������.
				glPixelTransferf(GL_RED_SCALE, 1.0f);
				glPixelTransferf(GL_GREEN_SCALE, 0.0f);
				glPixelTransferf(GL_BLUE_SCALE, 1.0f);
				//��������� ������� � �����.
				glReadPixels(0, 0, picture_RB->header.width, picture_RB->header.height, picture_RB->header.colorFormat, picture_RB->header.colorComponentDataFormat, picture_RB->pixels);
				current_picture = picture_RB;
				//��������������� ����� ������������ � �����.
				glPixelTransferf(GL_RED_SCALE, 1.0f);
				glPixelTransferf(GL_GREEN_SCALE, 1.0f);
				glPixelTransferf(GL_BLUE_SCALE, 1.0f);
			}
			else
			{
				std::cout << "�� ������� �������� ������������ ������ �� ����! ���� �����������." << std::endl;
				free(current_picture);
				free(pImage);
				free(picture_bmp);
				free(picture_save);
				free(picture_RB);
				exit(-1);
			}
		}
		break;
	case 6: //�������� ��������� R � B
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
		std::cout << "���������� ���������..." << std::endl;
		free(current_picture);
		free(pImage);
		free(picture_save);
		exit(0);
	default:
		break;
	}
	if (choice != 0 && current_picture != nullptr)
	{
		//�������� �������
		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
		//� ����������� �� ������� ����������� ������� �� ������ ������� ������ ������ ������ ������� �����������
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
	//����������� ������
	glutSwapBuffers();
}
void ResizeWindow(int w, int h)
{
	//������������� ������� �� ����, ����� ���� ������� ���������
	if (h == 0)
		h = 1;
	glViewport(0, 0, w, h);
	//������� ��������� ����������� ����� ������������
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
	//��������� ���� � ����������� ����� ������
	GLint submenu = glutCreateMenu(MenuProcessing);
	glutAddMenuEntry("��������� ����������� .bmp", 1);
	glutAddMenuEntry("��������� ������� ����������� � ����", 2);
	glutAddMenuEntry("��������� ����������� �� �����", 3);

	glutCreateMenu(MenuProcessing);
	glutAddMenuEntry("�������� �����", 0);
	glutAddSubMenu("������/������ �����������", submenu);
	glutAddMenuEntry("�������� ����������� ������������ ��� Y", 4);
	glutAddMenuEntry("����������� ������ ��������� ����� R � B", 5);
	glutAddMenuEntry("�������� ��������� ����� R � B", 6);
	glutAddMenuEntry("�����", 7);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
	gluOrtho2D(0, 512, 0, 512);
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	choice = 0;
	glutMainLoop();
	//����������� ��������� �� �����������
	free(current_picture);
	free(pImage);
	free(picture_bmp);
	free(picture_save);
	free(picture_RB);
	return 0;
}