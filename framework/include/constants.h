#ifndef OPENGL_FRAMEWORK_CONSTANTS_H
#define OPENGL_FRAMEWORK_CONSTANTS_H

#include <vector>
#include <string>
#include <glm/glm.hpp>

const std::vector<std::string> PLANET_NAMES {
        "Mercury",
        "Venus",
        "Earth",
        "Mars",
        "Jupiter",
        "Saturn",
        "Uranus",
        "Neptune",
        "Notplanet Pluto"
};

std::vector<float> PLANET_SIZES {
        0.2f,
        0.4f,
        0.5f,
        0.3f,
        0.8f,
        0.7f,
        0.4f,
        0.4f,
        0.1f
};

std::vector<float> PLANET_DISTANCES {
        2.0f,
        4.0f,
        6.0f,
        8.0f,
        10.0f,
        12.0f,
        14.0f,
        16.0f,
        18.0f
};

std::vector<glm::vec3> PLANET_COLOR {
        glm::vec3(87,103,180),
        glm::vec3(173,141,84),
        glm::vec3(156,87,0),
        glm::vec3(193,68,14),
        glm::vec3(148,105,86),
        glm::vec3(244,165,135),
        glm::vec3(98,174,231),
        glm::vec3(43,55,139),
        glm::vec3(150,133,112)
};

glm::vec3 SUN_COLOR = glm::vec3(255,249,0);
//glm::vec3 SUN_COLOR = glm::vec3(255, 255, 255);

#endif //OPENGL_FRAMEWORK_CONSTANTS_H
