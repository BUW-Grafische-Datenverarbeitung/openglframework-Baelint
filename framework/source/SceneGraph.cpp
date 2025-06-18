#include "SceneGraph.h"
#include "Node.hpp"
#include "camera_Node.h"
#include "GeometryNode.hpp"
#include "PointLightNode.hpp"
#include "model.hpp"
#include "structs.hpp"
#include "constants.h"
#include <string>
#include <utility>
#include <vector>
#include <glm/gtx/string_cast.hpp>


std::string SceneGraph::getName() const
{
	return name_;
}

void SceneGraph::setName(std::string new_name)
{
	name_ = std::move(new_name);
}

void SceneGraph::setRoot(const std::shared_ptr<Node>& new_root) {
    root_ = new_root;  // copies the shared_ptr, so caller's pointer stays valid
}

const std::shared_ptr<Node> & SceneGraph::getRoot() const {
    return root_;
}


SceneGraph setupSolarSystem(std::map<std::string, model_object> const& model_objects, std::string const& resource_path) {
    std::cout << "Calling setupSolarSystem\n";
    SceneGraph sceneGraph{};

    //initialize root
    std::shared_ptr<Node> root = std::make_shared<Node>("root", nullptr);
    //set root of scene graph
    sceneGraph.setRoot(root);

    //initialize sun as a point light
    auto sun_light_node = std::make_shared<PointLightNode>(root,"Planet-Sun-Holder",glm::vec3{1.0f,1.0f,1.0f},30.0f);
    //initialize geometry node for sun
    auto sun_geometry_node = std::make_shared<GeometryNode>(sun_light_node,"Planet-Sun-Geometry",
                                                            model_objects.at("planet-object"), SUN_COLOR);
    //add geometry node as child to sun node
    sun_light_node->addChild(sun_geometry_node);
    //add sun node as child to root
    root->addChild(sun_light_node);
    //Create star Geometry
    auto star_geometry = std::make_shared<GeometryNode>(root, "Star-Geometry", model_objects.at("star-object"));
    //Add it to root
    root->addChild(star_geometry);

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
        planet_node -> translate(glm::vec3{PLANET_DISTANCES[i], 0.0f, 0.0f});
        //change size of planet
        planet_node -> scale(PLANET_SIZES[i]);

    }

    std::cout << "setupSolarSystem done\n";
    return sceneGraph;
}
