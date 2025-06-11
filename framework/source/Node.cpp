#include "Node.hpp"
#include <algorithm>
#include <utility>
#include <glm/gtc/matrix_transform.hpp>
#include <utility>
#include <iostream>

std::vector<std::pair<std::string, float>> PLANET_REVOLUTION {
        std::make_pair("Planet-Mercury-Holder", -0.04f),
        std::make_pair("Planet-Venus-Holder", 0.03f),
        std::make_pair("Planet-Earth-Holder", 0.01f),
        std::make_pair("Planet-Mars-Holder", 0.009f),
        std::make_pair("Planet-Jupiter-Holder", -0.006f),
        std::make_pair("Planet-Saturn-Holder", 0.003f),
        std::make_pair("Planet-Uranus-Holder", -0.001f),
        std::make_pair("Planet-Neptune-Holder", 0.0009f),
        std::make_pair("Planet-Notplanet Pluto-Holder", 0.0006f)
};

// Constructors
Node::Node(std::string name)
        : parent_{nullptr}, name_{std::move(name)}, depth_{0} {}

Node::Node(std::string name, std::shared_ptr<Node> parent)
        : parent_(std::move(parent)), name_{std::move(name)}, depth_{0} {}

Node::Node(std::string name, std::shared_ptr<Node> parent, const glm::vec3& color)
        : parent_(std::move(parent)), name_{std::move(name)}, color_(color) {}


// Getters
std::shared_ptr<Node> Node::getParent() const {
    return parent_;
}

void Node::setParent(std::shared_ptr<Node> parent) {
    parent_ = std::move(parent);
}

std::shared_ptr<Node> Node::getChild(const std::string& searchedName) const {
    auto it = std::find_if(children_.begin(), children_.end(),
                           [&searchedName](const std::shared_ptr<Node>& child) {
                               return searchedName == child->name_;
                           });

    return (it != children_.end()) ? *it : nullptr;
}

const std::vector<std::shared_ptr<Node>>& Node::getChildren() const {
    return children_;
}

const std::string& Node::getName() const {
    return name_;
}

const std::string& Node::getPath() const {
    return path_;
}

int Node::getDepth() const {
    return depth_;
}

const glm::mat4& Node::getLocalTransform() const {
    return localTransform_;
}

void Node::setLocalTransform(const glm::mat4& localTransform) {
    localTransform_ = localTransform;

    // Update children's world transform
    for (auto& child : children_) {
        child->setWorldTransform(worldTransform_ * child->localTransform_);
    }
}

glm::mat4 Node::getWorldTransform() const {
    if (parent_) {
        return parent_->getWorldTransform() * localTransform_;
    } else {
        return localTransform_;
    }
}

void Node::setWorldTransform(const glm::mat4& worldTransform) {
    worldTransform_ = worldTransform;

    // Propagate to children
    for (auto& child : children_) {
        child->setWorldTransform(worldTransform * child->localTransform_);
    }
}

const glm::vec3& Node::getColor() const {
    return color_;
}

void Node::setColor(const glm::vec3& color) {
    color_ = color;
}


// Scene graph operations
void Node::addChild(const std::shared_ptr<Node>& child) {
    children_.push_back(child);
}

void Node::removeChild(const std::string& childName) {
    auto it = std::remove_if(children_.begin(), children_.end(),
                             [&childName](const std::shared_ptr<Node>& child) {
                                 return child->getName() == childName;
                             });

    if (it != children_.end()) {
        children_.erase(it, children_.end());
    }
}

void Node::renderNode(std::map<std::string, shader_program> const& m_shaders, glm::mat4 const& m_view_transform) {
    //get value to compute speed of revolution around the sun
    float revolution_value = std::find_if(PLANET_REVOLUTION.begin(), PLANET_REVOLUTION.end(), [&] (std::pair<std::string, float> const& pair) {return name_ == pair.first; })->second;
    //compute rotation value
    glm::mat4 rotation_mat = glm::rotate(glm::fmat4{}, glm::radians(revolution_value), glm::fvec3{0.0f, 1.0f, 0.0f});
    setLocalTransform(rotation_mat * getLocalTransform());
    //call function also for children of node

    for (auto const& child : children_) {
        child->renderNode(m_shaders, m_view_transform);
    }
}

// Transformation utilities
void Node::translate(const glm::vec3& translation) {
    setLocalTransform(glm::translate(localTransform_, translation));
}

void Node::rotate(float angle) {
    glm::mat4 rotation_matrix = glm::rotate(glm::mat4(1.0f), angle, glm::vec3(0.0f, 1.0f, 0.0f));
    setLocalTransform(rotation_matrix * localTransform_);
}

void Node::scale(float scale) {
    setLocalTransform(glm::scale(localTransform_, glm::vec3(scale)));
}


