#include "camera_Node.h"

bool camera_Node::getPerspective() const
{
	return isPerspective;
}
bool camera_Node::getEnabled() const
{
	return isEnabled;
}

void camera_Node::setEnabled(bool boolean)
{
	isEnabled = boolean;
}
void camera_Node::setProjectionMat(glm::mat4 matrix)
{
	projectionMatrix = matrix;
}

void camera_Node::addYaw(float add) { yaw += add; }
float camera_Node::getYaw() const { return yaw; }

void camera_Node::addPitch(float add) { pitch += add; }
float camera_Node::getPitch() const { return pitch; }