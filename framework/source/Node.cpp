#include "Node.hpp"
#include <algorithm>


Node::Node(const std::string &name): parent_{nullptr}, name_{name} {}


Node::Node(std::string const &name, Node* &parent) : name_{name }, parent_(parent) {}


Node* Node::getParent() {
    return parent_;
}

void Node::setParent(Node* parent) {
parent_ = parent;
}

Node Node::getChild(std::string const& searchedName) {
    auto searchedChild = std::find_if(children_.begin(), children_.end(), [searchedName] (Node const& child) {return searchedName == child.name_;});
    return *searchedChild;
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
    worldTransform_ = worldTransform;
}

void Node::addChild(const Node &child) {
    children_.push_front(child);
}

void Node::removeChild(std::string delete_child) {
    auto found_child = std::remove_if(children_.begin(), children_.end(), [delete_child] (Node const& child) {return delete_child == child.name_;});
}


