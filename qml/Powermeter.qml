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

    Item {
        id: powerMeterContainer
        anchors.centerIn: parent // To zastępuje anchors z Powermeter_Column
        
        // Ustawiamy wymiary na podstawie zawartości
        width: power.width
        height: power.height + powerUnit.height

        Text {
            id: power
            anchors.horizontalCenter: parent.horizontalCenter
            y: -10 // Odpowiednik verticalCenterOffset w tym kontekście
            text: "30"
            color: "#FFFFFF"
            font.pixelSize: 84
            font.family: oxaniumSemiBold.name
        }

        Text {
            id: powerUnit
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.top: power.bottom
            anchors.topMargin: -10 // Korekta, by jednostka była bliżej liczby
            text: "kW"
            color: "#FFFFFF"
            font.pixelSize: 20
            font.family: oxaniumSemiBold.name
        }
}

    Arrow{
        width: 400
        height: 400
        anchors.centerIn: parent
        rotation: 20
    }

}
