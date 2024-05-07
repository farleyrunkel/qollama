#include "mainwindow.h"

#include <QApplication>
#include <QFile>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;


    // 从样式表文件加载样式并设置给应用程序
    QString stylePath = ":/qss/style.qss";  // 样式表文件在资源文件中的路径
    QFile styleFile(stylePath);
    if (styleFile.open(QFile::ReadOnly)) {
        QString styleSheet = QLatin1String(styleFile.readAll());
        a.setStyleSheet(styleSheet);
        styleFile.close();
    } else {
        qDebug() << "Failed to open style file:" << stylePath;
    }

    w.show();

    return a.exec();
}
