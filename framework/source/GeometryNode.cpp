#include "GeometryNode.hpp"

model &GeometryNode::getGeometry() {
    return geometry_;
}

void GeometryNode::setGeometry(const model &geometry) {
    geometry_ = geometry;

}
