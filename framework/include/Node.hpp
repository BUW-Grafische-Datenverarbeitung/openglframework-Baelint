#ifndef OPENGL_FRAMEWORK_NODE_HPP
#define OPENGL_FRAMEWORK_NODE_HPP

#include "string"
#include "list"
#include <glm/glm.hpp>

class Node{

private: //variables I guess
    Node* parent_;
    std::list<Node> children_;
    std::string name_;
    std::string path_;
    int depth_;
    glm::mat4 localTransform_ = glm::mat4(1.0f);
    glm::mat4 worldTransform_ = glm::mat4(1.0f);

public:
    Node() = default;
    explicit Node(std::string const &name);
    explicit Node(std::string const &name, Node* &parent);
    ~Node() = default; // i forgor why the heck the destructor is needed, but everywhere I looked in raytracer I left it like this
    // It's there to free up memory space! Its automatically called when it goes out of scope so it doesnt eat all of the space in the background!

    Node* getParent();
    void setParent(Node* parent);
    Node getChild(std::string const& childName);
    std::list<Node> getChildren();
    std::string getName();
    std::string getPath();
    int getDepth() const;
    glm::mat4 getLocalTransform();
    void setLocalTransform(glm::mat4 const& localTransform);
    glm::mat4 getWorldTransform();
    void setWorldTransform(glm::mat4 const& localTransform);
    void addChild(Node const& child);
    void removeChild(std::string childName);
};
#endif //OPENGL_FRAMEWORK_NODE_HPP
