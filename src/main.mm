#include "initializer.h"
#include "mainwindow.h"
#import <Cocoa/Cocoa.h>
#include <QApplication>
#include <QMainWindow>
#include <QTimer>
#include <QWindow>
#include <objc/objc-runtime.h>

void setMacWindowStyle(QMainWindow *mainWindow);

int main(int argc, char *argv[]) {
  QApplication app(argc, argv);

  Initializer initializer;

  MainWindow mainWindow;

  initializer.initialize(&mainWindow);

  QTimer::singleShot(0, [&mainWindow]() { setMacWindowStyle(&mainWindow); });

  return app.exec();
}

void setMacWindowStyle(QMainWindow *mainWindow) {
  QWindow *window = mainWindow->windowHandle();
  if (window) {
    NSView *nsView = reinterpret_cast<NSView *>(window->winId());
    if (nsView) {
      NSWindow *nsWindow = [nsView window];
      if (nsWindow) {
        [nsWindow setTitlebarAppearsTransparent:YES];
        [nsWindow setBackgroundColor:[NSColor whiteColor]];
        [nsWindow setHasShadow:YES];
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
