#pragma once
#include "CameraTP.h"
#include "Mesh.h"
#include "LightSource.h"
#include "HitBox.h"
class Entity
{
protected:

	glm::vec3 position, rotation, velocity, acceleration;
public:
	HitBox *box;
	Entity(glm::vec3 pos, glm::vec3 rot);
	~Entity();
	virtual void add_velocity(glm::vec3 vel) = 0;
	virtual void gravity() = 0;
	virtual void updateEntity(float dt) = 0;
	virtual void draw(Shader* shader) = 0;
	virtual glm::vec3 response(Entity& hit) = 0;
};

