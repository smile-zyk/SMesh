#include "config_edit_widget.h"
#include "qttreepropertybrowser.h"
#include "qtvariantproperty.h"
#include <QVBoxLayout>
#include <QtTreePropertyBrowser>
#include <QtVariantEditorFactory>
#include <QtVariantPropertyManager>
#include <QtVariantProperty>
#include <qboxlayout.h>
#include <qglobal.h>
#include <qpushbutton.h>
#include <qwidget.h>

namespace smesh
{
    ConfigEditWidget::ConfigEditWidget(QWidget* parent) : QWidget(parent)
    {
        variant_manager_ = new QtVariantPropertyManager(this);
        variant_manager_read_only_ = new QtVariantPropertyManager(this);
        variant_editor_factory_ = new QtVariantEditorFactory(this);
        property_browser_ = new QtTreePropertyBrowser(this);
        layout_ = new QVBoxLayout(this);
        layout_->addWidget(property_browser_);
        setLayout(layout_);
    }
    
    void ConfigEditWidget::set_config_def(const ConfigDef* def)
    {
        config_def_ = def;
        for(auto& key: def->keys())
        {
            property_browser_->addProperty(ConstructVariantProperty(key, def->property_def(key)));
        }
        property_browser_->setFactoryForManager(variant_manager_, variant_editor_factory_);
        // property_browser_->setPropertiesWithoutValueMarked(true);
        property_browser_->setHeaderVisible(false);
    }
    
    QtVariantProperty* ConfigEditWidget::ConstructVariantProperty(const PropertyKey& key, const PropertyDef* def)
    {
        QtVariantProperty* item = nullptr;
        if(def->read_only())
            item = variant_manager_read_only_->addProperty(def->type(), key);
        else
            item = variant_manager_->addProperty(def->type(), key);

        for(auto& attribute: def->attributes())
            item->setAttribute(attribute, def->attribute_value(attribute));

        item->setDescriptionToolTip(def->tool_tip());
        item->setValue(def->default_value());

        for(auto& sub_key : def->sub_keys())
            item->addSubProperty(ConstructVariantProperty(sub_key, def->sub_property_def(sub_key)));
        
        return item;
    }
}