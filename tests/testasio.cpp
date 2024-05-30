#include <QTest>

#include <asio.hpp>
#include <ollama.hpp>

class TestAsio: public QObject
{
    Q_OBJECT
private slots:
    void toUpper();
    void toRegularExpression();
        void toRegularExpression2();
};


void TestAsio::toRegularExpression()
{
    QString str = "background-color: transparent; /*@PrimaryColor*/";

    QRegularExpression regex(R"(\s([^\s;]+)\s*;\s*/\*\s*@(\w+)\s*\*/)");
    QRegularExpressionMatchIterator it = regex.globalMatch(str);
    QRegularExpressionMatch match = it.next();

    QCOMPARE(match.hasMatch(), true);
    QCOMPARE(match.captured(1), "transparent");
    QCOMPARE(match.captured(2), "PrimaryColor");
}
void TestAsio::toRegularExpression2()
{
    QString str = "border: 1px solid transparent; /*@DarkBorder*/";

    QRegularExpression regex(R"(\s([^\s;]+)\s*;\s*/\*\s*@(\w+)\s*\*/)");
    QRegularExpressionMatchIterator it = regex.globalMatch(str);
    QRegularExpressionMatch match = it.next();

    QCOMPARE(match.hasMatch(), true);
    QCOMPARE(match.captured(1), "transparent");
    QCOMPARE(match.captured(2), "DarkBorder");
}

void TestAsio::toUpper()
{
    QString str = "Hello";
    QCOMPARE(str.toUpper(), QString("HELLO"));
}

QTEST_MAIN(TestAsio)

#include "testasio.moc"
