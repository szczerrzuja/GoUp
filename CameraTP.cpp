#include "CameraTP.h"
CameraTP::CameraTP() : CameraMan()
{

}
CameraTP::CameraTP(glm::vec3 pos, glm::vec3 rot) :CameraMan(pos, rot)
{

}
CameraTP::~CameraTP()
{

}
void CameraTP::updateCamera(glm::vec3 pos, glm::vec3 rot)
{
	position.x += pos.x;
	position.y += pos.y;
	position.z += pos.z;
	rotation.x += rot.x;
	rotation.y += rot.y;
	rotation.z += rot.z;
	check_rot();

}
void CameraTP::updateCamera_pos(glm::vec3 pos)
{
	position.x += pos.x;
	position.y += pos.y;
	position.z += pos.z;
}
void CameraTP::updateCamera_rot(glm::vec3 rot)
{
	rotation.x += rot.x;
	rotation.y += rot.y;
	rotation.z += rot.z;
	check_rot();
}
void CameraTP::setCamera(glm::vec3 pos, glm::vec3 rot)
{
	position.x = pos.x;
	position.y = pos.y;
	position.z = pos.z;
	rotation.x = rot.x;
	rotation.y = rot.y;
	rotation.z = rot.z;
	check_rot();
}
void CameraTP::check_rot()
{
	if (rotation.x > 81.0f)
	{
		rotation.x = 80.0f;
	}
	else if (rotation.x < -81.0f)
	{
		rotation.x = -80.0f;
	}
	if (rotation.y > 183.0f)
	{
		rotation.y -= 360.0f;
	}
	else if (rotation.y < -183.0f)
	{
		rotation.y += 360.0f;
	}
}
