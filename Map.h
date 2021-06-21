#pragma once
#include <GL/glew.h>
#include "glm/glm/glm.hpp"
#include "HitBox.h"
#include "StableObject.h"
class Map
{
private:

public:
	StableObject* gro;
	Map();
	~Map();
	void draw(Shader *shader);
	float height(float x, float z);
	bool is_touching(HitBox box2);
};

