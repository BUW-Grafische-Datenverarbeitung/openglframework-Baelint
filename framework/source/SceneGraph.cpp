#include "SceneGraph.h"

std::string SceneGraph::getName() const
{
	return name;
}

void SceneGraph::setName(std::string new_name)
{
	name = new_name;
}

//void SceneGraph::setRoot(Node::Node new_root const&) {root = new_root }
//Node::Node& getRoot() const {return root;}   //needs checking for const correctness