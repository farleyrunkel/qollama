#include <QApplication>
#include <QFile>
#include "mainwindow.h"
#include "initializer.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    Initializer initializer;

    MainWindow mainWindow;

    initializer.initialize(&mainWindow);

    return app.exec();
}
