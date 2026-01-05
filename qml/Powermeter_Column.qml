import QtQuick

Item {
    implicitWidth: power.width
    implicitHeight: power.height + powerUnit.height

    Text {
        id: power
        anchors.centerIn: parent
        anchors.verticalCenterOffset: -10
        text : "10"
        color : "#FFFFFF"
        font.pixelSize: 84
        font.family: oxaniumSemiBold.name
    }

    Text {
        id: powerUnit
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: power.bottom
        text : "kW"
        color : "#FFFFFF"
        font.pixelSize : 20
        font.family: oxaniumSemiBold.name
    }

}
