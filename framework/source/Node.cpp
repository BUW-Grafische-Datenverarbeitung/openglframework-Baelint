#include "Node.hpp"

Node::Node(std::string const& name) : name_{ name } {}


Node Node::getParent() {
    return parent_;
}

void Node::setParent(const Node& parent) {
parent_ = parent;
}

Node Node::getChild(std::string const& childName) {
    return Node(); // write name dependant searching, im too lazy now.
}

std::list<Node> Node::getChildren() {
    return children_;
}

std::string Node::getName() {
    return name_;
}

std::string Node::getPath() {
    return path_;
}

int Node::getDepth() const {
    return depth_;
}

glm::mat4 Node::getLocalTransform() {
    return localTransform_;
}

void Node::setLocalTransform(const glm::mat4 &localTransform) {
    localTransform_ = localTransform;
}

glm::mat4 Node::getWorldTransform() {
    return worldTransform_;
}

void Node::setWorldTransform(const glm::mat4 &worldTransform) {
    worldTransform_ =

}

void Node::addChild(const Node &child) {
    children_.push_front(child);
}

void Node::removeChild(std::string childName) {
    //again, name dependant searching
}
