#include "modelobject.h"
#include <memory>

namespace smesh
{
    ModelObject::ModelObject(const std::string &name, const std::string &path)
    {
        name_ = name;
        mesh_ = std::make_shared<Mesh>(path);
        transform_ = glm::mat4(1.0);
        // config_ = std::make_unique<Config>();
        // auto def = config_->AddConfigDefinition("Test1", QVariant::Int);
        // def->set_default_value(5);
        // def->set_min(0);
        // def->set_max(10);

        // def = config_->AddConfigDefinition("Test2", QVariant::Bool);
        // def->set_default_value(false);
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