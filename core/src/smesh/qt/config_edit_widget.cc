#include "config_edit_widget.h"
#include <QVBoxLayout>
#include <QtTreePropertyBrowser>
#include <QtVariantEditorFactory>
#include <QtVariantPropertyManager>
#include <QtVariantProperty>
#include <qpushbutton.h>
#include <qwidget.h>

namespace smesh
{
    ConfigEditWidget::ConfigEditWidget(Config* config, QWidget* parent): QWidget(parent)
    {
        set_config(config);
    }
    
    void ConfigEditWidget::set_config(Config* config)
    {
        QVBoxLayout* layout = new QVBoxLayout(this);
        QtTreePropertyBrowser* browser = new QtTreePropertyBrowser(this);
        QtVariantPropertyManager *variantManager = new QtVariantPropertyManager();
        QtVariantEditorFactory *variantFactory = new QtVariantEditorFactory();
        browser->setFactoryForManager(variantManager, variantFactory);
        browser->setPropertiesWithoutValueMarked(true);
        auto keys = config->keys();
        for(auto& key: keys)
        {
            auto def = config->GetConfigDefinition(key);
            QtVariantProperty* property = variantManager->addProperty(def->type(), key);
            property->setValue(def->default_value());
            property->setAttribute("minimum", def->min());
            property->setAttribute("maximum", def->max());
            browser->addProperty(property);
        }
        layout->setMargin(0);
        layout->addWidget(browser);
    }
}