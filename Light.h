#pragma once
#include "Vector.h"
struct Light
{
	Vector position;
	Vector ambient;
	Vector diffuse;
	Vector specular;

	float constant;
	float linear;
	float radial;
};