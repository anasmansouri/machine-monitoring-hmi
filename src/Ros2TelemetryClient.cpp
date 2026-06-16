#include "Ros2TelemetryClient.hpp"

Ros2TelemetryClient::Ros2TelemetryClient(QObject *parent)
    : QObject(parent)
{
    node_ = rclcpp::Node::make_shared("machine_monitoring_hmi_node");

    telemetrySubscriber_ =
        node_->create_subscription<machine_interfaces::msg::MachineTelemetry>(
            "/machine/telemetry",
            10,
            [this](const machine_interfaces::msg::MachineTelemetry::SharedPtr msg)
            {
                handleTelemetry(msg);
            });
}



Ros2TelemetryClient::~Ros2TelemetryClient()
{
    stop();
}

rclcpp::Node::SharedPtr Ros2TelemetryClient::node() const
{
    return node_;
}

void Ros2TelemetryClient::start()
{
    if (running_)
    {
        return;
    }

    running_ = true;

    rosThread_ = std::thread([this]()
    {
        rclcpp::spin(node_);
    });
}

void Ros2TelemetryClient::stop()
{
    if (!running_)
    {
        return;
    }

    running_ = false;

    rclcpp::shutdown();

    if (rosThread_.joinable())
    {
        rosThread_.join();
    }
}

void Ros2TelemetryClient::handleTelemetry(
    const machine_interfaces::msg::MachineTelemetry::SharedPtr msg)
{
    emit telemetryReceived(
        msg->temperature,
        msg->humidity,
        msg->load,
        QString::fromStdString(msg->state),
        QString::fromStdString(msg->fault));
}
