#ifndef OPENGL_FRAMEWORK_NODE_HPP
#define OPENGL_FRAMEWORK_NODE_HPP

#include "string"
#include "vector"
#include <glm/glm.hpp>
#include <memory>

class Node{

private: //variables I guess
    std::shared_ptr<Node> parent_;
    std::vector<std::shared_ptr<Node>> children_;
    std::string name_;
    std::string path_;
    int depth_;
    glm::mat4 localTransform_ = glm::mat4(1.0f);
    glm::mat4 worldTransform_ = glm::mat4(1.0f);

public:
    Node() = default;
    explicit Node(std::string name);
    explicit Node(std::string name, std::shared_ptr<Node> parent);
    ~Node() = default; // i forgor why the heck the destructor is needed, but everywhere I looked in raytracer I left it like this
    // It's there to free up memory space! Its automatically called when it goes out of scope so it doesnt eat all of the space in the background!

    std::shared_ptr<Node> getParent();
    void setParent(std::shared_ptr<Node> parent);
    std::shared_ptr<Node> getChild(std::string const& searchedName);
    std::vector<std::shared_ptr<Node>> getChildren();
    std::string getName();
    std::string getPath();
    int getDepth() const;
    glm::mat4 getLocalTransform();
    void setLocalTransform(glm::mat4 const& localTransform);
    glm::mat4 getWorldTransform();
    void setWorldTransform(glm::mat4 const& localTransform);
    void addChild(const std::shared_ptr<Node>& child);
    void removeChild(const std::string& childName);
};
#endif //OPENGL_FRAMEWORK_NODE_HPP
