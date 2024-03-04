#include "camera.h"
#include <glm/ext/vector_relational.hpp>
#include <glm/gtc/quaternion.hpp>
#include "smesh/log/log.h"
#include <optional>

namespace smesh
{
    Camera::Camera()
    {
    }
    
    std::optional<glm::vec3> GetTrackBallCoord(const glm::vec2& pos)
    {
        if(pos.x >= -1 && pos.x <= 1 && pos.y >= -1 && pos.y <= 1)
        {
            float p = static_cast<float>(pow(pos.x, 2) + pow(pos.y, 2));
            float z = 0;
            if(p <= 0.5f)
                z = sqrt(1 - p);
            else
                z = 0.5f / sqrt(p);
            return glm::normalize(glm::vec3(pos.x, pos.y, z));
        }
        else
        {
            SMESH_ERROR("Camera Rotate Wrong: pos is not in [-1, 1]");
            return std::nullopt;
        }
    }

    void Camera::TrackBallRotate(const glm::vec2& last_mouse_pos, const glm::vec2& cur_mouse_pos)
    {
        auto last_trackball_opt = GetTrackBallCoord(last_mouse_pos);
        auto cur_trackball_opt = GetTrackBallCoord(cur_mouse_pos);
        glm::vec3 last_trackball_coord = last_trackball_opt != std::nullopt ? last_trackball_opt.value(): glm::vec3();
        glm::vec3 cur_trackball_coord = cur_trackball_opt != std::nullopt ? cur_trackball_opt.value(): glm::vec3();
        bool is_equal = glm::all(glm::equal(last_trackball_coord, cur_trackball_coord, FLT_EPSILON));
        if(is_equal) return;

        glm::vec3 rotate_axis_in_view_space = glm::cross(last_trackball_coord, cur_trackball_coord);
        glm::vec3 rotate_axis_in_world_space = glm::inverse(GetViewMatrix()) * glm::vec4(rotate_axis_in_view_space, 1.0);
        rotate_axis_in_world_space = glm::normalize(rotate_axis_in_world_space);
        float rotate_angle = glm::acos(fmin(1.0f, glm::dot(last_trackball_coord, cur_trackball_coord)));
        rotate_angle *= 100;
        SMESH_TRACE("rotate angle is {}", glm::degrees(rotate_angle));
        SMESH_TRACE("rotate axis is ({}, {}, {})", rotate_axis_in_world_space.x, rotate_axis_in_world_space.y, rotate_axis_in_world_space.z);
        glm::quat rotate_quat = glm::quat(cos(rotate_angle / 2),
                            rotate_axis_in_world_space.x * sin(rotate_angle / 2),
                            rotate_axis_in_world_space.y * sin(rotate_angle / 2),
                            rotate_axis_in_world_space.z * sin(rotate_angle / 2));

        eye_ = rotate_quat * eye_;
    }

    void Camera::Rotate(const glm::vec2 &motion)
    {
        glm::vec3 centerVec = eye_ - target_;
        float radius = glm::length(centerVec);
        float yaw = std::atan2(centerVec.y, centerVec.x);
        float pitch = std::asin(centerVec.z / radius);
        float factor = static_cast<float>(M_PI) * 2.f;
        glm::vec3 offset;
        yaw -= motion.x * factor;
        pitch += motion.y * factor;

        if (pitch + M_PI_2 < DBL_EPSILON)
            pitch = -glm::radians(89.9f);
        if (pitch - M_PI_2 > DBL_EPSILON)
            pitch = glm::radians(89.9f);

        offset.y = (radius * (float)std::cos(pitch) * (float)std::sin(yaw));
        offset.z = (radius * (float)std::sin(pitch));
        offset.x = (radius * (float)std::cos(pitch) * (float)std::cos(yaw));

        eye_ = target_ + offset;
    }

    void Camera::Move(const glm::vec2 &motion)
    {
        glm::vec3 positionVec = target_ - eye_;
        glm::vec3 forward = glm::normalize(positionVec);
        glm::vec3 left = glm::normalize(glm::cross(up_, forward));
        glm::vec3 up = glm::normalize(glm::cross(forward, left));

        float distance = glm::length(positionVec);
        float factor = distance * (float)tan(glm::radians(fov_) / 2) * 2;
        glm::vec3 deltaX = factor * aspect_ * motion.x * left;
        glm::vec3 deltaY = factor * motion.y * up;
        target_ += (deltaX + deltaY);
        eye_ += (deltaX + deltaY);
    }

    void Camera::Approach(float ratio)
    {
        glm::vec3 centerVec = eye_ - target_;
        float radius = glm::length(centerVec);
        float yaw = (float)std::atan2(centerVec.x, centerVec.z);
        float pitch = (float)std::asin(centerVec.y / radius);
        glm::vec3 offset;
        radius *= (float)std::pow(0.95, ratio);
        offset.x = (radius * (float)std::cos(pitch) * (float)std::sin(yaw));
        offset.y = (radius * (float)std::sin(pitch));
        offset.z = (radius * (float)std::cos(pitch) * (float)std::cos(yaw));
        eye_ = target_ + offset;
    }

    glm::mat4 Camera::GetViewMatrix()
    {
        return glm::lookAt(eye_, target_, up_);
    }

    glm::mat4 Camera::GetProjectionMatrix()
    {
        return glm::perspective(glm::radians(fov_), aspect_, znear_, zfar_);
    }

    void Camera::SetCenter(const glm::vec3 &pos)
    {
        glm::vec3 offset = eye_ - target_;
        target_ = pos;
        eye_ = target_ + offset;
    }
} // namespace smesh