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
        void set_config(Config* config);
    signals:
        void valueChanged(QString key);
    private:
        QtVariantProperty* ConstructVariantProperty(const PropertyKey& key, const PropertyDef* def, const PropertyKey& parent_key = "");
        const ConfigDef* config_def_{};
        Config* config_{};
        QtVariantPropertyManager* variant_manager_{};
        QtVariantPropertyManager* variant_manager_read_only_{};
        QtTreePropertyBrowser* property_browser_{};
        QtVariantEditorFactory* variant_editor_factory_{};
        QMap<QString, QtVariantProperty*> key_to_property_{};
        QMap<QtProperty*, QString> property_to_key_{};
        QVBoxLayout* layout_{};
    };
}