#pragma once
#include "smesh/core.h"
#include "smesh/mesh/mesh.h"
#include <QObject>
#include <glm/mat4x4.hpp>
#include <memory>
#include <string>


namespace smesh
{
    class SMESH_API ModelObject : public QObject
    {
        Q_OBJECT
      public:
        ModelObject(const std::string &name, const std::string &path);
        ModelObject(const std::string &path);
        ModelObject();
        ~ModelObject();
        std::string name() { return name_; }
        std::shared_ptr<Mesh> mesh() { return mesh_; }
        glm::mat4 transform() { return transform_; }
        void set_transform(const glm::mat4 &transform) { transform_ = transform; }
      private:
        std::string name_;
        std::shared_ptr<Mesh> mesh_;
        glm::mat4 transform_;
    };
} // namespace smesh