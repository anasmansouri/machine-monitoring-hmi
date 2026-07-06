import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

ApplicationWindow {
    visible: true
    width: 1000
    height: 580
    minimumWidth: 900
    minimumHeight: 560
    title: "Machine Monitoring HMI"

    color: "#1f2430"

    property color cardBackground: "#f9fafb"
    property color cardTextColor: "#111827"
    property color secondaryTextColor: "#4b5563"
    property color borderColor: "#d1d5db"

    function isConnected(status) {
        return status === true || status === 1
    }

    function connectionStatusText(status) {
        return isConnected(status) ? "CONNECTED" : "OFFLINE"
    }

    function connectionStatusColor(status) {
        return isConnected(status) ? "#16a34a" : "#dc2626"
    }

    function stateColor(state) {
        if (state === "MACHINE_STATE_RUNNING") {
            return "#15803d"
        }
        if (state === "MACHINE_STATE_WARNING") {
            return "#d97706"
        }
        if (state === "MACHINE_STATE_FAULT") {
            return "#dc2626"
        }
        return cardTextColor
    }

    function faultColor(fault) {
        return fault === "FAULT_NONE" ? cardTextColor : "#dc2626"
    }

    component MetricCard: Rectangle {
        property string title: ""
        property string value: ""
        property color valueColor: cardTextColor
        property int valueSize: 21

        Layout.fillWidth: true
        Layout.preferredHeight: 74
        radius: 10
        color: cardBackground
        border.color: borderColor
        border.width: 1

        Column {
            anchors.centerIn: parent
            spacing: 3

            Label {
                text: title
                font.pixelSize: 14
                color: secondaryTextColor
                horizontalAlignment: Text.AlignHCenter
                anchors.horizontalCenter: parent.horizontalCenter
            }

            Label {
                text: value
                font.pixelSize: valueSize
                font.bold: true
                color: valueColor
                horizontalAlignment: Text.AlignHCenter
                anchors.horizontalCenter: parent.horizontalCenter
                elide: Text.ElideRight
                maximumLineCount: 1
            }
        }
    }

    component ThresholdCard: Rectangle {
        property string title: ""
        property string warningText: ""
        property string faultText: ""
        property alias warningInput: warningField
        property alias faultInput: faultField
        property string buttonText: "Set"
        signal applyClicked(int warning, int fault)

        Layout.fillWidth: true
        Layout.preferredHeight: 74
        radius: 10
        color: cardBackground
        border.color: borderColor
        border.width: 1

        RowLayout {
            anchors.fill: parent
            anchors.margins: 8
            spacing: 10

            Label {
                text: title
                font.pixelSize: 15
                font.bold: true
                color: cardTextColor
                Layout.preferredWidth: 150
                elide: Text.ElideRight
            }

            ColumnLayout {
                spacing: 2

                Label {
                    text: "Warning"
                    font.pixelSize: 12
                    font.bold: true
                    color: "#d97706"
                }

                TextField {
                    id: warningField
                    text: warningText
                    inputMethodHints: Qt.ImhDigitsOnly
                    Layout.preferredWidth: 90
                }
            }

            ColumnLayout {
                spacing: 2

                Label {
                    text: "Fault"
                    font.pixelSize: 12
                    font.bold: true
                    color: "#dc2626"
                }

                TextField {
                    id: faultField
                    text: faultText
                    inputMethodHints: Qt.ImhDigitsOnly
                    Layout.preferredWidth: 90
                }
            }

            Button {
                text: buttonText
                enabled: isConnected(telemetryModel.connectStatus)
                Layout.preferredWidth: 130

                onClicked: {
                    const warning = parseInt(warningField.text)
                    const fault = parseInt(faultField.text)

                    if (isNaN(warning) || isNaN(fault)) {
                        console.log("Invalid threshold input")
                        return
                    }

                    if (warning >= fault) {
                        console.log("Warning threshold must be lower than fault threshold")
                        return
                    }

                    applyClicked(warning, fault)
                }
            }
        }
    }

    ColumnLayout {
        anchors.fill: parent
        anchors.margins: 14
        spacing: 10

        Label {
            text: "Machine Monitoring HMI"
            font.pixelSize: 26
            font.bold: true
            color: "white"
            Layout.alignment: Qt.AlignHCenter
        }

        Rectangle {
            Layout.fillWidth: true
            Layout.preferredHeight: 56
            radius: 10
            color: cardBackground
            border.color: borderColor
            border.width: 1

            RowLayout {
                anchors.fill: parent
                anchors.margins: 10
                spacing: 10

                Label {
                    text: "System Status:"
                    font.pixelSize: 18
                    font.bold: true
                    color: cardTextColor
                }

                Label {
                    text: connectionStatusText(telemetryModel.connectStatus)
                    font.pixelSize: 18
                    font.bold: true
                    color: connectionStatusColor(telemetryModel.connectStatus)
                }

                Item {
                    Layout.fillWidth: true
                }

                Label {
                    text: "Mode: AUTO"
                    font.pixelSize: 14
                    color: secondaryTextColor
                }
            }
        }

        GridLayout {
            columns: 3
            columnSpacing: 12
            rowSpacing: 12
            Layout.fillWidth: true

            MetricCard {
                title: "Temperature"
                value: telemetryModel.temperature + " °C"
                valueSize: 22
            }

            MetricCard {
                title: "Humidity"
                value: telemetryModel.humidity + " %"
                valueSize: 22
            }

            MetricCard {
                title: "Load"
                value: telemetryModel.load + " %"
                valueSize: 22
            }

            MetricCard {
                title: "Machine State"
                value: telemetryModel.state
                valueColor: stateColor(telemetryModel.state)
                valueSize: 17
            }

            MetricCard {
                title: "Fan RPM"
                value: telemetryModel.fanRpm + " RPM"
                valueSize: 21
            }

            MetricCard {
                title: "Emergency Button"
                value: telemetryModel.emergency_button
                valueColor: telemetryModel.emergency_button === "pressed" ? "#dc2626" : cardTextColor
                valueSize: 20
            }

            /*
            MetricCard {
                title: "Vibration Level"
                value: telemetryModel.vibration_level_mg + " mg"
                valueSize: 21
                Layout.row: 2
                Layout.column: 1
            }*/
        }

        Rectangle {
            Layout.fillWidth: true
            Layout.preferredHeight: 52
            radius: 10
            color: cardBackground
            border.color: borderColor
            border.width: 1

            RowLayout {
                anchors.fill: parent
                anchors.margins: 10
                spacing: 10

                Label {
                    text: "Fault:"
                    font.pixelSize: 18
                    font.bold: true
                    color: cardTextColor
                }

                Label {
                    text: telemetryModel.fault
                    font.pixelSize: 18
                    font.bold: true
                    color: faultColor(telemetryModel.fault)
                    Layout.fillWidth: true
                    elide: Text.ElideRight
                }
            }
        }

        ThresholdCard {
            title: "Load Thresholds"
            warningText: "60"
            faultText: "85"
            buttonText: "Set Load"

            onApplyClicked: function(warning, fault) {
                telemetryModel.setLoadThreshold(warning, fault)
            }
        }

	/*
        ThresholdCard {
            title: "Vibration Thresholds"
            warningText: "1800"
            faultText: "2500"
            buttonText: "Set Vibration"

            onApplyClicked: function(warning, fault) {
                telemetryModel.setVibrationThreshold(warning, fault)
            }
        }
	*/

        Rectangle {
            Layout.fillWidth: true
            Layout.preferredHeight: 72
            radius: 10
            color: cardBackground
            border.color: borderColor
            border.width: 1

            ColumnLayout {
                anchors.fill: parent
                anchors.margins: 8
                spacing: 4

                Label {
                    text: "Last Command Result"
                    font.pixelSize: 14
                    font.bold: true
                    color: cardTextColor
                }

                RowLayout {
                    Layout.fillWidth: true
                    spacing: 10

                    Label {
                        text: "Command:"
                        font.pixelSize: 14
                        color: secondaryTextColor
                    }

                    Label {
                        text: telemetryModel.lastCommandName
                        font.pixelSize: 14
                        font.bold: true
                        color: cardTextColor
                    }

                    Label {
                        text: telemetryModel.lastCommandSuccess ? "SUCCESS" : "FAILED"
                        font.pixelSize: 14
                        font.bold: true
                        color: telemetryModel.lastCommandSuccess ? "#15803d" : "#b91c1c"
                    }
                }

                Label {
                    text: telemetryModel.lastCommandMessage
                    font.pixelSize: 14
                    color: cardTextColor
                    Layout.fillWidth: true
                    elide: Text.ElideRight
                    maximumLineCount: 1
                }
            }
        }

        RowLayout {
            Layout.alignment: Qt.AlignHCenter
            spacing: 10

            Button {
                text: "Start Machine"
                onClicked: telemetryModel.startMachine()
                enabled: isConnected(telemetryModel.connectStatus)
            }

            Button {
                text: "Stop Machine"
                onClicked: telemetryModel.stopMachine()
                enabled: isConnected(telemetryModel.connectStatus)
            }

            Button {
                text: "Reset Fault"
                onClicked: telemetryModel.resetFault()
                enabled: isConnected(telemetryModel.connectStatus)
            }
        }
    }
}
