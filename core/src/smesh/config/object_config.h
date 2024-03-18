#pragma once

#include "config.h"
#include "smesh/config/config.h"
#include "smesh/core.h"
#include <memory>

namespace smesh {
    
    class SMESH_API ModelObjectConfigDef : public ConfigDef
    {
       public:
        static const ModelObjectConfigDef* Instance();
        virtual QString ConfigDefName() const override;
       private:
         ModelObjectConfigDef();
    };

    class ModelObject;

    class SMESH_API ModelObjectConfig : public Config
    {
        public:
         static std::unique_ptr<ModelObjectConfig> CreateUnique(ModelObject* object);
        public:
         ModelObjectConfig(const ModelObjectConfigDef* def, ModelObject* object): Config(def){ object_ = object; }
         ModelObject* object() { return object_; }
        private:
         ModelObject* object_;
    };
}