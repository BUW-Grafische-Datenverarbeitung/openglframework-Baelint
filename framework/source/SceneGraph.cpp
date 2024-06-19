#include "SceneGraph.h"
#include "node.hpp"
#include "camera_Node.h"
#include "GeometryNode.hpp"
#include "PointLightNode.hpp"
#include "model.hpp"
#include "structs.hpp"
#include "constants.h"
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

void SceneGraph::setRoot(std::shared_ptr<Node> &new_root ) {root_ = std::move(new_root);}

const std::shared_ptr<Node> & SceneGraph::getRoot() const {
    return root_;
}

// what about Moons? Could set Moons as Children of Planets, so we can also define their names here? (look at Figure 2 in Assignment 1)
SceneGraph setupSolarSystem(std::map<std::string, model_object> const& model_objects, std::string const& resource_path) {
    SceneGraph sceneGraph{};

    //initialize root
    std::shared_ptr<Node> root = std::make_shared<Node>(Node{"root", nullptr});
    //set root of scene graph
    sceneGraph.setRoot(root);

    //initialize sun as a point light
    auto sun_light_node = std::make_shared<PointLightNode>(root,"Planet-Sun-Holder",glm::vec3{1.0f,1.0f,1.0f},4.0f);
    //initialize geometry node for sun
    auto sun_geometry_node = std::make_shared<GeometryNode>(sun_light_node,"Planet-Sun-Geometry",
                                                            model_objects.at("planet-object"), SUN_COLOR);

    //add geometry node as child to sun node
    sun_light_node->addChild(sun_geometry_node);
    //add sun node as child to root
    root->addChild(sun_light_node);

    //for all planets do
    for (size_t i = 0; i <= PLANET_NAMES.size() - 1; ++i) {
        //initialize planet as a node
        auto planet_node = std::make_shared<Node>( "Planet-" + PLANET_NAMES[i] + "-Holder", sun_light_node, PLANET_COLOR[i]);
        //initialize geometry node for said planet
        auto geometry_node = std::make_shared<GeometryNode>(planet_node, "Planet-" + PLANET_NAMES[i] + "-Geometry",
                                                            model_objects.at("planet-object"), PLANET_COLOR[i]);

        //add geometry node as a child to planet node
        planet_node->addChild(geometry_node);
        //add planet as a child to sun node
        sun_light_node->addChild(planet_node);
        //translate planet that it has a distance to the sun
        planet_node->translate(glm::vec3{0.0f, 0.0f, PLANET_DISTANCES[i]});
        //change size of planet
        planet_node->scale(PLANET_SIZES[i]);

        //add geometry node as a child to planet node
        planet_node->addChild(geometry_node);
        //add planet as a child to sun node
        sun_light_node->addChild(planet_node);
        //translate planet that it has a distance to the sun
        planet_node->translate(glm::vec3{0.0f, 0.0f, PLANET_DISTANCES[i]});
        //change size of planet
        planet_node->scale(PLANET_SIZES[i]);
    }

    return sceneGraph;
}
