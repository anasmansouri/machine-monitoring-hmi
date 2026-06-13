#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "TelemetryModel.hpp"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    TelemetryModel telemetryModel;

    QQmlApplicationEngine engine;

    engine.rootContext()->setContextProperty("telemetryModel", &telemetryModel);

    const QUrl url(QStringLiteral("file:///" APP_SOURCE_DIR "/qml/Main.qml"));

    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreated,
        &app,
        [url](QObject *object, const QUrl &objectUrl)
        {
            if (!object && url == objectUrl)
            {
                QCoreApplication::exit(-1);
            }
        },
        Qt::QueuedConnection);

    engine.load(url);

    return app.exec();
}
