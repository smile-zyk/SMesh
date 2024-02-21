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

      private:
        float fov_;
        float znear_;
        float zfar_;
        float aspect_;
        glm::vec3 eye_;
        glm::vec3 target_;
        glm::vec3 up_;
    };
} // namespace smesh