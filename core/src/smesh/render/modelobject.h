#pragma once
#include "smesh/core.h"
#include "smesh/mesh/mesh.h"
#include <glm/fwd.hpp>
#include <glm/mat4x4.hpp>
#include <memory>
#include <string>
#include "smesh/config/object_config.h"
#include "transform.h"
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
        void UpdateTransformFromConfig(bool is_rotate_mode_change = false);
        void UpdateConfigFromTransform();
        std::string name() { return name_; }
        std::shared_ptr<Mesh> mesh() { return mesh_; }
        Transform* transform() { return transform_.get(); }
        glm::mat4 transform_matrix() { return transform_->matrix(); }
        Config* config() { return config_.get(); }
      private:
        std::string name_;
        std::shared_ptr<Mesh> mesh_;
        std::unique_ptr<Transform> transform_;
        std::unique_ptr<ModelObjectConfig> config_;
    };
} // namespace smesh