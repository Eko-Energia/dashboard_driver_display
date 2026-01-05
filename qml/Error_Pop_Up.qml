import QtQuick

Item {
    Image{
        source : "qrc:/img/error_pop_up.png"
        anchors.fill: parent
    }

    Text{
        id: error_pop_up_title
        anchors.horizontalCenter: parent.horizontalCenter
        y: 12
        text : "Wykryto błędy"
        color : "#FFFFFF"
        font.pixelSize : 24
        font.family: oxaniumSemiBold.name
    }

    Text{
        id: error_text
        x: 24
        anchors.top: error_pop_up_title.bottom
        anchors.topMargin: 10
        text : "# 0420 Check engine!"
        color : "#FFFFFF"
        font.pixelSize : 24
        font.family: oxaniumSemiBold.name
    }
}

