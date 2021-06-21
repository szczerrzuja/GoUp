#include "StableObject.h"
Mesh amake_flashlight()
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

			for (j = 0; j < 16-1; j++)
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
			for (j = 0; j < 16-1; j++)
			{
				//do œrodka
				indices.push_back(i * 16 + j);
				indices.push_back(i * 16 + j + 1);
				indices.push_back(vertices.size() - 1);


			}
			indices.push_back(i * 16 + j+1);
			indices.push_back(i * 16);
			indices.push_back(vertices.size() - 1);

		}
	}
	int tmp = vertices.size();
	for (unsigned int i = 0; i < 2; i++)
	{
		for (unsigned int j = 0; j < 16; j++)
		{
			vertices.push_back({ {0.15f * sinf(2 * 3.14 / 16*j), 0.15f * cosf(2 * 3.14 / 16 * j), -0.10f - 0.70 * i}, {0.0f, 0.0f, 1.0f}, {0.0f, 0.0f},{0.3, 0.3, 0.3, 1.0f} });
		}

	}
	vertices.push_back({ { 0, 0, -0.80 }, { 0.0f, 0.0f, 1.0f }, { 0.0f, 0.0f }, { 0.3, 0.3, 0.3, 1.0f } });
	for (unsigned int i = 0; i < 2; i++)
	{
		if (i == 0)
		{

			for (j = 0; j < 16-1; j++)
			{
				//do œrodka - tego nie bêdzie widaæ

				//œciany boczne
				indices.push_back(i * 16 + j + tmp);
				indices.push_back(i * 16 + j + 1 + tmp);
				indices.push_back((i + 1) * 16 + j + 1+tmp);

				indices.push_back(i * 16 + j + tmp);
				indices.push_back((i + 1) * 16 + j + tmp);
				indices.push_back((i + 1) * 16 + j + 1 + tmp);
			}

			//œciany boczne

			indices.push_back(i * 16 + j + tmp);
			indices.push_back(i * 16 + tmp);
			indices.push_back((i + 1) * 16 + tmp);

			indices.push_back(i * 16 + j + tmp);
			indices.push_back((i + 1) * 16 + j+ tmp);
			indices.push_back((i + 1) * 16 + tmp);

		}
		else if (i == 1)
		{
			for (j = 0; j < 16-1; j++)
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

Mesh make_triangle(glm::vec4 color)
{
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
	vertices.push_back({ {1.0f, 1.0f, 0.0f}, {0.0f, 0.0f, 1.0f}, {0.0f, 0.0f}, color });
	vertices.push_back({ {0.0f, 1.0f, 1.0f}, {0.0f, 0.0f, 1.0f}, {0.0f, 0.0f},color });
	vertices.push_back({ {0.0f, 1.0f, -1.0f}, {0.0f, 0.0f, 1.0f}, {0.0f, 0.0f},color  });
	indices.push_back(0);
	indices.push_back(1);
	indices.push_back(2);
	Mesh mesh(vertices, indices, 0);
	return mesh;
}
Mesh make_square(glm::vec4 color, glm::vec3 scale = {1,1,1})
{

	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
	vertices.push_back({ {1.0f * scale.x, 0.0f, 1.0f * scale.z}, {0.0f, 0.0f, 1.0f}, {0.0f, 0.0f},color });
	vertices.push_back({ {1.0f * scale.x, 0.0f, -1.0f * scale.z}, {0.0f, 0.0f, 1.0f}, {0.0f, 0.0f},color });
	vertices.push_back({ {-1.0f * scale.x, 0.0f, -1.0f * scale.z}, {0.0f, 0.0f, 1.0f}, {0.0f, 0.0f},color });
	vertices.push_back({ {-1.0f * scale.x, 0.0f, 1.0f * scale.z}, {0.0f, 0.0f, 1.0f}, {0.0f, 0.0f},color });
	indices.push_back(0);
	indices.push_back(1);
	indices.push_back(2);
	indices.push_back(0);
	indices.push_back(2);
	indices.push_back(3);
	Mesh mesh(vertices, indices, 0);
	
	return mesh;
}
Mesh make_box(glm::vec4 color, glm::vec3 pos = {0,0,0})
{
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
	vertices.push_back({pos + glm::vec3( 1.0f, 1.0f, 1.0f), {0.0f, 0.0f, 1.0f}, {0.0f, 0.0f},color });
	vertices.push_back({ pos + glm::vec3(1.0f, 1.0f, -1.0f), {0.0f, 0.0f, 1.0f}, {0.0f, 0.0f},color });
	vertices.push_back({ pos + glm::vec3(1.0f, -1.0f, -1.0f), {0.0f, 0.0f, 1.0f}, {0.0f, 0.0f},color });
	vertices.push_back({ pos + glm::vec3(1.0f, -1.0f, 1.0f), {0.0f, 0.0f, 1.0f}, {0.0f, 0.0f},color });
	vertices.push_back({ pos + glm::vec3(-1.0f, 1.0f, 1.0f), {0.0f, 0.0f, 1.0f}, {0.0f, 0.0f},color });
	vertices.push_back({ pos + glm::vec3(-1.0f, 1.0f, -1.0f), {0.0f, 0.0f, 1.0f}, {0.0f, 0.0f},color });
	vertices.push_back({ pos + glm::vec3(-1.0f, -1.0f, -1.0f), {0.0f, 0.0f, 1.0f}, {0.0f, 0.0f},color });
	vertices.push_back({ pos + glm::vec3(-1.0f, -1.0f, 1.0f), {0.0f, 0.0f, 1.0f}, {0.0f, 0.0f},color });
	//œciana nr1
	indices.push_back(0);
	indices.push_back(1);
	indices.push_back(2);

	indices.push_back(0);
	indices.push_back(3);
	indices.push_back(2);
	//œciana nr2
	indices.push_back(0);
	indices.push_back(1);
	indices.push_back(4);

	indices.push_back(1);
	indices.push_back(5);
	indices.push_back(4);

	//œciana nr 3
	indices.push_back(0);
	indices.push_back(7);
	indices.push_back(3);

	indices.push_back(0);
	indices.push_back(7);
	indices.push_back(4);
	//œciana nr 4

	indices.push_back(3);
	indices.push_back(6);
	indices.push_back(7);

	indices.push_back(3);
	indices.push_back(2);
	indices.push_back(6);

	//œciana nr5
	indices.push_back(2);
	indices.push_back(5);
	indices.push_back(6);

	indices.push_back(2);
	indices.push_back(1);
	indices.push_back(5);

	//œciana nr 6
	indices.push_back(4);
	indices.push_back(6);
	indices.push_back(7);

	indices.push_back(4);
	indices.push_back(6);
	indices.push_back(5);

	Mesh mesh(vertices, indices, 0);

	return mesh;
}
Mesh make_Ball(int probingx = 10, int probingy = 10, float range = 1.0f, glm::vec4 color = {1.0f, 1.0f, 1.0f, 1.0f})
{
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
	float stack =  3.14f / probingx, a, sectors = 3.14f * 2 / probingy, phi;
	//tworzenie wiercho³ków
	for (unsigned int i = 0; i <= probingx; i++)
	{
		a = sinf(stack * i);
		if (i == 0)
		{
			vertices.push_back({ {0.0f, 0.0f, range}, {0.0f, 0.0f, 1.0f}, {0.0f, 0.0f}, color });
		}
		if (i == probingx)
		{
			vertices.push_back({ {0.0f, 0.0f, -range}, {0.0f, 0.0f, 1.0f}, {0.0f, 0.0f},color });
		}
		else
		{
			for (unsigned int j = 0; j <= probingy; j++)
			{
				phi = 3.14f/2 -  stack * i;
				vertices.push_back({ 
					{ range * cosf(phi) * cosf(sectors * j),
					range * cosf(phi) * sinf(sectors * j),
					range * sinf(phi) },
					{ 0.0f, 0.0f, 1.0f }, 
					{ 0.0f, 0.0f },color });
			}
		}
		
	}
	//³¹czenie wierzcho³ków
	for (int i = 0; i <= probingx; i++)
	{
		unsigned int j;
	
		if (i == probingx )
		{
			for (j = 0; j <= probingy - 1; j++)
			{
				indices.push_back(vertices.size() - 1);
				indices.push_back(i  * probingx + j);
				indices.push_back(i * probingx + j + 1);
			}
			indices.push_back(vertices.size() - 1);
			indices.push_back(i  * probingx + j);
			
			indices.push_back(i  * probingx);
		}
		else if (i == -1)
		{
			for (j = 0; j <= probingy - 1; j++)
			{
				indices.push_back(0);
				indices.push_back(j);
				indices.push_back(j+1);
			}
			indices.push_back(0);
			indices.push_back(j+1);

			indices.push_back(1);
		}
		else 
		{		
			//zrobienie "Kwadratu"
			for (j = 0; j < probingy; j++)
			{
				indices.push_back(i * probingy + j);
				indices.push_back(i  * probingy + j +1);
				indices.push_back((i + 1) * probingy + j + 1);
				
				indices.push_back((i+1) * probingy + j);
				indices.push_back((i + 1) * probingy + j + 1);
				indices.push_back(i * probingy + j);
			}

		}
	}
	Mesh mesh(vertices, indices, 0);

	return mesh;
}
Mesh make_cone(int probing, float r,float h, glm::vec4 color = {0.0f,0.0f, 0.0f, 1.0f})
{
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
	float rings = 3.14f * 2 / probing;
	vertices.push_back({ {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 1.0f}, {0.0f, 0.0f},color }); //œrodek podstawy
	vertices.push_back({ {0.0f, 0.0f, h}, {0.0f, 0.0f, 1.0f}, {0.0f, 0.0f} ,color }); //czubek
	for (unsigned int i = 0; i < probing; i++)
	{
		vertices.push_back({ {r * sinf(rings * i), r * cosf(rings * i), 0.0f},
			{0.0f, 0.0f, 1.0f}, {0.0f, 0.0f} ,color });
	}
	for (unsigned int i = 2; i < vertices.size()-1; i++)
	{
		indices.push_back(0);
		indices.push_back(i);
		indices.push_back(i+1);
		indices.push_back(1);
		indices.push_back(i);
		indices.push_back(i + 1);
	}
	indices.push_back(0);
	indices.push_back(vertices.size()-1);
	indices.push_back(2);
	indices.push_back(1);
	indices.push_back(vertices.size()-1);
	indices.push_back(2);

	Mesh mesh(vertices, indices,0);
	return mesh;
}
std::vector<Mesh> draw_snnowman(glm::vec3 position)
{
	Mesh tmp;
	std::vector<Mesh> cont;
	// Draw Body
	tmp = make_Ball(20, 20, 0.75f, {1,1,1,1.0f});
	move_mesh(&tmp, {0.0f+ position.x, 0.75f+ position.y, 0.0f+ position.z});
	tmp.setMaterial({  { 0.25f, 0.25f, 0.25f }, { 0.35f,0.35f, 0.35f }, 25.0f });
	cont.push_back(tmp);
	// Draw Head
	tmp = make_Ball(20, 20, 0.25f, { 1,1,1,1.0f });
	move_mesh(&tmp, { 0.0f+ position.x, 1.75f+ position.y, 0.0f+ position.z });
	tmp.setMaterial({ { 0.25f, 0.25f, 0.25f }, { 0.35f,0.35f, 0.35f }, 25.0f });
	cont.push_back(tmp);


	// Draw Eyes
	tmp = make_Ball(20, 20, 0.05f, { 0.0f, 0.0f, 1.0f, 1.0f });
	move_mesh(&tmp, { 0.05f+ position.x, 1.85f+ position.y, 0.18f+ position.z });
	tmp.setMaterial({  { 0.10f, 0.10f, 0.10f }, { 0.60f,0.60f, 0.60f }, 10.0f });
	cont.push_back(tmp);
	tmp = make_Ball(20, 20, 0.05f, { 0.0f, 0.0f, 01.0f, 1.0f });
	move_mesh(&tmp, { -0.05f+ position.x, 1.85f+ position.y, 0.18f+ position.z });
	tmp.setMaterial({  { 0.10f, 0.10f, 0.10f }, { 0.60f,0.60f, 0.60f }, 10.0f });
	cont.push_back(tmp);
	// Draw Nose
	tmp = make_cone(20, 0.08f, 0.5f, { 1.0f, 0.2f, 0.2f, 1.0f });
	move_mesh(&tmp, { 0.0f+ position.x, 1.75f+ position.y, 0.2f+ position.z });
	tmp.setMaterial({  { 0.10f, 0.10f, 0.10f }, { 0.1f,0.0f, 0.0f }, 3.0f });
	cont.push_back(tmp);

	return cont;
}


StableObject::StableObject() : Entity({ 0,0,0 }, {0,0,0})
{

}
StableObject::StableObject(glm::vec3 pos, glm::vec3 rot,int type,glm::vec3 sca, glm::vec4 color): Entity(pos,rot)
{
	std::vector<Mesh> tmp;
	switch(type)
	{
		case 0:
			//tworzy sobie storzek 
			tmp.push_back(make_cone(10, 0.1, 0.6, color));
			move_mesh(&tmp[0], pos);
			tmp[0].applyTransform();
			//box = HitBox(&position, {1.5f, 1.6f, 1.5f});
			mesh.push_back(new Mesh(tmp[0].vertices, tmp[0].indices, 1, tmp[0].material));
			box->scale({ 0.1f, 0.1f, 0.6f });
			scale(sca);
			rotate(rot);
			move(pos);

			break;
		case 1:
			tmp = draw_snnowman({ 0,0,0 });
			for (unsigned int i = 0; i < tmp.size(); i++)
			{
				tmp[i].applyTransform();
				mesh.push_back(new Mesh(tmp[i].vertices, tmp[i].indices, 1, tmp[i].material));
			}
			box->scale({ 1.5f, 1.7f, 1.5f });
			scale(sca);
			rotate(rot);
			move(pos);
			break;
		case 2:
			tmp.push_back(make_box(color, position));
			tmp[0].applyTransform();
			mesh.push_back(new Mesh(tmp[0].vertices, tmp[0].indices, 1, tmp[0].material));
			scale(sca);
			rotate(rot);
			move(pos);
			break;

		case 3:
			//mapa
			tmp.push_back(make_square(color, sca));
			tmp[0].applyTransform();
			mesh.push_back(new Mesh(tmp[0].vertices, tmp[0].indices, 1, tmp[0].material));

			break;
		case 4:
			tmp.push_back(amake_flashlight());
			rotate_mesh(&tmp[0],rot);
			scale_mesh(&tmp[0], sca);
			move_mesh(&tmp[0],pos);
			tmp[0].applyTransform();
			mesh.push_back(new Mesh(tmp[0].vertices, tmp[0].indices, 1, tmp[0].material));
			move(pos);
			break;
		case 5:
			tmp.push_back(make_box(color));
			rotate_mesh(&tmp[0], rot);
			scale_mesh(&tmp[0], sca);
			move_mesh(&tmp[0], pos);
			tmp[0].applyTransform();
			box->scale({ sca.x * 2,sca.y * 2,sca.z * 2 });
			mesh.push_back(new Mesh(tmp[0].vertices, tmp[0].indices, 1, tmp[0].material));
			break;
	}

	
	
	

}
StableObject::~StableObject()
{
	for (unsigned int i = mesh.size() - 1; i > 0; i--)
	{
		delete mesh[i];
		mesh.pop_back();
	}
}
void StableObject::add_velocity(glm::vec3 vel)
{

}
void StableObject::gravity()
{

}
void StableObject::updateEntity(float dt)
{

}
void StableObject::draw(Shader *shader)
{
	for (unsigned int i = 0; i < mesh.size(); i++)
	{
		
		mesh[i]->Draw(shader);
	}
}
void StableObject::rotate( glm::vec3 axis)
{
	for (unsigned int i = 0; i < mesh.size(); i++)
	{
		rotate_mesh(mesh[i], axis.x, {1,0,0});
		rotate_mesh(mesh[i], axis.y, { 0,1,0 });
		rotate_mesh(mesh[i], axis.z, { 0,0,1 });
	}
}
void StableObject::rotate(int angle, glm::vec3 axis)
{
	rotation.x += angle * axis.x;
	rotation.y += angle * axis.y;
	rotation.z += angle * axis.z;
	for (unsigned int i = 0; i < mesh.size(); i++)
	{
		rotate_mesh(mesh[i], angle, axis);
	}
}
void StableObject::move(glm::vec3 pos)
{
	position.x += pos.x;
	position.y += pos.y;
	position.z += pos.z;
	for (unsigned int i = 0; i < mesh.size(); i++)
	{
		move_mesh(mesh[i], pos);
	}
}
void StableObject::scale(glm::vec3 scale)
{
	box->Half_size *= scale;
	for (unsigned int i = 0; i < mesh.size(); i++)
	{
		move_mesh(mesh[i], scale);
	}
}
glm::vec3 StableObject::response(Entity& hit)
{
	return { 0,0,0 };
}