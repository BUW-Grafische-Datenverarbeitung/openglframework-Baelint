#include "GeometryNode.hpp"
#include <glm/gtx/string_cast.hpp>

model_object &GeometryNode::getGeometry() {
    return geometry_;
}

void GeometryNode::setGeometry(const model_object &geometry) {
    geometry_ = geometry;

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

void GeometryNode::renderNode(const std::map<std::string, shader_program> &m_shaders,
                              const glm::mat4 &m_view_transform) {

    if (getName() == "Star-Geometry") {
        //std::cout << "rendering stars" << std::endl;
        renderStars(m_shaders, m_view_transform);
    } else {
        // bind shader to upload uniforms
        glUseProgram(m_shaders.at("planet").handle);

        glm::fmat4 model_matrix = getWorldTransform();

        glUniformMatrix4fv(m_shaders.at("planet").u_locs.at("ModelMatrix"),
                           1, GL_FALSE, glm::value_ptr(model_matrix));

        // extra matrix for normal transformation to keep them orthogonal to surface
        glm::fmat4 normal_matrix = glm::inverseTranspose(glm::inverse(m_view_transform) * model_matrix);
        gl::glUniformMatrix4fv(m_shaders.at("planet").u_locs.at("NormalMatrix"),
                               1, GL_FALSE, glm::value_ptr(normal_matrix));

        // bind the VAO to draw
        gl::glBindVertexArray(geometry_.vertex_AO);

        // draw bound vertex array using bound shader
        gl::glDrawElements(geometry_.draw_mode, geometry_.num_elements, model::INDEX.type, NULL);
    }
}
