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

    class SMESH_API ModelObjectConfig : public Config
    {
        public:
         static std::unique_ptr<ModelObjectConfig> CreateUnique();
        public:
         ModelObjectConfig(const ModelObjectConfigDef* def): Config(def){}
    };
}