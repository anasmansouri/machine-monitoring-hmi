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

QString TelemetryModel::lastCommandName() const
{
    return lastCommandName_;
}

bool TelemetryModel::lastCommandSuccess() const
{
    return lastCommandSuccess_;
}

QString TelemetryModel::lastCommandMessage() const
{
    return lastCommandMessage_;
}

void TelemetryModel::startMachine()
{
    qDebug() << "Start machine clicked";
    emit startMachineRequested();
}

void TelemetryModel::stopMachine()
{
    qDebug() << "Stop machine clicked";
    emit stopMachineRequested();
}

void TelemetryModel::resetFault()
{
    qDebug() << "Reset fault clicked";
    emit resetFaultRequested();
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

void TelemetryModel::setCommandResult(const QString &commandName,
                                      bool success,
                                      const QString &message)
{
    lastCommandName_ = commandName;
    lastCommandSuccess_ = success;
    lastCommandMessage_ = message;

    emit commandResultChanged();
}
