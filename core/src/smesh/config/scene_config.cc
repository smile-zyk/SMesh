#include "scene_config.h"
#include "qtvariantproperty.h"
#include "smesh/config/scene_config.h"
#include <qcolor.h>
#include <qvariant.h>

namespace smesh
{
    const SceneConfigDef* SceneConfigDef::Instance()
    {
        static SceneConfigDef def;
        return &def;
    }

    SceneConfigDef::SceneConfigDef()
    {
        auto grid_def = AddProperty("Grid", QtVariantPropertyManager::flagTypeId());
        grid_def->set_attribute_value("flagNames", QStringList{"X", "Y"});
        grid_def->set_tool_tip("grid axis");
        grid_def->set_default_value(3);

        auto back_def = AddProperty("BackGroud", QVariant::Color);
        back_def->set_default_value(QColor("red"));
        back_def->set_tool_tip("backgroud color");
    }

    SceneConfig SceneConfig::Create()
    {
        return SceneConfig(SceneConfigDef::Instance());
    }
}