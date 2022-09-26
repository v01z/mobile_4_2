#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QtCharts>
#include "chartinflator.h"


//-----------------------------------------------------

int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif
    QApplication app(argc, argv);

    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);

    qmlRegisterType<ChartInflator>("ru.gb.ChartInflator", 1, 0,
        "ChartInflator");

    engine.load(url);

    return app.exec();
}

//-----------------------------------------------------
