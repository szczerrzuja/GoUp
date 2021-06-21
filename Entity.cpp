#include "Entity.h"
Entity::Entity(glm::vec3 pos, glm::vec3 rot)
{
	
	position = pos;
	rotation = rot;
	velocity = { 0,0,0 };
	acceleration = {0,0,0};
	box = new HitBox(&position, { 1.0f,1.0f,1.0f });
}
Entity::~Entity()
{

}
