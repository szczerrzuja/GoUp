#include "Ground.h"
float maxh = 15.0f;
Ground::Ground()
{
	/*
	startPoint = {-50, 0, -50};
	lenght = 100;
	//height generation
	int j = 0;
	for (int i = 0; i < lenght; i++)
	{

		for (j = 0; j < lenght; j++)
		{
			if (j + startPoint.z<50 && j - startPoint.z>-50 && i + startPoint.x<50 && i + startPoint.x>-50)
				heightMap[i + startPoint.x][j + startPoint.z] = 0.0f;
			else
			{ 
				std::srand(i + j);
				heightMap[i + startPoint.x][j + startPoint.z] = (float)(std::rand() % int(maxh));
			}
				
		}
		
	}
	*/
}
Ground::~Ground()
{

}
float Ground::getHeight(float x, float y)
{
	return 0;
}
void Ground::drawGround()
{
	/*
	int j = 0;
	for (int i = 0; i < lenght-1; i++)
	{
		j = 0;
		glBegin(GL_TRIANGLES);
			glVertex3d(i - lenght, heightMap[i + startPoint.x][j + startPoint.z], j - lenght);
			glVertex3d(i + 1 - lenght, heightMap[i + 1 + startPoint.x][j + startPoint.z], j - lenght);
			glVertex3d(i - lenght, heightMap[i + startPoint.x][j + 1 + startPoint.z], j + 1 - lenght);
		glEnd;
		for (j = 1; j < lenght-1; j++)
		{
			//zmieñ metode mo¿e podziel na chunki
			glBegin(GL_TRIANGLES);
				glVertex3d(i - lenght, heightMap[i + startPoint.x][j + startPoint.z], j - lenght);
				glVertex3d(i + 1 - lenght, heightMap[i + 1 + startPoint.x][j + startPoint.z], j - lenght);
				glVertex3d(i - lenght, heightMap[i + startPoint.x][j + 1 + startPoint.z], j + 1 - lenght);
			glEnd;
			glBegin(GL_TRIANGLES);
				glVertex3d(i - lenght, heightMap[i + startPoint.x][j + startPoint.z], j - lenght);
				glVertex3d(i - lenght, heightMap[i + startPoint.x][j + 1 + startPoint.z], j + 1 - lenght);
				glVertex3d(i - 1 - lenght, heightMap[i - 1 + startPoint.x][j + 1 + startPoint.z], j + 1 - lenght);
			glEnd;
		}
		glBegin(GL_TRIANGLES);
		glVertex3d(i - lenght, heightMap[i + startPoint.x][j + startPoint.z], j - lenght);
		glVertex3d(i - lenght, heightMap[i  + startPoint.x][j + 1 + startPoint.z], j + 1 - lenght);
		glVertex3d(i - 1 - lenght, heightMap[i - 1 + startPoint.x][j + 1 + startPoint.z], j + 1 - lenght);
		glEnd;
	}
	*/
}