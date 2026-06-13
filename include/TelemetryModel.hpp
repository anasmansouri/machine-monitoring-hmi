#pragma once

#include <QObject>
#include <QString>
#include <QTimer>

class TelemetryModel : public QObject
{
    Q_OBJECT

    Q_PROPERTY(int temperature READ temperature NOTIFY telemetryChanged)
    Q_PROPERTY(int humidity READ humidity NOTIFY telemetryChanged)
    Q_PROPERTY(int load READ load NOTIFY telemetryChanged)
    Q_PROPERTY(QString state READ state NOTIFY telemetryChanged)
    Q_PROPERTY(QString fault READ fault NOTIFY telemetryChanged)

public:
    explicit TelemetryModel(QObject *parent = nullptr);

    int temperature() const;
    int humidity() const;
    int load() const;
    QString state() const;
    QString fault() const;

    Q_INVOKABLE void startMachine();
    Q_INVOKABLE void stopMachine();
    Q_INVOKABLE void resetFault();

signals:
    void telemetryChanged();

private slots:
    void updateFakeTelemetry();

private:
    int temperature_ = 24;
    int humidity_ = 50;
    int load_ = 20;

    QString state_ = "MACHINE_STATE_IDLE";
    QString fault_ = "FAULT_NONE";

    QTimer timer_;
};
