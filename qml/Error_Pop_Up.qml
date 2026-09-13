import QtQuick

Item {
    id: root

    // Niewidoczny dopoki nie ma zadnego aktywnego bledu
    visible: errorListModel.count > 0

    readonly property int rowSpacing: 6
    readonly property int rowHeight: 22
    readonly property int errorLifetimeMs: 60000 // czas po ktorym blad znika samoistnie

    // Ile wpisow zmiesci sie w dostepnej przestrzeni popupu, zeby lista
    // nigdy nie wychodzila poza element
    readonly property int maxVisibleErrors: Math.max(1, Math.floor((errorColumn.height + rowSpacing) / (rowHeight + rowSpacing)))

    FontLoader {
        id: oxaniumSemiBold
        source: "qrc:/fonts/Oxanium-SemiBold.ttf"
    }

    ListModel {
        id: errorListModel
    }

    Connections {
        target: system
        function onErrorReceived(code, name) {
            root.addError(code, name)
        }
    }

    function addError(code, name) {
        while (errorListModel.count >= maxVisibleErrors) {
            errorListModel.remove(0) // brak miejsca -> najstarszy blad znika
        }
        errorListModel.append({ code: code, name: name })
    }

    Image {
        source: "qrc:/img/error_pop_up.png"
        anchors.fill: parent
    }

    Text {
        id: error_pop_up_title
        anchors.horizontalCenter: parent.horizontalCenter
        y: 12
        text: "Wykryto błędy"
        color: "#FFFFFF"
        font.pixelSize: 24
        font.family: oxaniumSemiBold.name
    }

    Column {
        id: errorColumn
        x: 24
        anchors.top: error_pop_up_title.bottom
        anchors.topMargin: 10
        width: parent.width - 48
        height: parent.height - y - 12
        spacing: root.rowSpacing
        clip: true

        Repeater {
            model: errorListModel

            delegate: Text {
                width: errorColumn.width
                height: root.rowHeight
                verticalAlignment: Text.AlignVCenter
                elide: Text.ElideRight
                text: "Błąd " + Math.round(code) + ": " + name
                color: "#FFFFFF"
                font.pixelSize: 16
                font.family: oxaniumSemiBold.name

                Timer {
                    interval: root.errorLifetimeMs
                    running: true
                    repeat: false
                    onTriggered: errorListModel.remove(index) // blad znika samoistnie po czasie
                }
            }
        }
    }
}
