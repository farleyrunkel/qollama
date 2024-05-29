#include <QTest>

#include <asio.hpp>
#include <ollama.hpp>

class TestAsio: public QObject
{
    Q_OBJECT
private slots:
    void toUpper();

    void toSend();
};

void TestAsio::toSend()
{

   // ollama::SyncClient client("localhost");
    // auto res = client.chat("llama3",  nlohmann::json( {{
    //                                                      {"role",  "user"},
    //                                                      {"content", "why is the sky blue?"}
    //                                                  },
    //                                                  {
    //                                                      { "role", "assistant"},
    //                                                      {"content", "due to rayleigh scattering."}
    //                                                  }}));
QString str = "Hello";
  QCOMPARE(str.toUpper(), QString("HELLO"));
}

void TestAsio::toUpper()
{
    QString str = "Hello";
    QCOMPARE(str.toUpper(), QString("HELLO"));
}

QTEST_MAIN(TestAsio)

#include "testasio.moc"
