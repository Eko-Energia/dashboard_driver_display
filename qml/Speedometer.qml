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
