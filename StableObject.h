#pragma once
#include "Entity.h"
class StableObject :
    public Entity
{
private:
	std::string model_type;

public:

	std::vector<Mesh*> mesh;
	StableObject();
	StableObject(glm::vec3 pos, glm::vec3  rot, int type, glm::vec3 sca = {1,1,1}, glm::vec4 color = { 0,0,0,1 });
	~StableObject();
	virtual void add_velocity(glm::vec3  vel);
	virtual void gravity();
	virtual void updateEntity(float dt);
	virtual void draw(Shader *shader);
	glm::vec3 response(Entity& hit);
	void rotate(int angle, glm::vec3 axis); 
	void move(glm::vec3 pos);
	void scale(glm::vec3 scale);
	void rotate(glm::vec3 axis);
};

