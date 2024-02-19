#pragma once
#include <glm/fwd.hpp>
#include <vector>
#include <glm/glm.hpp>

#include "smesh/core.h"

namespace smesh
{
    struct VertexRenderData
    {
        glm::vec3 position;
    };

    struct MeshRenderData
    {
        std::vector<glm::vec3> render_points;
        std::vector<int> render_indices;
    };

    class SMESH_API Renderer
    {
    public:
        Renderer();
        ~Renderer(){}
    };
}