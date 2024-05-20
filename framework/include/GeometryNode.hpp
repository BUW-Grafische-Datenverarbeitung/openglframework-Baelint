#ifndef OPENGL_FRAMEWORK_GEOMETRYNODE_HPP
#define OPENGL_FRAMEWORK_GEOMETRYNODE_HPP

#include <Node.hpp>
#include "string"
#include "list"
#include <glm/glm.hpp>
#include "model.hpp"

class GeometryNode : public Node{
private:
    //GeometryNode() : Node(<#initializer#>, <#initializer#>) {}

    model geometry_;

public:
    model &getGeometry();
    void setGeometry(const model &geometry);
};
#endif //OPENGL_FRAMEWORK_GEOMETRYNODE_HPP
