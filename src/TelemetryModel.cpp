#include "TelemetryModel.hpp"

#include <QDebug>

TelemetryModel::TelemetryModel(QObject *parent)
    : QObject(parent)
{
    connect(&timer_, &QTimer::timeout,
            this, &TelemetryModel::updateFakeTelemetry);

    timer_.start(1000);
}

int TelemetryModel::temperature() const
{
    return temperature_;
}

int TelemetryModel::humidity() const
{
    return humidity_;
}

int TelemetryModel::load() const
{
    return load_;
}

QString TelemetryModel::state() const
{
    return state_;
}

QString TelemetryModel::fault() const
{
    return fault_;
}

void TelemetryModel::startMachine()
{
    qDebug() << "Start machine clicked";

    if (fault_ == "FAULT_NONE")
    {
        state_ = "MACHINE_STATE_RUNNING";
        emit telemetryChanged();
    }
}

void TelemetryModel::stopMachine()
{
    qDebug() << "Stop machine clicked";

    state_ = "MACHINE_STATE_IDLE";
    emit telemetryChanged();
}

void TelemetryModel::resetFault()
{
    qDebug() << "Reset fault clicked";

    fault_ = "FAULT_NONE";
    state_ = "MACHINE_STATE_IDLE";
    emit telemetryChanged();
}

void TelemetryModel::updateFakeTelemetry()
{
    load_ += 5;

    if (load_ > 100)
    {
        load_ = 10;
    }

    temperature_ = 22 + (load_ / 10);
    humidity_ = 45 + (load_ / 20);

    if (load_ >= 80)
    {
        state_ = "MACHINE_STATE_FAULT";
        fault_ = "FAULT_LOAD_TOO_HIGH";
    }
    else if (load_ >= 60)
    {
        state_ = "MACHINE_STATE_WARNING";
        fault_ = "FAULT_NONE";
    }
    else if (state_ != "MACHINE_STATE_IDLE")
    {
        state_ = "MACHINE_STATE_RUNNING";
        fault_ = "FAULT_NONE";
    }

    emit telemetryChanged();
}
