#include "TelemetryModel.hpp"

#include <QDebug>

TelemetryModel::TelemetryModel(QObject *parent)
    : QObject(parent)
{

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

void TelemetryModel::setTelemetry(int temperature,
                                  int humidity,
                                  int load,
                                  const QString &state,
                                  const QString &fault)
{
    temperature_ = temperature;
    humidity_ = humidity;
    load_ = load;
    state_ = state;
    fault_ = fault;

    emit telemetryChanged();
}
