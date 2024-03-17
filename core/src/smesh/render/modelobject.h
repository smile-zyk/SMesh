#pragma once
#include "smesh/core.h"
#include "smesh/mesh/mesh.h"
#include <glm/mat4x4.hpp>
#include <memory>
#include <string>
#include "smesh/config/object_config.h"
#include <QObject>

namespace smesh
{
    class SMESH_API ModelObject : QObject
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
        Config* config() { return config_.get(); }
      private:
        std::string name_;
        std::shared_ptr<Mesh> mesh_;
        glm::mat4 transform_{1.0};
        std::unique_ptr<ModelObjectConfig> config_;
    };
} // namespace smesh