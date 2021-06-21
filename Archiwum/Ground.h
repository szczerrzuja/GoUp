#pragma once

#include "CameraMan.h"
#include <map>
#include <string>
#include <stdio.h>
#include <windows.h>
#include <math.h>
class Ground
{
private:
	std::map< int, std::map< int, float> > heightMap;
	Vector startPoint;
	int lenght;
public:
	Ground();
	~Ground();
	float getHeight(float x, float y);
	void drawGround();
};

