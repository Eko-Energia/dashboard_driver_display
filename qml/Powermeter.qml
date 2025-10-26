import QtQuick 2.15

Item {
    id :root
    height : 570
    width : height



    Column {
        anchors.centerIn: parent
        Text { // Speed
            anchors.horizontalCenter: parent.horizontalCenter
            text : engine_power ? engine_power.value : "-"
            font.family: chakraFont.name
            font.pixelSize : 90
            color : "#F3F3F3"
        }

        Text {// km/h
            anchors.horizontalCenter: parent.horizontalCenter
            text : "kW"
            font.pixelSize : 25
            font.family : chakraFont.name
            color : "#F3F3F3"

        }
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
            angle: {
                    if(engine_power == null){return 0;} // sprawdza czy obiekt istnieje
                    if(engine_power.value >= 0){
                        var a = -40 + 8 * engine_power.value;
                        return Math.min(Math.max(a, -40), 120);
                    }

                    else{
                        var b = -40 + 8 * engine_power.value;
                        return Math.min(Math.max(b, -120), -40);
                    }
                }
        }
    }

}

