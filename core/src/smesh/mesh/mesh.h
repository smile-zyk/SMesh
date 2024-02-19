#pragma once
#include <string>
#include <memory>

#include <OpenMesh/Core/Mesh/Attributes.hh>
#include <OpenMesh/Core/Mesh/Traits.hh>
#include <OpenMesh/Core/Mesh/TriMesh_ArrayKernelT.hh>

#include "smesh/core.h"

namespace smesh
{
    struct MeshTraits : public OpenMesh::DefaultTraits
    {
        VertexAttributes(OpenMesh::Attributes::Normal | OpenMesh::Attributes::Color |
                         OpenMesh::Attributes::Status);
        FaceAttributes(OpenMesh::Attributes::Normal | OpenMesh::Attributes::Status);
        EdgeAttributes(OpenMesh::Attributes::Status);
    };

    typedef OpenMesh::TriMesh_ArrayKernelT<MeshTraits> MeshBase;

    struct MeshRenderData;

    class SMESH_API Mesh : public MeshBase
    {
      public:
        Mesh();
        Mesh(const std::string &path);
        virtual ~Mesh();
        bool ReadFromFile(const std::string &path);
        bool WriteToFile(const std::string &path);
        void Modifed(bool is_topo_change = false);
        MeshRenderData* get_render_data() { return render_data_.get(); }
      private:
        // cache render data
        std::unique_ptr<MeshRenderData> render_data_;
    };
} // namespace smesh