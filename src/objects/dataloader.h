#ifndef DATALOADER_H
#define DATALOADER_H

#include <QDebug>
#include <QDir>
#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonParseError>
#include <QObject>
#include <QRegularExpression>
#include <QTextStream>

class DataLoader : public QObject {
    Q_OBJECT

    struct MdContent {
        QString title;
        QString description;
        QString author;
        QString link;
        QString prompt;
    };

    struct JsonModel {
        QString name;
        QString intro;
        QString image;
        QJsonArray categories;
        QString prompt;
    };

public:
    // 单例模式
    static DataLoader &instance() {
        static DataLoader instance;
        return instance;
    }
    const QMap<QString, MdContent> &prompts() const { return m_prompts; }
    const QList<JsonModel> &models() const { return m_models; }

    // 加载数据的公共接口
    void loadData(const QString &directoryPath) {
        readMarkdownFiles(directoryPath);
        emit dataLoaded();
    }

signals:
    void dataLoaded();

private:
    DataLoader() {}
    // 删除拷贝构造函数和赋值运算符
    DataLoader(const DataLoader &) = delete;
    DataLoader &operator=(const DataLoader &) = delete;

    QList<JsonModel> m_models;

    QMap<QString, MdContent> m_prompts;

  // 读取 JSON 模型文件内容的私有函数
  void readJsonModelFiles(const QString &directoryPath);

  // 读取 .md 文件内容的私有函数
  void readMarkdownFiles(const QString &directoryPath);

  // 解析 .md 文件内容的私有函数
  MdContent parseMdContent(const QString &content);
};

#endif // DATALOADER_H
