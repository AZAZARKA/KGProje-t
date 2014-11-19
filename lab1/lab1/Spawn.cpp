#include "Spawn.h"

CSpawn::CSpawn(GLfloat x, GLfloat z)
{
	m_x = x; 
	m_y = 0.0f; 
	m_z = z; 
	m_a = 0.5f; 
	m_b = 0.5f; 
	m_h = 0.1f;

	parallel = new CParallelepiped(m_x, m_y, m_z, m_a, m_b, m_h, 0);

	createTime = 0.0;
}

CSpawn::~CSpawn(void)
{
	delete parallel;
}

void CSpawn::CreateZoombi(double dt)
{
	if (createTime >= 40.0)
	{
		if (!CollisionZoombi())
		{
			m_zoombies.push_back(CZoombi(m_x, m_z, NULL));
		}

		createTime = 0.0;
	}
	else
	{
		createTime += dt;
	}
}

bool CSpawn::Collision(CGemeObject & objA, CGemeObject & objB)
{
	if (objA.GetX() + objA.GetA() > objB.GetX() && objA.GetX() < objB.GetX() + objB.GetA() &&
	objA.GetZ() - objA.GetB() < objB.GetZ() && objA.GetZ() > objB.GetZ() - objB.GetB()) 
	{
        return true;
    }
    
	return false;
}

bool CSpawn::CollisionZoombi()
{
	for (size_t i = 0; i < m_zoombies.size(); ++i)
	{
		if (Collision (m_zoombies[i], *parallel))
		{
			return true;
		}
	}

	return false;
}

std::vector<CZoombi> CSpawn::GetZoombiesArray()
{
	return m_zoombies;
}

void CSpawn::Update(CGameMap & gameMap, double dt, CPlayer & player)
{	
	for (size_t indexOfWall = 0; m_zoombies.size() > indexOfWall; ++indexOfWall)
	{
		m_zoombies[indexOfWall].Update(gameMap, dt, player);
	}
}

void CSpawn::Draw()
{
	parallel->draw();

	for (size_t indexOfWall = 0; m_zoombies.size() > indexOfWall; ++indexOfWall)
	{
		m_zoombies[indexOfWall].Draw();
	}
}