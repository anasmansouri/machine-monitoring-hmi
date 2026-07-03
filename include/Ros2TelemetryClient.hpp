#pragma once

#include <QObject>
#include <QString>

#include <rclcpp/rclcpp.hpp>
#include <machine_interfaces/msg/machine_telemetry.hpp>

#include <memory>
#include <thread>
#include <QDateTime>
#include <QTimer>

class Ros2TelemetryClient : public QObject
{
    Q_OBJECT

public:
    explicit Ros2TelemetryClient(QObject *parent = nullptr);
    ~Ros2TelemetryClient();

    void start();
    void stop();
    rclcpp::Node::SharedPtr node() const;

signals:
    void telemetryReceived(int temperature,
                           int humidity,
                           int load,
                           int vibration_level_mg,
                           bool emergency_button,
                           unsigned int fanRpm,
                           QString state,
                           QString fault);

    void connectStatus(bool status);

private slots:
void checkConnectionStatus();
private:
    void handleTelemetry(
        const machine_interfaces::msg::MachineTelemetry::SharedPtr msg);

private:
    rclcpp::Node::SharedPtr node_;

    rclcpp::Subscription<machine_interfaces::msg::MachineTelemetry>::SharedPtr telemetrySubscriber_;

    std::thread rosThread_;

    bool running_ = false;
    bool connected_ = false;
    QDateTime lastTelemetryTime_;
    std::unique_ptr<QTimer> timer_;
};
