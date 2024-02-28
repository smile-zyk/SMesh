#pragma once
#include "smesh/render/camera.h"
#include <glm/glm.hpp>

namespace smesh
{
    namespace utils
    {
        glm::vec4 NdcToWorld(glm::vec3 ndc_point, Camera* camera);
    }
} // namespace smesh