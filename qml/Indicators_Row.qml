import QtQuick

Item {
    Row{
        spacing: 360

        //left_indicator
        Image {
            source : "qrc:/img/indicators/left_indicator.png"
            width: 50
            height: 50
            opacity: 1.0
        }

        //right_indicator
        Image {
            source : "qrc:/img/indicators/right_indicator.png"
            width: 50
            height: 50
            opacity: 1.0
        }
    }
}
