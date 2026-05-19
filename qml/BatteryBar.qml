import QtQuick
import QtQuick.Controls
import QtQuick.Shapes
import Qt5Compat.GraphicalEffects

ProgressBar {
    id: root

    from: 0
    to: 100

    // To trzeba zawsze recznie ustawic
    property real chargeValue: 0
    property real startAngle: 0
    property real endAngle: 0

    property real totalSweepAngle: endAngle - startAngle
    // Niby domyslnie jest ustawiony ale mozna edytowac wedle uznania
    property real radius: (root.width / 2) - 16
    property real arcLength: 2 * Math.PI * root.radius * (Math.abs(root.totalSweepAngle) / 360)
    property int barWidth: 10
    property real dashLine: (arcLength * 0.16) / root.barWidth
    property real dashSpace: (arcLength * 0.01) / root.barWidth


    width: 520
    height: 520

    background : Item {}

    contentItem : Item {


        Shape {
            id: chargeBar
            anchors.fill: parent
            layer.enabled: true
            layer.samples: 4
            visible: false

            ShapePath {
                fillColor: "transparent"
                strokeColor: "#DD9117"
                strokeWidth: root.barWidth
                capStyle: ShapePath.FlatCap

                strokeStyle: ShapePath.DashLine
                dashPattern: [root.dashLine,root.dashSpace]

                PathAngleArc {
                    centerX: root.width / 2
                    centerY: root.height / 2
                    radiusX: root.radius
                    radiusY: root.radius

                    startAngle: root.startAngle

                    sweepAngle: {
                        let visualProgress = Math.max(0.01, Math.min(1.0, root.chargeValue));
                        return visualProgress * root.totalSweepAngle;
                    }
                }
            }
        }

        Glow {
            anchors.fill: chargeBar
            radius: 6
            samples: 13
            color: "#DD9117"
            source: chargeBar
            spread: 0.2
        }
    }
}