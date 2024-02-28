#include "camera.h"

namespace smesh
{
    Camera::Camera()
    {
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