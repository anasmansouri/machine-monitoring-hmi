#include "Ros2CommandClient.hpp"

#include <QDebug>

Ros2CommandClient::Ros2CommandClient(rclcpp::Node::SharedPtr node,
                                     QObject *parent)
    : QObject(parent),
      node_(node)
{
    startMachineClient_ =
        node_->create_client<std_srvs::srv::Trigger>("/machine/start_machine");

    stopMachineClient_ =
        node_->create_client<std_srvs::srv::Trigger>("/machine/stop_machine");

    resetFaultClient_ =
        node_->create_client<std_srvs::srv::Trigger>("/machine/reset_fault");
}

void Ros2CommandClient::startMachine()
{
    callTriggerService("START_MACHINE", startMachineClient_);
}

void Ros2CommandClient::stopMachine()
{
    callTriggerService("STOP_MACHINE", stopMachineClient_);
}

void Ros2CommandClient::resetFault()
{
    callTriggerService("RESET_FAULT", resetFaultClient_);
}

void Ros2CommandClient::callTriggerService(
    const QString &commandName,
    rclcpp::Client<std_srvs::srv::Trigger>::SharedPtr client)
{
    if (!client->service_is_ready())
    {
        QString message = "Service is not available";

        qDebug() << commandName << ":" << message;

        emit commandResult(commandName, false, message);
        return;
    }

    auto request = std::make_shared<std_srvs::srv::Trigger::Request>();

    client->async_send_request(
        request,
        [this, commandName](rclcpp::Client<std_srvs::srv::Trigger>::SharedFuture future)
        {
            auto response = future.get();

            QString message = QString::fromStdString(response->message);

            qDebug() << commandName
                     << "success:" << response->success
                     << "message:" << message;

            emit commandResult(commandName, response->success, message);
        });
}
