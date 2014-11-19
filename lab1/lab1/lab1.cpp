#include <cstdlib>
#include <windows.h>		// Заголовочный файл для Windows
#include <gl\gl.h>			// Заголовочный файл для OpenGL32 библиотеки
#include <gl\glu.h>			// Заголовочный файл для GLu32 библиотеки
#include <gl\glaux.h>              // Заголовочные файлы для библиотеки GLaux
#include <time.h>

#pragma comment(lib, "winmm.lib")

#include "GemeObject.h"
#include "Parallelepiped.h"
#include "GameMap.h"
#include "Player.h"
#include "VisibileSqear.h"

#include "Zoombi.h"

#include "Guardian.h"

#include "Spawn.h"

#include "modelsCode/MilkshapeModel.h"

static HGLRC hRC;		// Постоянный контекст рендеринга
static HDC hDC;			// Приватный контекст устройства GDI

BOOL	keys[256];		// Массив для процедуры обработки клавиатуры
GLuint	texture[3];		// Место для трех текстуры

CGameMap * gameMap;
CPlayer player(1.5f, 0.0f, 2.5f);
CGuardian * guardian;
CSpawn * spawn;
//ВРЕМЯ ВЫНЕСТИ В ХЭДР

__int64 g_freq; // глобальная переменная

__int64 Init()
{
	LARGE_INTEGER s;
	QueryPerformanceFrequency(&s);
	g_freq = s.QuadPart;
	return g_freq;
}

__int64 GetTiсks()
{
	LARGE_INTEGER s;
	QueryPerformanceCounter(&s);
	return s.QuadPart;
}

__int64 GetMicroTickCount()		// время в mcs
{
	return (GetTiсks() * 1000000 / g_freq);
}

//ВРЕМЯ ВЫНЕСТИ В ХЭДР

// Загрузка картинки и конвертирование в текстуру
AUX_RGBImageRec *LoadBMP(const char *Filename)						// Loads A Bitmap Image
{
	FILE *File=NULL;												// File Handle

	if (!Filename)													// Make Sure A Filename Was Given
	{
		return NULL;												// If Not Return NULL
	}

	File=fopen(Filename,"r");										// Check To See If The File Exists

	if (File)														// Does The File Exist?
	{
		fclose(File);												// Close The Handle
		return auxDIBImageLoad(Filename);							// Load The Bitmap And Return A Pointer
	}

	return NULL;													// If Load Failed Return NULL
}

GLuint LoadGLTexture( const char *filename )						// Load Bitmaps And Convert To Textures
{
	AUX_RGBImageRec *pImage;										// Create Storage Space For The Texture
	GLuint texture = 0;												// Texture ID

	pImage = LoadBMP( filename );									// Loads The Bitmap Specified By filename

	// Load The Bitmap, Check For Errors, If Bitmap's Not Found Quit
	if ( pImage != NULL && pImage->data != NULL )					// If Texture Image Exists
	{
		glGenTextures(1, &texture);									// Create The Texture

		// Typical Texture Generation Using Data From The Bitmap
		glBindTexture(GL_TEXTURE_2D, texture);
		glTexImage2D(GL_TEXTURE_2D, 0, 3, pImage->sizeX, pImage->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, pImage->data);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);

		free(pImage->data);											// Free The Texture Image Memory
		free(pImage);												// Free The Image Structure
	}

	return texture;													// Return The Status
}

GLvoid LoadGLTextures()
{
	// Загрузка картинки
	AUX_RGBImageRec *texture1;
	AUX_RGBImageRec *texture2;
	AUX_RGBImageRec *texture3;
	texture1 = auxDIBImageLoad("Data/CRATE.bmp");
	texture2 = auxDIBImageLoad("Data/trava.bmp");
	texture3 = auxDIBImageLoad("Data/metka.bmp");
	// Создание текстуры
	glGenTextures(1, &texture[0]);
	glBindTexture(GL_TEXTURE_2D, texture[0]);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, texture1->sizeX, texture1->sizeY, 0,
		GL_RGB, GL_UNSIGNED_BYTE, texture1->data);

	glGenTextures(1, &texture[1]);
	glBindTexture(GL_TEXTURE_2D, texture[1]);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, texture2->sizeX, texture2->sizeY, 0,
		GL_RGB, GL_UNSIGNED_BYTE, texture2->data);

	glGenTextures(1, &texture[2]);
	glBindTexture(GL_TEXTURE_2D, texture[2]);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, texture3->sizeX, texture3->sizeY, 0,
		GL_RGB, GL_UNSIGNED_BYTE, texture3->data);
}

