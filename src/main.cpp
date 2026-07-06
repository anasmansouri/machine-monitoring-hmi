#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QMetaObject>
#include <QString>
#include "Ros2TelemetryClient.hpp"
#include <rclcpp/rclcpp.hpp>
#include <machine_interfaces/msg/machine_telemetry.hpp>

#include <thread>

#include "Ros2CommandClient.hpp"
#include "TelemetryModel.hpp"

int main(int argc, char *argv[])
{
    rclcpp::init(argc, argv);
    QGuiApplication app(argc, argv);

    TelemetryModel telemetryModel;
    Ros2TelemetryClient ros2Client;
    Ros2CommandClient commandClient(ros2Client.node());

    QObject::connect(
        &ros2Client,
        &Ros2TelemetryClient::telemetryReceived,
        &telemetryModel,
        &TelemetryModel::setTelemetry,
        Qt::QueuedConnection);
    QObject::connect(
        &ros2Client,
        &Ros2TelemetryClient::connectStatus,
        &telemetryModel,
        &TelemetryModel::setConnectStatus,
        Qt::QueuedConnection);

    QObject::connect(
        &telemetryModel,
        &TelemetryModel::startMachineRequested,
        &commandClient,
        &Ros2CommandClient::startMachine);

    QObject::connect(
        &telemetryModel,
        &TelemetryModel::stopMachineRequested,
        &commandClient,
        &Ros2CommandClient::stopMachine);

    QObject::connect(
        &telemetryModel,
        &TelemetryModel::resetFaultRequested,
        &commandClient,
        &Ros2CommandClient::resetFault);
    QObject::connect(
        &commandClient,
        &Ros2CommandClient::commandResult,
        &telemetryModel,
        &TelemetryModel::setCommandResult,
        Qt::QueuedConnection);
    QObject::connect(
        &telemetryModel,
        &TelemetryModel::setLoadThresholdRequested,
        &commandClient,
        &Ros2CommandClient::setLoadThreshold);
    QObject::connect(
        &telemetryModel,
        &TelemetryModel::setVibrationThresholdRequested,
        &commandClient,
        &Ros2CommandClient::setVibrationThreshold);



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
                     { ros2Client.stop(); });
    engine.load(url);

    return app.exec();
}
