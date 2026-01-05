import QtQuick

Item {
    implicitWidth: 520
    implicitHeight: 520

    Image{
        id: powermeter
        source: "qrc:/img/gauges/speedometer/speedometer.png"
        anchors.centerIn: parent
        anchors.horizontalCenterOffset: -3
        anchors.verticalCenterOffset: 7
        height: 630
        width: 635
    }


    Speed_Control{
        height: 40
        width: 50
        anchors.horizontalCenter: parent.horizontalCenter
        y:360
        opacity: 1.0
    }

    Speedometer_Column{
        anchors.centerIn: parent
    }

    Arrow{
        width: 400
        height: 400
        anchors.centerIn: parent
        rotation: -53
    }

}
