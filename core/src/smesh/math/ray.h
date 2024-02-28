#pragma once
#include <glm/glm.hpp>
#include <optional>

#include "plane.h"

namespace smesh {
    struct Ray
    {
        glm::vec3 origin;
        glm::vec3 direction;
        std::optional<glm::vec3> Intersect(const Plane& plane);
    };
}