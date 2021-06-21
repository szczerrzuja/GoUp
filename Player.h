#pragma once
#include "Entity.h"

class Player : public Entity
{
private:
	std::vector<Mesh*> mesh;
public:
	bool is_standing;
	CameraMan* camera;
	int jump_count;
	Player(glm::vec3 pos, glm::vec3 rot);
	~Player();
	void add_velocity(glm::vec3 vel);
	void gravity() override;
	void set_acceleration(glm::vec3 acc);
	void rotate(glm::vec3 rot);
	void updateEntity(float dt) override;
	bool is_coliding(glm::vec3 pos);
	glm::vec3 response(Entity& hit);
	glm::vec3 get_position();
	void draw(Shader* shader);
	void response(HitBox& hit);
	void movePlayer(glm::vec3 pos);

};

