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

    Warnings_Row{
        anchors.horizontalCenter: parent.horizontalCenter
        y: 430
    }

    Lights_Row{
        anchors.horizontalCenter: parent.horizontalCenter
        y: 510
    }

    /* Suwak do testowania
    Item {
            id: root
            width: 400
            height: 50
            anchors.bottom: parent.bottom
            anchors.horizontalCenter: parent.horizontalCenter

            property int suwak_v: 0

            RowLayout {
                anchors.fill: parent
                spacing: 15

                Slider {
                    id: slider
                    Layout.fillWidth: true

                    from: -100
                    to: 100
                    stepSize: 1

                    value: root.suwak_v

                    onMoved: {
                        root.suwak_v = value
                    }
                }

                TextField {
                    id: inputField
                    Layout.preferredWidth: 60
                    Layout.alignment: Qt.AlignVCenter
                    horizontalAlignment: TextInput.AlignHCenter

                    validator: IntValidator { bottom: -100; top: 100 }

                    text: root.suwak_v.toString()

                    onTextEdited: {
                        let parsedValue = parseInt(text)
                        if (!isNaN(parsedValue)) {
                            root.suwak_v = parsedValue
                        }
                    }


                    onEditingFinished: {
                        if (text === "" || text === "-") {
                            root.suwak_v = 0
                        }
                        inputField.text = Qt.binding(() => root.suwak_v.toString())
                    }
                }
            }
        }
    */
    Row{
        spacing: 450
        id: gaugesRow
        anchors.centerIn: parent

        Speedometer{
            speedValue: 90 // root.suwak_v
            speedValueText: "90" // Math.floor(root.suwak_v * 1.4).toString()
            driveMode: "D"
        }

        Powermeter{
            powerValue: 12
            batteryCharge: 0.9
            /*
            {
                system.dataTick;
                return system.values("VECTOR__INDEPENDENT_SIG_MSG","BMSMaster_MasterBatteryVoltage");
            }*/
        }
    }


}
