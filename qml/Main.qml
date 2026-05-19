import QtQuick
import QtQuick.Controls
import QtQuick.Layouts //usunac pozniej
import Qt5Compat.GraphicalEffects

Window {
    visible: true
    width: 1600
    height: 600
    //flags: Qt.FramelessWindowHint

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


    Item {
            id: root
            width: 400
            height: 50
            anchors.bottom: parent.bottom
            anchors.horizontalCenter: parent.horizontalCenter

            // Twoja główna zmienna. Możesz ją zbindować z C++ lub używać w innych miejscach QML
            property int suwak_v: 0 // Dla zakresu od -100 do 100, 0 jest dobrym punktem startowym

            RowLayout {
                anchors.fill: parent
                spacing: 15

                Slider {
                    id: slider
                    Layout.fillWidth: true

                    // Zmieniono zakres suwaka
                    from: -100
                    to: 100
                    stepSize: 1

                    // Łączymy pozycję suwaka ze zmienną
                    value: root.suwak_v

                    // Aktualizujemy 'suwak_v' tylko przy fizycznym przesuwaniu suwaka przez użytkownika.
                    // Zapobiega to nieskończonym pętlom wiązań (binding loops).
                    onMoved: {
                        root.suwak_v = value
                    }
                }

                TextField {
                    id: inputField
                    Layout.preferredWidth: 60
                    Layout.alignment: Qt.AlignVCenter
                    horizontalAlignment: TextInput.AlignHCenter

                    // Ograniczamy wpisywanie z klawiatury tylko do liczb całkowitych od -100 do 100
                    validator: IntValidator { bottom: -100; top: 100 }

                    // Wyświetla aktualny stan zmiennej
                    text: root.suwak_v.toString()

                    // Kiedy użytkownik ręcznie wpisuje cyfry, aktualizujemy zmienną w czasie rzeczywistym
                    onTextEdited: {
                        let parsedValue = parseInt(text)
                        if (!isNaN(parsedValue)) {
                            root.suwak_v = parsedValue
                        }
                    }

                    // Ważne: wpisanie tekstu przerywa deklaratywny "binding" właściwości text.
                    // Poniższy kod przywraca go, gdy użytkownik skończy edycję (np. wciśnie Enter lub kliknie gdzieś indziej).
                    onEditingFinished: {
                        // Zabezpieczenie na wypadek wyczyszczenia pola lub zostawienia samego znaku "-"
                        if (text === "" || text === "-") {
                            root.suwak_v = 0
                        }
                        // Ponowne związanie pola tekstowego z naszą zmienną
                        inputField.text = Qt.binding(() => root.suwak_v.toString())
                    }
                }
            }
        }

    Row{
        spacing: 450
        id: gaugesRow
        anchors.centerIn: parent

        Speedometer{
            speedValue: root.suwak_v
            speedValueText: Math.floor(root.suwak_v * 1.4).toString()
            driveMode: "D"
        }

        Powermeter{
            powerValue: root.suwak_v
            batteryCharge: root.suwak_v / 100
        }
    }


}
