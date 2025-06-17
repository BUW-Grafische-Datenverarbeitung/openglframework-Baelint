#ifndef OPENGL_FRAMEWORK_NODE_HPP
#define OPENGL_FRAMEWORK_NODE_HPP

#include <utility>
#include <vector>
#include <iostream>
#include <functional>
#include <glm/glm.hpp>
#include <memory>
#include "structs.hpp"

//dont load gl bindings from glfw
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/matrix_inverse.hpp>
#include <glm/gtc/type_ptr.hpp>

class Node {
private:
    std::shared_ptr<Node> parent_;
    std::vector<std::shared_ptr<Node>> children_;
    std::string name_;
    std::string path_;
    int depth_ = 0;

    glm::mat4 localTransform_ = glm::mat4(1.0f);
    glm::mat4 worldTransform_ = glm::mat4(1.0f);
    glm::vec3 color_ = glm::vec3(1.0f);

public:
    Node() = default;
    explicit Node(std::string name);
    explicit Node(std::string name, std::shared_ptr<Node> parent):
            parent_{std::move(parent)},
            children_{},
            name_{std::move(name)},
            path_{},
            depth_{},
            local_transform_{},
            world_transform_{},
            color_{0.5, 0.5, 0.5}
    {};
    explicit Node(std::string name, std::shared_ptr<Node> parent, const glm::vec3& color):
            parent_{std::move(parent)},
            children_{},
            name_{std::move(name)},
            path_{},
            depth_{},
            local_transform_{},
            world_transform_{},
            color_{color.x / 255, color.y / 255, color.z / 255}
    {};
    ~Node() = default;

    // Getters (const correctness)
    std::shared_ptr<Node> getParent() const;
    void setParent(std::shared_ptr<Node> parent);

    std::shared_ptr<Node> getChild(std::string const& searchedName) const;
    const std::vector<std::shared_ptr<Node>>& getChildren() const;

    const std::string& getName() const;
    const std::string& getPath() const;
    int getDepth() const;

    const glm::mat4& getLocalTransform() const;
    void setLocalTransform(const glm::mat4& localTransform);

    glm::mat4 getWorldTransform() const;
    void setWorldTransform(const glm::mat4& worldTransform);

    const glm::vec3& getColor() const;
    void setColor(const glm::vec3& color);

    virtual void renderNode(std::map<std::string, shader_program> const& m_shaders, glm::mat4 const& m_view_transform);

    const glm::vec3 &getColor() const;

    void setColor(const glm::vec3 &color);

    // Scene hierarchy
    void addChild(const std::shared_ptr<Node>& child);
    void removeChild(const std::string& childName);

    // Transform utilities
    void translate(const glm::vec3& translation);
    void rotate(float angle); // You might want to clarify axis later
    void scale(float scale);
};
#endif //OPENGL_FRAMEWORK_NODE_HPP
