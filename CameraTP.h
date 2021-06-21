#pragma once
#include "CameraMan.h"
class CameraTP :
    public CameraMan
{
public:
	CameraTP();
	CameraTP(glm::vec3 pos, glm::vec3 rot);
	~CameraTP();
	void updateCamera(glm::vec3 pos, glm::vec3 rot) override;
	void updateCamera_pos(glm::vec3 pos) override;
	void updateCamera_rot(glm::vec3 rot) override;
	void setCamera(glm::vec3 pos, glm::vec3 rot) override;
	void check_rot();

};

