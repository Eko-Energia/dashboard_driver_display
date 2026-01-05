import QtQuick

Item {
    implicitWidth: lightsRow.implicitWidth
    implicitHeight: lightsRow.implicitHeight

    Row{
        spacing: 53
        id: lightsRow

        //park_lights
        Image {
            source : "qrc:/img/lights/park_lights.png"
            width: 72
            height: 50
            opacity: 1.0
        }

        //low_beams
        Image {
            source : "qrc:/img/lights/low_beams.png"
            width: 50
            height: 50
            opacity: 1.0
        }

        //full_beams
        Image {
            source : "qrc:/img/lights/full_beams.png"
            width: 50
            height: 50
            opacity: 1.0
        }

        //hazard_lights
        Image {
            source : "qrc:/img/lights/hazard_lights.png"
            width: 50
            height: 50
            opacity: 1.0
        }
    }
}
