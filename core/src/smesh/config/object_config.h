#pragma once

#include "config.h"
#include "smesh/config/config.h"
#include "smesh/core.h"

namespace smesh {
    
    class SMESH_API ModelObjectConfigDef : public ConfigDef
    {
       public:
        static const ModelObjectConfigDef* Instance();
       private:
         ModelObjectConfigDef();
    };

    class SMESH_API ModelObjectConfig : public Config
    {
        public:
         static ModelObjectConfig Create();
        public:
         ModelObjectConfig(const ModelObjectConfigDef* def): Config(def){}
    };
}