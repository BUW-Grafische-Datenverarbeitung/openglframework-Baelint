#include "application_solar.hpp"
#include "window_handler.hpp"

#include "utils.hpp"
#include "shader_loader.hpp"
#include "model_loader.hpp"

#include "camera_Node.h"
#include "PointLightNode.hpp"
#include "GeometryNode.hpp"
#include "SceneGraph.h"
#include "model.hpp"

#include <glbinding/gl/gl.h>
// use gl definitions from glbinding
using namespace gl;

//dont load gl bindings from glfw
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/matrix_inverse.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <memory>
#include <iostream>
#include <fstream>

#pragma region CONSTANTS
int STAR_COUNT = 1000;
int LINE_SEGMENT_COUNT = 100;

#pragma endregion

ApplicationSolar::ApplicationSolar(std::string const& resource_path)
 :Application{resource_path}
 ,planet_object{}
 ,m_view_transform{glm::translate(glm::fmat4{}, glm::fvec3{0.0f, 0.0f, 10.0f})}
 ,m_view_projection{utils::calculate_projection_matrix(initial_aspect_ratio)}
 ,sceneGraph()
{
  initializeGeometry();
  initializeShaderPrograms();

    // fill map with all necessary objects, so they can be accessed by name
    std::cout << "Creating model_objects\n";
    std::map<std::string ,model_object> model_objects {
            std::make_pair("planet-object", planet_object),
            std::make_pair("star-object", star_object),
    };
    std::cout << "model_objects done\n";

    // create graph hierarchy
    sceneGraph = setupSolarSystem(model_objects, resource_path);
}

ApplicationSolar::~ApplicationSolar() {
    glDeleteBuffers(1, &planet_object.vertex_BO);
    glDeleteBuffers(1, &planet_object.element_BO);
    glDeleteVertexArrays(1, &planet_object.vertex_AO);

    glDeleteBuffers(1, &star_object.vertex_BO);
    glDeleteBuffers(1, &star_object.element_BO);
    glDeleteVertexArrays(1, &star_object.vertex_AO);
}

void ApplicationSolar::render() const {
    sceneGraph.getRoot()->renderNode(m_shaders, m_view_transform);
}

void ApplicationSolar::uploadView() {
    // vertices are transformed in camera space, so camera transform must be inverted
    glm::fmat4 view_matrix = glm::inverse(m_view_transform);
    // upload matrix to gpu
    glUseProgram(m_shaders.at("planet").handle);
    glUniformMatrix4fv(m_shaders.at("planet").u_locs.at("ViewMatrix"),
                     1, GL_FALSE, glm::value_ptr(view_matrix));
    glUseProgram(m_shaders.at("stars").handle);
    glUniformMatrix4fv(m_shaders.at("stars").u_locs.at("ViewMatrix"), 1,
                       GL_FALSE, glm::value_ptr(view_matrix));
}

void ApplicationSolar::uploadProjection() {
    // upload matrix to gpu
    glUseProgram(m_shaders.at("planet").handle);
    glUniformMatrix4fv(m_shaders.at("planet").u_locs.at("ProjectionMatrix"),
                     1, GL_FALSE, glm::value_ptr(m_view_projection));
    glUseProgram(m_shaders.at("stars").handle);
    glUniformMatrix4fv(m_shaders.at("stars").u_locs.at("ProjectionMatrix"),
                       1, GL_FALSE, glm::value_ptr(m_view_projection));
}

// update uniform locations
void ApplicationSolar::uploadUniforms() {
  // bind shader to which to upload uniforms
  // upload uniform values to new locations
  uploadView();
  uploadProjection();
}

///////////////////////////// initialisation functions /////////////////////////
// load shader sources
void ApplicationSolar::initializeShaderPrograms() {
    std::cout << "Calling initializeShaderPrograms()\n";
    // store shader program objects in container
    m_shaders.emplace("planet", shader_program{{{GL_VERTEX_SHADER,m_resource_path + "shaders/simple.vert"},
                                                {GL_FRAGMENT_SHADER, m_resource_path + "shaders/simple.frag"}}});
    // request uniform locations for shader program
    m_shaders.at("planet").u_locs["NormalMatrix"] = -1;
    m_shaders.at("planet").u_locs["ModelMatrix"] = -1;
    m_shaders.at("planet").u_locs["ViewMatrix"] = -1;
    m_shaders.at("planet").u_locs["ProjectionMatrix"] = -1;

    m_shaders.emplace("stars", shader_program{{{GL_VERTEX_SHADER, m_resource_path + "shaders/vao.vert"},
                                               {GL_FRAGMENT_SHADER, m_resource_path + "shaders/vao.frag"}}});

    m_shaders.at("stars").u_locs["NormalMatrix"] = -1;
    m_shaders.at("stars").u_locs["ModelMatrix"] = -1;
    m_shaders.at("stars").u_locs["ViewMatrix"] = -1;
    m_shaders.at("stars").u_locs["ProjectionMatrix"] = -1;

    std::cout << "initializeShaderPrograms() done\n";
}

// load models
void ApplicationSolar::initializeGeometry() {
    initializePlanetGeometry();
    initializeStarGeometry();
}

