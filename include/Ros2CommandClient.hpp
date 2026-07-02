#pragma once

#include <QObject>
#include <QString>

#include <rclcpp/rclcpp.hpp>
#include <std_srvs/srv/trigger.hpp>
#include "machine_interfaces/srv/set_threshold.hpp"

class Ros2CommandClient : public QObject
{
    Q_OBJECT

public:
    explicit Ros2CommandClient(rclcpp::Node::SharedPtr node,
                               QObject *parent = nullptr);

public slots:
    void startMachine();
    void stopMachine();
    void resetFault();
    void setLoadThreshold(int warning, int fault);

signals:
    void commandResult(QString commandName,
                       bool success,
                       QString message);
private:
    void callTriggerService(
        const QString &commandName,
        rclcpp::Client<std_srvs::srv::Trigger>::SharedPtr client);

private:
    rclcpp::Node::SharedPtr node_;

    rclcpp::Client<std_srvs::srv::Trigger>::SharedPtr startMachineClient_;
    rclcpp::Client<std_srvs::srv::Trigger>::SharedPtr stopMachineClient_;
    rclcpp::Client<std_srvs::srv::Trigger>::SharedPtr resetFaultClient_;
    rclcpp::Client<machine_interfaces::srv::SetThreshold>::SharedPtr setLoadThresholdClient_;
};
