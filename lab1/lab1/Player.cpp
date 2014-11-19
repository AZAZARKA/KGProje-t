#include "Player.h"

CPlayer::CPlayer(GLfloat x, GLfloat y, GLfloat z)
{
	 m_x = x;
	 m_y = y;
	 m_z = z;

	 m_heading = 0;
	 m_xpos = x;
	 m_zpos = z;
	 m_yrot = 0;

	 m_walkbias = 0;
	 m_walkbiasangle = 0;
	 m_lookupdown = 0.0f;

	 m_isMove = false;

	 m_speed = 0.5f;
}

CPlayer::~CPlayer(void)
{
}

void CPlayer::MakeStepUp(CGameMap & map, double dt)
{
	float lastX = m_xpos;
	float lastZ = m_zpos;

	m_xpos -= (float) sin(m_heading * piover180) * m_speed * (float)dt;// 0.05f отвечает за скорость перемещения
	m_zpos -= (float) cos(m_heading * piover180) * m_speed * (float)dt;// 0.05f отвечает за скорость перемещения

	m_isMove = true;

	m_x = m_xpos;
	m_z = m_zpos;

	if (CollisionWalls(map))
	{
		m_xpos = lastX;
		m_zpos = lastZ;
		m_x = m_xpos;
		m_z = m_zpos;
	}
}

void CPlayer::MakeStepDown(CGameMap & map, double dt)
{
	float lastX = m_xpos;
	float lastZ = m_zpos;

	m_xpos += (float)sin(m_heading*piover180) * m_speed * (float)dt;// 0.05f отвечает за скорость перемещения
	m_zpos += (float)cos(m_heading*piover180) * m_speed * (float)dt;// 0.05f отвечает за скорость перемещения
	
	m_isMove = true;

	m_x = m_xpos;
	m_z = m_zpos;

	if (CollisionWalls(map))
	{
		m_xpos = lastX;
		m_zpos = lastZ;
		m_x = m_xpos;
		m_z = m_zpos;
	}
}

void CPlayer::MakeStepLeft(CGameMap & map, double dt)
{
	float lastX = m_xpos;
	float lastZ = m_zpos;

	m_xpos -= (float) sin((m_heading + 90.0f) * piover180) * m_speed * (float)dt;// 0.05f отвечает за скорость перемещения
	m_zpos -= (float) cos((m_heading + 90.0f) * piover180) * m_speed * (float)dt;// 0.05f отвечает за скорость перемещения

	m_isMove = true;

	m_x = m_xpos;
	m_z = m_zpos;

	if (CollisionWalls(map))
	{
		m_xpos = lastX;
		m_zpos = lastZ;
		m_x = m_xpos;
		m_z = m_zpos;
	}
}

void CPlayer::MakeStepRight(CGameMap & map, double dt)
{
	float lastX = m_xpos;
	float lastZ = m_zpos;

	m_xpos += (float)sin((m_heading + 90.0f)*piover180) * m_speed * (float)dt;// 0.05f отвечает за скорость перемещения
	m_zpos += (float)cos((m_heading + 90.0f)*piover180) * m_speed * (float)dt;// 0.05f отвечает за скорость перемещения
	
	m_isMove = true;

	m_x = m_xpos;
	m_z = m_zpos;

	if (CollisionWalls(map))
	{
		m_xpos = lastX;
		m_zpos = lastZ;
		m_x = m_xpos;
		m_z = m_zpos;
	}
}

void CPlayer::MakeTurn(GLfloat angleLeftRight, GLfloat angleUpDown)
{
	m_heading += angleLeftRight;	
	m_yrot = m_heading;

	m_lookupdown += angleUpDown;
}

void CPlayer::SetCamera()
{
	if (m_isMove)
	{
		if (m_walkbiasangle <= 1.0f)
		{
			m_walkbiasangle = 359.0f;
		}
		else
		{
			m_walkbiasangle-= 10;
		}

		m_walkbias = (float)sin(m_walkbiasangle * piover180)/20.0f;//дерганья
	}

	GLfloat xtrans = - m_xpos;
	GLfloat ztrans = - m_zpos;
	GLfloat ytrans = - m_walkbias - 0.25f;
	GLfloat sceneroty = 360.0f - m_yrot;

	glRotatef(m_lookupdown, 1.0f, 0, 0);
	glRotatef(sceneroty, 0, 1.0f, 0);
	
	glTranslatef(xtrans, ytrans, ztrans);

	m_isMove = false;
}

GLfloat CPlayer::GetX()
{
	return m_x - 0.2f;
}

GLfloat CPlayer::GetY()
{
	return m_y;
}

GLfloat CPlayer::GetZ()
{
	return m_z + 0.2f;
}

GLfloat CPlayer::GetHeight()
{
	return 0.0f;
}

GLfloat CPlayer::GetA()
{
	return 0.4f;
}

GLfloat CPlayer::GetB()
{
	return 0.4f;
}

bool CPlayer::Collision(CGemeObject & objA, CGemeObject & objB)
{
	if (objA.GetX() + objA.GetA() > objB.GetX() && objA.GetX() < objB.GetX() + objB.GetA() &&
	objA.GetZ() - objA.GetB() < objB.GetZ() && objA.GetZ() > objB.GetZ() - objB.GetB()) 
	{
        return true;
    }
    
	return false;
}

bool CPlayer::CollisionWalls(CGameMap & map)
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

void CPlayer::DrawMarks()
{
	for (size_t i = 0; marks.size() > i; ++i)
	{
		marks[i].draw();
	}
}

void CPlayer::PutMark(GLuint texture)
{
	marks.push_back(CParallelepiped(m_x, 0.001f, m_z + 0.2f, 0.5f, 0.5f, 0.0f, texture));
}