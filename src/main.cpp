#include <QQmlApplicationEngine>
#include <QApplication>
#include <QObject>


int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    QQmlApplicationEngine engine;
    const QUrl qrcUrl("qrc:qml/main.qml");
    QObject::connect(&engine,   &QQmlApplicationEngine::objectCreated, &app,
        [qrcUrl](QObject *obj,const QUrl &objUrl) {
        if(!obj &&  objUrl != qrcUrl)
            QApplication::exit(-1);
    }, Qt::QueuedConnection);

    engine.load(qrcUrl);

    return app.exec();
}