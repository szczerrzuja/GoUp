#include "Game.h"


int olds[2] = { 100 + 1280 / 2, 100 + 800 / 2 };
Game::Game()
{
	intKeys();
	fps_cap = 1.0/89 * 1000;
	player = new Player({ 0, 1, 4}, { -10,0,0 });
	timer = Timer();
	ColidingObjects.push_back(new StableObject({ 5,0,0 }, { 0,0,0 }, 1));

	//ColidingObjects.push_back(new StableObject({ 10,10,10 }, { 10,10,10 }, 0));
	//ColidingObjects.push_back(new StableObject({ -5,2,0 }, { 0,0,0 }, 4, { 50,50,50 }));

	programValuesInit;
	initShaders();
	initParkour(50);
	
}
Game::~Game()
{
	for (unsigned int i = ColidingObjects.size() - 1; i > 0; i--)
	{
		delete ColidingObjects[i];
		ColidingObjects.pop_back();
	}
	for (unsigned int i = sources.size() - 1; i > 0; i--)
	{
		delete sources[i];
		sources.pop_back();
	}
	for (unsigned int i = shaders.size() - 1; i > 0; i--)
	{
		delete shaders[i];
		shaders.pop_back();
	}
	delete player;
}
void Game::initParkour(int amount)
{
	for (int i = 0; i < amount; i++)
	{
		ColidingObjects.push_back(new StableObject({ 0.3*i+24 * sinf(3.14 * 2 * i / 12),i * 1.1-1,0.36 * i + 24 * cosf(3.14 * 2 * i / 12) }, { 0,0,0 }, 5,
			{ 2,2,2 }, { sinf(3.14 * 2 * i / 12), cosf(3.14 * 2 * i / 4), sinf(3.14 * 2 * i / 20),1.0f }));
	}
}
void Game::setLighting()
{
	//glm::vec3 pos, glm::vec4 col, glm::vec3 amb, glm::vec3 diff, glm::vec3 spec
	sources.push_back(new LightSource(&shaders, 0, { 10.0f, 0.0f,10.0f }, { 0,0,1,0 }, { 0,0,0.4 }, { 0,0,0.6 }, {0,0,0.5}));
	sources.push_back(new LightSource(&shaders, 0, { 10.0f, 0.0f,-10.0f }, { 0,1,0,0 }, { 0,0.4,0 }, { 0,0.6,0 }, { 0,0.5,0 }));
	sources.push_back(new LightSource(&shaders, 1, { -10.0f, 10.0f,10.0f }));
	sources.push_back(new LightSource(&shaders, 1, { -10.0f, 10.0f,-10.0f }));
	//sources.push_back(new LightSource(&shaders, 2, { 0.0f, 10.0f,0.0f }, {1.0f, 1.0f, 1.0f}, { 0.8f,0.8f,0.8f }, { 0.2f,0.2f,0.2f }, { 0.5f,0.5f,0.5f }));
}
void Game::initShaders()
{
	shaders.push_back(new Shader("Shaders/lighting.vert", "Shaders/lighting.frag"));
	shaders.push_back(new Shader("Shaders/lamp.vert", "Shaders/lamp.frag"));
}
void Game::display()
{
	
	// Clear Color and Depth Buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Reset transformations
	glLoadIdentity();
	// Set the camera
	CameraDir = player->camera->actualizeCamera();
	viewMatrix = player->camera->viewMatrix;
	
	//CameraPosition = player->camera->position;
	shaders[0]->run();
	programValuesInit.setCameraPos( *shaders[0]);
	programValuesInit.setProjetionMatrix(*shaders[0]);
	programValuesInit.test(*shaders[0]);
	programValuesInit.setViewMarix(*shaders[0]);
	GLint lightPosLoc = glGetUniformLocation(shaders[0]->Program, "light.postion");
	glUniform3f(lightPosLoc, player->get_position().x, player->get_position().y+1.0, player->get_position().z-0.5);
	glPushMatrix();
	map.draw(shaders[0]);
	glPopMatrix();
	for (unsigned int i= 0; i < ColidingObjects.size(); i++)
	{
		//objects[i]->rotate(1, { 0,1,0 });
		ColidingObjects[i]->draw(shaders[0]);
	}
	player->draw(shaders[0]);
	glutSwapBuffers();
	
}
void Game::update()
{
	dtime = timer.getDeltaTime();
	if (dtime < fps_cap)
	{
		Sleep((fps_cap - dtime));
		dtime = fps_cap - dtime;
	}
	Keys_procesor();
	if (!map.is_touching(*player->box))
	{
		player->is_standing = false;
		player->gravity();
	}
	else
	{
		player->is_standing = true;
		player->movePlayer({ 0.0f, -player->get_position().y+0.5, 0.0f });

	}

	for (unsigned int i = 0; i < ColidingObjects.size(); i++)
	{

		if (player->box->getColision(*ColidingObjects[i]->box))
		{
			player->response(*ColidingObjects[i]->box);
		}
	}
	player->updateEntity(dtime);
	
	//reakcja gracza z map¹

	//reakcja gracza z innymi obiektami
	ColidingObjects[1]->rotate({ 0,1,0 });
	
}
void Game::reshape(int w, int h)
{
	// Prevent a divide by zero, when window is too short
	// (you cant make a window of zero width).
	if (h == 0)
		h = 1;

	float ratio = w * 1.0 / h;

	// Use the Projection Matrix
	glMatrixMode(GL_PROJECTION);

	// Reset Matrix
	glLoadIdentity();

	// Set the viewport to be the entire window
	glViewport(0, 0, w, h);

	// Set the correct perspective.
	gluPerspective(45.0f, ratio, 0.1f, 100.0f);

	// Get Back to the Modelview
	glMatrixMode(GL_MODELVIEW);
}

