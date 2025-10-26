import QtQuick 2.15

Item {
    id:root
    Row{
        spacing : 30
        anchors.centerIn: parent

        Image {
            id:crs_ctrl
            height: 45
            width: 50
            source : "qrc:/images/cruise_control.png"
            opacity: cruise_control ? cruise_control.value : 0.0
        }

        Image {
            id:engFailure
            source : "qrc:/images/check_engine.png"
            opacity: engine_failure ? engine_failure.value : 0.0
        }

        Image{
            id:pwrFailure
            source : "qrc:/images/power_warning.png"
            opacity: power_failure ? power_failure.value : 0.0
        }
        Image{
            id:lowBattery
            source : "qrc:/images/battery_warning.png"
            opacity: battery ? (battery.value <= 10 ? 1.0 : 0.0) : 0.0 // Sprawdza obiekt battery_cpp
        }
        Image{
            id:highTemp
            source : "qrc:/images/temp_warning.png"
            opacity: high_temperature ? high_temperature.value : 0.0// Tu tez niejawna konwersja 0(false) -> 0.0
        }
        Text{ // To placeholder, no clue jak zaprogramowac to narazie
            text : "Silnik"
            font.pixelSize : 27
            font.family : chakraFont.name
            color : "#FF0000"
            y : 4
        }
    }
}
