#include "chatitemdelegate.h"

#include <QPainter>

void ChatItemDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const {
    // 绘制背景
    painter->save();
    painter->setPen(Qt::NoPen);
    painter->setBrush(QColor(255, 255, 255));  // 背景色为白色
    painter->drawRect(option.rect);
    painter->restore();

    // 获取数据
    QVariantMap chatData = index.data(Qt::DisplayRole).toMap();
    QIcon icon = qvariant_cast<QIcon>(chatData["icon"]);
    QString username = chatData["username"].toString();
    QString message = chatData["message"].toString();

    // 绘制图标
    QRect iconRect = option.rect.adjusted(5, 5, 25, 25);
    icon.paint(painter, iconRect);

    // 绘制用户名
    QRect usernameRect = QRect(iconRect.right() + 5, iconRect.top(), option.rect.width() - iconRect.width() - 10, 20);
    painter->setFont(QFont("Arial", 10, QFont::Bold));  // 设置字体和字号
    painter->drawText(usernameRect, Qt::AlignLeft | Qt::AlignTop, username);

    // 绘制聊天内容
    QRect messageRect = QRect(iconRect.right() + 5, usernameRect.bottom(), option.rect.width() - iconRect.width() - 10, option.rect.height() - usernameRect.height() - 10);
    painter->setFont(QFont("Arial", 9));  // 设置字体和字号
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
