#include "itestwidget.h"

ITestWidget::ITestWidget(QWidget *parent) : QDialog(parent) {

    setAutoFillBackground(true);
    setFixedSize(QSize(500, 500));
    show();
    // ollama::SyncClient client("localhost");
    //     try {
    //         auto res = client.chat("llama3",  nlohmann::json({
    // {
    //                                                          {"role",  "user"},
    //                                                          {"content", "why
    //                                                          is the sky blue?"}
    //                                          }}
    // ));
    //     qDebug() << "res.dump()";
    //     qDebug() << res.dump();

    //     }
    //     catch (std::exception& e)
    //     {
    //         std::cerr << e.what() << std::endl;
    //     }
}
