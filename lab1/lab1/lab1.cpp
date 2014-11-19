#include <cstdlib>
#include <windows.h>		// ������������ ���� ��� Windows
#include <gl\gl.h>			// ������������ ���� ��� OpenGL32 ����������
#include <gl\glu.h>			// ������������ ���� ��� GLu32 ����������
#include <gl\glaux.h>              // ������������ ����� ��� ���������� GLaux
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

static HGLRC hRC;		// ���������� �������� ����������
static HDC hDC;			// ��������� �������� ���������� GDI

BOOL	keys[256];		// ������ ��� ��������� ��������� ����������
GLuint	texture[3];		// ����� ��� ���� ��������

CGameMap * gameMap;
CPlayer player(1.5f, 0.0f, 2.5f);
CGuardian * guardian;
CSpawn * spawn;
//����� ������� � ����

__int64 g_freq; // ���������� ����������

__int64 Init()
{
	LARGE_INTEGER s;
	QueryPerformanceFrequency(&s);
	g_freq = s.QuadPart;
	return g_freq;
}

__int64 GetTi�ks()
{
	LARGE_INTEGER s;
	QueryPerformanceCounter(&s);
	return s.QuadPart;
}

__int64 GetMicroTickCount()		// ����� � mcs
{
	return (GetTi�ks() * 1000000 / g_freq);
}

//����� ������� � ����

// �������� �������� � ��������������� � ��������
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
	// �������� ��������
	AUX_RGBImageRec *texture1;
	AUX_RGBImageRec *texture2;
	AUX_RGBImageRec *texture3;
	texture1 = auxDIBImageLoad("Data/CRATE.bmp");
	texture2 = auxDIBImageLoad("Data/trava.bmp");
	texture3 = auxDIBImageLoad("Data/metka.bmp");
	// �������� ��������
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

GLvoid InitGL(GLsizei Width, GLsizei Height)	// ������� ����� �������� ���� GL
{
	LoadGLTextures();			// �������� �������
	glEnable(GL_TEXTURE_2D);		// ���������� ��������� ��������

	glClearColor(0.5f,0.5f,0.5f,1.0f);      // ����� ������� �����, �������� ��� ������ ������.

	glClearDepth(1.0);		// ��������� ������� ������ �������
	glDepthFunc(GL_LESS);	// ��� ����� �������
	glEnable(GL_DEPTH_TEST);// ��������� ���� �������
	glShadeModel(GL_SMOOTH);// ��������� ������� �������� �����������
	glMatrixMode(GL_PROJECTION);// ����� ������� ��������
	glLoadIdentity();		// ����� ������� ��������
	gluPerspective(45.0f,(GLfloat)Width/(GLfloat)Height,0.1f,100.0f);
							// ��������� ����������� �������������� �������� ��� ����
	glMatrixMode(GL_MODELVIEW);// ����� ������� ��������� ������

	GLfloat fogColor[4]= {0.5f, 0.5f, 0.5f, 1.0f}; // ���� ������

	glEnable(GL_FOG);                       // �������� ����� (GL_FOG)
	glFogi(GL_FOG_MODE, GL_LINEAR);// �������� ��� ������
	glFogfv(GL_FOG_COLOR, fogColor);        // ������������� ���� ������
	glFogf(GL_FOG_DENSITY, 1.0f);          // ��������� ������ ����� �����
	glHint(GL_FOG_HINT, GL_DONT_CARE);      // ��������������� ��������� ������
	glFogf(GL_FOG_START, 0.5f);             // �������, � ������� ���������� �����
	glFogf(GL_FOG_END, 2.0f);               // �������, ��� ����� �������������.
}

GLvoid ReSizeGLScene(GLsizei Width, GLsizei Height)
{
	if (Height==0)		// �������������� ������� �� ����, ���� ���� ������� ����
		Height=1;

	glViewport(0, 0, Width, Height);
		// ����� ������� ������� ������ � ������������� ��������������

	glMatrixMode(GL_PROJECTION);// ����� ������� ��������
	glLoadIdentity();			// ����� ������� ��������

	gluPerspective(45.0f,(GLfloat)Width/(GLfloat)Height,0.1f,100.0f);
		// ���������� ����������� �������������� �������� ��� ����
	glMatrixMode(GL_MODELVIEW);	// ����� ������� ��������� ������
}

