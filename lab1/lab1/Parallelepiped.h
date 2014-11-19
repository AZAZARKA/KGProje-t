#pragma once

#include <windows.h>		// ������������ ���� ��� Windows
#include <gl\gl.h>			// ������������ ���� ��� OpenGL32 ����������
#include <gl\glu.h>			// ������������ ���� ��� GLu32 ����������

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
	//x,y,z ��������� ����� ������ ����
	GLuint m_texture;
};
