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

    model_object &getGeometry();
    void setGeometry(const model_object &geometry);

    GeometryNode(std::shared_ptr<Node> parent, std::string const& name):
            Node::Node(name, std::move(parent)),
            geometry_{}
    {};

    GeometryNode(std::shared_ptr<Node> parent,
                 std::string const& name,
                 model_object const& geometry):
            Node::Node(name, std::move(parent)),
            geometry_{geometry}
    {};

    GeometryNode(std::shared_ptr<Node> parent,
                 std::string const& name,
                 model_object const& geometry,
                 glm::vec3 const& color):
            Node::Node(name, std::move(parent), color),
            geometry_{geometry}
    {};

    void renderPlanet(const std::map<std::string, shader_program> &m_shaders,
                      const glm::mat4 &m_view_transform) const;

    void renderStars(const std::map<std::string, shader_program> &m_shaders,
                     const glm::mat4 &m_view_transform) const;

    void renderNode(std::map<std::string, shader_program> const& m_shaders, glm::mat4 const& m_view_transform) override;

private:
    model_object geometry_;
};
#endif //OPENGL_FRAMEWORK_GEOMETRYNODE_HPP
