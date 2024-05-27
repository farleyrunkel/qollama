#include "mainwindow.h"

#include <QApplication>
#include <QFile>
#include <QGraphicsDropShadowEffect>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QString stylePath = ":/qss/style.qss";
    QFile styleFile(stylePath);
    if (styleFile.open(QFile::ReadOnly)) {
        QString styleSheet = QLatin1String(styleFile.readAll());
        a.setStyleSheet(styleSheet);
        styleFile.close();
    } else {
        qDebug() << "Failed to open style file:" << stylePath;
    }

    MainWindow w;


    w.show();

    return a.exec();
}
