import QtQuick

Item {
    width: 30
    height: width

    Image {
        id: needle
        source: "qrc:/img/gauges/arrow.png"

        width: 20
        height: 172
        fillMode: Image.PreserveAspectFit
        anchors.horizontalCenter: parent.horizontalCenter
        y: parent.height / 2 - height
    }
}


