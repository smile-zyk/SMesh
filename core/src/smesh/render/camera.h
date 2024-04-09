#pragma once
#include <glm/gtc/matrix_transform.hpp>

namespace smesh
{
    // OrbitCamera
    class Camera
    {
      public:
        explicit Camera();
        void TrackBallRotate(const glm::vec2& last_mouse_pos, const glm::vec2& cur_mouse_pos);
        void Rotate(const glm::vec2 &motion);
        void Move(const glm::vec2 &motion);
        void Approach(float ratio);
        glm::mat4 GetViewMatrix();
        glm::mat4 GetProjectionMatrix();
        void SetCenter(const glm::vec3 &pos);
        void set_aspect(float aspect) {aspect_ = aspect;}
        glm::vec3 eye() { return eye_; }
        float znear() { return znear_; }
        float zfar() { return zfar_; }
      private:
        float fov_ {60};
        float znear_ {0.01f};
        float zfar_ {2000};
        float aspect_ {1.777f};
        glm::vec3 eye_ = {10.f, 10.f, 10.f};
        glm::vec3 target_ = {0.0f, 0.0f, 0.0f};
        glm::vec3 up_ = {0.0f, 0.0f, 1.0f};
    };
} // namespace smesh