void ApplicationSolar::initializePlanetGeometry() {
    model planet_model = model_loader::obj(m_resource_path + "models/sphere.obj", model::NORMAL);

    // generate vertex array object
    glGenVertexArrays(1, &planet_object.vertex_AO);
    // bind the array for attaching buffers
    glBindVertexArray(planet_object.vertex_AO);

    // generate generic buffer
    glGenBuffers(1, &planet_object.vertex_BO);
    // bind this as a vertex array buffer containing all attributes
    glBindBuffer(GL_ARRAY_BUFFER, planet_object.vertex_BO);
    // configure currently bound array buffer
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * planet_model.data.size(), planet_model.data.data(), GL_STATIC_DRAW);

    // activate first attribute on gpu
    glEnableVertexAttribArray(0);
    // first attribute is 3 floats with no offset & stride
    glVertexAttribPointer(0, model::POSITION.components, model::POSITION.type, GL_FALSE, planet_model.vertex_bytes, planet_model.offsets[model::POSITION]);
    // activate second attribute on gpu
    glEnableVertexAttribArray(1);
    // second attribute is 3 floats with no offset & stride
    glVertexAttribPointer(1, model::NORMAL.components, model::NORMAL.type, GL_FALSE, planet_model.vertex_bytes, planet_model.offsets[model::NORMAL]);

    // generate generic buffer
    glGenBuffers(1, &planet_object.element_BO);
    // bind this as an vertex array buffer containing all attributes
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, planet_object.element_BO);
    // configure currently bound array buffer
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, model::INDEX.size * planet_model.indices.size(), planet_model.indices.data(), GL_STATIC_DRAW);

    // store type of primitive to draw
    planet_object.draw_mode = GL_TRIANGLES;
    // transfer number of indices to model object
    planet_object.num_elements = GLsizei(planet_model.indices.size());
}

void ApplicationSolar::initializeStarGeometry() {
    std::srand((unsigned) time(nullptr));
    std::vector<float> stars_vec;

    // for each star push random position and color values
    for (int i = 0; i < STAR_COUNT; ++i) {
        float x = (static_cast <float> (std::rand()) / (static_cast <float> (RAND_MAX / 100))) - 50;
        float y = (static_cast <float> (std::rand()) / (static_cast <float> (RAND_MAX / 100))) - 50;
        float z = (static_cast <float> (std::rand()) / (static_cast <float> (RAND_MAX / 100))) - 50;
        float r = static_cast <float> (std::rand()) / static_cast <float> (RAND_MAX);
        float g = static_cast <float> (std::rand()) / static_cast <float> (RAND_MAX);
        float b = static_cast <float> (std::rand()) / static_cast <float> (RAND_MAX);


        for (float const number: {x, y, z, r, g, b}) {
            stars_vec.push_back(number);
        }
    }

    std::cout << stars_vec.size() << std::endl;
    //
    glGenVertexArrays(1, &star_object.vertex_AO);
    glBindVertexArray(star_object.vertex_AO);
    //
    glGenBuffers(1, &star_object.vertex_BO);
    glBindBuffer(GL_ARRAY_BUFFER, star_object.vertex_BO);
    //
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * STAR_COUNT * 6, stars_vec.data(), GL_STATIC_DRAW);
    //
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, nullptr);
    //
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE,
                          sizeof(float) * 6, (void*)(sizeof(float) * 3));
    // set the draw_mode to GL_POINTS
    star_object.draw_mode = GL_POINTS;
    star_object.num_elements = GLsizei(STAR_COUNT);
}

///////////////////////////// callback functions for window events ////////////
// handle key input
void ApplicationSolar::keyCallback(int key, int action, int mods) {

  //w a s d press/hold -> transforms view ^^ important to see if its positive or negative transformation depending on direction
  if (key == GLFW_KEY_W  && (action == GLFW_PRESS || action == GLFW_REPEAT)) {
    m_view_transform = glm::translate(m_view_transform, glm::fvec3{0.0f, 0.0f, -0.1f});
    uploadView();
  }
  else if (key == GLFW_KEY_S  && (action == GLFW_PRESS || action == GLFW_REPEAT)) {
    m_view_transform = glm::translate(m_view_transform, glm::fvec3{0.0f, 0.0f, 0.1f});
    uploadView();
  }

  else if (key == GLFW_KEY_A && (action == GLFW_PRESS || action == GLFW_REPEAT)) {
      m_view_transform = glm::translate(m_view_transform, glm::fvec3{ -0.1f, 0.0f, 0.0f });
      uploadView();
  }

  else if (key == GLFW_KEY_D && (action == GLFW_PRESS || action == GLFW_REPEAT)) {
      m_view_transform = glm::translate(m_view_transform, glm::fvec3{ 0.1f, 0.0f, 0.0f });
      uploadView();
  }
  //this should work like that!
}

//handle delta mouse movement input
void ApplicationSolar::mouseCallback(double pos_x, double pos_y) {
  // mouse handling

   // using x_pos and glm::rotate to rotate view position, using m_view_tansform
    m_view_transform = glm::rotate(m_view_transform, glm::radians(float(pos_x / 50)), glm::vec3{ 0.0f, -1.0f, 0.0f });
    // using y_pos
    m_view_transform = glm::rotate(m_view_transform, glm::radians(float(pos_y / 50)), glm::vec3{ -1.0f, 0.0f, 0.0f });
    uploadView(); //dont forget to update!
}

//handle resizing
void ApplicationSolar::resizeCallback(unsigned width, unsigned height) {
  // recalculate projection matrix for new aspect ratio
  m_view_projection = utils::calculate_projection_matrix(float(width) / float(height));
  // upload new projection matrix
  uploadProjection();
}


// exe entry point
int main(int argc, char* argv[]) {
  Application::run<ApplicationSolar>(argc, argv, 3, 2);
}