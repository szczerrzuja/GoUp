#include "CameraMan.h"
void CrossProduct(float* A, float* B, float* result)
{
	result[0] = (A[1] * B[2]) - (A[2] * B[1]);
	result[1] = (A[2] * B[0]) - (A[0] * B[2]);
	result[2] = (A[0] * B[1]) - (A[1] * B[0]);
}


CameraMan::CameraMan()
{
	this->viewMatrix = glm::mat4(1.0f);
	position.x = 0.0f;
	position.y = 0.0f;
	position.z = 0.0f;
	rotation.x = 0.0f;
	rotation.y = 0.0f;
	rotation.z = 0.0f;
	actualizeCamera();
}
CameraMan::CameraMan(glm::vec3 pos, glm::vec3 rot)
{
	this->viewMatrix = glm::mat4(1.0f);
	position.x = pos.x;
	position.y = pos.y;
	position.z = pos.z;
	rotation.x = rot.x;
	rotation.y = rot.y;
	rotation.z = rot.z;
	actualizeCamera();
}
CameraMan::~CameraMan()
{
	
}
void CameraMan::updateCamera(glm::vec3 pos, glm::vec3 rot)
{
	position.x += pos.x;
	position.y += pos.y;
	position.z += pos.z;
	rotation.x += rot.x;
	rotation.y += rot.y;
	rotation.z += rot.z;
}
void CameraMan::updateCamera_pos(glm::vec3 pos)
{
	position.x = pos.x;
	position.y = pos.y;
	position.z = pos.z;
}
void CameraMan::updateCamera_rot(glm::vec3 rot)
{
	rotation.x = rot.x;
	rotation.y = rot.y;
	rotation.z = rot.z;
}
void CameraMan::setCamera(glm::vec3 pos, glm::vec3 rot)
{
	position.x = pos.x;
	position.y = pos.y;
	position.z = pos.z;
	rotation.x = rot.x;
	rotation.y = rot.y;
	rotation.z = rot.z;
}
glm::vec3 CameraMan::actualizeCamera()
{
	
	float a = sinf(degtorad * this->rotation.x), 
		b = sinf(degtorad * this->rotation.y),
		c = sinf(degtorad * this->rotation.z),
		d = cosf(degtorad * this->rotation.x),
		e = cosf(degtorad * this->rotation.y),
		h = cosf(degtorad * this->rotation.z);
	//gluLookAt(x, 1.0f, z,		x + lx, 1.0f, z + lz,		0.0f, 1.0f, 0.0f);
	/*
	gluLookAt( position[0], 
		position[1], 
		position[2], 
		position[0] + (h * b - c * a * e),
		position[1] + (b * d * c - a * e),
		position[2] - (-a * c * b + d * e) ,
		-e * c * d - a * b,
		a * b * c + d * h,
		b * d * c - a * h
		); 
	gluLookAt(
		position[0],
		position[1],
		position[2],
		position[0] + (h * b  - c * a * e),
		position[1] + (d * c * b - a * h),
		position[2] + (a * c * b - d * e),
		a * b + e * c * d,
		a * b * c + d * h,
		b * d * c - a * e
	gluLookAt(
		position[0],
		position[1],
		position[2],
		position[0] + (h * b - c * a * e),
		position[1] + (d * c * b - a * h),
		position[2] + (a * c * b - d * e),
		-c * d + a * h * b,
		a * b * c + d * h,
		b * d * c - a * e
		*/
	// float tVec[3] = { 0,1,0};
	glm::vec3 tVec = { 0.0f,a * b * c + d * h,0.0f };
	glm::vec3 forward = { d * h * b + a * c, d * b * c - h * a, d * e + b * c * a };

	glm::vec3 right = glm::normalize(glm::cross(forward, tVec));
	glm::vec3 up = glm::normalize(glm::cross(right, forward));

	CameraPosition = position;
	viewMatrix = glm::lookAt(position, position + forward, up);
	/*
	gluLookAt(
		position.x,
		position.y,
		position.z,
		position.x + forward[0],
		position.y + forward[1],
		position.z + forward[2],
		up[0],
		up[1],
		up[2]
	); */
	return forward;
}
