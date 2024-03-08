#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QTextStream>
#include <smesh/qt/object_list_model.h>

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
        } });
    connect(ui->render_widget, &smesh::RenderWidget::AddObject, this, [list_model, this]()
            { list_model->UpdateObject(static_cast<int>(ui->render_widget->renderer()->GetObjectCount() - 1)); });
}

MainWindow::~MainWindow()
{
}
