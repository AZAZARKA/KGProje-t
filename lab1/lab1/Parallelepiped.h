#pragma once

#include <windows.h>		// Заголовочный файл для Windows
#include <gl\gl.h>			// Заголовочный файл для OpenGL32 библиотеки
#include <gl\glu.h>			// Заголовочный файл для GLu32 библиотеки

#include "GemeObject.h"

class CParallelepiped : public CGemeObject
{
public:
	CParallelepiped(GLfloat x, GLfloat y, GLfloat z,
		GLfloat a, GLfloat b, GLfloat h, GLuint texture);
	~CParallelepiped(void);

	GLfloat GetX();
	GLfloat GetY();
	GLfloat GetZ();
	GLfloat GetHeight();
	GLfloat GetA();
	GLfloat GetB();

	void draw();
private:
	GLfloat m_x, m_y, m_z, m_a, m_b, m_h;
	//x,y,z ближайший левый нижний угол
	GLuint m_texture;
};
