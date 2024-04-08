#include <QApplication>
#include <qicon.h>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setWindowIcon(QIcon(":/icons/icons/icon.png"));
    w.showMaximized();
    return a.exec();
}