#include "Map.h"

Map::Map()
{
	gro =new StableObject({ 0.0f,-20.0f,0.0f }, { 0.0f,0.0f,0.0f }, 3, { 400.0f,1.0f, 400.0f }, { 0.0f, 0.5f, 0.5f, 1.0f });
	gro->box->Half_size = { 100.0f, 20.0f, 100.0f };
}
Map::~Map()
{
	delete gro;
}

void Map::draw(Shader *shader)
{
	gro->draw(shader);

}
float Map::height(float x, float z)
{
	return 0.0f;
}
bool Map::is_touching(HitBox box2)
{

	return gro->box->getColision(box2);;

}