#pragma once

#include <windows.h>		// Заголовочный файл для Windows
#include <gl\gl.h>			// Заголовочный файл для OpenGL32 библиотеки
#include <gl\glu.h>			// Заголовочный файл для GLu32 библиотеки
#include "Zoombi.h"
#include "Constants.h"
#include "GemeObject.h"
#include "Parallelepiped.h"

using namespace std;

class CSpawn
{
public:
	CSpawn(GLfloat x, GLfloat z);
	~CSpawn(void);

	void Draw();
	void Update(CGameMap & gameMap, double dt, CPlayer & player);

	void CreateZoombi(double dt);
	std::vector<CZoombi> GetZoombiesArray();

private:
	CParallelepiped * parallel;
	GLfloat m_x, m_y, m_z, m_a, m_b, m_h;

	double createTime;

	std::vector<CZoombi> m_zoombies;

	bool Collision(CGemeObject & objA, CGemeObject & objB);
	bool CollisionZoombi();
};
