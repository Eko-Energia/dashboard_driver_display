import QtQuick

Item {
    implicitWidth: topRow.implicitWidth
    implicitHeight: topRow.implicitHeight

    Row{
        spacing: 44
        id: topRow

        Text{
            id: date
            anchors.verticalCenter: parent.verticalCenter
            text : "27.10"
            color : "#FFFFFF"
            font.pixelSize : 24
            font.family: oxaniumSemiBold.name
        }

        Text{
            id: time
            anchors.verticalCenter: parent.verticalCenter
            text : "21:37"
            color : "#FFFFFF"
            font.pixelSize : 24
            font.family: oxaniumSemiBold.name
        }

        Text{
            id: temperature
            anchors.verticalCenter: parent.verticalCenter
            text : "26℃"
            color : "#FFFFFF"
            font.pixelSize : 24
            font.family: oxaniumSemiBold.name
        }
    }
}
