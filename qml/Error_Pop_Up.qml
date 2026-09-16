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
        function onErrorReceived(frame, code, name) {
            root.addError(frame, code, name)
        }
        function onSnapshotErrorsReceived(count) {
            root.addSnapshotSummary(count)
        }
    }

    // Nazwa wezla bez technicznego sufiksu ramki bledu (_NODE/_EMCY, patrz ERROR_SUFFIXES
    // w rpi_utilities/config.py) - kierowca czyta "MPPT", nie "MPPT_NODE".
    function nodeLabel(frame) {
        return String(frame).replace(/_(NODE|EMCY)$/, "")
    }

    function pluralUsterki(count) {
        if (count === 1)
            return "usterka"
        var lastTwo = count % 100
        var last = count % 10
        if (last >= 2 && last <= 4 && (lastTwo < 12 || lastTwo > 14))
            return "usterki"
        return "usterek"
    }

    // Jeden wiersz na klucz. rpi_utilities nie wysylaja "blad ustapil" (kod 0 jest
    // pomijany), wiec ta sama usterka potrafi wrocic po reconnectcie - bez tego
    // zajelaby kolejny wiersz zamiast odswiezyc istniejacy.
    function pushRow(key, message) {
        var expiresAt = Date.now() + root.errorLifetimeMs

        for (var i = 0; i < errorListModel.count; ++i) {
            if (errorListModel.get(i).key === key) {
                errorListModel.set(i, { key: key, message: message, expiresAt: expiresAt })
                return
            }
        }

        while (errorListModel.count >= maxVisibleErrors) {
            errorListModel.remove(0) // brak miejsca -> najstarszy blad znika
        }
        errorListModel.append({ key: key, message: message, expiresAt: expiresAt })
    }

    function addError(frame, code, name) {
        var label = root.nodeLabel(frame)
        var description = name.length > 0 ? name : "kod " + Math.round(code)
        root.pushRow("frame:" + frame,
                     label.length > 0 ? label + ": " + description
                                      : "Błąd " + Math.round(code) + ": " + description)
    }

    // Paczka bledow ze snapshotu po polaczeniu - zwinieta do jednego wiersza przez
    // TelemetryWebSocketClient, zeby komplet zapamietanych usterek nie wypchnal
    // z popupu tego, co dzieje sie teraz.
    function addSnapshotSummary(count) {
        root.pushRow("snapshot", "Stan poprzedni: " + count + " " + root.pluralUsterki(count))
    }

    // Wygaszanie liczone centralnie, po znaczniku czasu wpisu. Timer w delegacie kasowal
    // po swoim `index`, ktory przesuwa sie przy usunieciu wczesniejszego wiersza - potrafil
    // wiec zabrac nie ten blad, co trzeba. Iterujemy od konca, zeby indeksy nie uciekaly.
    Timer {
        interval: 1000
        running: errorListModel.count > 0
        repeat: true
        onTriggered: {
            var now = Date.now()
            for (var i = errorListModel.count - 1; i >= 0; --i) {
                if (errorListModel.get(i).expiresAt <= now) {
                    errorListModel.remove(i)
                }
            }
        }
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
                text: model.message
                color: "#FFFFFF"
                font.pixelSize: 16
                font.family: oxaniumSemiBold.name
            }
        }
    }
}
