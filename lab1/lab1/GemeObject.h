#pragma once

#include <windows.h>
#include <gl\gl.h>
#include <gl\glu.h>
#include <math.h>

class CGemeObject
{
public:
	CGemeObject(void);
	virtual ~CGemeObject(void);

	virtual GLfloat GetX() = 0;
	virtual GLfloat GetY() = 0;
	virtual GLfloat GetZ() = 0;
	virtual GLfloat GetHeight() = 0;
	virtual GLfloat GetA() = 0;
	virtual GLfloat GetB() = 0;
private:
};
