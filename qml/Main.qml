import QtQuick
import QtQuick.Controls
import QtQuick.Layouts //usunac pozniej
import Qt5Compat.GraphicalEffects

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

    FontLoader {
        id: oxaniumXBold
        source : "qrc:/fonts/Oxanium-ExtraBold.ttf"
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

    Utils{
        x: 656
        y: 140 + 158 + 4
        avgPowerW: system.avgPowerW
        energyIntervalS: system.energyIntervalS
        mileageKm: system.totalKm
    }

    /* Nie zaimplementowane
    Warnings_Row{
        anchors.horizontalCenter: parent.horizontalCenter
        y: 430
    }*/

    Lights_Row{
        anchors.horizontalCenter: parent.horizontalCenter
        y: 510
    }

    Row{
        spacing: 450
        id: gaugesRow
        anchors.centerIn: parent

        Speedometer{        
            speedValue : system.speedKmh
            /*
            {
                system.dataTick;
                let rightRPM = Math.abs(Number(system.values("EngineRight_STATIC_TPDO1","RightMotorRPM")));
                let leftRPM = Math.abs(Number(system.values("EngineLeft_STATIC_TPDO1","LeftMotorRPM")));
                // Srednia z obrotow -> dzielenie przez 6 (przekladnia) -> droga przebyta przez kolo obrot ->  zamiana jednostek
                return Math.abs(Math.round((rightRPM+leftRPM)/12 * (2*Math.PI*0.35) * (60/1000)))
            }*/
            speedValueText : Math.round(speedValue)

            driveMode:{
                system.dataTick;
                let gear = Number(system.values("Dashboard_Control","PRND"));
                switch(gear){
                case 0:
                    return "P"
                case 1:
                    return "R"
                case 2:
                    return "N"
                case 3:
                    return "D"
                default:
                    console.log("Out of range value for PRND")
                    return "?"
                }
            }
        }

        Powermeter{
            powerValue:
            {
                system.dataTick;
                return (
                    Number(system.values("BMSMaster_JK_Pack","BMSMaster_JK_PackVoltage")) * Number(system.values("BMSMaster_JK_Pack","BMSMaster_JK_PackCurrent"))
                     / 1000.0
                )
            }

            batteryCharge:
            {
                /*
                  Totalnie nie podoba mi sie ten sposob obliczania stanu baterii
                  Rozwiazanie chwilowe, nasza bateria na 100% nie ma charakterystyki
                  liniowej xdddddd
                */
                system.dataTick;

                return (Number(system.values("BMSMaster_JK_Pack","BMSMaster_JK_SOC")))
            }
        }
    }


}
