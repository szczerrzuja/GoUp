#include "Player.h"
#define SPEED  0.001f
Mesh make_flashlight()
{
	//tutaj rysuje latarke, sk³ada siê z 2 walców
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
	for (unsigned int i = 0; i < 2; i++)
	{
		for (unsigned int j = 0; j < 16; j++)
		{
			vertices.push_back({ {0.35f * sinf(2 * 3.14 / 16 * j), 0.35f * cosf(2 * 3.14 / 16 * j), 0.10f - 0.20 * i}, {0.0f, 0.0f, 1.0f}, {0.0f, 0.0f},{0.5, 0.5, 0.5, 1.0f} });
		}

	}
	vertices.push_back({ { 0, 0, 0.10 }, { 0.0f, 0.0f, 1.0f }, { 0.0f, 0.0f }, { 0.5, 0.5, 0.5, 1.0f } });
	vertices.push_back({ { 0, 0, -0.10 }, { 0.0f, 0.0f, 1.0f }, { 0.0f, 0.0f }, { 0.5, 0.5, 0.5, 1.0f } });
	unsigned int j = 0;
	for (unsigned int i = 0; i < 2; i++)
	{
		if (i == 0)
		{

			for (j = 0; j < 16 - 1; j++)
			{
				//do œrodka
				indices.push_back(i * 16 + j);
				indices.push_back(vertices.size() - 2);
				indices.push_back(i * 16 + j + 1);

				//œciany boczne
				indices.push_back(i * 16 + j);
				indices.push_back(i * 16 + j + 1);
				indices.push_back((i + 1) * 16 + j + 1);

				indices.push_back(i * 16 + j);
				indices.push_back((i + 1) * 16 + j);
				indices.push_back((i + 1) * 16 + j + 1);
			}
			indices.push_back(i * 16 + j);
			indices.push_back(i * 16);
			indices.push_back(vertices.size() - 2);
			//œciany boczne
			indices.push_back(i * 16 + j);
			indices.push_back(i * 16);
			indices.push_back((i + 1) * 16);

			indices.push_back(i * 16 + j);
			indices.push_back((i + 1) * 16 + j);
			indices.push_back((i + 1) * 16);

		}
		else if (i == 1)
		{
			for (j = 0; j < 16 - 1; j++)
			{
				//do œrodka
				indices.push_back(i * 16 + j);
				indices.push_back(i * 16 + j + 1);
				indices.push_back(vertices.size() - 1);


			}
			indices.push_back(i * 16 + j + 1);
			indices.push_back(i * 16);
			indices.push_back(vertices.size() - 1);

		}
	}
	int tmp = vertices.size();
	for (unsigned int i = 0; i < 2; i++)
	{
		for (unsigned int j = 0; j < 16; j++)
		{
			vertices.push_back({ {0.15f * sinf(2 * 3.14 / 16 * j), 0.15f * cosf(2 * 3.14 / 16 * j), -0.10f - 0.70 * i}, {0.0f, 0.0f, 1.0f}, {0.0f, 0.0f},{0.3, 0.3, 0.3, 1.0f} });
		}

	}
	vertices.push_back({ { 0, 0, -0.80 }, { 0.0f, 0.0f, 1.0f }, { 0.0f, 0.0f }, { 0.3, 0.3, 0.3, 1.0f } });
	for (unsigned int i = 0; i < 2; i++)
	{
		if (i == 0)
		{

			for (j = 0; j < 16 - 1; j++)
			{
				//do œrodka - tego nie bêdzie widaæ

				//œciany boczne
				indices.push_back(i * 16 + j + tmp);
				indices.push_back(i * 16 + j + 1 + tmp);
				indices.push_back((i + 1) * 16 + j + 1 + tmp);

				indices.push_back(i * 16 + j + tmp);
				indices.push_back((i + 1) * 16 + j + tmp);
				indices.push_back((i + 1) * 16 + j + 1 + tmp);
			}

			//œciany boczne

			indices.push_back(i * 16 + j + tmp);
			indices.push_back(i * 16 + tmp);
			indices.push_back((i + 1) * 16 + tmp);

			indices.push_back(i * 16 + j + tmp);
			indices.push_back((i + 1) * 16 + j + tmp);
			indices.push_back((i + 1) * 16 + tmp);

		}
		else if (i == 1)
		{
			for (j = 0; j < 16 - 1; j++)
			{
				//do œrodka
				indices.push_back(i * 16 + j + tmp);
				indices.push_back(i * 16 + j + 1 + tmp);
				indices.push_back(vertices.size() - 1);

			}
			indices.push_back(i * 16 + j + tmp);
			indices.push_back(i * 16 + tmp);
			indices.push_back(vertices.size() - 1);

		}

	}
	Mesh mesh(vertices, indices, 0);
	return mesh;
}

