#include "object_config.h"
#include "qtvariantproperty.h"
#include "smesh/config/config.h"
#include "smesh/config/object_config.h"
#include <qvariant.h>
#include <QVector4D>
namespace smesh
{
    const ModelObjectConfigDef* ModelObjectConfigDef::Instance()
    {
        static ModelObjectConfigDef def;
        return &def;
    }

    QString ModelObjectConfigDef::ConfigDefName() const
    {
        return "ModelObjectConfigDef";
    }

    ModelObjectConfigDef::ModelObjectConfigDef()
    {
        auto transform_def = AddProperty("Transform", QtVariantPropertyManager::groupTypeId());
        auto translate_def = transform_def->AddSubProperty("Translate", QVariant::Vector3D);
        translate_def->set_tool_tip("translate");
        auto rotate_def = transform_def->AddSubProperty("Rotate", QtVariantPropertyManager::groupTypeId());
        rotate_def->set_tool_tip("rotate");
        auto rotate_mode_def = rotate_def->AddSubProperty("Mode", QtVariantPropertyManager::enumTypeId());
        rotate_mode_def->set_attribute_value("enumNames", QStringList
        {"XYZ Euler", "XZY Euler", "YXZ Euler", "YZX Euler", "ZXY Euler", "ZYX Euler", "Axis Angle", "Quaternion"});
        rotate_mode_def->set_tool_tip("rotate mode");
        auto rotate_angle_def = rotate_def->AddSubProperty("Rotation", QVariant::Int);
        rotate_angle_def->set_tool_tip("rotate angle");
        rotate_angle_def->set_attribute_value("suffix", " m");
        rotate_angle_def->set_attribute_value("singleStep", 1);
        auto scale_def = transform_def->AddSubProperty("Scale", QVariant::Vector4D);
        scale_def->set_tool_tip("scale");
        scale_def->set_default_value(QVariant::fromValue(QVector4D{1,2,3,4}));
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
    
    std::unique_ptr<ModelObjectConfig> ModelObjectConfig::CreateUnique()
    {
        return std::make_unique<ModelObjectConfig>(ModelObjectConfigDef::Instance());
    }
}