void Game::intKeys()
{
	Keys["Forward"] = 'W';
	Keys["Backward"] = 'S';
	Keys["MoveLeft"] = 'A';
	Keys["MoveRight"] = 'D';
	Keys["GoDown"] = 'V';
	Keys["Spacebar"] = 32;
	Keys["Alt"] = 3000;
	Keys["Shift"] = 3001;
	Keys["Ctrl"] = 3002;
	for (auto it = Keys.begin(); it != Keys.end(); ++it)
	{
		is_key_pressed[it->first] = 0;
	}
}
void Game::normal_keys(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 27:
		exit;
		break;	
	}
	if (key > 96 && key < 123)
	{
		key = key - 32;
	}
	for (auto it = Keys.begin(); it != Keys.end(); ++it)
	{
		if (key == it->second)
		{
			is_key_pressed[it->first] = true;
			break;
		}
	}
}

void Game::normal_keys_up(unsigned char key, int x, int y)
{
	if (key > 96 && key < 123)
	{
		key = key - 32;
	}
	for (auto it = Keys.begin(); it != Keys.end(); ++it)
	{
		if (key == it->second)
		{
			is_key_pressed[it->first] = false;
			break;
		}
	}
}
void Game::special_keys(int key, int x, int y)
{
	switch (key)
	{
	case(0x0070): //lewy shift
	case(0x0071)://prawy shift
		is_key_pressed["Shift"] = true;
		break;
	case(0x0072): //lewy ctrl
	case(0x0073): //prawy ctrl
		is_key_pressed["Ctrl"] = true;
		break;
	case(0x0074)://lewy alt
	case(0x0075)://prawy alt
		is_key_pressed["Alt"] = true;
		break;
	}
}
void Game::special_keys_up(int key, int x, int y)
{
	switch (key)
	{
	case(0x70): //lewy shift
	case(0x71)://prawy shift
		is_key_pressed["Shift"] = false;
		break;
	case(0x72): //lewy ctrl
	case(0x73): //prawy ctrl
		is_key_pressed["Ctrl"] = false;
		break;
	case(0x74)://lewy alt
	case(0x75)://prawy alt
		is_key_pressed["Alt"] = false;
		break;
	}
}
void Game::special_special_keys()
{
	if (glutGetModifiers() == GLUT_ACTIVE_SHIFT)
	{
		is_key_pressed["Shift"] = true;
	}
	if (glutGetModifiers() == GLUT_ACTIVE_CTRL)
	{
		is_key_pressed["Ctrl"] = true;
	}
	if (glutGetModifiers() == GLUT_ACTIVE_ALT)
	{
		is_key_pressed["Alt"] = true;
	}
}
void Game::move_mouse(int x, int y)
{
	player->rotate( { float(y - olds[1]) * 0.05f,float(x - olds[0]) * 0.05f,0 });
	glutWarpPointer(olds[0], olds[1]);
}
void Game::special_special_keys_up()
{
	is_key_pressed["Shift"] = false;
	is_key_pressed["Ctrl"] = false;
	is_key_pressed["Alt"] = false;
}
void Game::Keys_procesor()
{
	glm::vec3 add_acc = { 0.0f,0.0f,0.0f };
	if (is_key_pressed["Forward"])
	{
		add_acc.z += 1.0f;
	}
	if (is_key_pressed["Backward"])
	{
		add_acc.z += -1.0f;
	}
	if (is_key_pressed["MoveLeft"])
	{
		add_acc.x += 1.0f;
	}
	if (is_key_pressed["MoveRight"])
	{
		add_acc.x += -1.0f;
	}
	if (is_key_pressed["Spacebar"])
	{
		if (player->is_standing )
		{
			player->is_standing = false;
			add_acc.y += 0.0025f;
		}

	}
	if (is_key_pressed["GoDown"])
	{
		add_acc.y += -5.0f;
	}
	player->set_acceleration(add_acc);

	/*
	if (is_key_pressed["Ctrl"])
	{
		camera->updateCamera({ 0,-1,0 }, { 0, 0, 0 });
	}
	if (is_key_pressed["Alt"])
	{
		camera->updateCamera({ 0,-1,0 }, { 0, 0, 0 });
	}
	if (is_key_pressed["Shift"])
	{
		camera->updateCamera({ 0,-1,0 }, { 0, 0, 0 });
	}
	*/
}