#include "GeometryNode.hpp"
#include <glm/gtx/string_cast.hpp>

model_object &GeometryNode::getGeometry() {
    return geometry_;
}

void GeometryNode::setGeometry(const model_object &geometry) {
    geometry_ = geometry;

}

void GeometryNode::renderPlanet(const std::map<std::string, shader_program> &m_shaders,
                                const glm::mat4 &m_view_transform) const {

    // bind shader to upload uniforms
    glUseProgram(m_shaders.at("planet").handle);
    // rotate planets around own y-axis
    glm::fmat4 model_matrix = getWorldTransform() * getLocalTransform();
    model_matrix = model_matrix * glm::rotate(glm::fmat4{}, float(glfwGetTime()), glm::fvec3{0.0f, 1.0f, 0.0f});
    glUniformMatrix4fv(m_shaders.at("planet").u_locs.at("ModelMatrix"),
                       1, GL_FALSE, glm::value_ptr(model_matrix));

    // extra matrix for normal transformation to keep them orthogonal to surface
    glm::fmat4 normal_matrix = glm::inverseTranspose(model_matrix);
    gl::glUniformMatrix4fv(m_shaders.at("planet").u_locs.at("NormalMatrix"),
                           1, GL_FALSE, glm::value_ptr(normal_matrix));

    // camera position as derived from m_view_transform (last column)
    glm::vec4 camera_position = m_view_transform[3];
    gl::glUniform4fv(m_shaders.at("planet").u_locs.at("CameraPosition"), 1, glm::value_ptr(camera_position));

    // get planet colour and ambient colour to handle in shader
    gl::glUniform3f(m_shaders.at("planet").u_locs.at("PlanetColor"),
                    color_.x, color_.y, color_.z);

    gl::glUniform3f(m_shaders.at("planet").u_locs.at("AmbientColor"),
                    color_.x, color_.y, color_.z);

    // bind the VAO to draw
    gl::glBindVertexArray(geometry_.vertex_AO);

    // draw bound vertex array using bound shader
    gl::glDrawElements(geometry_.draw_mode, geometry_.num_elements, model::INDEX.type, NULL);
}

void GeometryNode::renderStars(const std::map<std::string, shader_program> &m_shaders,
                               const glm::mat4 &m_view_transform) const {
    glUseProgram(m_shaders.at("stars").handle);
    glm::fmat4 model_matrix = getWorldTransform() * getLocalTransform();

    glUniformMatrix4fv(m_shaders.at("stars").u_locs.at("ModelMatrix"),
                       1, GL_FALSE, glm::value_ptr(model_matrix));

    glm::fmat4 normal_matrix = glm::inverseTranspose(glm::inverse(m_view_transform) * model_matrix);
    gl::glUniformMatrix4fv(m_shaders.at("stars").u_locs.at("NormalMatrix"),
                           1, GL_FALSE, glm::value_ptr(normal_matrix));
    gl::glBindVertexArray(geometry_.vertex_AO);

    glDrawArrays(GL_POINTS, 0,geometry_.num_elements);
}

/// renders orbits using glDrawArray
/// \param m_shaders shader information
/// \param m_view_transform camera information
void GeometryNode::renderOrbit(const std::map<std::string, shader_program> &m_shaders,
                               const glm::mat4 &m_view_transform) const {
    glUseProgram(m_shaders.at("orbit").handle);
    glm::fmat4 model_matrix = getWorldTransform();

    glUniformMatrix4fv(m_shaders.at("orbit").u_locs.at("ModelMatrix"),
                       1, GL_FALSE, glm::value_ptr(model_matrix));

    gl::glBindVertexArray(geometry_.vertex_AO);

    glDrawArrays(geometry_.draw_mode,0, geometry_.num_elements);
}

void GeometryNode::renderNode(const std::map<std::string, shader_program> &m_shaders,
                              const glm::mat4 &m_view_transform) {

    if (name_.find("Planet") != std::string::npos) {
        renderPlanet(m_shaders, m_view_transform);
    } else if (name_ == "Star-Geometry") {
        renderStars(m_shaders, m_view_transform);
    }
    else if (name_ == "Orbit") {
        renderOrbit(m_shaders, m_view_transform);
    }
}
