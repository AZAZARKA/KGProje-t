#include "GameMap.h"

CGameMap::CGameMap(string fileName, GLuint texture[2])
{
	//ifstream file(fileName.c_str());//"Maps\map1.txt"
	ifstream file("map1.txt");
	string str = "";
	GLfloat x = 0.0f;
	GLfloat z = 0.0f;
	
	while (file)
	{
		x = 0.0f;
		getline(file, str);

		for (size_t i = 0; i < str.size(); ++i)
		{
			if (str[i] == '#')
			{
				m_walls.push_back(CParallelepiped(x, 0.0f, z, 1.0f, 1.0f, 2.0f, texture[0]));
			}

			m_floor.push_back(CParallelepiped(x, 0.0f, z, 1.0f, 1.0f, 0.0f, texture[1]));
			x += 1.0f;
		}

		z += 1.0f;
	}
	//m_walls.push_back(CParallelepiped(0.0f, 0.0f, 0.0f, 0.5f, 0.5f, 0.5f));
	//m_walls.push_back(CParallelepiped(0.0f, 0.0f, 0.5f, 0.5f, 0.5f, 0.5f));
	//m_walls.push_back(CParallelepiped(0.5f, 0.0f, 0.0f, 0.5f, 0.5f, 0.5f));
	//m_walls.push_back(CParallelepiped(0.0f, 0.0f, -10.0f, 0.5f, 0.5f, 0.5f));

	//m_floor = new CParallelepiped(-20.0f, 0.0f, 20.0f, 40.0f, 40.0f, 0.0f);
}

CGameMap::~CGameMap(void)
{
}

void CGameMap::draw(CVisibileSqear & playerVisions)
{
	//glColor3f(0.0f,0.0f,0.0f);// Предает эффект сумерек

	for (size_t indexOfFloor = 0; m_floor.size() > indexOfFloor; ++indexOfFloor)
	{
		if (Collision(playerVisions, m_floor[indexOfFloor]))
		{
			m_floor[indexOfFloor].draw();
		}
	}

	for (size_t indexOfWall = 0; m_walls.size() > indexOfWall; ++indexOfWall)
	{
		if (Collision(playerVisions, m_walls[indexOfWall]))
		{
			m_walls[indexOfWall].draw();
		}
	}
}

vector<CParallelepiped>& CGameMap::GetWallsArray()
{
	return m_walls;
}

void CGameMap::update()
{
}

bool CGameMap::Collision(CGemeObject & objA, CGemeObject & objB)
{
	if (objA.GetX() + objA.GetA() > objB.GetX() && objA.GetX() < objB.GetX() + objB.GetA() &&
	objA.GetZ() - objA.GetB() < objB.GetZ() && objA.GetZ() > objB.GetZ() - objB.GetB()) 
	{
        return true;
    }
    
	return false;
}