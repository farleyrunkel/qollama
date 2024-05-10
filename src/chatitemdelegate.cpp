#include "chatitemdelegate.h"

#include <QPainter>

void ChatItemDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const {
    // 绘制背景
    painter->save();
    painter->setPen(Qt::NoPen);
    painter->setBrush(QColor(255, 255, 255));  // 背景色为白色
    painter->drawRect(option.rect);
    painter->restore();


    QRect contRect = option.rect.adjusted(5, 5, -5, -5);

    painter->drawRoundedRect(contRect, 5, 5);
    // 计算左右两部分的矩形区域
    int leftWidth = 30;
    QRect leftRect = contRect.adjusted(0, 0, -contRect.width() + leftWidth, 0);
    QRect rightRect = contRect.adjusted(leftWidth, 0, 0, 0);

    // 获取数据
    QVariantMap chatData = index.data(Qt::DisplayRole).toMap();
    QIcon icon = qvariant_cast<QIcon>(chatData["icon"]);
    QString username = chatData["username"].toString();
    QString message = chatData["message"].toString();

    // 绘制图标
    QPixmap iconPixmap = icon.pixmap(QSize(20, 20)); // 获取图标的 pixmap，大小为20x20
    painter->drawPixmap(leftRect.topLeft(), iconPixmap); // 在图标区域的左上角绘制图标

    // 绘制用户名
    int userHeight = 30;
    QRect usernameRect = rightRect.adjusted(0, 0, 0, -rightRect.height() + userHeight);
    painter->setFont(QFont("Arial", 10, QFont::Bold));  // 设置字体和字号
    painter->drawText(usernameRect, Qt::AlignLeft | Qt::AlignTop, username);

    // 绘制聊天内容
    QRect messageRect1 =  rightRect.adjusted(0, userHeight, 0, 0);

    // 计算消息内容的实际大小
    QFont messageFont("Arial", 9); // 设置字体和字号
    QFontMetrics fontMetrics(messageFont);
    QRect messageRect = fontMetrics.boundingRect(messageRect1, Qt::AlignLeft | Qt::AlignTop | Qt::TextWordWrap, message);
    messageRect.setHeight(messageRect.height() + 5); // 增加一些额外的高度作为边距

    // 绘制聊天内容
    painter->setFont(messageFont);
    painter->drawText(messageRect, Qt::AlignLeft | Qt::AlignTop | Qt::TextWordWrap, message);
}


QSize ChatItemDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const {
    QVariantMap chatData = index.data(Qt::DisplayRole).toMap();
    QString username = chatData["username"].toString();
    QString message = chatData["message"].toString();

    // 计算用户名的高度
    QFontMetrics usernameMetrics(option.font);
    QSize usernameSize = usernameMetrics.size(Qt::TextWordWrap, username);
    int usernameHeight = usernameSize.height();

    // 计算聊天内容的高度
    QFontMetrics messageMetrics(option.font);
    QSize messageSize = messageMetrics.size(Qt::TextWordWrap, message);
    int messageHeight = messageSize.height();

    // 计算项目的总高度
    int totalHeight = qMax(40, usernameHeight + messageHeight + 20);  // 设置一个最小高度为40，确保显示完整内容
    return QSize(option.rect.width(), totalHeight);
}
