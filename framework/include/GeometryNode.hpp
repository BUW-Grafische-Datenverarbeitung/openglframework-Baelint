#ifndef OPENGL_FRAMEWORK_GEOMETRYNODE_HPP
#define OPENGL_FRAMEWORK_GEOMETRYNODE_HPP

#include <Node.hpp>
#include "string"
#include "list"
#include <glm/glm.hpp>
#include "model.hpp"
#include "structs.hpp"

class GeometryNode : public Node{

public:
    //default constructor
    GeometryNode() = default;

    GeometryNode(std::shared_ptr<Node> parent, std::string const& name):
            Node::Node(name, std::move(parent)),
            geometry_{}
    {};

    GeometryNode(std::shared_ptr<Node> parent,
                 std::string const& name,
                 model_object const& geometry,
                 glm::vec3 const& color):
            Node::Node(name, std::move(parent), color),
            geometry_{geometry}
    {};

private:

    model_object geometry_;



    model_object &getGeometry();
    void setGeometry(const model_object &geometry);
};
#endif //OPENGL_FRAMEWORK_GEOMETRYNODE_HPP
