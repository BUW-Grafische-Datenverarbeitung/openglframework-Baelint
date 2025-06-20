#include "camera_Node.h"


//all WIP
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
void camera_Node::setProjectionMat(glm::mat4 const& matrix) //TODO: lookup const ref
{
	projectionMatrix = matrix;
}

const glm::mat4& camera_Node::getProjectionMat() const
{
	return projectionMatrix;
}
