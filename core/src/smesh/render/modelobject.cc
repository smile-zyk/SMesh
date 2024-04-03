#include "modelobject.h"
#include <glm/ext/matrix_transform.hpp>
#include <memory>
#include <QDebug>
#include <imgui.h>
#include <ImGuizmo.h>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/euler_angles.hpp>
#include "rotation.h"
#include "smesh/log/log.h"

namespace smesh
{
    ModelObject::ModelObject(const std::string &name, const std::string &path)
    {
        name_ = name;
        mesh_ = std::make_shared<Mesh>(path);
        config_ = ModelObjectConfig::CreateUnique(this);
        connect(config_.get(), &Config::triggeredPropertyChanged, this, [this](const PropertyKey& key, QVariant value)
        {
            update_transform();
        });
    }
    
    ModelObject::ModelObject(const std::string &path)
    {
        name_ = path;
        mesh_ = std::make_shared<Mesh>(path);
    }
    
    void ModelObject::set_transform(const glm::mat4 &transform)
    {
        float translate[3], rotate[3], scale[3];
        ImGuizmo::DecomposeMatrixToComponents(glm::value_ptr(transform), translate, rotate, scale);
        Rotation r(RotationMode::kEulerXYZ, {rotate[0], rotate[1], rotate[2], 0});
        r.SetRotationMode(config_->property("Transform/Rotate/Mode").toInt());
        SMESH_INFO("set translate ({}, {}, {})", translate[0], translate[1], translate[2]);
        SMESH_INFO("set rotate ({}, {}, {})", rotate[0], rotate[1], rotate[2]);
        SMESH_INFO("set scale ({}, {}, {})", scale[0], scale[1], scale[2]);
        config_->set_property("Transform/Translate/X", translate[0]);
        config_->set_property("Transform/Translate/Y", translate[1]);
        config_->set_property("Transform/Translate/Z", translate[2]);
        config_->set_property("Transform/Rotate/X", r.rotate_data().x);
        config_->set_property("Transform/Rotate/Y", r.rotate_data().y);
        config_->set_property("Transform/Rotate/Z", r.rotate_data().z);
        config_->set_property("Transform/Rotate/W", r.rotate_data().w);
        config_->set_property("Transform/Scale/X", scale[0]);
        config_->set_property("Transform/Scale/Y", scale[1]);
        config_->set_property("Transform/Scale/Z", scale[2]);
        transform_ = transform;
    }

    void ModelObject::update_transform()
    {
        float translate_x = config_->property("Transform/Translate/X").toDouble();
        float translate_y = config_->property("Transform/Translate/Y").toDouble();
        float translate_z = config_->property("Transform/Translate/Z").toDouble();
        float rotate_x = config_->property("Transform/Rotate/X").toDouble();
        float rotate_y = config_->property("Transform/Rotate/Y").toDouble();
        float rotate_z = config_->property("Transform/Rotate/Z").toDouble();
        float rotate_w = config_->property("Transform/Rotate/W").toDouble();
        int rotate_mode = config_->property("Transform/Rotate/Mode").toInt();
        float scale_x = config_->property("Transform/Scale/X").toDouble();
        float scale_y = config_->property("Transform/Scale/Y").toDouble();
        float scale_z = config_->property("Transform/Scale/Z").toDouble();
        Rotation r(rotate_mode, {rotate_x, rotate_y, rotate_z, rotate_w});
        SMESH_INFO("translate ({}, {}, {})", translate_x, translate_y, translate_z);
        SMESH_INFO("rotate ({}, {}, {})", rotate_x, rotate_y, rotate_z);
        SMESH_INFO("scale ({}, {}, {})", scale_x, scale_y, scale_z);
        glm::mat4 res{1.0f};
        res = glm::translate(res, {translate_x, translate_y, translate_z});
        res = res * r.GetRotateMatrix();
        res = glm::scale(res, {scale_x, scale_y, scale_z});
        transform_ = res;
    }

    ModelObject::~ModelObject()
    {
        
    }
}