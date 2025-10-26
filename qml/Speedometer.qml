import QtQuick 2.15

Item {
    id :root
    height : 570
    width : height

    Column {
        anchors.centerIn: parent
        Text { // Speed
            anchors.horizontalCenter: parent.horizontalCenter
            text : speedometer ? speedometer.value : "-"
            font.family: chakraFont.name
            font.pixelSize : 90
            color : "#F3F3F3"
        }

        Text {// km/h
            anchors.horizontalCenter: parent.horizontalCenter
            text : "km/h"
            font.pixelSize : 25
            font.family : chakraFont.name
            color : "#F3F3F3"

        }
    }

    Text { // gear
        anchors.horizontalCenter: parent.horizontalCenter
        text : drivemode ? drivemode.value : "-"
        font.pixelSize : 45
        font.family : chakraFont.name
        color : "#F3F3F3"
        y : 435
    }

    Item {
        id: needleContainer
        x: 274
        y: 0
        width : 24
        height : parent.width/2
        Image {
            y : 13
            anchors.horizontalCenter: parent.horizontalCenter
            source : "qrc:/images/arrow.png"

        }

        transform : Rotation {
            origin.x : needleContainer.width /2
            origin.y : needleContainer.height
            angle: { // Potrzebne ograniczenie zeby po przekroczeiu 140 wskazowka sie nie wychylala dalej
                    if(speedometer == null){return 0;}
                    var a = -140 + 2 * speedometer.value;
                    return Math.min(Math.max(a, -140), 140);
                }
        }
    }

}
