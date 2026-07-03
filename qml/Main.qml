import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

ApplicationWindow {
    visible: true
    width: 900
    height: 900
    title: "Machine Monitoring HMI"

    color: "#1f2430"

    property color cardBackground: "#f9fafb"
        property color cardTextColor: "#111827"
            property color secondaryTextColor: "#4b5563"
                property color borderColor: "#d1d5db"
                    function connectionStatusText(status)
                    {
                        if (status === 1)
                        {
                            return "CONNECTED"
                        }

                        return "OFFLINE"
                    }

                    function connectionStatusColor(status)
                    {
                        if (status === 1)
                        {
                            return "#16a34a"   // green
                        }

                        return "#dc2626"       // red
                    }

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
                        Rectangle {
                            Layout.fillWidth: true
                            height: 70
                            radius: 12
                            color: cardBackground
                            border.color: borderColor
                            border.width: 1

                            RowLayout {
                                anchors.fill: parent
                                anchors.margins: 18
                                spacing: 12

                                Label {
                                    text: "System Status:"
                                    font.pixelSize: 20
                                    font.bold: true
                                    color: cardTextColor
                                }

                                Label {
                                    text: connectionStatusText(telemetryModel.connectStatus)
                                    font.pixelSize: 20
                                    font.bold: true
                                    color: connectionStatusColor(telemetryModel.connectStatus)
                                }
                            }
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
                                        text: "Fan RPM"
                                        font.pixelSize: 18
                                        color: secondaryTextColor
                                    }

                                    Label {
                                        text: telemetryModel.fanRpm
                                        font.pixelSize: 22
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
                                        text: "emergency Button"
                                        font.pixelSize: 18
                                        color: secondaryTextColor
                                    }

                                    Label {
                                        text: telemetryModel.emergency_button
                                        font.pixelSize: 22
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
                                        text: "vibration level"
                                        font.pixelSize: 18
                                        color: secondaryTextColor
                                    }

                                    Label {
                                        text: telemetryModel.vibration_level_mg
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
                            height: 120
                            radius: 12
                            color: cardBackground
                            border.color: borderColor
                            border.width: 1

                            RowLayout {
                                anchors.fill: parent
                                anchors.margins: 16
                                spacing: 16

                                Label {
                                    text: "Load Thresholds"
                                    font.pixelSize: 18
                                    font.bold: true
                                    color: cardTextColor
                                }

                                ColumnLayout {
                                    spacing: 4

                                    Label {
                                        text: "Warning Threshold"
                                        font.pixelSize: 14
                                        font.bold: true
                                        color: "#d97706"
                                    }

                                    TextField {
                                        id: warningThresholdInput
                                        text: "60"
                                        inputMethodHints: Qt.ImhDigitsOnly
                                        Layout.preferredWidth: 120
                                        // color: "#d97706"
                                    }
                                }

                                ColumnLayout {
                                    spacing: 4

                                    Label {
                                        text: "Fault Threshold"
                                        font.pixelSize: 14
                                        font.bold: true
                                        color: "#dc2626"
                                    }

                                    TextField {
                                        id: faultThresholdInput
                                        text: "85"
                                        inputMethodHints: Qt.ImhDigitsOnly
                                        Layout.preferredWidth: 120
                                        // color: "#dc2626"
                                    }
                                }

                                Button {
                                    text: "Set Threshold"
                                    enabled: telemetryModel.connectStatus===1

                                    onClicked: {
                                        const warning = parseInt(warningThresholdInput.text)
                                        const fault = parseInt(faultThresholdInput.text)

                                        if (isNaN(warning) || isNaN(fault))
                                        {
                                            console.log("Invalid threshold input")
                                            return
                                        }

                                        if (warning >= fault)
                                        {
                                            console.log("Warning threshold must be lower than fault threshold")
                                            return
                                        }

                                        telemetryModel.setLoadThreshold(warning, fault)
                                    }
                                }
                            }
                        }

                     Rectangle {
                            Layout.fillWidth: true
                            height: 120
                            radius: 12
                            color: cardBackground
                            border.color: borderColor
                            border.width: 1

                            RowLayout {
                                anchors.fill: parent
                                anchors.margins: 16
                                spacing: 16

                                Label {
                                    text: "Vibration Thresholds"
                                    font.pixelSize: 18
                                    font.bold: true
                                    color: cardTextColor
                                }

                                ColumnLayout {
                                    spacing: 4

                                    Label {
                                        text: "Warning Threshold"
                                        font.pixelSize: 14
                                        font.bold: true
                                        color: "#d97706"
                                    }

                                    TextField {
                                        id: vibration_warningThresholdInput
                                        text: "1800"
                                        inputMethodHints: Qt.ImhDigitsOnly
                                        Layout.preferredWidth: 120
                                        // color: "#d97706"
                                    }
                                }

                                ColumnLayout {
                                    spacing: 4

                                    Label {
                                        text: "Fault Threshold"
                                        font.pixelSize: 14
                                        font.bold: true
                                        color: "#dc2626"
                                    }

                                    TextField {
                                        id: vibration_faultThresholdInput
                                        text: "2500"
                                        inputMethodHints: Qt.ImhDigitsOnly
                                        Layout.preferredWidth: 120
                                        // color: "#dc2626"
                                    }
                                }

                                Button {
                                    text: "Set Threshold"
                                    enabled: telemetryModel.connectStatus===1

                                    onClicked: {
                                        const warning = parseInt(vibration_warningThresholdInput.text)
                                        const fault = parseInt(vibration_faultThresholdInput.text)

                                        if (isNaN(warning) || isNaN(fault))
                                        {
                                            console.log("Invalid threshold input")
                                            return
                                        }

                                        if (warning >= fault)
                                        {
                                            console.log("Warning threshold must be lower than fault threshold")
                                            return
                                        }

                                        telemetryModel.setVibrationThreshold(warning, fault)
                                    }
                                }
                            }
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
                                enabled: telemetryModel.connectStatus===1
                            }

                            Button {
                                text: "Stop Machine"
                                onClicked: telemetryModel.stopMachine()
                                enabled: telemetryModel.connectStatus===1
                            }

                            Button {
                                text: "Reset Fault"
                                onClicked: telemetryModel.resetFault()
                                enabled: telemetryModel.connectStatus===1
                            }
                        }
                    }
                }
