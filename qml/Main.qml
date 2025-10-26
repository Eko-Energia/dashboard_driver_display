import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15


Window {
    width: 1600
    height: 600
    visible: true
    flags: Qt.FramelessWindowHint

    minimumWidth: 1600
    maximumWidth: 1600
    minimumHeight: 600
    maximumHeight: 600
    FontLoader {
        id: chakraFont
        source : "qrc:/fonts/ChakraPetch-Medium.ttf"
    }

    Image { // Background
        //anchors.fill : parent
        source : "qrc:/images/base_ready.png"

    }

    Speedometer {
        x : 15
        y : 15
    }

    Powermeter {
        x : 1015
        y : 15
    }

    Row {
        x: 498 // Kierunkowskazy
        spacing : 514
        y : 40

        Blinker {
            height: 45
            width : 45
            opacity : blinkerLeft ? blinkerLeft.blinkState : 0.0
        }

        Blinker {
            height: 45
            width : 45
            opacity : blinkerRight ? blinkerRight.blinkState : 0.0
            mirrored : true
        }
    }

//################# BOT MENU ###############################################

    Text { // Temperature
        id: temperature_string
        text: temperature ? qsTr(temperature.value + "℃") : "-"
        font.pixelSize : 24
        font.family : chakraFont.name
        color : "#F3F3F3"
        x: 1060
        y: 520
    }

    Text { // Time
        id: time_string
        y: 520
        x: 765
        text: clock ? clock.time : "-"
        font.pixelSize : 24
        font.family : chakraFont.name
        color : "#F3F3F3"
    }

    Text { // Date
        id: date_string
        x: 475
        y: 520
        text: clock ? clock.date : "-"
        font.pixelSize : 24
        font.family : chakraFont.name
        color : "#F3F3F3"
    }

    Lights {
        x: 805
        y: 485
    }

    Text { // Mileage
        id: mileage_string
        x: 800
        y: 414
        width: 1
        height: 10
        text: mileage ? qsTr(mileage.value + " km") : "-"
        font.pixelSize : 24
        horizontalAlignment: Text.AlignHCenter
        font.family : chakraFont.name
        color : "#F3F3F3"
        //anchors.horizontalCenter: parent.horizontalCenter

    }

// ################## MID MENU ####################################################

    Text { // Reach, brak cpp
        id: reach_string
        x: 700
        text: qsTr("Zasięg 130km")
        font.pixelSize : 21
        font.family : chakraFont.name
        color : "#F3F3F3"
        y: 235
    }

    Text { // Power_usage, brak cpp
        id: usage_string
        x: 700
        text: qsTr("Zużycie energii \n >Aktualne 3kW/100km \n >Średnie 3.6kW/100km")
        font.pixelSize : 21
        font.family : chakraFont.name
        color : "#F3F3F3"
        y: 281
    }

// ################### TOP MENU ##########################################
    Warnings{
        x: 800
        y : 170
    }

    Text { // Battery
        id: battery_string
        x: 592
        y: 102
        text: battery ? qsTr("Bateria " + battery.value + "%") : "-"
        font.pixelSize : 21
        font.family : chakraFont.name
        color : "#F3F3F3"
    }

    Text { // Battery
        id: eco_string
        x: 862
        y: 102
        text: qsTr("Tryb jazdy : Eco")
        font.pixelSize : 21
        font.family : chakraFont.name
        color : "#F3F3F3"
    }
}
