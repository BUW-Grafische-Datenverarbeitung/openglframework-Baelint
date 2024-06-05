#include "SceneGraph.h"
#include "node.hpp"
#include "camera_Node.h"
#include "GeometryNode.hpp"
#include "PointLightNode.hpp"
#include "model.hpp"
#include <string>
#include <utility>
#include <vector>

std::string SceneGraph::getName() const
{
	return name_;
}

void SceneGraph::setName(std::string new_name)
{
	name_ = std::move(new_name);
}

void SceneGraph::setRoot(std::shared_ptr<Node> &new_root ) { root_ = std::move(new_root);}

std::shared_ptr<Node> &SceneGraph::getRoot() {
    return root_;
}

// what about Moons? Could set Moons as Children of Planets, so we can also define their names here? (look at Figure 2 in Assignment 1)
SceneGraph setupSolarSystem() {
    SceneGraph sceneGraph{};

    //initialize root
    std::shared_ptr<Node> root = std::make_shared<Node>(Node{"root", nullptr});
    //set root of scene graph
    sceneGraph.setRoot(root);

    return sceneGraph;
}
