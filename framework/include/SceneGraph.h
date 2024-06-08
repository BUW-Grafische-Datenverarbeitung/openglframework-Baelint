#ifndef SCENEGRAPH_HPP
#define SCENEGRAPH_HPP
#include <iostream>
#include "node.hpp"
class SceneGraph
{
public:
    SceneGraph() = default;                    // constructor
    SceneGraph(SceneGraph const&);     // no implementation
    void operator=(SceneGraph const&); // no implementation

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
    const std::shared_ptr<Node> & getRoot() const; //TODO: lookup const correctness for complex datatypes like objects regarding functions/getters
    void setName(std::string new_name);  //TODO: lookup const correctness and when to use ref for setters, usally const& for complex things in constructor, but here?
    void setRoot(std::shared_ptr<Node> &new_root);

    SceneGraph setupSolarSystem(std::map<std::string, model_object> const& model_objects,  std::string const& resource_path);

};
#endif