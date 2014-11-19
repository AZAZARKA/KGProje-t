#include "VisibileSqear.h"

CVisibileSqear::CVisibileSqear(GLfloat x, GLfloat y, GLfloat z)
{
	GLfloat r = 3.0f;
	m_x = x - r;
	m_y = y;
	m_z = z + r;
	m_a = r * 2;
	m_b = r * 2;
	m_h = r * 2;
}

CVisibileSqear::~CVisibileSqear(void)
{
}

GLfloat CVisibileSqear::GetX()
{
	return m_x;
}

GLfloat CVisibileSqear::GetY()
{
	return m_y;
}

GLfloat CVisibileSqear::GetZ()
{
	return m_z;
}

GLfloat CVisibileSqear::GetHeight()
{
	return m_h;
}

GLfloat CVisibileSqear::GetA()
{
	return m_a;
}

GLfloat CVisibileSqear::GetB()
{
	return m_b;
}