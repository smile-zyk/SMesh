#pragma once

#include "glm/mat4x4.hpp"
#include "glm/vec4.hpp"
#include "smesh/common.h"
#include "smesh/core.h"


namespace smesh
{
    class SMESH_API Rotation
    {
      public:
        Rotation(int rotate_mode, const glm::vec4& rotate_data): rotate_mode_(rotate_mode), rotate_data_(rotate_data){}
        glm::mat4 GetRotateMatrix();
        void SetRotation(int rotate_mode, const glm::vec4& rotate_data);
        void SetRotationMode(int rotate_mode);
        void SetRotationData(const glm::vec4& rotate_data);
        int rotate_mode() { return rotate_mode_; }
        glm::vec4 rotate_data() { return rotate_data_; }
      private:
        int rotate_mode_{RotationMode::kEulerXYZ};
        glm::vec4 rotate_data_{};
    };
} // namespace smesh