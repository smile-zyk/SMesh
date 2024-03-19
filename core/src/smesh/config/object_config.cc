#include "object_config.h"
#include "qtvariantproperty.h"
#include "smesh/config/config.h"
#include "smesh/config/object_config.h"
#include <qvariant.h>
#include <QVector4D>
#include <QDebug>

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

        auto translate_def = transform_def->AddSubProperty("Translate", QtVariantPropertyManager::groupTypeId());
        translate_def->set_tool_tip("Translate");
        auto translate_x_def = translate_def->AddSubProperty("X", QVariant::Double);
        translate_x_def->set_tool_tip("Translate X");
        translate_x_def->set_attribute_value("singleStep", 0.1);
        translate_x_def->set_attribute_value("suffix", " m");
        auto translate_y_def = translate_def->AddSubProperty("Y", QVariant::Double);
        translate_y_def->set_tool_tip("Translate Y");
        translate_y_def->set_attribute_value("singleStep", 0.1);
        translate_y_def->set_attribute_value("suffix", " m");
        auto translate_z_def = translate_def->AddSubProperty("Z", QVariant::Double);
        translate_z_def->set_tool_tip("Translate Z");
        translate_z_def->set_attribute_value("singleStep", 0.1);
        translate_z_def->set_attribute_value("suffix", " m");

        auto rotate_def = transform_def->AddSubProperty("Rotate", QtVariantPropertyManager::groupTypeId());
        rotate_def->set_tool_tip("Rotate");

        auto rotate_w_def = rotate_def->AddSubProperty("W", QVariant::Double);
        rotate_w_def->set_visible(false);
        rotate_w_def->set_tool_tip("Rotate W");
        rotate_w_def->set_attribute_value("singleStep", 0.1);
        auto rotate_x_def = rotate_def->AddSubProperty("X", QVariant::Double);
        rotate_x_def->set_tool_tip("Rotate X");
        rotate_x_def->set_attribute_value("singleStep", 0.1);
        auto rotate_y_def = rotate_def->AddSubProperty("Y", QVariant::Double);
        rotate_y_def->set_tool_tip("Rotate Y");
        rotate_y_def->set_attribute_value("singleStep", 0.1);
        auto rotate_z_def = rotate_def->AddSubProperty("Z", QVariant::Double);
        rotate_z_def->set_tool_tip("Rotate Z");
        rotate_z_def->set_attribute_value("singleStep", 0.1);
        auto rotate_mode_def = rotate_def->AddSubProperty("Mode", QtVariantPropertyManager::enumTypeId());
        rotate_mode_def->set_attribute_value("enumNames", QStringList
        {"XYZ Euler", "XZY Euler", "YXZ Euler", "YZX Euler", "ZXY Euler", "ZYX Euler", "Axis Angle", "Quaternion"});
        rotate_mode_def->add_condition({0, 1, 2, 3, 4, 5},
         {"Transform/Rotate/X", "Transform/Rotate/Y", "Transform/Rotate/Z", "Transform/Rotate/W"}, [=]()
        {
            rotate_x_def->set_attribute_value("suffix", " °");
            rotate_y_def->set_attribute_value("suffix", " °");
            rotate_z_def->set_attribute_value("suffix", " °");
            rotate_w_def->set_visible(false);
        });
        rotate_mode_def->add_condition({6},
         {"Transform/Rotate/X", "Transform/Rotate/Y", "Transform/Rotate/Z", "Transform/Rotate/W"}, [=]()
        {
            rotate_x_def->set_attribute_value("suffix", "");
            rotate_y_def->set_attribute_value("suffix", "");
            rotate_z_def->set_attribute_value("suffix", "");
            rotate_w_def->set_visible(true);
            rotate_w_def->set_attribute_value("suffix", " °");
        });
        rotate_mode_def->add_condition({7},
         {"Transform/Rotate/X", "Transform/Rotate/Y", "Transform/Rotate/Z", "Transform/Rotate/W"}, [=]()
        {
            rotate_x_def->set_attribute_value("suffix", "");
            rotate_y_def->set_attribute_value("suffix", "");
            rotate_z_def->set_attribute_value("suffix", "");
            rotate_w_def->set_visible(true);
            rotate_w_def->set_attribute_value("suffix", "");
        });

        auto scale_def = transform_def->AddSubProperty("Scale", QtVariantPropertyManager::groupTypeId());
        scale_def->set_tool_tip("Scale");

        auto scale_x_def = scale_def->AddSubProperty("X", QVariant::Double);
        scale_x_def->set_tool_tip("Scale X");
        scale_x_def->set_default_value(1);
        scale_x_def->set_attribute_value("singleStep", 0.1);
        scale_x_def->set_attribute_value("minimum", 0);
        auto scale_y_def = scale_def->AddSubProperty("Y", QVariant::Double);
        scale_y_def->set_tool_tip("Scale Y");
        scale_y_def->set_default_value(1);
        scale_y_def->set_attribute_value("singleStep", 0.1);
        scale_y_def->set_attribute_value("minimum", 0);
        auto scale_z_def = scale_def->AddSubProperty("Z", QVariant::Double);
        scale_z_def->set_tool_tip("Scale Z");
        scale_z_def->set_default_value(1);
        scale_z_def->set_attribute_value("singleStep", 0.1);
        scale_z_def->set_attribute_value("minimum", 0);

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
    
    std::unique_ptr<ModelObjectConfig> ModelObjectConfig::CreateUnique(ModelObject* object)
    {
        return std::make_unique<ModelObjectConfig>(ModelObjectConfigDef::Instance(), object);
    }
}