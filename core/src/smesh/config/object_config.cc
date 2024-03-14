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
        auto translate_def = AddProperty("Translate", QtVariantPropertyManager::groupTypeId());
        
        auto translate_x_def = translate_def->AddSubProperty("TranslateX", QVariant::Double);
        translate_x_def->set_default_value(0.5);
        translate_x_def->set_attribute_value("tooltip", "Translate X");
        auto translate_y_def = translate_def->AddSubProperty("TranslateY", QVariant::Double);
        translate_y_def->set_default_value(0.5);
        translate_y_def->set_attribute_value("tooltip", "Translate Y");
        auto translate_z_def = translate_def->AddSubProperty("TranslateZ", QVariant::Double);
        translate_z_def->set_default_value(1.0);
        translate_z_def->set_attribute_value("tooltip", "Translate Z");

        auto rotate_def = AddProperty("Rotate", QtVariantPropertyManager::groupTypeId());
        auto rotate_x_def = rotate_def->AddSubProperty("RotateX", QVariant::Double);
        rotate_x_def->set_default_value(0.5);
        rotate_x_def->set_attribute_value("tooltip", "Rotate X");
        auto rotate_y_def = rotate_def->AddSubProperty("RotateY", QVariant::Double);
        rotate_y_def->set_default_value(0.5);
        rotate_y_def->set_attribute_value("tooltip", "Rotate Y");
        auto rotate_z_def = rotate_def->AddSubProperty("RotateZ", QVariant::Double);
        rotate_z_def->set_default_value(1.0);
        rotate_z_def->set_attribute_value("tooltip", "Rotate Z");

        auto point_def = AddProperty("Point", QVariant::Point);
    } 
    
    ModelObjectConfig ModelObjectConfig::Create()
    {
        return ModelObjectConfig(ModelObjectConfigDef::Instance());
    }
}