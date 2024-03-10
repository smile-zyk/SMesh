#pragma once

#include <QFrame>
#include "smesh/common.h"

namespace Ui {
    class RenderControl;
}

class RenderControl : public QFrame
{
    Q_OBJECT

public:
    RenderControl(QWidget *parent = nullptr);

    ~RenderControl();
signals:
    void SetGizmoMode(GizmoMode mode);

private:
    Ui::RenderControl *ui; // UI对象指针
};