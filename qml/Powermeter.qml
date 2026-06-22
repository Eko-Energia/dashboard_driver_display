import QtQuick
import Qt5Compat.GraphicalEffects

Item {
    id: root
    width: 520
    height: 520
    property real powerValue: 0
    property real batteryCharge: 0

    FontLoader {
            id: oxaniumSemiBold
            source : "qrc:/fonts/Oxanium-SemiBold.ttf"
    }

    FontLoader {
            id: oxaniumXBold
            source : "qrc:/fonts/Oxanium-ExtraBold.ttf"
    }

    Image{
        id: bckgrd_glow
        source: "qrc:/img/gauges/powermeter/glow_right.png"
        anchors.centerIn: parent
        fillMode: Image.PreserveAspectFit
    }

    Image{
        id: powermeter_background
        source: "qrc:/img/gauges/powermeter/powermeter.png"
        anchors.centerIn: parent
        fillMode: Image.PreserveAspectFit
        width: root.width
        height: root.height
    }

    Item {
        id: battery_indicator
        width: parent.width
        height: parent.height
        anchors.centerIn: parent


        BatteryBar{
            chargeValue: root.batteryCharge
            startAngle: 114
            endAngle: 16
        }

        Row {
            anchors.horizontalCenter: parent.horizontalCenter
            y: 450
            spacing: 2

            Image {
                id: battery_icon
                source: "qrc:/img/gauges/powermeter/battery/battery_icon.png"
                fillMode: Image.PreserveAspectFit
                sourceSize.width: 50
                anchors.verticalCenter: parent.verticalCenter
            }

            Text {
                id: battery_text
                text: (Math.round(root.batteryCharge)).toString() + "%"
                color: "#DD9117"
                font.pixelSize: 24
                font.family: oxaniumXBold.name
                anchors.verticalCenter: parent.verticalCenter
            }

        }
    }

    Item {
        id: powermeter_column
        anchors.centerIn: parent
        width: parent.width
        height: parent.height

        Column{
            anchors.centerIn: parent
            anchors.verticalCenterOffset: 14
            spacing : 6

            Text {
                id: power
                anchors.horizontalCenter: parent.horizontalCenter
                text: (Math.floor(root.powerValue)).toString()
                color: "#D9D9D9"
                font.pixelSize: 72
                font.family: oxaniumSemiBold.name
            }

            Text {
                id: powerUnit
                anchors.horizontalCenter: parent.horizontalCenter
                text: "kW"
                color: "#D9D9D9"
                font.pixelSize: 20
                font.family: oxaniumSemiBold.name
            }
        }
}

    Needle { // Strzaleczka predkosciomierza
        rotationValue: root.powerValue
        startAngle: -60 // katy
        rotationRangeLow: -140 // w katach
        rotationRangeHigh: 100
        valueMin: -10 // liczby
        valueMax: 20
    }

}
