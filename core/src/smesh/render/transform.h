#pragma once
#include "rotation.h"
#include "smesh/core.h"
#include <memory>
#include <glm/fwd.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>


namespace smesh
{
    class SMESH_API Transform
    {
      public:
        Transform();
        void set_matrix(glm::mat4 matrix);
        glm::mat4 matrix();
        void set_translate(const glm::vec3 &translate) { translate_ = translate; }
        void set_scale(const glm::vec3 &scale) { scale_ = scale; }
        glm::vec3 translate() { return translate_; }
        glm::vec3 scale() { return scale_; }
        Rotation* rotate() { return rotate_.get(); }

      private:
        glm::vec3 translate_;
        std::unique_ptr<Rotation> rotate_;
        glm::vec3 scale_{1.0, 1.0, 1.0};
    };
} // namespace smesh