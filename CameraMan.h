#pragma once
#include <GL/glew.h>
#include "glm/glm/glm.hpp"
#include "glm/glm/gtc/matrix_transform.hpp"
#include "LightSource.h"
#include <math.h>
#include "Stable.h"
class CameraMan
{
public:
	glm::vec3 position;
	glm::vec3 rotation;
	glm::mat4 viewMatrix;
	CameraMan();
	CameraMan(glm::vec3 pos, glm::vec3 rot);
	~CameraMan();
	virtual void updateCamera(glm::vec3 pos, glm::vec3 rot);
	virtual void updateCamera_pos(glm::vec3 pos);
	virtual void updateCamera_rot(glm::vec3 rot);
	virtual void setCamera(glm::vec3 pos, glm::vec3 rot);
	//returns camera dir
	virtual glm::vec3 actualizeCamera();
};

