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

    Item {
        anchors.centerIn: parent
        implicitWidth: speed.width
        implicitHeight: speed.height + speedUnit.height + driveMode.height

        Text {
            id: driveMode
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.bottom: speed.top
            text : "D"
            color : "#FFFFFF"
            font.pixelSize : 48
            font.family: oxaniumSemiBold.name
        }

        Text {
            id: speed
            anchors.centerIn: parent
            anchors.verticalCenterOffset: 15
            text : (system.dataTick,system.values("SensorData","Speed"))
            color : "#FFFFFF"
            font.pixelSize: 84
            font.family: oxaniumSemiBold.name
        }

        Text {
            id: speedUnit
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.top: speed.bottom
            text : "km/h"
            color : "#FFFFFF"
            font.pixelSize : 20
            font.family: oxaniumSemiBold.name
        }

}

    Arrow{
        id: arrow
        anchors.centerIn: parent

        transform: Rotation {
                origin.x: arrow.width/2    // pixel X względem lewego górnego rogu
                origin.y: arrow.height/2   // pixel Y
                angle: Math.max(-140, Math.min(140, -140 + (Number(30) * 2)))
            }
        Behavior on rotation {
            SmoothedAnimation {
                velocity: 30   // stopnie na sekundę
            }
        }
    }
}
