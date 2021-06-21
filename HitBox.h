#pragma once
#include "glm/glm/glm.hpp"
#include <math.h>
#include <vector>
class HitBox
{

	//wykrywanie kolizji za pomoc¹ algorytmu OBB

public:
	glm::vec3 *Position , Half_size;
	bool getColision(HitBox& box2);
	void scale(glm::vec3 sca);
	HitBox(glm::vec3* Pos,  glm::vec3 lenghtInAxis);
	HitBox();
	~HitBox();
};

