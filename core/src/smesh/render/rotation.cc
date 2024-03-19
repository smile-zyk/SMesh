#include "rotation.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/euler_angles.hpp>
#include <glm/gtc/quaternion.hpp>

namespace smesh
{
    glm::mat4 Rotation::GetRotateMatrix()
    {
        if (rotate_mode_ == RotationMode::kEulerXYZ)
        {
            return glm::eulerAngleXYZ(glm::radians(rotate_data_.x), glm::radians(rotate_data_.y), glm::radians(rotate_data_.z));
        }
        else if (rotate_mode_ == RotationMode::kEulerXZY)
        {
            return glm::eulerAngleXZY(glm::radians(rotate_data_.x), glm::radians(rotate_data_.z), glm::radians(rotate_data_.y));
        }
        else if (rotate_mode_ == RotationMode::kEulerYXZ)
        {
            return glm::eulerAngleYXZ(glm::radians(rotate_data_.y), glm::radians(rotate_data_.x), glm::radians(rotate_data_.z));
        }
        else if (rotate_mode_ == RotationMode::kEulerYZX)
        {
            return glm::eulerAngleYZX(glm::radians(rotate_data_.y), glm::radians(rotate_data_.z), glm::radians(rotate_data_.x));
        }
        else if (rotate_mode_ == RotationMode::kEulerZXY)
        {
            return glm::eulerAngleZXY(glm::radians(rotate_data_.z), glm::radians(rotate_data_.x), glm::radians(rotate_data_.y));
        }
        else if (rotate_mode_ == RotationMode::kEulerZYX)
        {
            return glm::eulerAngleZYX(glm::radians(rotate_data_.z), glm::radians(rotate_data_.y), glm::radians(rotate_data_.x));
        }
        else if (rotate_mode_ == RotationMode::kAxisAngle)
        {
            return glm::mat4_cast(glm::angleAxis(glm::radians(rotate_data_.w), glm::vec3(rotate_data_)));
        }
        else if (rotate_mode_ == RotationMode::kQuaternion)
        {
            return glm::mat4_cast(glm::quat(rotate_data_));
        }
        else
            return glm::mat4{1.0};
    }

    void Rotation::SetRotation(int rotate_mode, const glm::vec4 &rotate_data)
    {
        rotate_mode_ = rotate_mode;
        rotate_data_ = rotate_data;
    }

    void Rotation::SetRotationData(const glm::vec4 &rotate_data)
    {
        rotate_data_ = rotate_data;
    }

    void Rotation::SetRotationMode(int rotate_mode)
    {
        if(rotate_mode == rotate_mode_) return;
        glm::mat4 cur_mat = GetRotateMatrix();
        if ((rotate_mode_ == RotationMode::kEulerXYZ ||
             rotate_mode_ == RotationMode::kEulerXZY ||
             rotate_mode_ == RotationMode::kEulerYXZ ||
             rotate_mode_ == RotationMode::kEulerYZX ||
             rotate_mode_ == RotationMode::kEulerZXY ||
             rotate_mode_ == RotationMode::kEulerZYX))
        {
            glm::quat q = glm::quat_cast(cur_mat);
            if(rotate_mode == RotationMode::kQuaternion)
            {
                rotate_data_ = {q.x, q.y, q.z, q.w};
            }
            else if(rotate_mode == RotationMode::kAxisAngle)
            {
                glm::vec3 axis = glm::axis(q);
                float angle = glm::angle(q);
                rotate_data_ = {axis.x, axis.y, axis.z, glm::degrees(angle)};
            }
        }
        else if(rotate_mode_ == RotationMode::kQuaternion ||
            rotate_mode_ == RotationMode::kAxisAngle)
        {
            float x = 0, y = 0, z = 0;
            if(rotate_mode == RotationMode::kEulerXYZ)
            {
                glm::extractEulerAngleXYZ(cur_mat, x, y, z);
                rotate_data_ = {x, y, z, 0};
            }
            else if(rotate_mode == RotationMode::kEulerXZY)
            {
                glm::extractEulerAngleXZY(cur_mat, x, z, y);
                rotate_data_ = {x, y, z, 0};
            }
            else if(rotate_mode == RotationMode::kEulerYXZ)
            {
                glm::extractEulerAngleYXZ(cur_mat, y, x, z);
                rotate_data_ = {x, y, z, 0};
            }
            else if(rotate_mode == RotationMode::kEulerYZX)
            {
                glm::extractEulerAngleYZX(cur_mat, y, z, x);
                rotate_data_ = {x, y, z, 0};
            }
            else if(rotate_mode == RotationMode::kEulerZXY)
            {
                glm::extractEulerAngleZXY(cur_mat, z, x, y);
                rotate_data_ = {x, y, z, 0};
            }
            else if(rotate_mode == RotationMode::kEulerZYX)
            {
                glm::extractEulerAngleZYX(cur_mat, z, y, x);
                rotate_data_ = {x, y, z, 0};
            }
            else if(rotate_mode_ == RotationMode::kAxisAngle)
            {
                glm::vec3 axis = glm::axis(glm::quat(rotate_data_));
                float angle = glm::angle(glm::quat(rotate_data_));
                rotate_data_ = {axis.x, axis.y, axis.z, glm::degrees(angle)};
            }
            else if(rotate_mode_ == RotationMode::kQuaternion)
            {
                glm::quat q = glm::angleAxis(glm::radians(rotate_data_.w), glm::vec3(rotate_data_));
                rotate_data_ = {q.x, q.y, q.z, q.w};
            }
        }
        rotate_mode_ = rotate_mode;
    }
} // namespace smesh