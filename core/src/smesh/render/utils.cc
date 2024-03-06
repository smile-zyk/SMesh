#include "utils.h"
#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>

namespace smesh
{
    namespace utils
    {
        glm::vec4 NdcToWorld(glm::vec3 ndc_point, glm::mat4 view_matrix, glm::mat4 proj_matrix)
        {
            glm::vec4 world_point = inverse(proj_matrix * view_matrix) * glm::vec4(ndc_point, 1.0);
            return world_point / world_point.w;
        }
        
        glm::vec2 Screen2Ndc(glm::vec2 screen_pos, glm::vec2 screen_size, bool is_reverse_y)
        {
            glm::vec2 ndc_pos = glm::vec2((screen_pos.x / screen_size.x) * 2 - 1.0,
                    (screen_pos.y / screen_size.y) * 2 - 1.0);
            if(is_reverse_y)
                ndc_pos.y = -ndc_pos.y;
            return ndc_pos;
        }
        
    } // namespace utils
} // namespace smesh