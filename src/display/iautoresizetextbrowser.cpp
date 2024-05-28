#include "iautoresizetextbrowser.h"
#include <QPainter>

IAutoResizeTextBrowser::IAutoResizeTextBrowser(QWidget *parent) : QTextBrowser(parent)
{
    setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFrameShape(QFrame::NoFrame);

    connect(this, &IAutoResizeTextBrowser::textChanged, this, &IAutoResizeTextBrowser::updateGeometry);
}

void IAutoResizeTextBrowser::resizeEvent(QResizeEvent *event)
{
    QTextBrowser::resizeEvent(event);
    updateGeometry();
}

void IAutoResizeTextBrowser::updateGeometry()
{
    // Set the text width of the document to match the width of the text browser
    document()->setTextWidth(width());

    // Get the document height and set it as the fixed height of the text browser
    qreal docHeight = document()->size().height();
    setFixedHeight(static_cast<int>(docHeight));

    // Call the base class updateGeometry() method
    QTextBrowser::updateGeometry();
}
