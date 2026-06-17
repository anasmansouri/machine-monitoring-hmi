#include "Ros2TelemetryClient.hpp"
#include <memory>

Ros2TelemetryClient::Ros2TelemetryClient(QObject *parent)
    : QObject(parent)
{
    node_ = rclcpp::Node::make_shared("machine_monitoring_hmi_node");

    timer_= std::make_unique<QTimer>();

    telemetrySubscriber_ =
        node_->create_subscription<machine_interfaces::msg::MachineTelemetry>(
            "/machine/telemetry",
            10,
            [this](const machine_interfaces::msg::MachineTelemetry::SharedPtr msg)
            {
                this->lastTelemetryTime_=QDateTime::currentDateTime();
                this->connected_=true;
                handleTelemetry(msg);
            });
    connect(timer_.get(), &QTimer::timeout, this, &Ros2TelemetryClient::checkConnectionStatus);
    
    // Start the timer
    timer_->start(100);
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

void Ros2TelemetryClient::checkConnectionStatus(){
    QDateTime currentTime =QDateTime::currentDateTime();
    // Calculate seconds between the last recorded time and right now
    qint64 secondsSinceLastMsg = this->lastTelemetryTime_.secsTo(currentTime);
    if(secondsSinceLastMsg > 5){
        this->connected_=false;
    }
    emit connectStatus(this->connected_);
}
