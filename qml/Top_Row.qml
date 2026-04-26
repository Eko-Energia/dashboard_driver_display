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
            text : clock.date
            color : "#FFFFFF"
            font.pixelSize : 24
            font.family: oxaniumSemiBold.name
        }

        Text{
            id: time
            anchors.verticalCenter: parent.verticalCenter
            text : clock.time
            color : "#FFFFFF"
            font.pixelSize : 24
            font.family: oxaniumSemiBold.name
        }

        Text{
            id: temperature
            anchors.verticalCenter: parent.verticalCenter
            text : {
                system.dataTick; 
                return system.values("MotorStatus","MotorTemp");
            }            
            color : "#FFFFFF"
            font.pixelSize : 24
            font.family: oxaniumSemiBold.name
        }
    }
}
