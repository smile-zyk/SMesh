#include "utils.h"
#include <glm/fwd.hpp>

namespace smesh
{
    namespace utils
    {
        glm::vec4 NdcToWorld(glm::vec3 ndc_point, Camera *camera)
        {
            glm::mat4 view_matrix = camera->GetViewMatrix();
            glm::mat4 projection_matrix = camera->GetProjectionMatrix();
            float near = camera->znear();
            float far = camera->zfar();
            float z_view_space = 2 * near * far / (ndc_point.z * (far - near) - (far + near));
            float w = -z_view_space;
            glm::vec4 clip_point =
                {
                    ndc_point.x * w,
                    ndc_point.y * w,
                    ndc_point.z * w,
                    w,
                };
            // p * v * world_point = clip_point
            // => world_point = (p * v)^-1 * clip_point
            glm::mat4 proj_view_inv = glm::inverse(projection_matrix * view_matrix);
            return proj_view_inv * clip_point;
        }
    } // namespace utils
} // namespace smesh