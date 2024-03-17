#include "config_edit_widget.h"
#include "QDebug"
#include "qttreepropertybrowser.h"
#include "qtvariantproperty.h"
#include "smesh/log/log.h"
#include <QVBoxLayout>
#include <QVector3D>
#include <QVector4D>
#include <QtTreePropertyBrowser>
#include <QtVariantEditorFactory>
#include <QtVariantProperty>
#include <QtVariantPropertyManager>
#include <qboxlayout.h>
#include <qglobal.h>
#include <qpushbutton.h>
#include <qwidget.h>


namespace smesh
{
    ConfigEditWidget::ConfigEditWidget(QWidget *parent) : QWidget(parent)
    {
        variant_manager_ = new QtVariantPropertyManager(this);
        variant_manager_read_only_ = new QtVariantPropertyManager(this);
        variant_editor_factory_ = new QtVariantEditorFactory(this);
        property_browser_ = new QtTreePropertyBrowser(this);
        layout_ = new QVBoxLayout(this);
        layout_->addWidget(property_browser_);
        setLayout(layout_);

        connect(variant_manager_, &QtVariantPropertyManager::valueChanged, this, [this](QtProperty *property, QVariant value)
        {
            if(property_to_key_.contains(property) == true)
            {
                auto key = property_to_key_[property];
                qDebug() << key;
                if(config_ != nullptr)
                {
                    config_->set_property(key, value);
                }
            }
            else {
                SMESH_ERROR("key is not contain in key map1 ");
                qDebug() << value;
        } });
    }

    void ConfigEditWidget::set_config(Config *config)
    {
        if (config->def()->ConfigDefName() != config_def_->ConfigDefName())
        {
            SMESH_ERROR("config's def is not match");
            return;
        }
        if (config_def_ == nullptr)
        {
            SMESH_ERROR("must set config def first!");
            return;
        }
        if (config == nullptr)
        {
            SMESH_ERROR("config is nullptr");
            return;
        }

        if (config_ != nullptr)
        {
            config_->disconnect(this);
        }

        config_ = config;

        // init value
        for (const auto &key : config_->all_keys())
        {
            qDebug() << key;
            if (key_to_property_.contains(key) == true)
            {
                key_to_property_[key]->setValue(config->property(key));
            }
            else
            {
                SMESH_ERROR("key is not contain in key map");
            }
        }

        connect(config_, &Config::propertyChanged, this, [this](const PropertyKey &key, QVariant value)
        {
            if(key_to_property_.contains(key) == true)
            {
                key_to_property_[key]->propertyManager()->blockSignals(true);
                key_to_property_[key]->setValue(value);
                key_to_property_[key]->propertyManager()->blockSignals(false);
            }
            else {
                SMESH_ERROR("key is not contain in key map");
        } });
    }

    void ConfigEditWidget::set_config_def(const ConfigDef *def)
    {
        if (def == nullptr)
        {
            SMESH_ERROR("def is nullptr");
            return;
        }
        config_def_ = def;
        for (auto &key : def->keys())
        {
            property_browser_->addProperty(ConstructVariantProperty(key, def->property_def(key)));
        }
        property_browser_->setFactoryForManager(variant_manager_, variant_editor_factory_);
        // property_browser_->setPropertiesWithoutValueMarked(true);
        property_browser_->setHeaderVisible(false);
    }

    QtVariantProperty *ConfigEditWidget::ConstructVariantProperty(const PropertyKey &key, const PropertyDef *def, const PropertyKey &parent_key)
    {
        QtVariantProperty *item = nullptr;
        if (def->read_only())
            item = variant_manager_read_only_->addProperty(def->type(), key);
        else
            item = variant_manager_->addProperty(def->type(), key);

        auto map_key = parent_key.isEmpty() ? key : (parent_key + '/' + key);
        qDebug() << map_key;
        key_to_property_.insert(map_key, item);
        property_to_key_.insert(item, map_key);
        for (auto &attribute : def->attributes())
        {
            item->setAttribute(attribute, def->attribute_value(attribute));
        }

        item->setDescriptionToolTip(def->tool_tip());
        item->setValue(def->default_value());

        for (auto &sub_key : def->sub_keys())
            item->addSubProperty(ConstructVariantProperty(sub_key, def->sub_property_def(sub_key), map_key));

        return item;
    }
} // namespace smesh