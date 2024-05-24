#include "Node.hpp"
#include <algorithm>
#include <utility>


Node::Node(std::string name): parent_{nullptr}, name_{std::move(name)} {}


Node::Node(std::string name, std::shared_ptr<Node> parent) : parent_(parent), name_{std::move(name )} {}


std::shared_ptr<Node> Node::getParent() {
    return parent_;
}

void Node::setParent(std::shared_ptr<Node> parent) {
parent_ = std::move(parent);
}

std::shared_ptr<Node> Node::getChild(std::string const& searchedName) {
    auto searchedChild = std::find_if(children_.begin(), children_.end(),[searchedName] (std::shared_ptr<Node> child) {return searchedName == child.name_;});
    return *searchedChild;
}

std::vector<std::shared_ptr<Node>> Node::getChildren() {
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


