#ifndef SCENEGRAPH_HPP
#define SCENEGRAPH_HPP
#include <iostream>
class SceneGraph
{
public:
    static SceneGraph& getInstance()  //setup it being a singleton
    {
        static SceneGraph    instance; // gets destroyed                              
        return instance;
    }
private:
    SceneGraph() {}                    // constructor
    SceneGraph(SceneGraph const&);     // no implementation
    void operator=(SceneGraph const&); // no implementation

    std::string name;
    //Node::Node root; //needs implementation!! 
public:
    SceneGraph(SceneGraph const&) = delete;
    void operator=(SceneGraph const&) = delete;

    std::string getName() const;
    //Node::Node& getRoot() const; //TODO: lookup const correctness for complex datatypes like objects regarding functions/getters
    void setName(std::string new_name);  //TODO: lookup const correctness and when to use ref for setters, usally const& for complex things in constructor, but here?
    //void setRoot(Node::Node new_root const&);

};
#endif