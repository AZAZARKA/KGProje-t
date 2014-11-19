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
		//glColor3f(0.0f,1.0f,0.0f);		// �������

		glTexCoord2f(1.0f, 1.0f);glVertex3f(m_x + m_a, m_y + m_h, m_z - m_b);		// ����� ���� �������� (����)
		glTexCoord2f(0.0f, 1.0f);glVertex3f(m_x, m_y + m_h, m_z - m_b);		// ���� ����
		glTexCoord2f(0.0f, 0.0f);glVertex3f(m_x, m_y + m_h, m_z);		// ���� ���
		glTexCoord2f(1.0f, 0.0f);glVertex3f(m_x + m_a, m_y + m_h, m_z);		// ����� ���
		
		//glColor3f(1.0f,0.5f,0.0f);		// ���������

		glTexCoord2f(1.0f, 1.0f);glVertex3f(m_x + m_a, m_y, m_z - m_b);		// ���� ����� �������� (���)
		glTexCoord2f(0.0f, 1.0f);glVertex3f(m_x, m_y, m_z - m_b);		// ���� ����
		glTexCoord2f(0.0f, 0.0f);glVertex3f(m_x, m_y, m_z);		// ��� ����
		glTexCoord2f(1.0f, 0.0f);glVertex3f(m_x + m_a, m_y, m_z);		// ��� �����
	
		//glColor3f(1.0f,0.0f,0.0f);		// �������

		glTexCoord2f(1.0f, 1.0f);glVertex3f(m_x + m_a, m_y + m_h, m_z);		// ���� ����� �������� (�����)
		glTexCoord2f(0.0f, 1.0f);glVertex3f(m_x, m_y + m_h, m_z);		// ���� ����
		glTexCoord2f(0.0f, 0.0f);glVertex3f(m_x, m_y, m_z);		// ��� ����
		glTexCoord2f(1.0f, 0.0f);glVertex3f(m_x + m_a, m_y, m_z);		// ��� �����

		//glColor3f(1.0f,1.0f,0.0f);		// ������

		glTexCoord2f(1.0f, 1.0f);glVertex3f(m_x + m_a, m_y + m_h, m_z - m_b);		// ���� ����� �������� (���)
		glTexCoord2f(0.0f, 1.0f);glVertex3f(m_x, m_y + m_h, m_z - m_b);		// ���� ����
		glTexCoord2f(0.0f, 0.0f);glVertex3f(m_x, m_y, m_z - m_b);		// ��� ����
		glTexCoord2f(1.0f, 0.0f);glVertex3f(m_x + m_a, m_y, m_z - m_b);		// ��� �����
		
		//glColor3f(0.0f,0.0f,1.0f);		// �����

		glTexCoord2f(1.0f, 1.0f);glVertex3f(m_x, m_y + m_h, m_z);		// ���� ����� �������� (����)
		glTexCoord2f(0.0f, 1.0f);glVertex3f(m_x, m_y + m_h, m_z - m_b);		// ���� ����
		glTexCoord2f(0.0f, 0.0f);glVertex3f(m_x, m_y, m_z - m_b);		// ��� ����
		glTexCoord2f(1.0f, 0.0f);glVertex3f(m_x, m_y, m_z);		// ��� �����

		//glColor3f(1.0f,0.0f,1.0f);		// ����������

		glTexCoord2f(1.0f, 1.0f);glVertex3f(m_x + m_a, m_y + m_h, m_z - m_b);		// ���� ����� �������� (�����)
		glTexCoord2f(0.0f, 1.0f);glVertex3f(m_x + m_a, m_y + m_h, m_z);		// ���� ����
		glTexCoord2f(0.0f, 0.0f);glVertex3f(m_x + m_a, m_y, m_z);		// ��� ����
		glTexCoord2f(1.0f, 0.0f);glVertex3f(m_x + m_a, m_y, m_z - m_b);		// ��� �����
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