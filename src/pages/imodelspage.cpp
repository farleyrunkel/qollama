#include "imodelspage.h"
#include "galleryphotowidget.h"

IModelsPage::IModelsPage(QWidget* parent) : GalleryWidget(parent)
{ 
    setAutoFillBackground(true);
    setFrameShape(QFrame::NoFrame);
    setStyleSheet("background-color: white;");

    QList<GalleryPhotoData> list;
    srand(time(0));
    int count = rand() % 10 + 5;
    for (int i = 0; i < count; i++)
    {
        QPixmap pixmap(":/images/farley.png");
        QString title = "farley" + QString::number(i);
        QString subTitle = "author：farley" + QString::number(i);
        GalleryPhotoData data{pixmap, title, subTitle};
        list.append(data);
    }

    loadData(list);
}
