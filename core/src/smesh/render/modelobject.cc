#include "modelobject.h"
#include <memory>
#include "smesh/log/log.h"

namespace smesh
{
    ModelObject::ModelObject(const std::string &name, const std::string &path)
    {
        name_ = name;
        mesh_ = std::make_shared<Mesh>(path);
        transform_ = glm::mat4(1.0);
        config_ = ModelObjectConfig::CreateUnique();
        connect(config_.get(), &Config::propertyChanged, this, [this](const PropertyKey& key, QVariant value)
        {
            SMESH_INFO("111");
        });
    }
    
    ModelObject::ModelObject(const std::string &path)
    {
        name_ = path;
        mesh_ = std::make_shared<Mesh>(path);
        transform_ = glm::mat4(1.0);
    }
    
    ModelObject::~ModelObject()
    {
        
    }
}