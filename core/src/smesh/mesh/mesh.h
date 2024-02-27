#pragma once
#include <string>
#include <memory>

#include <glm/vec3.hpp>
#include <OpenMesh/Core/Mesh/Attributes.hh>
#include <OpenMesh/Core/Mesh/Traits.hh>
#include <OpenMesh/Core/Mesh/TriMesh_ArrayKernelT.hh>

#include "smesh/core.h"

namespace smesh
{
    struct VertexRenderData
    {
        VertexRenderData(glm::vec3 p, glm::vec3 n, glm::vec3 c = {0.5f, 0.5f, 0.5f}): position(p), normal(n), color(c){}
        glm::vec3 position;
        glm::vec3 normal;
        glm::vec3 color;
    };

    struct MeshRenderData
    {
        std::vector<VertexRenderData> render_points;
        std::vector<unsigned int> render_indices;
    };

    struct MeshTraits : public OpenMesh::DefaultTraits
    {
        VertexAttributes(OpenMesh::Attributes::Normal | OpenMesh::Attributes::Color |
                         OpenMesh::Attributes::Status);
        FaceAttributes(OpenMesh::Attributes::Normal | OpenMesh::Attributes::Status);
        EdgeAttributes(OpenMesh::Attributes::Status);
    };

    typedef OpenMesh::TriMesh_ArrayKernelT<MeshTraits> MeshBase;

    class ModelObject;

    class SMESH_API Mesh : public MeshBase
    {
      public:
        Mesh();
        Mesh(const std::string &path);
        virtual ~Mesh();
        bool ReadFromFile(const std::string &path);
        bool WriteToFile(const std::string &path);
        void RefreshRenderData();
        void RefreshIndexRenderData();
        void RefreshVertexRenderData();
        void RefreshVertexRenderData(std::vector<unsigned int> vertex_list);
        MeshRenderData* render_data() { return render_data_.get(); }
        std::vector<std::weak_ptr<ModelObject>>& ref_object_list() { return ref_object_list_; }
      private:
        // cache render data for renderer use
        std::unique_ptr<MeshRenderData> render_data_;
        std::vector<std::weak_ptr<ModelObject>> ref_object_list_;
    };
} // namespace smesh