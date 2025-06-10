#ifndef OPENGL_FRAMEWORK_POINTLIGHTNODE_HPP
#define OPENGL_FRAMEWORK_POINTLIGHTNODE_HPP

#include "Node.hpp"
#include "string"
#include "list"
#include <glm/glm.hpp>

class PointLightNode : public Node{


public:
    PointLightNode() = default;

    PointLightNode(glm::vec3 const& color, float intensity):
            Node(),
            color_{color},
            intensity_{intensity} {};

    PointLightNode(std::shared_ptr<Node> parent, std::string const& name, glm::vec3 const& color, float intensity):
            Node(name, std::move(parent)),
            color_{color},
            intensity_{intensity} {};

    const glm::vec3& getColor() const;
    void setColor(glm::vec3 const& color);
    float getIntensity() const;
    void setIntensity(float intensity);
private:


    glm::vec3 color_;
    float intensity_;


};
#endif //OPENGL_FRAMEWORK_POINTLIGHTNODE_HPP
