#ifndef OPENGL_FRAMEWORK_POINTLIGHTNODE_HPP
#define OPENGL_FRAMEWORK_POINTLIGHTNODE_HPP

#include <Node.hpp>
#include "string"
#include "list"
#include <glm/glm.hpp>

class PointLightNode : public Node{

private:
    glm::vec3 color_;
    float intensity_;

public:
    glm::vec3 getColor();
    void setColor(glm::vec3 const& color);
    float getIntensity();
    void setIntensity(float intensity);
};
#endif //OPENGL_FRAMEWORK_POINTLIGHTNODE_HPP
