#ifndef IAUTORESIZETEXTBROWSER_H
#define IAUTORESIZETEXTBROWSER_H

#include <QTextBrowser>

class IAutoResizeTextBrowser : public QTextBrowser {
    Q_OBJECT

public:
    IAutoResizeTextBrowser(QWidget *parent = nullptr);

protected:
    void resizeEvent(QResizeEvent *event) override;

public:
    void updateGeometry();
};

#endif // IAUTORESIZETEXTBROWSER_H
