// Gl_template.c
//Wy³šczanie b³êdów przed "fopen"
#define  _CRT_SECURE_NO_WARNINGS
#include "Game.h"
Game* game;
// the key states. These variables will be zero
//when no key is being presses
void display()
{
	game->update();
	game->display();
}
void reshape(int w, int h)
{
	game->reshape(w,h);
}
void normal_keys(unsigned char key, int x, int y)
{
	game->normal_keys( key,  x, y);
}
void normal_keys_up(unsigned char key, int x, int y)
{
	game->normal_keys_up(key, x, y);
}
void special_keys(int key, int x, int y)
{
	game->special_keys(key, x, y);
}
void special_keys_up(int key, int x, int y)
{
	game->special_keys_up(key, x, y);
}
void move_mouse(int x, int y)
{
	game->move_mouse(x, y);
}
int main(int argc, char** argv) {
	
	// init GLUT and create window
	glewExperimental = GL_TRUE;
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(1280, 800);
	glutInit(&argc, argv);
	glutCreateWindow("GoUP");
	/*
	glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	const float lightPos[4] = { 10, .5, 10, 0.1 },
		Ambient[4] = {0.2, 0.2, 0.2 , 1.0 },
		Specular[4] = { 0.8, 0.8, 0.8 , 1.0 },
		Diffuse[4] = { 1.0, 1.0, 1.0 , 1.0 };
	glLightfv(GL_LIGHT0, GL_AMBIENT, Ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, Specular);
	glLightfv(GL_LIGHT0, GL_SPECULAR, Diffuse);
	
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
	*/
	glEnable(GL_DEPTH_TEST);
	glClearColor(1.0, 1.0, 1.0, 1.0);

	GLenum err = glewInit();
	if (GLEW_OK != err)
	{
		/* Problem: glewInit failed, something is seriously wrong. */
		fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
	}
	// register callbacks
	game = new Game();
	glutDisplayFunc(display);
	
	glutReshapeFunc(reshape);
	glutIdleFunc(display);
	glutKeyboardFunc(normal_keys);
	glutKeyboardUpFunc(normal_keys_up);
	glutSpecialFunc(special_keys);
	glutSpecialUpFunc(special_keys_up);
	// here are the two new functions
	//glutMouseFunc(mouseButton);
	glutMotionFunc(move_mouse);
	glutPassiveMotionFunc(move_mouse);
	// OpenGL init
	glEnable(GL_DEPTH_TEST);
	// enter GLUT event processing cycle
	glutMainLoop();
	return 1;
}

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    main(__argc, __argv);

}

