#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QMetaObject>
#include <QString>
#include "Ros2TelemetryClient.hpp"
#include <rclcpp/rclcpp.hpp>
#include <machine_interfaces/msg/machine_telemetry.hpp>

#include <thread>

#include "TelemetryModel.hpp"

int main(int argc, char *argv[])
{
    rclcpp::init(argc, argv);
    QGuiApplication app(argc, argv);

    TelemetryModel telemetryModel;
    Ros2TelemetryClient ros2Client;

    QObject::connect(
        &ros2Client,
        &Ros2TelemetryClient::telemetryReceived,
        &telemetryModel,
        &TelemetryModel::setTelemetry,
        Qt::QueuedConnection);

    ros2Client.start();

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

    QObject::connect(&app, &QCoreApplication::aboutToQuit, [&]()
    {
        ros2Client.stop();
    });
    engine.load(url);

    return app.exec();
}
