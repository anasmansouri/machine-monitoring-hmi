import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

ApplicationWindow {
    visible: true
    width: 900
    height: 650
    title: "Machine Monitoring HMI"

    color: "#1f2430"

    property color cardBackground: "#f9fafb"
    property color cardTextColor: "#111827"
    property color secondaryTextColor: "#4b5563"
    property color borderColor: "#d1d5db"

    ColumnLayout {
        anchors.fill: parent
        anchors.margins: 24
        spacing: 22

        Label {
            text: "Machine Monitoring HMI"
            font.pixelSize: 32
            font.bold: true
            color: "white"
            Layout.alignment: Qt.AlignHCenter
        }

        GridLayout {
            columns: 2
            columnSpacing: 20
            rowSpacing: 20
            Layout.fillWidth: true

            Rectangle {
                Layout.fillWidth: true
                height: 100
                radius: 12
                color: cardBackground
                border.color: borderColor
                border.width: 1

                Column {
                    anchors.centerIn: parent
                    spacing: 8

                    Label {
                        text: "Temperature"
                        font.pixelSize: 18
                        color: secondaryTextColor
                    }

                    Label {
                        text: telemetryModel.temperature + " °C"
                        font.pixelSize: 28
                        font.bold: true
                        color: cardTextColor
                    }
                }
            }

            Rectangle {
                Layout.fillWidth: true
                height: 100
                radius: 12
                color: cardBackground
                border.color: borderColor
                border.width: 1

                Column {
                    anchors.centerIn: parent
                    spacing: 8

                    Label {
                        text: "Humidity"
                        font.pixelSize: 18
                        color: secondaryTextColor
                    }

                    Label {
                        text: telemetryModel.humidity + " %"
                        font.pixelSize: 28
                        font.bold: true
                        color: cardTextColor
                    }
                }
            }

            Rectangle {
                Layout.fillWidth: true
                height: 100
                radius: 12
                color: cardBackground
                border.color: borderColor
                border.width: 1

                Column {
                    anchors.centerIn: parent
                    spacing: 8

                    Label {
                        text: "Load"
                        font.pixelSize: 18
                        color: secondaryTextColor
                    }

                    Label {
                        text: telemetryModel.load + " %"
                        font.pixelSize: 28
                        font.bold: true
                        color: cardTextColor
                    }
                }
            }

            Rectangle {
                Layout.fillWidth: true
                height: 100
                radius: 12
                color: cardBackground
                border.color: borderColor
                border.width: 1

                Column {
                    anchors.centerIn: parent
                    spacing: 8

                    Label {
                        text: "Machine State"
                        font.pixelSize: 18
                        color: secondaryTextColor
                    }

                    Label {
                        text: telemetryModel.state
                        font.pixelSize: 22
                        font.bold: true
                        color: cardTextColor
                    }
                }
            }
        }

        Rectangle {
            Layout.fillWidth: true
            height: 90
            radius: 12
            color: cardBackground
            border.color: borderColor
            border.width: 1

            RowLayout {
                anchors.fill: parent
                anchors.margins: 18
                spacing: 12

                Label {
                    text: "Fault:"
                    font.pixelSize: 22
                    font.bold: true
                    color: cardTextColor
                }

                Label {
                    text: telemetryModel.fault
                    font.pixelSize: 22
                    color: cardTextColor
                    Layout.fillWidth: true
                }
            }
        }

        Item {
            Layout.fillHeight: true
        }
        Rectangle {
            Layout.fillWidth: true
            height: 110
            radius: 12
            color: cardBackground
            border.color: borderColor
            border.width: 1

            ColumnLayout {
                anchors.fill: parent
                anchors.margins: 16
                spacing: 8

                Label {
                    text: "Last Command Result"
                    font.pixelSize: 18
                    font.bold: true
                    color: cardTextColor
                }

                RowLayout {
                    Layout.fillWidth: true
                    spacing: 12

                    Label {
                        text: "Command:"
                        font.pixelSize: 16
                        color: secondaryTextColor
                    }

                    Label {
                        text: telemetryModel.lastCommandName
                        font.pixelSize: 16
                        font.bold: true
                        color: cardTextColor
                    }

                    Label {
                        text: telemetryModel.lastCommandSuccess ? "SUCCESS" : "FAILED"
                        font.pixelSize: 16
                        font.bold: true
                        color: telemetryModel.lastCommandSuccess ? "#15803d" : "#b91c1c"
                    }
                }

                Label {
                    text: telemetryModel.lastCommandMessage
                    font.pixelSize: 16
                    color: cardTextColor
                    Layout.fillWidth: true
                }
            }
        }

        RowLayout {
            Layout.alignment: Qt.AlignHCenter
            spacing: 16

            Button {
                text: "Start Machine"
                onClicked: telemetryModel.startMachine()
            }

            Button {
                text: "Stop Machine"
                onClicked: telemetryModel.stopMachine()
            }

            Button {
                text: "Reset Fault"
                onClicked: telemetryModel.resetFault()
            }
        }
    }
}