Player::Player(glm::vec3 pos, glm::vec3 rot): Entity(pos, rot)
{
	camera = new CameraTP(pos + glm::vec3(0,1.7,0), rot);
	is_standing = true;
	Mesh tmp = make_flashlight();
	move_mesh(&tmp, { 0.0, 1.5, 2.0 });
	tmp.applyTransform();
	mesh.push_back(new Mesh(tmp.vertices, tmp.indices,1));
	move_mesh(mesh[0],pos);
	m_rotate_mesh(mesh[0], rot);
	jump_count = 1;
}
Player::~Player()
{
	delete camera;
}
void Player::add_velocity(glm::vec3 vel)
{
	velocity.x += vel.x;
	velocity.y += vel.y;
	velocity.z += vel.z;
}
void Player::gravity() 
{
	acceleration -= glm::vec3(0.0f, 0.1f * SPEED, 0.0f);
}
//tutaj wrzucam wyjscie klawiatury
void Player::set_acceleration(glm::vec3 vec)
{
	float sinrot = sinf(degtorad * rotation.y);
	float cosrot = cosf(degtorad * rotation.y);
	acceleration =
	{
		(vec.z * sinrot + vec.x * cosrot) * SPEED,
		vec.y  ,
		(vec.z * cosrot - sinrot * vec.x) * SPEED
	};
}
void Player::updateEntity(float dt)
{
	if (!is_standing)
	{
		gravity();
	}
	else
		jump_count = 1;
	glm::vec3 deltaPos = {
		dt*(velocity.x+acceleration.x*dt/2),
		dt* (velocity.y + acceleration.y * dt / 2),
		dt* (velocity.z + acceleration.z * dt / 2) };
	position = {
	position.x + deltaPos.x,
	position.y + deltaPos.y,
	position.z + deltaPos.z
	};
	velocity = {
		velocity.x + acceleration.x * dt - velocity.x / 2,
		velocity.y + acceleration.y * dt,
		velocity.z + acceleration.z * dt - velocity.z / 2
	};
	move_mesh(mesh[0], deltaPos);
	camera->updateCamera_pos(deltaPos);
	camera->actualizeCamera();
}
void Player::rotate(glm::vec3 rot)
{
	

	glm::vec3 drot = glm::vec3(0.0f, 0.0f, 0.0f);

	if (rotation.x > 81.0f)
	{
		drot.x = 81.0f - rotation.x;
	}
	else if (rotation.x < -81.0f)
	{
		drot.x = -81.0f - rotation.x;
	}
	else
		drot.x = rot.x;
	if (rotation.y > 173.0f)
	{
		drot.y = 173.0f - rotation.y;
	}
	else if (rotation.y < -173.0f)
	{
		drot.y = -173.0f - rotation.y;
	}
	else drot.y = rot.y;
	rotation += rot;

	m_rotate_mesh(mesh[0], {drot.x, rot.y, rot.z });
	camera->updateCamera_rot(rot);

}
glm::vec3 Player::get_position()
{
	return position;
}
bool Player::is_coliding(glm::vec3 pos)
{
	return 0;
}
glm::vec3  Player::response(Entity& hit)
{
	glm::vec3 resp = { 0.0f,0.0f,0.0f };
	if (box->getColision(*hit.box))
	{
		resp = position + box->Half_size - *(hit.box->Position) - hit.box->Half_size;
	}
	position -= resp;
	return resp;
}
void Player::draw(Shader* shader)
{
	for (unsigned int i = 0; i < mesh.size(); i++)
	{
		mesh[i]->Draw(shader);
	}
}
void Player::response(HitBox& hit)
{
	glm::vec3 Vdist = { 0.0f,0.0f,0.0f }, abss, temp;
	float max;
	Vdist = position - *hit.Position; 
	//absolute values of vector
	abss = glm::vec3(glm::abs(Vdist.x), glm::abs(Vdist.y), glm::abs(Vdist.z))-box->Half_size - hit.Half_size;
	max = glm::max(glm::max(abss.x, abss.y), abss.z);
	if (max == abss.x)
	{
		if (Vdist.x > 0)
		{
			if (acceleration.x < 0)
				acceleration.x = 0;
			velocity.x = 0.0f;
		}
		else
		{
			if (acceleration.x > 0)
				acceleration.x = 0;
			velocity.x = 0.0f;
		}
	}
	if (max == abss.y)
	{
 		if (Vdist.y > 0)
		{
			if (acceleration.y < 0)
				acceleration.y = 0;
			velocity.y = 0.0f;
			is_standing = true;
	
		}
		else
		{
			if (acceleration.y < 0)
					acceleration.y = 0;
				velocity.y = 0.0f;
				is_standing = false;
				this->movePlayer({ 0,-1.0,0 });
		}

	}
	if (max == abss.z)
	{
		if (Vdist.z > 0)
		{
			if (acceleration.z < 0)
				acceleration.z = 0;
			velocity.z = 0.0f;
		}
		else
		{
			if (acceleration.z > 0)
				acceleration.z = 0;
			velocity.z = 0.0f;
		}
	}
	

}

void Player::movePlayer(glm::vec3 pos)
{
	position += pos;
	move_mesh(mesh[0], pos);
	camera->updateCamera_pos(pos);
}