GLvoid InitGL(GLsizei Width, GLsizei Height)	// Вызвать после создания окна GL
{
	LoadGLTextures();			// Загрузка текстур
	glEnable(GL_TEXTURE_2D);		// Разрешение наложение текстуры

	glClearColor(0.5f,0.5f,0.5f,1.0f);      // Будем очищать экран, заполняя его цветом тумана.

	glClearDepth(1.0);		// Разрешить очистку буфера глубины
	glDepthFunc(GL_LESS);	// Тип теста глубины
	glEnable(GL_DEPTH_TEST);// разрешить тест глубины
	glShadeModel(GL_SMOOTH);// разрешить плавное цветовое сглаживание
	glMatrixMode(GL_PROJECTION);// Выбор матрицы проекции
	glLoadIdentity();		// Сброс матрицы проекции
	gluPerspective(45.0f,(GLfloat)Width/(GLfloat)Height,0.1f,100.0f);
							// Вычислить соотношение геометрических размеров для окна
	glMatrixMode(GL_MODELVIEW);// Выбор матрицы просмотра модели

	GLfloat fogColor[4]= {0.5f, 0.5f, 0.5f, 1.0f}; // Цвет тумана

	glEnable(GL_FOG);                       // Включает туман (GL_FOG)
	glFogi(GL_FOG_MODE, GL_LINEAR);// Выбираем тип тумана
	glFogfv(GL_FOG_COLOR, fogColor);        // Устанавливаем цвет тумана
	glFogf(GL_FOG_DENSITY, 1.0f);          // Насколько густым будет туман
	glHint(GL_FOG_HINT, GL_DONT_CARE);      // Вспомогательная установка тумана
	glFogf(GL_FOG_START, 0.5f);             // Глубина, с которой начинается туман
	glFogf(GL_FOG_END, 2.0f);               // Глубина, где туман заканчивается.
}

GLvoid ReSizeGLScene(GLsizei Width, GLsizei Height)
{
	if (Height==0)		// Предотвращение деления на ноль, если окно слишком мало
		Height=1;

	glViewport(0, 0, Width, Height);
		// Сброс текущей области вывода и перспективных преобразований

	glMatrixMode(GL_PROJECTION);// Выбор матрицы проекций
	glLoadIdentity();			// Сброс матрицы проекции

	gluPerspective(45.0f,(GLfloat)Width/(GLfloat)Height,0.1f,100.0f);
		// Вычисление соотношения геометрических размеров для окна
	glMatrixMode(GL_MODELVIEW);	// Выбор матрицы просмотра модели
}

GLvoid DrawGLScene(GLvoid)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		// очистка Экрана и буфера глубины
	glLoadIdentity();
		// Сброс просмотра

	CVisibileSqear playerVisions(player.GetX(), player.GetY(), player.GetZ());

	player.SetCamera();
	spawn->Draw();
	gameMap->draw(playerVisions);
	guardian->Draw();
	player.DrawMarks();
}

