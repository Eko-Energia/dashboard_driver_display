import QtQuick

Item {
    implicitWidth: 520
    implicitHeight: 520

    Image{
        id: powermeter
        source: "qrc:/img/gauges/powermeter/powermeter.png"
        anchors.centerIn: parent
        anchors.horizontalCenterOffset: 6
        anchors.verticalCenterOffset: 7
        height: 630
        width: 635
    }

    Battery_Charge_Bar{
        anchors.centerIn: parent
        height: 602
        width: 602
    }

    Battery_Icon{
        height: 36
        width: 50
        x: 153
        y: 461
    }

    Powermeter_Column{
        anchors.centerIn: parent
    }

    Arrow{
        width: 400
        height: 400
        anchors.centerIn: parent
        rotation: 20
    }

}
