import QtQuick 2.15

Item {
    id: root

    Row{
        spacing: 60
        anchors.centerIn: parent

        Image {
            source : "qrc:/images/mijania"
            opacity : low_beam ? low_beam.value : 0.0
        }

        Image {
            source : "qrc:/images/drogowe"
            opacity : high_beam ? high_beam.value : 0.0
        }

        Image {
            source : "qrc:/images/postojowe"
            opacity : parking_lights ? parking_lights.value : 0.0
        }

        Image {
            source : "qrc:/images/awaryjne"
            opacity : hazard_lights ? hazard_lights.value : 0.0
        }

    }
}
