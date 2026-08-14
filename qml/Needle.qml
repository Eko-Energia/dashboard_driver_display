import QtQuick

Item {
    id: root
    width: parent.width
    height: parent.height

    // Aktualna wartość wejściowa (np. obecna moc w W/kW lub prędkość), która steruje ruchem wskazówki
    property real rotationValue: 0

    // Kąt spoczynkowy wskazówki odpowiadający wartości 0 (środek skali/punkt zerowy)
    property real startAngle: 0

    // Minimalny dopuszczalny kąt wychylenia wskazówki (lewy koniec skali tarczy)
    property real rotationRangeLow: 0

    // Maksymalny dopuszczalny kąt wychylenia wskazówki (prawy koniec skali tarczy)
    property real rotationRangeHigh: 0

    // Minimalna odczytywana wartość logiczna
    property real valueMin: 0

    // Maksymalna odczytywana wartość logiczna
    property real valueMax: 0

    Image {
        id: needle
        source: "qrc:/img/gauges/arrow.png"
        fillMode: Image.PreserveAspectFit
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.bottom: parent.verticalCenter
        transformOrigin: Item.Bottom

        rotation: {
            let calculatedAngle = root.startAngle;

            if (root.rotationValue > 0) {
                if (root.valueMax <= 0) return root.startAngle;
                let fractionRight = root.rotationValue / root.valueMax;
                let rightSpan = root.rotationRangeHigh - root.startAngle;
                calculatedAngle = root.startAngle + (fractionRight * rightSpan);

            } else if (root.rotationValue < 0) {
                if (root.valueMin >= 0) return root.startAngle;
                let fractionLeft = root.rotationValue / root.valueMin;
                let leftSpan = root.startAngle - root.rotationRangeLow;
                calculatedAngle = root.startAngle - (fractionLeft * leftSpan);
            }

            return Math.max(root.rotationRangeLow, Math.min(root.rotationRangeHigh, calculatedAngle));
        }

        Behavior on rotation {
            SmoothedAnimation {
                velocity: 200
            }
        }
    }
}