LRESULT CALLBACK WndProc(
				HWND	hWnd,
				UINT	message,
				WPARAM	wParam,
				LPARAM	lParam)
{
	RECT	Screen;		// используется позднее для размеров окна
	GLuint	PixelFormat;
	static	PIXELFORMATDESCRIPTOR pfd=
	{
		sizeof(PIXELFORMATDESCRIPTOR),	// Размер этой структуры
		1,				// Номер версии (?)
		PFD_DRAW_TO_WINDOW |// Формат для Окна
		PFD_SUPPORT_OPENGL |// Формат для OpenGL
		PFD_DOUBLEBUFFER,// Формат для двойного буфера
		PFD_TYPE_RGBA,	// Требуется RGBA формат
		16,				// Выбор 16 бит глубины цвета
		0, 0, 0, 0, 0, 0,// Игнорирование цветовых битов (?)
		0,				// нет буфера прозрачности
		0,				// Сдвиговый бит игнорируется (?)
		0,				// Нет буфера аккумуляции
		0, 0, 0, 0,		// Биты аккумуляции игнорируются (?)
		16,				// 16 битный Z-буфер (буфер глубины)  
		0,				// Нет буфера траффарета
		0,				// Нет вспомогательных буферов (?)
		PFD_MAIN_PLANE,	// Главный слой рисования
		0,				// Резерв (?)
		0, 0, 0			// Маски слоя игнорируются (?)
	};
	switch (message)	// Тип сообщения
	{
		case WM_CREATE:
		hDC = GetDC(hWnd);	// Получить контекст устройства для окна
		PixelFormat = ChoosePixelFormat(hDC, &pfd);
			// Найти ближайшее совпадение для нашего формата пикселов
		if (!PixelFormat)
		{
			MessageBox(0,"Can't Find A Suitable PixelFormat.","Error",MB_OK|MB_ICONERROR);
			PostQuitMessage(0);
			// Это сообщение говорит, что программа должна завершится
			break;	// Предтовращение повтора кода
		}
		if(!SetPixelFormat(hDC,PixelFormat,&pfd))
		{
			MessageBox(0,"Can't Set The PixelFormat.","Error",MB_OK|MB_ICONERROR);
			PostQuitMessage(0);
			break;
		}
		hRC = wglCreateContext(hDC);
		if(!hRC)
		{
			MessageBox(0,"Can't Create A GL Rendering Context.","Error",MB_OK|MB_ICONERROR);
			PostQuitMessage(0);
			break;
		}
		if(!wglMakeCurrent(hDC, hRC))
		{
			MessageBox(0,"Can't activate GLRC.","Error",MB_OK|MB_ICONERROR);
			PostQuitMessage(0);
			break;
		}
		GetClientRect(hWnd, &Screen);
		InitGL(Screen.right, Screen.bottom);
		break;

		case WM_DESTROY:
		case WM_CLOSE:
		ChangeDisplaySettings(NULL, 0);

		wglMakeCurrent(hDC,NULL);
		wglDeleteContext(hRC);
		ReleaseDC(hWnd,hDC);

		PostQuitMessage(0);
		break;

		case WM_KEYDOWN:
		keys[wParam] = TRUE;
		break;

		case WM_KEYUP:
		keys[wParam] = FALSE;
		break;

		case WM_SIZE:
		ReSizeGLScene(LOWORD(lParam),HIWORD(lParam));
		break;

		default:
	return (DefWindowProc(hWnd, message, wParam, lParam));
	}
	return (0);
}

