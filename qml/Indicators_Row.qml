import QtQuick

Item {
    id: root
    implicitWidth: indicatorsRow.implicitWidth
    implicitHeight: indicatorsRow.implicitHeight

    property bool isLeftActive: {
        system.dataTick;
        Number(system.values("Dashboard_Lights", "TurnSignal_Left")) === 1
    }

    property bool isRightActive: {
        system.dataTick;
        Number(system.values("Dashboard_Lights", "TurnSignal_Right")) === 1
    }

    property bool blinkState: false

    Timer {
        id: blinkerTimer
        interval: 500
        repeat: true
        running: root.isLeftActive || root.isRightActive

        onTriggered: {
            root.blinkState = !root.blinkState
        }

        onRunningChanged: {
            if (running) {
                root.blinkState = true
            } else {
                root.blinkState = false
            }
        }
    }

    Row {
        id: indicatorsRow
        spacing: 360

        // left_indicator
        Image {
            source : "qrc:/img/indicators/left_indicator.png"
            width: 50
            height: 50
            opacity: (root.isLeftActive && root.blinkState) ? 1.0 : 0.0
        }

        // right_indicator
        Image {
            source : "qrc:/img/indicators/right_indicator.png"
            width: 50
            height: 50
            opacity: (root.isRightActive && root.blinkState) ? 1.0 : 0.0
        }
    }
}