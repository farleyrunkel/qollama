#include "initializer.h"
#include "mainwindow.h"
#include <QApplication>
#include <QFile>

int main(int argc, char *argv[]) {


    QApplication app(argc, argv);

    Initializer initializer;

    MainWindow mainWindow;

    initializer.initialize(&mainWindow);

    ITestWidget test ;
    test.show();

    return app.exec();
}
