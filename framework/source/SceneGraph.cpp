#include "SceneGraph.h"
#include "node.hpp"
#include "camera_Node.h"
#include "GeometryNode.hpp"
#include <string>
#include <vector>

std::string SceneGraph::getName() const
{
	return name_;
}

void SceneGraph::setName(std::string new_name)
{
	name_ = new_name;
}

void SceneGraph::setRoot(Node const& new_root ) {root_ = new_root;}

Node const &SceneGraph::getRoot() {
    return root_;
}

// what about Moons? Could set Moons as Children of Planets, so we can also define their names here? (look at Figure 2 in Assignment 1)
SceneGraph setupSolarSystem() {
    SceneGraph sceneGraph{};

    return sceneGraph;
}
