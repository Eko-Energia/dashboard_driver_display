import QtQuick

// Panel informacyjny w stylu Error_Pop_Up (zaokraglone rogi, poswiata na
// gornej/dolnej krawedzi), ale w ciemniejszej, neutralnej tonacji pasujacej
// do reszty ekranu zamiast ostrzegawczego pomaranczu. Wyswietla srednie
// zuzycie energii oraz przebieg.
Rectangle {
    id: root
    width: 287
    height: 158
    radius: 18

    property real avgConsumptionKwh: 0
    property real mileageKm: 0

    color: "#0A0E27"
    border.color: "#2A2F55"
    border.width: 1
    antialiasing: true

    FontLoader {
        id: oxaniumSemiBold
        source: "qrc:/fonts/Oxanium-SemiBold.ttf"
    }

    Rectangle {
        anchors.top: parent.top
        anchors.horizontalCenter: parent.horizontalCenter
        width: parent.width * 0.86
        height: 2
        radius: 1
        opacity: 0.5
        gradient: Gradient {
            orientation: Gradient.Horizontal
            GradientStop { position: 0.0; color: "transparent" }
            GradientStop { position: 0.5; color: "#5A65A0" }
            GradientStop { position: 1.0; color: "transparent" }
        }
    }

    Rectangle {
        anchors.bottom: parent.bottom
        anchors.horizontalCenter: parent.horizontalCenter
        width: parent.width * 0.86
        height: 2
        radius: 1
        gradient: Gradient {
            orientation: Gradient.Horizontal
            GradientStop { position: 0.0; color: "transparent" }
            GradientStop { position: 0.5; color: "#5A65A0" }
            GradientStop { position: 1.0; color: "transparent" }
        }
    }

    Column {
        anchors.centerIn: parent
        spacing: 14

        Column{
            spacing: 10
            Text {
                text: "Śr. zużycie energii"
                color: "#8A93C0"
                font.pixelSize: 20
                font.family: oxaniumSemiBold.name
            }
            Text {
                text: root.avgConsumptionKwh.toFixed(2) + " kWh/h"
                color: "#D9D9D9"
                font.pixelSize: 20
                font.family: oxaniumSemiBold.name
            }
        }

        Column {
            spacing: 10
            Text {
                text: "Przebieg"
                color: "#8A93C0"
                font.pixelSize: 20
                font.family: oxaniumSemiBold.name
            }
            Text {
                text: root.mileageKm.toFixed(1) + " km"
                color: "#D9D9D9"
                font.pixelSize: 20
                font.family: oxaniumSemiBold.name
            }
        }
    }
}
