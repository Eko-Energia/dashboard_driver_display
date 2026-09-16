import QtQuick

// Karta z wartosciami wyliczonymi przez rpi_utilities (port 8081), w odroznieniu od
// zegarow, ktore licza sie z surowych ramek CAN. Stad nazwa mowiaca o zrodle, a nie
// o tresci - przebieg nie jest energia, a oba wiersze przychodza tym samym kanalem.
Rectangle {
    id: root
    width: 287
    height: 158
    radius: 18

    // Jednostki takie, jakie nadaje producent - przeliczenie na Wh/km robimy dopiero
    // przy formatowaniu, zeby nazwa property zgadzala sie z nazwa pola w API.
    property real avgPowerKw: 0
    property real consumptionKwhPerKm: 0
    property bool consumptionValid: false
    property real energyCoverage: 0
    property real energyIntervalS: 900
    property real mileageKm: 0

    readonly property int rowHeight: 40

    // Ponizej tego pokrycia okna obie srednie licza sie z na tyle krotkiego przedzialu,
    // ze nie opisuja jazdy tylko ostatnie kilkanascie sekund. Przy oknie 15 min to okolo
    // 3 minuty jazdy. Wiersz znika zamiast klamac - tak samo jak przy consumption == null.
    readonly property real minCoverage: 0.2
    readonly property bool energyReady: root.energyCoverage >= root.minCoverage

    readonly property string intervalLabel: {
        var s = root.energyIntervalS > 0 ? root.energyIntervalS : 900
        return Math.round(s / 60) + " min"
    }

    // Wh/km zamiast kWh/km: realne zuzycie auta solarnego to rzad 0.02-0.10 kWh/km,
    // czyli same zera po przecinku. W Wh/km to czytelna liczba calkowita.
    readonly property string consumptionText: Math.round(root.consumptionKwhPerKm * 1000) + " Wh/km"
    readonly property string avgPowerText: root.avgPowerKw.toFixed(1) + " kW"

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
        width: parent.width - 44
        spacing: 6

        // Kazdy wiersz to staly slot: gdy wartosci nie ma, znikaja same teksty, a wiersz
        // zostaje pusty. Inaczej pozostale liczby przeskakiwalyby kierowcy w polu widzenia
        // za kazdym razem, gdy auto staje albo rusza.
        Item {
            width: parent.width
            height: root.rowHeight

            Text {
                anchors.left: parent.left
                anchors.verticalCenter: parent.verticalCenter
                visible: root.energyReady && root.consumptionValid
                text: "Zużycie"
                color: "#8A93C0"
                font.pixelSize: 16
                font.family: oxaniumSemiBold.name
            }
            Text {
                anchors.right: parent.right
                anchors.verticalCenter: parent.verticalCenter
                visible: root.energyReady && root.consumptionValid
                text: root.consumptionText
                color: "#D9D9D9"
                font.pixelSize: 18
                font.family: oxaniumSemiBold.name
            }
        }

        Item {
            width: parent.width
            height: root.rowHeight

            Text {
                anchors.left: parent.left
                anchors.verticalCenter: parent.verticalCenter
                visible: root.energyReady
                text: "Śr. moc (" + root.intervalLabel + ")"
                color: "#8A93C0"
                font.pixelSize: 16
                font.family: oxaniumSemiBold.name
            }
            Text {
                anchors.right: parent.right
                anchors.verticalCenter: parent.verticalCenter
                visible: root.energyReady
                text: root.avgPowerText
                color: "#D9D9D9"
                font.pixelSize: 18
                font.family: oxaniumSemiBold.name
            }
        }

        Item {
            width: parent.width
            height: root.rowHeight

            Text {
                anchors.left: parent.left
                anchors.verticalCenter: parent.verticalCenter
                text: "Przebieg"
                color: "#8A93C0"
                font.pixelSize: 16
                font.family: oxaniumSemiBold.name
            }
            Text {
                anchors.right: parent.right
                anchors.verticalCenter: parent.verticalCenter
                text: root.mileageKm.toFixed(1) + " km"
                color: "#D9D9D9"
                font.pixelSize: 18
                font.family: oxaniumSemiBold.name
            }
        }
    }
}
