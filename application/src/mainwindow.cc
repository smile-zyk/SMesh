#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->actionOpen, &QAction::triggered, this, [this]()
    {
        QString fileName = QFileDialog::getOpenFileName(nullptr, "OpenFile", "", "STL file (*.stl);;OBJ file (*.obj)");

        if (!fileName.isNull()) {
            ui->render_widget->LoadModelObject(fileName);
        }
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}
