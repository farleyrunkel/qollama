#include "dataloader.h"

void DataLoader::readJsonModelFiles(const QString &directoryPath) {
    QDir modelsDir(directoryPath);

    qDebug() << "modelsDir:" << modelsDir.dirName();
    // List all JSON files in the directory
    QStringList jsonFiles =
        modelsDir.entryList(QStringList() << "*.json", QDir::Files);

    // Iterate through each JSON file
    foreach (const QString &jsonFile, jsonFiles) {
        qDebug() << "jsonFile:" << jsonFile;

        QFile file(modelsDir.absoluteFilePath(jsonFile));

        if (!file.open(QIODevice::ReadOnly)) {
            qWarning() << "Could not open file" << jsonFile;
            continue;
        }

        QByteArray fileData = file.readAll();
        file.close();

        QJsonParseError parseError;
        QJsonDocument doc = QJsonDocument::fromJson(fileData, &parseError);

        if (parseError.error != QJsonParseError::NoError) {
            qWarning() << "Failed to parse JSON file" << jsonFile << ":"
                       << parseError.errorString();
            continue;
        }

        if (!doc.isObject()) {
            qWarning() << "Invalid JSON structure in file" << jsonFile;
            continue;
        }

        QJsonObject jsonObj = doc.object();

        JsonModel model;
        model.name = jsonObj.value("name").toString();
        model.intro = jsonObj.value("intro").toString();
        model.image = jsonObj.value("image").toString();
        model.categories = jsonObj.value("categories").toArray();
        model.prompt = jsonObj.value("prompt").toString();

        m_models.append(model);
    }
}

void DataLoader::readMarkdownFiles(const QString &directoryPath) {
    QDir dir(directoryPath);

    if (!dir.exists()) {
        qWarning() << "Directory does not exist:" << directoryPath;
        return;
    }

    QStringList filters;
    filters << "*.md";
    dir.setNameFilters(filters);

    QFileInfoList fileList = dir.entryInfoList(QDir::Files);

    foreach (const QFileInfo &fileInfo, fileList) {
        QFile file(fileInfo.filePath());

        if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            qWarning() << "Cannot open file:" << fileInfo.filePath();
            continue;
        }

        QTextStream in(&file);
        QString content = in.readAll();
        file.close();

        MdContent mdContent = parseMdContent(content);
        qDebug() << "Title:" << mdContent.title;
        qDebug() << "Description:" << mdContent.description;
        qDebug() << "Author:" << mdContent.author;
        qDebug() << "Link:" << mdContent.link;
        qDebug() << "Prompt:" << mdContent.prompt;

        m_prompts[mdContent.title] = mdContent;
    }
}

DataLoader::MdContent DataLoader::parseMdContent(const QString &content) {

    MdContent mdContent;

    // 解析标题
    static QRegularExpression titleRegex(R"(^##\s*(.+)$)",
                                         QRegularExpression::MultilineOption);
    QRegularExpressionMatch titleMatch = titleRegex.match(content);
    if (titleMatch.hasMatch()) {
        mdContent.title = titleMatch.captured(1).trimmed();
    }

    // 解析描述
    static QRegularExpression descriptionRegex(
        R"(^##\s*.+$\n(.+?)\n^By\s+.+$)",
        QRegularExpression::MultilineOption |
            QRegularExpression::DotMatchesEverythingOption);
    QRegularExpressionMatch descriptionMatch =
        descriptionRegex.match(content);
    if (descriptionMatch.hasMatch()) {
        mdContent.description = descriptionMatch.captured(1).trimmed();
    }

    // 解析作者
    static QRegularExpression authorRegex(R"(^By\s+(.+)$)",
                                          QRegularExpression::MultilineOption);
    QRegularExpressionMatch authorMatch = authorRegex.match(content);
    if (authorMatch.hasMatch()) {
        mdContent.author = authorMatch.captured(1).trimmed();
    }

    // 解析链接
    static QRegularExpression linkRegex(R"((https?://[^\s]+))",
                                        QRegularExpression::MultilineOption);
    QRegularExpressionMatch linkMatch = linkRegex.match(content);
    if (linkMatch.hasMatch()) {
        mdContent.link = linkMatch.captured(1).trimmed();
    }

    // 解析 prompt
    static QRegularExpression promptRegex(R"(^```markdown\n([\s\S]+)\n```$)",
                                   QRegularExpression::MultilineOption);
    QRegularExpressionMatch promptMatch = promptRegex.match(content);
    if (promptMatch.hasMatch()) {
        mdContent.prompt = promptMatch.captured(1).trimmed();
    } else {
        // Handle case where prompt might be missing the ending ```
        int start = content.indexOf("```markdown\n");
        if (start != -1) {
            start += QString("```markdown\n").length();
            int end = content.indexOf("\n```", start);
            if (end == -1) {
                mdContent.prompt = content.mid(start).trimmed();
            } else {
                mdContent.prompt = content.mid(start, end - start).trimmed();
            }
        }
    }

    return mdContent;
}
