#include "object_config.h"
#include "qtvariantproperty.h"
#include "smesh/config/config.h"
#include "smesh/config/object_config.h"
#include <qvariant.h>

namespace smesh
{
    const ModelObjectConfigDef* ModelObjectConfigDef::Instance()
    {
        static ModelObjectConfigDef def;
        return &def;
    }

    ModelObjectConfigDef::ModelObjectConfigDef()
    {
        auto transform_def = AddProperty("Transform", QtVariantPropertyManager::groupTypeId());
        auto translate_def = transform_def->AddSubProperty("Translate", QVariant::RectF);
        translate_def->set_tool_tip("translate");
        auto rotate_def = transform_def->AddSubProperty("Rotate", QVariant::RectF);
        rotate_def->set_tool_tip("rotate");
        auto scale_def = transform_def->AddSubProperty("Scale", QVariant::RectF);
        scale_def->set_tool_tip("scale");
        auto info_def = AddProperty("Information", QtVariantPropertyManager::groupTypeId());
        auto vertex_def = info_def->AddSubProperty("Vertex Count", QVariant::Int);
        vertex_def->set_tool_tip("vertex count");
        vertex_def->set_read_only(true);
        auto edge_def = info_def->AddSubProperty("Edge Count", QVariant::Int);
        edge_def->set_tool_tip("edge count");
        edge_def->set_read_only(true);
        auto face_def = info_def->AddSubProperty("Face Count", QVariant::Int);
        face_def->set_tool_tip("face count");
        face_def->set_read_only(true);
    } 
    
    ModelObjectConfig ModelObjectConfig::Create()
    {
        return ModelObjectConfig(ModelObjectConfigDef::Instance());
    }
}