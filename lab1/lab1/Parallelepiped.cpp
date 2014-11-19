#include "Parallelepiped.h"


CParallelepiped::CParallelepiped(GLfloat x, GLfloat y, GLfloat z,
								 GLfloat a, GLfloat b, GLfloat h, GLuint texture)
{
	 m_x = x;
	 m_y = y;
	 m_z = z;
	 m_a = a;
	 m_b = b;
	 m_h = h;
	 m_texture = texture;
}

CParallelepiped::~CParallelepiped(void)
{
}

void CParallelepiped::draw()
{
	glBindTexture(GL_TEXTURE_2D, m_texture);
	glBegin(GL_QUADS);
		//glColor3f(0.0f,1.0f,0.0f);		// Зеленый

		glTexCoord2f(1.0f, 1.0f);glVertex3f(m_x + m_a, m_y + m_h, m_z - m_b);		// Право верх квадрата (Верх)
		glTexCoord2f(0.0f, 1.0f);glVertex3f(m_x, m_y + m_h, m_z - m_b);		// Лево верх
		glTexCoord2f(0.0f, 0.0f);glVertex3f(m_x, m_y + m_h, m_z);		// Лево низ
		glTexCoord2f(1.0f, 0.0f);glVertex3f(m_x + m_a, m_y + m_h, m_z);		// Право низ
		
		//glColor3f(1.0f,0.5f,0.0f);		// Оранжевый

		glTexCoord2f(1.0f, 1.0f);glVertex3f(m_x + m_a, m_y, m_z - m_b);		// Верх право квадрата (Низ)
		glTexCoord2f(0.0f, 1.0f);glVertex3f(m_x, m_y, m_z - m_b);		// Верх лево
		glTexCoord2f(0.0f, 0.0f);glVertex3f(m_x, m_y, m_z);		// Низ лево
		glTexCoord2f(1.0f, 0.0f);glVertex3f(m_x + m_a, m_y, m_z);		// Низ право
	
		//glColor3f(1.0f,0.0f,0.0f);		// Красный

		glTexCoord2f(1.0f, 1.0f);glVertex3f(m_x + m_a, m_y + m_h, m_z);		// Верх право квадрата (Перед)
		glTexCoord2f(0.0f, 1.0f);glVertex3f(m_x, m_y + m_h, m_z);		// Верх лево
		glTexCoord2f(0.0f, 0.0f);glVertex3f(m_x, m_y, m_z);		// Низ лево
		glTexCoord2f(1.0f, 0.0f);glVertex3f(m_x + m_a, m_y, m_z);		// Низ право

		//glColor3f(1.0f,1.0f,0.0f);		// Желтый

		glTexCoord2f(1.0f, 1.0f);glVertex3f(m_x + m_a, m_y + m_h, m_z - m_b);		// Верх право квадрата (Зад)
		glTexCoord2f(0.0f, 1.0f);glVertex3f(m_x, m_y + m_h, m_z - m_b);		// Верх лево
		glTexCoord2f(0.0f, 0.0f);glVertex3f(m_x, m_y, m_z - m_b);		// Низ лево
		glTexCoord2f(1.0f, 0.0f);glVertex3f(m_x + m_a, m_y, m_z - m_b);		// Низ право
		
		//glColor3f(0.0f,0.0f,1.0f);		// Синий

		glTexCoord2f(1.0f, 1.0f);glVertex3f(m_x, m_y + m_h, m_z);		// Верх право квадрата (Лево)
		glTexCoord2f(0.0f, 1.0f);glVertex3f(m_x, m_y + m_h, m_z - m_b);		// Верх лево
		glTexCoord2f(0.0f, 0.0f);glVertex3f(m_x, m_y, m_z - m_b);		// Низ лево
		glTexCoord2f(1.0f, 0.0f);glVertex3f(m_x, m_y, m_z);		// Низ право

		//glColor3f(1.0f,0.0f,1.0f);		// Фиолетовый

		glTexCoord2f(1.0f, 1.0f);glVertex3f(m_x + m_a, m_y + m_h, m_z - m_b);		// Верх право квадрата (Право)
		glTexCoord2f(0.0f, 1.0f);glVertex3f(m_x + m_a, m_y + m_h, m_z);		// Верх лево
		glTexCoord2f(0.0f, 0.0f);glVertex3f(m_x + m_a, m_y, m_z);		// Низ лево
		glTexCoord2f(1.0f, 0.0f);glVertex3f(m_x + m_a, m_y, m_z - m_b);		// Низ право
	glEnd();
}

GLfloat CParallelepiped::GetX()
{
	return m_x;
}

GLfloat CParallelepiped::GetY()
{
	return m_y;
}

GLfloat CParallelepiped::GetZ()
{
	return m_z;
}

GLfloat CParallelepiped::GetHeight()
{
	return m_h;
}

GLfloat CParallelepiped::GetA()
{
	return m_a;
}

GLfloat CParallelepiped::GetB()
{
	return m_b;
}