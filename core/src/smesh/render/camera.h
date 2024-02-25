#pragma once
#include <glm/gtc/matrix_transform.hpp>

namespace smesh
{
    // OrbitCamera
    class Camera
    {
      public:
        explicit Camera();
        void Rotate(const glm::vec2 &motion);
        void Move(const glm::vec2 &motion);
        void Approach(float ratio);
        glm::mat4 GetViewMatrix();
        glm::mat4 GetProjectionMatrix();
        void SetCenter(const glm::vec3 &pos);
        void set_aspect(float aspect) {aspect_ = aspect;}
        glm::vec3 eye() { return eye_; }
      private:
        float fov_ {60};
        float znear_ {1};
        float zfar_ {1000};
        float aspect_ {1.777f};
        glm::vec3 eye_ = {0.0f, 0.0f, 100.0f};
        glm::vec3 target_ = {0.0f, 0.0f, 0.0f};
        glm::vec3 up_ = {0.0f, 1.0f, 0.0f};
    };
} // namespace smesh