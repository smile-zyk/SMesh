#pragma once
#include "qttreepropertybrowser.h"
#include "qtvariantproperty.h"
#include "smesh/core.h"
#include "smesh/config/config.h"
#include <QWidget>
#include <qboxlayout.h>

namespace smesh 
{
    class SMESH_API ConfigEditWidget : public QWidget
    {
        Q_OBJECT
    public:
        ConfigEditWidget(QWidget* parent = nullptr);
        void set_config_def(const ConfigDef* def);
    signals:
        void valueChanged(QString key);
    private:
        QtVariantProperty* ConstructVariantProperty(const PropertyKey& key, const PropertyDef* def);
        const ConfigDef* config_def_;
        QtVariantPropertyManager* variant_manager_;
        QtVariantPropertyManager* variant_manager_read_only_;
        QtTreePropertyBrowser* property_browser_;
        QtVariantEditorFactory* variant_editor_factory_;
        QVBoxLayout* layout_;
    };
}