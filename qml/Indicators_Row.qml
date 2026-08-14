import QtQuick

Item {
    Row{
        spacing: 360

        //left_indicator
        Image {
            source : "qrc:/img/indicators/left_indicator.png"
            width: 50
            height: 50
            opacity: {
                system.dataTick;
                return Math.max(
                Number(system.values("LightsFL_Status","direction")),
                Number(system.values("LightsRL_Status","direction"))
                )
            }
        }

        //right_indicator
        Image {
            source : "qrc:/img/indicators/right_indicator.png"
            width: 50
            height: 50
            opacity: {
                system.dataTick;
                return  Math.max(
                Number(system.values("LightsFR_Status","direction")),
                Number(system.values("LightsRR_Status","direction"))
                )
            }
        }
    }
}
