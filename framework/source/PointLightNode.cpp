#include "PointLightNode.hpp"

glm::vec3 PointLightNode::getColor() {
    return color_;
}

void PointLightNode::setColor(const glm::vec3 &color) {
    color_ = color;
}

float PointLightNode::getIntensity() {
    return intensity_;
}

void PointLightNode::setIntensity(float intensity) {
    intensity_ = intensity;
}
