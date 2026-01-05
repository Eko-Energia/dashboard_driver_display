import QtQuick

Item {
    implicitWidth: warningsRow.implicitWidth
    implicitHeight: warningsRow.implicitHeight

    Row{
        spacing: 24
        id: warningsRow

        //Check_Engine
        Image {
            source : "qrc:/img/warnings/check_engine.png"
            width: 50
            height: 40
            opacity: 1.0
        }

        //low_battery
        Image {
            source : "qrc:/img/warnings/low_battery.png"
            width: 50
            height: 50
            opacity: 1.0
        }

        //high_temperature
        Image {
            source : "qrc:/img/warnings/high_temperature.png"
            width: 50
            height: 50
            opacity: 1.0
        }

        //open_door
        Image {
            source : "qrc:/img/warnings/open_door.png"
            width: 50
            height: 50
            opacity: 1.0
        }
    }
}
