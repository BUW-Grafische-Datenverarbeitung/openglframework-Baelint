#include "Node.hpp"
#include <algorithm>
#include <utility>
#include <glm/gtc/matrix_transform.hpp>
#include <utility>


Node::Node(std::string name): parent_{nullptr}, name_{std::move(name)}, depth_{0} {}


Node::Node(std::string name, std::shared_ptr<Node> parent) : parent_(std::move(parent)), name_{std::move(name )}, depth_{0} {}


Node::Node(std::string name, std::shared_ptr<Node> parent, const glm::vec3& color) : parent_(std::move(parent)), name_{std::move(name)}, color_(color){}


std::shared_ptr<Node> Node::getParent() {
    return parent_;
}

void Node::setParent(std::shared_ptr<Node> parent) {
parent_ = std::move(parent);
}

std::shared_ptr<Node> Node::getChild(std::string const& searchedName) {
    auto searchedChild = std::find_if(children_.begin(), children_.end(),[searchedName] (std::shared_ptr<Node> child) {return searchedName == child -> name_;});
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
    for (auto child : children_) {
        //child->setWorldTransform(world_transform_ * child->getLocalTransform()); // local transform of child, not current node
        child->setWorldTransform(worldTransform_ * localTransform);
    }
}

glm::mat4 Node::getWorldTransform() {
    return worldTransform_;
}

void Node::setWorldTransform(const glm::mat4 &worldTransform) {
    worldTransform_ = worldTransform;
    //setting also the worldTransformation for the children of the node
    for (auto child : children_) {
        child->setWorldTransform(worldTransform * child->localTransform_);
    }
}

void Node::addChild(const std::shared_ptr<Node>& child) {
    children_.push_back(child);
}

void Node::removeChild(const std::string& delete_child) {
    auto found_child = std::remove_if(children_.begin(), children_.end(), [delete_child] (
            const std::shared_ptr<Node>& child) {return delete_child == child -> name_;});
}

void Node::translate(glm::vec3 const& translation){
    localTransform_ = glm::translate(localTransform_, translation);
}

void Node::rotate(float angle){
    glm::mat4 rotation_matrix = glm::rotate(glm::fmat4{}, angle, glm::fvec3{0.0f, 1.0f, 0.0f});
    setLocalTransform(rotation_matrix * localTransform_);
}

void Node::scale(float scale){
    localTransform_=glm::scale(localTransform_, glm::vec3{scale,scale,scale});
}


