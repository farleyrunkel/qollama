#include "initializer.h"
#include "mainwindow.h"
#include <QApplication>
#include <QFile>

int main(int argc, char *argv[]) {

    QApplication appliction(argc, argv);

    Initializer initializer;
    initializer.initialize();

    MainWindow mainWindow;

    mainWindow.load();

    mainWindow.show();

    return appliction.exec();
}