int WINAPI WinMain(
		HINSTANCE hInstance,
		HINSTANCE hPrevInstance, 
		LPSTR lpCmdLine,
		int nCmdShow)
{
	MSG		msg;	// Структура сообщения Windows
	WNDCLASS	wc; // Структура класса Windows для установки типа окна
	HWND		hWnd;// Сохранение дискриптора окна

	wc.style			= CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wc.lpfnWndProc		= (WNDPROC) WndProc;
	wc.cbClsExtra		= 0;
	wc.cbWndExtra		= 0;
	wc.hInstance		= hInstance;
	wc.hIcon			= NULL;
	wc.hCursor			= LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground	= NULL;
	wc.lpszMenuName		= NULL;
	wc.lpszClassName	= "OpenGL WinClass";

	if(!RegisterClass(&wc))
	{
	MessageBox(0,"Failed To Register The Window Class.","Error",MB_OK|MB_ICONERROR);
	return FALSE;
	}

	hWnd = CreateWindow(
	"OpenGL WinClass",
	"Jeff Molofee's GL Code Tutorial ... NeHe '99",	// Заголовок вверху окна

	WS_POPUP |
	WS_CLIPCHILDREN |
	WS_CLIPSIBLINGS,

	0, 0,			// Позиция окна на экране
	//640, 480,		// Ширина и высота окна
	1024, 600,		// Ширина и высота окна

	NULL,
	NULL,
	hInstance,
	NULL);

	if(!hWnd)
	{
	MessageBox(0,"Window Creation Error.","Error",MB_OK|MB_ICONERROR); 
		return FALSE;
	}

	DEVMODE dmScreenSettings;			// Режим работы

	memset(&dmScreenSettings, 0, sizeof(DEVMODE));	// Очистка для хранения установок
	dmScreenSettings.dmSize	= sizeof(DEVMODE);		// Размер структуры Devmode
	dmScreenSettings.dmPelsWidth	= 1024;//640;			// Ширина экрана
	dmScreenSettings.dmPelsHeight	= 600;//480;			// Высота экрана
	dmScreenSettings.dmFields	= DM_PELSWIDTH | DM_PELSHEIGHT;	// Режим Пиксела
	ChangeDisplaySettings(&dmScreenSettings, CDS_FULLSCREEN);
	// Переключение в полный экран

	ShowWindow(hWnd, SW_SHOW);
	UpdateWindow(hWnd);
	SetFocus(hWnd);

	POINT  pt;
	POINT  lastPt;
    GetCursorPos(&lastPt);
	//загрузка модели
	Model *pModel = NULL;

	pModel = new MilkshapeModel();
	if ( pModel->loadModelData( "guardianModel/model.ms3d" ) == false )
	{
		MessageBox( NULL, "Couldn't load the model data/model.ms3d", "Error", MB_OK | MB_ICONERROR );
		return 0;  // Если модель не загружена, выходим
	}

	//pModel->reloadTextures();
	//загрузка модели
	gameMap = new CGameMap("Maps\\map1.txt", texture);
	guardian = new CGuardian(1.5f, 1.5f, pModel);
	spawn = new CSpawn(4.0f, 1.5f);

	ShowCursor(FALSE);

	__int64 g_freq = Init();
	__int64 lastTime = GetMicroTickCount();

	//mciSendString("play Fone.mp3 wait", NULL, NULL, NULL);//Проба с музыкой

	while (1)
	{
		// Обработка всех сообщений
		while (PeekMessage(&msg, NULL, 0, 0, PM_NOREMOVE))
		{
			if (GetMessage(&msg, NULL, 0, 0))
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
			else
			{
				return TRUE;
			}
		}

		__int64 newTime = GetMicroTickCount();
		double dt = (newTime - lastTime) / 1000000.0;

		lastTime = newTime;

		guardian->Update(*gameMap, dt, player);

		gameMap -> update();
		//zoombie
		spawn->CreateZoombi(dt);
		spawn->Update(*gameMap, dt, player);
		//zoombie

		GetCursorPos(&pt);

		if (keys[VK_UP])
		{
			player.MakeStepUp(*gameMap, dt);
		}
		if (keys[VK_DOWN])
		{
			player.MakeStepDown(*gameMap, dt);
		}
		if (keys[VK_LEFT])
		{
			player.MakeStepLeft(*gameMap, dt);
		}
		if (keys[VK_RIGHT])
		{
			player.MakeStepRight(*gameMap, dt);
		}
		if (keys['G'])
		{
			player.PutMark(texture[2]);
			keys['G'] = false;
		}

		player.MakeTurn((GLfloat)((lastPt.x - pt.x) * 0.7), (GLfloat)((pt.y - lastPt.y) * 0.2));
	
		if (pt.x <= 0 || pt.x >= 1020)
		{
			SetCursorPos(1024 / 2, pt.y);
			GetCursorPos(&pt);
		}

		lastPt = pt;

		DrawGLScene();				// Нарисовать сцену
		SwapBuffers(hDC);			// Переключить буфер экрана
		if (keys[VK_ESCAPE]) SendMessage(hWnd,WM_CLOSE,0,0);	// Если ESC - выйти
	}

	delete gameMap;
	delete guardian;
	delete spawn;
}