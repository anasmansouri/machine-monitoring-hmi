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

QString TelemetryModel::emergency_button() const
{
    if(this->emergency_button_){
        return QString::fromStdString("pressed");
    }else{
        return QString::fromStdString("released");
    }
}


unsigned int TelemetryModel::fanRpm() const
{
    return fanRpm_;
}


int TelemetryModel::vibration_level_mg() const
{
    return vibration_level_mg_;
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
                                  int vibration_level_mg,
                                  bool emergency_button,
                                  unsigned int fanRpm,
                                  const QString &state,
                                  const QString &fault)
{
    temperature_ = temperature;
    humidity_ = humidity;
    load_ = load;
    emergency_button_  = emergency_button;
    vibration_level_mg_ = vibration_level_mg;
    fanRpm_ = fanRpm;
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

void TelemetryModel::setLoadThreshold(int warning, int fault)
{
    qDebug() << "Set load threshold clicked:"
             << "warning =" << warning
             << "fault =" << fault;

    emit setLoadThresholdRequested(warning, fault);
}

void TelemetryModel::setVibrationThreshold(int warning, int fault)
{
    qDebug() << "Set vibration threshold clicked:"
             << "warning =" << warning
             << "fault =" << fault;

    emit setVibrationThresholdRequested(warning, fault);
}

void TelemetryModel::setConnectStatus(bool status){
    this->connectStatus_=status;
    emit connectStatusChanged();
}
bool TelemetryModel::connectStatus() const{
    return this->connectStatus_;
}
