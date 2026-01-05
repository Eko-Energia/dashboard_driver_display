import QtQuick

Item {
    implicitWidth: gaugesRow.implicitWidth
    implicitHeight: gaugesRow.implicitHeight

    Row{
        spacing: 450
        id: gaugesRow

        Speedometer{
            height: 530
            width: 535
        }

        Powermeter{
            anchors.horizontalCenterOffset: 1
            height: 530
            width: 535
        }
    }
}
