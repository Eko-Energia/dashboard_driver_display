import QtQuick

Item {
    Image {
        id: needle
        source: "qrc:/img/gauges/arrow.png"
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.bottom: parent.verticalCenter
        height: 196
        fillMode: Image.PreserveAspectFit
    }
}


