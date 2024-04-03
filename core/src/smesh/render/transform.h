#pragma once
#include "smesh/core.h"
#include "rotation.h"
#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>
#include <glm/gtx/quaternion.hpp>

namespace smesh
{
    class SMESH_API Transform
    {
      public:
        Transform();
        
      private:
        glm::vec3 translate_;
        Rotation rotate_;
        glm::vec3 scale_;
    };
} // namespace smesh