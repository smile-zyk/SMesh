#pragma once
#include "smesh/core.h"
#include "smesh/config/config.h"
#include <QWidget>

namespace smesh 
{
    class SMESH_API ConfigEditWidget : public QWidget
    {
        Q_OBJECT
    public:
        ConfigEditWidget(){}
        explicit ConfigEditWidget(Config* config, QWidget* parent = nullptr);
        void set_config(Config* config);
        Config* config() { return config_; }
    signals:
        void valueChanged(QString key);
    private:
        Config* config_;
    };
}