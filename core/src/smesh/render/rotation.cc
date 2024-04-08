#include "rotation.h"
#include "smesh/common.h"
#include <glm/ext/quaternion_trigonometric.hpp>
#include <glm/fwd.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/euler_angles.hpp>
#include <glm/trigonometric.hpp>

namespace smesh
{
    Rotation::Rotation(int euler_mode, const glm::vec3 &rotate_degree)
    {
        set_euler(euler_mode, rotate_degree);
    }

    Rotation::Rotation(const AxisAngle &rotate_axis_angle)
    {
        set_axis_angle(rotate_axis_angle);
    }

    Rotation::Rotation(const glm::quat &rotate_quat)
    {
        quat_ = rotate_quat;
    }

    void Rotation::set_euler(int euler_mode, const glm::vec3 &rotate_degree)
    {
        glm::mat4 rotate_matrix{1.0};
        switch (euler_mode)
        {
        case EulerMode::kXYZ:
            rotate_matrix = glm::eulerAngleXYZ(glm::radians(rotate_degree.x), glm::radians(rotate_degree.y), glm::radians(rotate_degree.z));
            break;
        case EulerMode::kXZY:
            rotate_matrix = glm::eulerAngleXZY(glm::radians(rotate_degree.x), glm::radians(rotate_degree.z), glm::radians(rotate_degree.y));
            break;
        case EulerMode::kYXZ:
            rotate_matrix = glm::eulerAngleYXZ(glm::radians(rotate_degree.y), glm::radians(rotate_degree.x), glm::radians(rotate_degree.z));
            break;
        case EulerMode::kYZX:
            rotate_matrix = glm::eulerAngleYZX(glm::radians(rotate_degree.y), glm::radians(rotate_degree.z), glm::radians(rotate_degree.x));
            break;
        case EulerMode::kZXY:
            rotate_matrix = glm::eulerAngleZXY(glm::radians(rotate_degree.z), glm::radians(rotate_degree.x), glm::radians(rotate_degree.y));
            break;
        case EulerMode::kZYX:
            rotate_matrix = glm::eulerAngleZYX(glm::radians(rotate_degree.z), glm::radians(rotate_degree.y), glm::radians(rotate_degree.x));
            break;
        }
        quat_ = glm::quat_cast(rotate_matrix);
    }

    void Rotation::set_axis_angle(const AxisAngle &rotate_axis_angle)
    {
        quat_ = glm::angleAxis(glm::radians(rotate_axis_angle.angle), glm::normalize(rotate_axis_angle.axis));
    }

    void Rotation::set_quaternion(const glm::quat &rotate_quat)
    {
        quat_ = glm::normalize(rotate_quat);
    }

    glm::vec3 Rotation::euler(int euler_mode)
    {
        glm::mat4 rotate_matrix = glm::mat4_cast(quat_);
        float x = 0, y = 0, z = 0;
        switch (euler_mode)
        {
        case EulerMode::kXYZ:
            glm::extractEulerAngleXYZ(rotate_matrix, x, y, z);
            break;
        case EulerMode::kXZY:
            glm::extractEulerAngleXZY(rotate_matrix, x, z, y);
            break;
        case EulerMode::kYXZ:
            glm::extractEulerAngleYXZ(rotate_matrix, y, x, z);
            break;
        case EulerMode::kYZX:
            glm::extractEulerAngleYZX(rotate_matrix, y, z, x);
            break;
        case EulerMode::kZXY:
            glm::extractEulerAngleZXY(rotate_matrix, z, x, y);
            break;
        case EulerMode::kZYX:
            glm::extractEulerAngleZYX(rotate_matrix, z, y, x);
            break;
        }
        return {glm::degrees(x), glm::degrees(y), glm::degrees(z)};
    }

    glm::quat Rotation::quaternion()
    {
        return quat_;
    }

    Rotation::AxisAngle Rotation::axis_angle()
    {
        float angle = glm::angle(quat_);
        glm::vec3 axis = glm::axis(quat_);
        return {axis, glm::degrees(angle)};
    }

    glm::mat4 Rotation::matrix()
    {
        return glm::mat4_cast(quat_);
    }

} // namespace smesh