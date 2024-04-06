#pragma once

#include "glm/gtx/quaternion.hpp"
#include "glm/mat4x4.hpp"
#include "glm/vec4.hpp"
#include "smesh/core.h"
#include <glm/fwd.hpp>

namespace smesh
{
    class SMESH_API Rotation
    {
      public:
        struct AxisAngle
        {
            glm::vec3 axis;
            float angle;
        };
        Rotation(): quat_() {}
        Rotation(int euler_mode, const glm::vec3& rotate_degree);
        Rotation(const AxisAngle& rotate_axis_angle);
        Rotation(const glm::quat& rotate_quat);
        void set_euler(int euler_mode, const glm::vec3& rotate_degree);
        void set_axis_angle(const AxisAngle& rotate_axis_angle);
        void set_quaternion(const glm::quat& rotate_quat);
        glm::vec3 euler(int euler_mode);
        glm::quat quaternion();
        AxisAngle axis_angle();
        glm::mat4 matrix();

      private:
        glm::quat quat_;
    };
} // namespace smesh