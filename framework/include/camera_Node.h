#ifndef CAMERA_NODE_HPP
#define CAMERA_NODE_HPP
#include <glm/glm.hpp>
#include <Node.hpp>

struct camera_Node : public Node //usally used for smaller/easier things, default is public so we set our get/set variables to private for better protection
                                 //Added it being a child of Node.
{
private:
    //camera_Node() : Node(<#initializer#>, <#initializer#>) {}

    bool isPerspective = true; // or better false? don't want to leave it uninitialized to avoid mistakes calling an undef
	bool isEnabled = true;
	glm::mat4 projectionMatrix = glm::mat4(1.0f);


public:

	//all WIP
	bool getPerspective() const;
	bool getEnabled() const;
	const glm::mat4& getProjectionMat() const;

	void setEnabled(bool boolean);
	void setProjectionMat(glm::mat4 const& matrix); //TODO: lookup const ref
};

#endif