#pragma once

#include <windows.h>
#include <gl\gl.h>
#include <gl\glu.h>

#include <vector>
#include <string>
#include <fstream>
using namespace std;

#include "Parallelepiped.h"
#include "VisibileSqear.h"

class CGameMap
{
public:
	CGameMap(string fileName, GLuint texture[2]);
	~CGameMap(void);

	void draw(CVisibileSqear & playerVisions);
	vector<CParallelepiped>& GetWallsArray();

	void update();
private:
	bool Collision(CGemeObject & objA, CGemeObject & objB);
	vector<CParallelepiped> m_walls;
	vector<CParallelepiped> m_floor;
};
