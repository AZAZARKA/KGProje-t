#pragma once

#include <windows.h>
#include <gl\gl.h>
#include <gl\glu.h>
#include <math.h>

#include "Constants.h"
#include "GemeObject.h"
#include "GameMap.h"
#include "Player.h"

#include "modelsCode/MilkshapeModel.h"//не робит(((

#include "Parallelepiped.h"

class CGuardian : public CGemeObject
{
public:
	CGuardian(GLfloat x, GLfloat z, Model *pModel);
	~CGuardian(void);

	void Draw();
	void Update(CGameMap & map, double dt, CPlayer & player);

	GLfloat GetX();
	GLfloat GetY();
	GLfloat GetZ();
	GLfloat GetHeight();
	GLfloat GetA();
	GLfloat GetB();
private:
	void m_TakeStep(CGameMap & map, double dt);
	void m_Turn(GLfloat angle);

	bool m_NextStepIsCollision(CGameMap & map, double dt);

	bool Collision(CGemeObject & objA, CGemeObject & objB);
	bool CollisionWalls(CGameMap & map);

	GLfloat m_x, m_y, m_z, m_h, m_a, m_b;
	GLfloat	m_yrot;
	GLfloat m_speed;

	Model *m_pModel;

	float m_heading;
	float piover180;
};
