#pragma once

#include <windows.h>
#include <gl\gl.h>
#include <gl\glu.h>
#include <math.h>

#include <vector>

#include "Constants.h"
#include "GemeObject.h"
#include "GameMap.h"
#include "Parallelepiped.h"

const float piover180 = 0.0174532925f;

class CPlayer : public CGemeObject
{
public:
	CPlayer(GLfloat x, GLfloat y, GLfloat z);
	~CPlayer(void);
	
	void MakeStepUp(CGameMap & map, double dt);
	void MakeStepDown(CGameMap & map, double dt);
	void MakeStepLeft(CGameMap & map, double dt);
	void MakeStepRight(CGameMap & map, double dt);
	void MakeTurn(GLfloat angleLeftRight, GLfloat angleUpDown);

	void SetCamera();

	void DrawMarks();
	void PutMark(GLuint texture);

	GLfloat GetX();
	GLfloat GetY();
	GLfloat GetZ();
	GLfloat GetHeight();
	GLfloat GetA();
	GLfloat GetB();
private:
	bool Collision(CGemeObject & objA, CGemeObject & objB);
	bool CollisionWalls(CGameMap & map);

	GLfloat m_x, m_y, m_z;

	GLfloat m_speed;

	std::vector<CParallelepiped> marks;

	bool m_isMove;

	float m_heading;
	float m_xpos;
	float m_zpos;

	GLfloat	m_yrot;
	GLfloat m_walkbias;
	GLfloat m_walkbiasangle;
	GLfloat m_lookupdown;		
};
