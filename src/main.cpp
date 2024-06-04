#include <QApplication>
#include <QFile>
#include "istylemanager.h"
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // Load and apply the stylesheet
    IStyleManager styleManager;
    styleManager.loadStyleSheet(":/qss/style.qss");

    MainWindow w;
    //styleManager.enableBorders(true);  // Enable borders
    styleManager.applyStyleSheet(&w);

    w.show();

    return a.exec();
}
