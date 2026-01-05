import QtQuick
import QtQuick.Controls

Window {
    visible: true
    width: 1600
    height: 600
    flags: Qt.FramelessWindowHint

    minimumWidth: 1600
    maximumWidth: 1600
    minimumHeight: 600
    maximumHeight: 600

    FontLoader {
        id: oxaniumRegular
        source : "qrc:/fonts/Oxanium-Regular.ttf"
    }

    FontLoader {
        id: oxaniumSemiBold
        source : "qrc:/fonts/Oxanium-SemiBold.ttf"
    }

    Image {
        source: "qrc:/img/background.png"
        anchors.fill: parent
        fillMode: Image.PreserveAspectCrop
    }

    Top_Row{
        anchors.horizontalCenter: parent.horizontalCenter
        y: 6
    }

    Indicators_Row{
        x: 560
        y: 63
    }

    Error_Pop_Up{
        x: 656
        y: 140
        width: 287
        height: 158
        opacity: 1.0
    }

    Warnings_Row{
        anchors.horizontalCenter: parent.horizontalCenter
        y: 430
    }

    Lights_Row{
        anchors.horizontalCenter: parent.horizontalCenter
        y: 510
    }

    Gauges{
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter
    }

}
