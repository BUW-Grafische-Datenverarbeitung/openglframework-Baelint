#ifndef SCENEGRAPH_HPP
#define SCENEGRAPH_HPP
#include <iostream>
#include <map>
#include "Node.hpp"
#include "structs.hpp"

class SceneGraph
{
public:
    SceneGraph() = default;                    // constructor

    static SceneGraph& getInstance()  //setup it being a singleton
    {
        static SceneGraph    instance; // gets destroyed
        return instance;
    }
private:
    std::string name_;
    std::shared_ptr<Node> root_;
public:
    std::string getName() const;
    const std::shared_ptr<Node> & getRoot() const;
    void setName(std::string new_name);
    void setRoot(const std::shared_ptr<Node> &new_root);

};

SceneGraph setupSolarSystem(std::map<std::string, model_object> const& model_objects,  std::string const& resource_path);

#endif