#include "mainwindow.h"
#include "smesh/config/scene_config.h"
#include "smesh/qt/config_edit_widget.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QTextStream>
#include <qaction.h>
#include <qboxlayout.h>
#include <qpushbutton.h>
#include <qvector3d.h>
#include <smesh/config/object_config.h>
#include <smesh/config/scene_config.h>
#include <smesh/qt/object_list_model.h>
#include <QVector3D>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    QFile f(":qdarkstyle/dark/darkstyle.qss");

    f.open(QFile::ReadOnly | QFile::Text);
    QTextStream ts(&f);
    qApp->setStyleSheet(ts.readAll());

    ui->setupUi(this);

    ObjectListModel *list_model = new ObjectListModel(ui->render_widget->renderer(), this);
    ui->object_list->setModel(list_model);
    setWindowTitle("SMesh");
    connect(ui->actionOpen, &QAction::triggered, this, [this]()
    {
        QString fileName = QFileDialog::getOpenFileName(nullptr, "OpenFile", "", "STL file (*.stl);;OBJ file (*.obj)");

        if (!fileName.isNull()) {
            ui->render_widget->LoadModelObject(fileName);
        }
    });
    // connect(ui->actiontest, &QAction::triggered, this, [this]()
    // {
    //     auto idx = ui->object_list->selectionModel()->currentIndex();
    //     if(idx.isValid())
    //     {
    //         ui->render_widget->renderer()->object(idx.row())->config()->set_property("Transform/Translate", QVector3D(1, 3, 5));
    //     }
    // });
    // ui->tabWidget->setTabVisible(1, true);
    connect(ui->render_widget, &smesh::RenderWidget::AddObject, this, [list_model, this]()
            { list_model->UpdateObject(static_cast<int>(ui->render_widget->renderer()->object_count() - 1)); });
    // ui->object_list->setSelectionMode(QAbstractItemView::SelectionMode::MultiSelection);
    //  QVBoxLayout* layout = new QVBoxLayout(ui->object_settings);
    //  ui->object_settings->setLayout(layout);
    //  QPushButton* btn = new QPushButton("test", ui->object_settings);
    //  // layout->addWidget(widget);
    //  layout->addWidget(btn);
    ui->object_settings->set_config_def(smesh::ModelObjectConfigDef::Instance());
    ui->global_settings->set_config_def(smesh::SceneConfigDef::Instance());
    connect(ui->object_list->selectionModel(), &QItemSelectionModel::selectionChanged, this, [this]()
    {
        auto idx = ui->object_list->selectionModel()->currentIndex();
        if (idx.isValid())
        {
            ui->tabWidget->setTabVisible(1, true);
        }
        else
        {
            ui->tabWidget->setTabVisible(1, false);
        }
        ui->render_widget->renderer()->DeselectAllObject();
        ui->render_widget->renderer()->SelectObject(idx.row());
        ui->object_settings->set_config(ui->render_widget->renderer()->object(idx.row())->config());
        // auto config = ui->render_widget->renderer()->object(idx.row())->config();
        // ui->object_settings->set_config(config);
    });
}

MainWindow::~MainWindow()
{
}
