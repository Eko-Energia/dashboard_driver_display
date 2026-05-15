import QtQuick

Item {
    id: root
    width: 520
    height: root.width
    property int speedValue: 0
    property string speedValueText: "null"
    property string driveMode: "null"

    Image{ // mysle nad zanimowaniem tego efektu kiedys
        id: bckgrd_glow
        source: "qrc:/img/gauges/speedometer/glow_left.png"
        anchors.centerIn: parent
        fillMode: Image.PreserveAspectFit
    }

    Image{ // Tło tarczy, numerki, kreseczki i kółeczka
        id: speedometer_background
        source: "qrc:/img/gauges/speedometer/speedometer.png"
        anchors.centerIn: parent
        fillMode: Image.PreserveAspectFit
        width: root.width
        height: root.height
    }

    Item { // Kolumna z prędkością, trybem jazdy i stanem tempomatu
        id : speedometer_column
        anchors.centerIn: parent
        width: parent.width
        height: parent.height

        Column {
            anchors.centerIn: parent
            anchors.verticalCenterOffset: 60
            spacing : 6

            Text {
                id: driveMode
                anchors.horizontalCenter: parent.horizontalCenter
                text : root.driveMode
                color : "#D9D9D9"
                font.pixelSize : 48
                font.family: oxaniumSemiBold.name
            }

            Text {
                id: speed
                anchors.horizontalCenter: parent.horizontalCenter
                text : root.speedValueText
                color : "#D9D9D9"
                font.pixelSize: 72
                font.family: oxaniumSemiBold.name
            }

            Text {
                id: speedUnit
                anchors.horizontalCenter: parent.horizontalCenter
                text : "km/h"
                color : "#D9D9D9"
                font.pixelSize : 20
                font.family: oxaniumSemiBold.name
            }

            Item {
                height: 90
                width : 90
                anchors.horizontalCenter: parent.horizontalCenter
                Image {
                    id: cruise_control
                    source : "qrc:/img/gauges/speedometer/cruise_control.png"
                    anchors.centerIn:  parent
                    width: 60
                    fillMode: Image.PreserveAspectFit
                    opacity: 1.0 // do zmiany
                }
            }
        }
    }

    Needle { // Strzaleczka predkosciomierza
        rotationValue: root.speedValue
        startAngle: -142 // katy
        rotationRangeLow: -142 // w katach
        rotationRangeHigh: 142
        valueMin: 0 // liczby
        valueMax: 140
    }
}


