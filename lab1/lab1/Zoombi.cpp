#include "Zoombi.h"

CZoombi::CZoombi(GLfloat x, GLfloat z, Model *pModel)
{
	m_x = x;
	m_y = 0.0f;
	m_z = z;
	m_h = 0.5f;
	m_a = 0.5f;
	m_b = 0.5f;
	m_yrot = 0.0f;
	
	m_heading = 0;

	m_speed = 0.05f;

	piover180 = 0.0174532925f;

	m_pModel = pModel;
}

CZoombi::~CZoombi(void)
{
}

void CZoombi::Draw()
{
	GLfloat sceneroty = 360.0f - m_yrot;
	//glTranslatef((m_x + (m_a / 2.0f)), m_y, (m_z - (m_b / 2.0f))); 
	//glRotatef(sceneroty, 0.0f, 0.0f, 0.0f);

	//m_pModel->draw();

	glBegin(GL_QUADS);
		glVertex3f(m_x + m_a, m_y + m_h, m_z - m_b);		// Право верх квадрата (Верх)
		glVertex3f(m_x, m_y + m_h, m_z - m_b);		// Лево верх
		glVertex3f(m_x, m_y + m_h, m_z);		// Лево низ
		glVertex3f(m_x + m_a, m_y + m_h, m_z);		// Право низ
		
		glVertex3f(m_x + m_a, m_y, m_z - m_b);		// Верх право квадрата (Низ)
		glVertex3f(m_x, m_y, m_z - m_b);		// Верх лево
		glVertex3f(m_x, m_y, m_z);		// Низ лево
		glVertex3f(m_x + m_a, m_y, m_z);		// Низ право

		glVertex3f(m_x + m_a, m_y + m_h, m_z);		// Верх право квадрата (Перед)
		glVertex3f(m_x, m_y + m_h, m_z);		// Верх лево
		glVertex3f(m_x, m_y, m_z);		// Низ лево
		glVertex3f(m_x + m_a, m_y, m_z);		// Низ право

		glVertex3f(m_x + m_a, m_y + m_h, m_z - m_b);		// Верх право квадрата (Зад)
		glVertex3f(m_x, m_y + m_h, m_z - m_b);		// Верх лево
		glVertex3f(m_x, m_y, m_z - m_b);		// Низ лево
		glVertex3f(m_x + m_a, m_y, m_z - m_b);		// Низ право
		
		glVertex3f(m_x, m_y + m_h, m_z);		// Верх право квадрата (Лево)
		glVertex3f(m_x, m_y + m_h, m_z - m_b);		// Верх лево
		glVertex3f(m_x, m_y, m_z - m_b);		// Низ лево
		glVertex3f(m_x, m_y, m_z);		// Низ право

		glVertex3f(m_x + m_a, m_y + m_h, m_z - m_b);		// Верх право квадрата (Право)
		glVertex3f(m_x + m_a, m_y + m_h, m_z);		// Верх лево
		glVertex3f(m_x + m_a, m_y, m_z);		// Низ лево
		glVertex3f(m_x + m_a, m_y, m_z - m_b);		// Низ право
	glEnd();

}

void CZoombi::Update(CGameMap & map, double dt, CPlayer & player)
{
	if (m_NextStepIsCollision(map, dt))
	{
		m_Turn(2.0f);
	}
	else
	{
		m_TakeStep(map, dt);
	}
}

bool CZoombi::m_NextStepIsCollision(CGameMap & map, double dt)
{
	float lastX = m_x;
	float lastZ = m_z;

	m_x -= ((float) sin(m_heading * piover180) * m_speed * (float)dt);// 0.05f отвечает за скорость перемещения
	m_z -= ((float) cos(m_heading * piover180) * m_speed * (float)dt);// 0.05f отвечает за скорость перемещения

	if (CollisionWalls(map))
	{
		m_x = lastX;
		m_z = lastZ;

		return true;
	}
	m_x = lastX;
	m_z = lastZ;

	return false;
}

GLfloat CZoombi::GetX()
{
	return m_x;
}

GLfloat CZoombi::GetY()
{
	return m_y;
}

GLfloat CZoombi::GetZ()
{
	return m_z;
}

GLfloat CZoombi::GetHeight()
{
	return m_h;
}

GLfloat CZoombi::GetA()
{
	return m_a;
}

GLfloat CZoombi::GetB()
{
	return m_b;
}

void CZoombi::m_TakeStep(CGameMap & map, double dt)
{
	float lastX = m_x;
	float lastZ = m_z;

	m_x -= (float) sin(m_heading * piover180) * m_speed * (float)dt;// 0.05f отвечает за скорость перемещения
	m_z -= (float) cos(m_heading * piover180) * m_speed * (float)dt;// 0.05f отвечает за скорость перемещения

	if (CollisionWalls(map))
	{
		m_x = lastX;
		m_z = lastZ;	
	}
}

void CZoombi::m_Turn(GLfloat angle)
{
	m_heading += angle;	
	m_yrot = m_heading;
}

bool CZoombi::Collision(CGemeObject & objA, CGemeObject & objB)
{
	if (objA.GetX() + objA.GetA() > objB.GetX() && objA.GetX() < objB.GetX() + objB.GetA() &&
	objA.GetZ() - objA.GetB() < objB.GetZ() && objA.GetZ() > objB.GetZ() - objB.GetB()) 
	{
        return true;
    }
    
	return false;
}

bool CZoombi::CollisionWalls(CGameMap & map)
{
	for (size_t i = 0; i < map.GetWallsArray().size(); ++i)
	{
		if (Collision (map.GetWallsArray()[i], *this))
		{
			return true;
		}
	}

	return false;
}
