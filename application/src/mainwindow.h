#pragma once

#include <QMainWindow>
#include <QSharedPointer>

namespace Ui
{
    class MainWindow;
}

class MainWindow : public QMainWindow
{ 
    Q_OBJECT
  public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

  private:
    QSharedPointer<Ui::MainWindow> ui;
};