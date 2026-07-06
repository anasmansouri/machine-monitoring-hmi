#pragma once

#include <QObject>
#include <QString>
// #include <QTimer>

class TelemetryModel : public QObject
{
    Q_OBJECT

    Q_PROPERTY(int temperature READ temperature NOTIFY telemetryChanged)
    Q_PROPERTY(int humidity READ humidity NOTIFY telemetryChanged)
    Q_PROPERTY(int load READ load NOTIFY telemetryChanged)
    Q_PROPERTY(QString emergency_button READ emergency_button NOTIFY telemetryChanged)
    Q_PROPERTY(unsigned int fanRpm READ fanRpm NOTIFY telemetryChanged)
    Q_PROPERTY(int vibration_level_mg READ vibration_level_mg NOTIFY telemetryChanged)

    Q_PROPERTY(QString state READ state NOTIFY telemetryChanged)
    Q_PROPERTY(QString fault READ fault NOTIFY telemetryChanged)

    Q_PROPERTY(QString lastCommandName READ lastCommandName NOTIFY commandResultChanged)
    Q_PROPERTY(bool lastCommandSuccess READ lastCommandSuccess NOTIFY commandResultChanged)
    Q_PROPERTY(QString lastCommandMessage READ lastCommandMessage NOTIFY commandResultChanged)

    Q_PROPERTY(int connectStatus READ connectStatus NOTIFY connectStatusChanged)

public:
    explicit TelemetryModel(QObject *parent = nullptr);

    int temperature() const;
    int humidity() const;
    int load() const;

    unsigned int fanRpm()const ;
    QString emergency_button() const ;
    int vibration_level_mg()const;

    QString state() const;
    QString fault() const;
    QString lastCommandName() const;
    bool lastCommandSuccess() const;
    QString lastCommandMessage() const;
    bool connectStatus() const;


    Q_INVOKABLE void startMachine();
    Q_INVOKABLE void stopMachine();
    Q_INVOKABLE void resetFault();
    Q_INVOKABLE void setLoadThreshold(int warning, int fault);
    Q_INVOKABLE void setVibrationThreshold(int warning, int fault);

signals:
    void telemetryChanged();
    void startMachineRequested();
    void stopMachineRequested();
    void resetFaultRequested();
    void commandResultChanged();
    void setLoadThresholdRequested(int warning, int fault);
    void setVibrationThresholdRequested(int warning, int fault);
    void connectStatusChanged();

public slots:
    void setTelemetry(int temperature,
                      int humidity,
                      int load,
                      int vibration_level_mg,
                      bool emergency_button,
                      unsigned int fanRpm,
                      const QString &state,
                      const QString &fault);
    void setCommandResult(const QString &commandName,
                      bool success,
                      const QString &message);
    void setConnectStatus(bool status);

private:
    int temperature_ = 24;
    int humidity_ = 50;
    int load_ = 20;

    bool emergency_button_ = 0;
    unsigned int fanRpm_ =0;
    int vibration_level_mg_=1000;

    QString state_ = "MACHINE_STATE_IDLE";
    QString fault_ = "FAULT_NONE";

    QString lastCommandName_ = "NONE";
    bool lastCommandSuccess_ = false;
    QString lastCommandMessage_ = "No command sent yet";
    bool connectStatus_ = false;
};
