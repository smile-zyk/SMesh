#pragma once
#include <glm/fwd.hpp>

namespace smesh
{
    namespace utils
    {
        glm::vec4 NdcToWorld(glm::vec3 ndc_point, glm::mat4 view_matrix, glm::mat4 proj_matrix);
        glm::vec2 Screen2Ndc(glm::vec2 screen_pos, glm::vec2 screen_size, bool is_reverse_y = true);
    }
} // namespace smesh