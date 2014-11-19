#pragma once
#include "gemeobject.h"

class CVisibileSqear :
	public CGemeObject
{
public:
	//вводим координаты игрока
	CVisibileSqear(GLfloat x, GLfloat y, GLfloat z);
	~CVisibileSqear(void);

	GLfloat GetX();
	GLfloat GetY();
	GLfloat GetZ();
	GLfloat GetHeight();
	GLfloat GetA();
	GLfloat GetB();
private:
	GLfloat m_x, m_y, m_z, m_a, m_b, m_h;
	//x,y,z ближайший левый нижний угол
};
