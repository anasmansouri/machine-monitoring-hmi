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
    Q_PROPERTY(QString state READ state NOTIFY telemetryChanged)
    Q_PROPERTY(QString fault READ fault NOTIFY telemetryChanged)

    Q_PROPERTY(QString lastCommandName READ lastCommandName NOTIFY commandResultChanged)
    Q_PROPERTY(bool lastCommandSuccess READ lastCommandSuccess NOTIFY commandResultChanged)
    Q_PROPERTY(QString lastCommandMessage READ lastCommandMessage NOTIFY commandResultChanged)

public:
    explicit TelemetryModel(QObject *parent = nullptr);

    int temperature() const;
    int humidity() const;
    int load() const;
    QString state() const;
    QString fault() const;
    QString lastCommandName() const;
    bool lastCommandSuccess() const;
    QString lastCommandMessage() const;


    Q_INVOKABLE void startMachine();
    Q_INVOKABLE void stopMachine();
    Q_INVOKABLE void resetFault();
    Q_INVOKABLE void setLoadThreshold(int warning, int fault);

signals:
    void telemetryChanged();
    void startMachineRequested();
    void stopMachineRequested();
    void resetFaultRequested();
    void commandResultChanged();
    void setLoadThresholdRequested(int warning, int fault);

public slots:
    void setTelemetry(int temperature,
                      int humidity,
                      int load,
                      const QString &state,
                      const QString &fault);
    void setCommandResult(const QString &commandName,
                      bool success,
                      const QString &message);

private:
    int temperature_ = 24;
    int humidity_ = 50;
    int load_ = 20;

    QString state_ = "MACHINE_STATE_IDLE";
    QString fault_ = "FAULT_NONE";

    QString lastCommandName_ = "NONE";
    bool lastCommandSuccess_ = false;
    QString lastCommandMessage_ = "No command sent yet";
};
