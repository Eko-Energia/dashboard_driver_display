import QtQuick

Item {
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
        text : "47"
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