GLvoid DrawGLScene(GLvoid)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		// ������� ������ � ������ �������
	glLoadIdentity();
		// ����� ���������

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
	RECT	Screen;		// ������������ ������� ��� �������� ����
	GLuint	PixelFormat;
	static	PIXELFORMATDESCRIPTOR pfd=
	{
		sizeof(PIXELFORMATDESCRIPTOR),	// ������ ���� ���������
		1,				// ����� ������ (?)
		PFD_DRAW_TO_WINDOW |// ������ ��� ����
		PFD_SUPPORT_OPENGL |// ������ ��� OpenGL
		PFD_DOUBLEBUFFER,// ������ ��� �������� ������
		PFD_TYPE_RGBA,	// ��������� RGBA ������
		16,				// ����� 16 ��� ������� �����
		0, 0, 0, 0, 0, 0,// ������������� �������� ����� (?)
		0,				// ��� ������ ������������
		0,				// ��������� ��� ������������ (?)
		0,				// ��� ������ �����������
		0, 0, 0, 0,		// ���� ����������� ������������ (?)
		16,				// 16 ������ Z-����� (����� �������)  
		0,				// ��� ������ ����������
		0,				// ��� ��������������� ������� (?)
		PFD_MAIN_PLANE,	// ������� ���� ���������
		0,				// ������ (?)
		0, 0, 0			// ����� ���� ������������ (?)
	};
	switch (message)	// ��� ���������
	{
		case WM_CREATE:
		hDC = GetDC(hWnd);	// �������� �������� ���������� ��� ����
		PixelFormat = ChoosePixelFormat(hDC, &pfd);
			// ����� ��������� ���������� ��� ������ ������� ��������
		if (!PixelFormat)
		{
			MessageBox(0,"Can't Find A Suitable PixelFormat.","Error",MB_OK|MB_ICONERROR);
			PostQuitMessage(0);
			// ��� ��������� �������, ��� ��������� ������ ����������
			break;	// �������������� ������� ����
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
	MSG		msg;	// ��������� ��������� Windows
	WNDCLASS	wc; // ��������� ������ Windows ��� ��������� ���� ����
	HWND		hWnd;// ���������� ����������� ����

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
	"Jeff Molofee's GL Code Tutorial ... NeHe '99",	// ��������� ������ ����

	WS_POPUP |
	WS_CLIPCHILDREN |
	WS_CLIPSIBLINGS,

	0, 0,			// ������� ���� �� ������
	//640, 480,		// ������ � ������ ����
	1024, 600,		// ������ � ������ ����

	NULL,
	NULL,
	hInstance,
	NULL);

	if(!hWnd)
	{
	MessageBox(0,"Window Creation Error.","Error",MB_OK|MB_ICONERROR); 
		return FALSE;
	}

	DEVMODE dmScreenSettings;			// ����� ������

	memset(&dmScreenSettings, 0, sizeof(DEVMODE));	// ������� ��� �������� ���������
	dmScreenSettings.dmSize	= sizeof(DEVMODE);		// ������ ��������� Devmode
	dmScreenSettings.dmPelsWidth	= 1024;//640;			// ������ ������
	dmScreenSettings.dmPelsHeight	= 600;//480;			// ������ ������
	dmScreenSettings.dmFields	= DM_PELSWIDTH | DM_PELSHEIGHT;	// ����� �������
	ChangeDisplaySettings(&dmScreenSettings, CDS_FULLSCREEN);
	// ������������ � ������ �����

	ShowWindow(hWnd, SW_SHOW);
	UpdateWindow(hWnd);
	SetFocus(hWnd);

	POINT  pt;
	POINT  lastPt;
    GetCursorPos(&lastPt);
	//�������� ������
	Model *pModel = NULL;

	pModel = new MilkshapeModel();
	if ( pModel->loadModelData( "guardianModel/model.ms3d" ) == false )
	{
		MessageBox( NULL, "Couldn't load the model data/model.ms3d", "Error", MB_OK | MB_ICONERROR );
		return 0;  // ���� ������ �� ���������, �������
	}

	//pModel->reloadTextures();
	//�������� ������
	gameMap = new CGameMap("Maps\\map1.txt", texture);
	guardian = new CGuardian(1.5f, 1.5f, pModel);
	spawn = new CSpawn(4.0f, 1.5f);

	ShowCursor(FALSE);

	__int64 g_freq = Init();
	__int64 lastTime = GetMicroTickCount();

	//mciSendString("play Fone.mp3 wait", NULL, NULL, NULL);//����� � �������

	while (1)
	{
		// ��������� ���� ���������
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

		DrawGLScene();				// ���������� �����
		SwapBuffers(hDC);			// ����������� ����� ������
		if (keys[VK_ESCAPE]) SendMessage(hWnd,WM_CLOSE,0,0);	// ���� ESC - �����
	}

	delete gameMap;
	delete guardian;
	delete spawn;
}