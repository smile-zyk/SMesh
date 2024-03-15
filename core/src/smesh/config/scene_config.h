#pragma once

#include "config.h"
#include "smesh/config/config.h"
#include "smesh/core.h"

namespace smesh {
    
    class SMESH_API SceneConfigDef : public ConfigDef
    {
       public:
        static const SceneConfigDef* Instance();
       private:
         SceneConfigDef();
    };

    class SMESH_API SceneConfig : public Config
    {
        public:
         static SceneConfig Create();
        public:
         SceneConfig(const SceneConfigDef* def): Config(def){}
    };
}