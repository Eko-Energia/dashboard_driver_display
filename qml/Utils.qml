import QtQuick
Rectangle {
    id: root
    width: 287
    height: 158
    radius: 18

    property real avgPowerW: 0
    property real energyIntervalS: 3600
    property real mileageKm: 0

    readonly property string intervalLabel: {
        var s = root.energyIntervalS > 0 ? root.energyIntervalS : 3600
        return Math.round(s / 60) + " min"
    }

    readonly property string consumptionText: {
        var v = root.avgPowerW
        if (Math.abs(v) >= 1000)
            return (v / 1000).toFixed(2) + " kWh / " + root.intervalLabel
        if (Math.abs(v) >= 100)
            return v.toFixed(0) + " Wh / " + root.intervalLabel
        return v.toFixed(1) + " Wh / " + root.intervalLabel
    }

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
                text: root.consumptionText
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
