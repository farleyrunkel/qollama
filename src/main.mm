#include <QApplication>
#include <QMainWindow>
#include <QWindow>
#include <QTimer>
#include <objc/objc-runtime.h>
#include "stylemanager.h"
#include "mainwindow.h"

#import <Cocoa/Cocoa.h>

void setMacWindowStyle(QMainWindow *mainWindow) {
    QWindow *window = mainWindow->windowHandle();
    if (window) {
        // 获取 NSView 对象
        NSView *nsView = reinterpret_cast<NSView *>(window->winId());
        if (nsView) {
            // 获取 NSWindow 对象
            NSWindow *nsWindow = [nsView window];
            if (nsWindow) {
                // 设置标题栏透明
                [nsWindow setTitlebarAppearsTransparent:YES];
                
                // 设置窗口背景颜色为白色
                [nsWindow setBackgroundColor:[NSColor whiteColor]];

                // 移除窗口阴影
                [nsWindow setHasShadow:NO];
                
                // 如果需要其他样式设置，可以在这里添加
            } else {
                qWarning("Failed to get NSWindow object.");
            }
        } else {
            qWarning("Failed to get NSView object.");
        }
    } else {
        qWarning("Failed to get QWindow object.");
    }
}

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    // Load and apply the stylesheet
    StyleManager styleManager;
    styleManager.loadStyleSheet(":/qss/style.qss");

    MainWindow w;
    //styleManager.enableBorders(true);  // Enable borders
    styleManager.applyStyleSheet(&w);

    w.show();

    QTimer::singleShot(0, [&w]() {
        setMacWindowStyle(&w);
    });

    return a.exec();
}
