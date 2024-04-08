#include "modelobject.h"
#include <glm/ext/matrix_transform.hpp>
#include <glm/fwd.hpp>
#include <glm/trigonometric.hpp>
#include <memory>
#include <QDebug>
#include <imgui.h>
#include <ImGuizmo.h>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/euler_angles.hpp>
#include "rotation.h"
#include "smesh/common.h"
#include "smesh/log/log.h"
#include "smesh/render/transform.h"

namespace smesh
{
    ModelObject::ModelObject(const std::string &name, const std::string &path): transform_()
    {
        name_ = name;
        mesh_ = std::make_shared<Mesh>(path);
        transform_ = std::make_unique<Transform>();
        config_ = ModelObjectConfig::CreateUnique(this);
        connect(config_.get(), &Config::triggeredPropertyChanged, this, [this](const PropertyKey& key, QVariant value, QVariant old_value)
        {
            UpdateTransformFromConfig(key == "Transform/Rotate/Mode" && value != old_value);
        });
    }
    
    ModelObject::ModelObject(const std::string &path)
    {
        name_ = path;
        mesh_ = std::make_shared<Mesh>(path);
    }
    
    ModelObject::~ModelObject()
    {
        
    }
    
    void ModelObject::UpdateTransformFromConfig(bool is_rotate_mode_change)
    {
        float translate_x = config_->property("Transform/Translate/X").toDouble();
        float translate_y = config_->property("Transform/Translate/Y").toDouble();
        float translate_z = config_->property("Transform/Translate/Z").toDouble();
        float scale_x = config_->property("Transform/Scale/X").toDouble();
        float scale_y = config_->property("Transform/Scale/Y").toDouble();
        float scale_z = config_->property("Transform/Scale/Z").toDouble();
        int rotate_mode = config_->property("Transform/Rotate/Mode").toInt();
        if(is_rotate_mode_change == true)
        {
            if(rotate_mode == RotationMode::kAxisAngle)
            {
                auto axis_angle = transform_->rotate()->axis_angle();
                config_->set_property("Transform/Rotate/X", axis_angle.axis.x);
                config_->set_property("Transform/Rotate/Y", axis_angle.axis.y);
                config_->set_property("Transform/Rotate/Z", axis_angle.axis.z);
                config_->set_property("Transform/Rotate/W", glm::degrees(axis_angle.angle));
            }
            else if(rotate_mode == RotationMode::kQuaternion)
            {
                auto quat = transform_->rotate()->quaternion();
                config_->set_property("Transform/Rotate/X", quat.x);
                config_->set_property("Transform/Rotate/Y", quat.y);
                config_->set_property("Transform/Rotate/Z", quat.z);
                config_->set_property("Transform/Rotate/W", quat.w);
            }
            else 
            {
                auto euler = transform_->rotate()->euler(rotate_mode);
                config_->set_property("Transform/Rotate/X", euler.x);
                config_->set_property("Transform/Rotate/Y", euler.y);
                config_->set_property("Transform/Rotate/Z", euler.z);
            }
        }
        float rotate_x = config_->property("Transform/Rotate/X").toDouble();
        float rotate_y = config_->property("Transform/Rotate/Y").toDouble();
        float rotate_z = config_->property("Transform/Rotate/Z").toDouble();
        float rotate_w = config_->property("Transform/Rotate/W").toDouble();
        SMESH_INFO("UpdateTransformFromConfig Scale ({}, {}, {})", scale_x, scale_y, scale_z);
        transform_->set_translate({translate_x, translate_y, translate_z});
        transform_->set_scale({scale_x, scale_y, scale_z});
        switch (rotate_mode) {
            case RotationMode::kAxisAngle:
                transform_->rotate()->set_axis_angle({{rotate_x, rotate_y, rotate_z}, rotate_w});
                break;
            case RotationMode::kQuaternion:
                transform_->rotate()->set_quaternion({rotate_w, rotate_x, rotate_y, rotate_z});
                break;
            case RotationMode::kEulerXYZ:
            case RotationMode::kEulerXZY:
            case RotationMode::kEulerYXZ:
            case RotationMode::kEulerYZX:
            case RotationMode::kEulerZXY:
            case RotationMode::kEulerZYX:
                transform_->rotate()->set_euler(rotate_mode, {rotate_x, rotate_y, rotate_z});
                break;
        }
    }
    
    void ModelObject::UpdateConfigFromTransform()
    {
        glm::vec3 translate = transform_->translate();
        glm::vec3 scale = transform_->scale();
        SMESH_INFO("UpdateConfigFromTransform Scale ({}, {}, {})", scale.x, scale.y, scale.z);
        int rotate_mode = config_->property("Transform/Rotate/Mode").toInt();
        config_->set_property("Transform/Translate/X", translate.x);
        config_->set_property("Transform/Translate/Y", translate.y);
        config_->set_property("Transform/Translate/Z", translate.z);
        config_->set_property("Transform/Scale/X", scale.x);
        config_->set_property("Transform/Scale/Y", scale.y);
        config_->set_property("Transform/Scale/Z", scale.z);
        if(rotate_mode == RotationMode::kAxisAngle)
        {
            auto axis_angle = transform_->rotate()->axis_angle();
            config_->set_property("Transform/Rotate/X", axis_angle.axis.x);
            config_->set_property("Transform/Rotate/Y", axis_angle.axis.y);
            config_->set_property("Transform/Rotate/Z", axis_angle.axis.z);
            config_->set_property("Transform/Rotate/W", axis_angle.angle);
        }
        else if(rotate_mode == RotationMode::kQuaternion)
        {
            auto quat = transform_->rotate()->quaternion();
            config_->set_property("Transform/Rotate/X", quat.x);
            config_->set_property("Transform/Rotate/Y", quat.y);
            config_->set_property("Transform/Rotate/Z", quat.z);
            config_->set_property("Transform/Rotate/W", quat.w);
        }
        else 
        {
            auto euler = transform_->rotate()->euler(rotate_mode);
            config_->set_property("Transform/Rotate/X", euler.x);
            config_->set_property("Transform/Rotate/Y", euler.y);
            config_->set_property("Transform/Rotate/Z", euler.z);
        }
    }
}