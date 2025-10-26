import QtQuick 2.15

Item {
    property bool mirrored : false

    id: root
    Image {
        source : "qrc:/images/Blinker.png"
        height: 50
        width : 50
        anchors.fill : parent

        mirror : parent.mirrored
    }
}
