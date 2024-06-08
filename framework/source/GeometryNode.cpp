#include "GeometryNode.hpp"

model_object &GeometryNode::getGeometry() {
    return geometry_;
}

void GeometryNode::setGeometry(const model_object &geometry) {
    geometry_ = geometry;

}
