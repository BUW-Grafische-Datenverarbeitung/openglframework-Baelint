#include "PointLightNode.hpp"

const glm::vec3& PointLightNode::getColor() const {
    return color_;
}

void PointLightNode::setColor(const glm::vec3 &color) {
    color_ = color;
}

float PointLightNode::getIntensity() const {
    return intensity_;
}

void PointLightNode::setIntensity(float intensity) {
    intensity_ = intensity;
}
