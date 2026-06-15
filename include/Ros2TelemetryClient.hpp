#pragma once

#include <QObject>
#include <QString>

#include <rclcpp/rclcpp.hpp>
#include <machine_interfaces/msg/machine_telemetry.hpp>

#include <memory>
#include <thread>

class Ros2TelemetryClient : public QObject
{
    Q_OBJECT

public:
    explicit Ros2TelemetryClient(QObject *parent = nullptr);
    ~Ros2TelemetryClient();

    void start();
    void stop();

signals:
    void telemetryReceived(int temperature,
                           int humidity,
                           int load,
                           QString state,
                           QString fault);

private:
    void handleTelemetry(
        const machine_interfaces::msg::MachineTelemetry::SharedPtr msg);

private:
    rclcpp::Node::SharedPtr node_;

    rclcpp::Subscription<machine_interfaces::msg::MachineTelemetry>::SharedPtr telemetrySubscriber_;

    std::thread rosThread_;

    bool running_ = false;
};
