#include "modelobject.h"
#include <memory>
#include <QDebug>

namespace smesh
{
    ModelObject::ModelObject(const std::string &name, const std::string &path)
    {
        name_ = name;
        mesh_ = std::make_shared<Mesh>(path);
        transform_ = glm::mat4(1.0);
        config_ = ModelObjectConfig::CreateUnique(this);
        connect(config_.get(), &Config::triggeredPropertyChanged, this, [this](const PropertyKey& key, QVariant value)
        {
            qDebug() << key;
            qDebug() << value;
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