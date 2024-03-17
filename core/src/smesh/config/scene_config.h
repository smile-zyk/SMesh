#pragma once

#include "config.h"
#include "smesh/config/config.h"
#include "smesh/core.h"

namespace smesh {
    
    class SMESH_API SceneConfigDef : public ConfigDef
    {
       public:
        static const SceneConfigDef* Instance();
        QString ConfigDefName() const override;
       private:
         SceneConfigDef();
    };

    class SMESH_API SceneConfig : public Config
    {
        public:
         static std::unique_ptr<SceneConfig> CreateUnique();
        public:
         SceneConfig(const SceneConfigDef* def): Config(def){}
    };
}