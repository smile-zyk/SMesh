#include "mesh.h"
#include "smesh/log/log.h"
#include "smesh/mesh/mesh.h"
#include <OpenMesh/Core/IO/MeshIO.hh>
#include <OpenMesh/Core/IO/Options.hh>
#include <fmt/core.h>
#include <memory>

namespace smesh
{
    Mesh::Mesh()
    {
    }
    
    Mesh::Mesh(const std::string& path)
    {
        render_data_ = std::make_unique<MeshRenderData>();
        ReadFromFile(path);
    }
    
    Mesh::~Mesh()
    {
        
    }

    bool Mesh::ReadFromFile(const std::string &path)
    {
        OpenMesh::IO::Options ropt;
        if (!OpenMesh::IO::read_mesh(*this, path, ropt))
        {
            SMESH_ERROR("Error loading mesh from file {}", path);
            return false;
        }
        if (!ropt.check(OpenMesh::IO::Options::VertexNormal))
        {
            update_normals();
        }

        render_data_->render_points.reserve(n_vertices());
        render_data_->render_indices.reserve(n_faces() * 3);
        for(VertexIter v_it = vertices_begin(); v_it != vertices_end(); ++v_it)
        {
            Point p = point(*v_it);
            Normal n = normal(*v_it);
            render_data_->render_points.push_back(VertexRenderData({p[0], p[1], p[2]}, {n[0], n[1], n[2]}));
        }

        for(FaceIter f_it = faces_begin(); f_it != faces_end(); ++f_it)
        {
            for(FaceVertexCCWIter fv_it = fv_ccwiter(*f_it); fv_it != fv_ccwend(*f_it); ++fv_it)
            {
                render_data_->render_indices.emplace_back(fv_it->idx());
            }
        }
        return true;
    }

    bool Mesh::WriteToFile(const std::string &path)
    {
        return false;
    }
} // namespace smesh