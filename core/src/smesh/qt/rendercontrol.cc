#include "rendercontrol.h"
#include "ui_rendercontrol.h"

RenderControl::RenderControl(QWidget *parent) : QFrame(parent), ui(new Ui::RenderControl)
{
    ui->setupUi(this);

    connect(ui->translate_btn, &QPushButton::clicked, this, [this](){ emit SetGizmoMode(GizmoMode::kTranslate); });
    connect(ui->rotate_btn, &QPushButton::clicked, this, [this](){ emit SetGizmoMode(GizmoMode::kRotate); });
    connect(ui->scale_btn, &QPushButton::clicked, this, [this](){ emit SetGizmoMode(GizmoMode::kScale); });
    connect(ui->transform_btn, &QPushButton::clicked, this, [this](){ emit SetGizmoMode(GizmoMode::kTransform); });
}

RenderControl::~RenderControl()
{
    delete ui;
}
