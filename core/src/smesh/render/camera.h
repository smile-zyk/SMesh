#pragma once
#include <glm/gtc/matrix_transform.hpp>

namespace smesh
{
    // OrbitCamera
    class Camera
    {
      public:
        explicit Camera(float _fov, float _zNear, float _zFar, float _aspect);
        void Rotate(const glm::vec2 &motion);
        void Move(const glm::vec2 &motion);
        void Approach(float ratio);
        glm::mat4 GetViewMatrix();
        glm::mat4 GetProjectionMatrix();
        void SetCenter(const glm::vec3 &pos);
        void set_aspect(float aspect) {aspect_ = aspect;}

      private:
        float fov_;
        float znear_;
        float zfar_;
        float aspect_;
        glm::vec3 eye_ = {0.0f, 0.0f, 100.0f};
        glm::vec3 target_ = {0.0f, 0.0f, 0.0f};
        glm::vec3 up_ = {0.0f, 1.0f, 0.0f};
    };
} // namespace smesh