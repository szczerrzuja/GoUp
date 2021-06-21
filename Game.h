#pragma once
#include "Player.h"
#include "Timer.h"
#include "Map.h"
#include <map>
#include "initProgVal.h"
#include "glm/glm/glm.hpp"
class Game
{
private:
	Player *player;
	Timer timer;
	double dtime;
	double fps_cap;
	std::map<std::string, int> Keys;
	std::map<std::string, bool> is_key_pressed;
	Map map;	
	std::vector<StableObject*> ColidingObjects;
	std::vector<Shader*> shaders;
	std::vector<LightSource*> sources;
	initProgVal programValuesInit;
public:
	Game();
	~Game();
	void initParkour(int amount);
	void initShaders();
	void display();
	void update();
	void reshape(int w, int h);
	void intKeys();
	void normal_keys(unsigned char key, int x, int y);
	void normal_keys_up(unsigned char key, int x, int y);
	void Keys_procesor();
	void special_keys_up(int key, int x, int y);
	void special_keys(int key, int x, int y);
	void special_special_keys();
	void special_special_keys_up();
	void move_mouse(int x, int y);
	void setLighting();
};
