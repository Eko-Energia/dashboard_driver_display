import QtQuick

Item {
    implicitWidth: lightsRow.implicitWidth
    implicitHeight: lightsRow.implicitHeight

    Row {
        spacing: 53
        id: lightsRow

        property bool isParkOn: {
            system.dataTick;
            let fr = Number(system.values("LightsFR_Status", "day")) || 0;
            let fl = Number(system.values("LightsFL_Status", "day")) || 0;
            let rr = Number(system.values("LightsRR_Status", "positionSide")) || 0;
            let rl = Number(system.values("LightsRL_Status", "positionSide")) || 0;
            return fr || fl || rr || rl;
        }

        property bool isLowBeamsOn: {
            system.dataTick;
            let fr = Number(system.values("LightsFR_Status", "headlights")) || 0;
            let fl = Number(system.values("LightsFL_Status", "headlights")) || 0;
            return fr || fl;
        }

        property bool isHighBeamsOn: {
            system.dataTick;
            let fr = Number(system.values("LightsFR_Status", "highBeams")) || 0;
            let fl = Number(system.values("LightsFL_Status", "highBeams")) || 0;
            return fr || fl;
        }

        property bool isHazardOn: {
            system.dataTick;
            let fr = Number(system.values("LightsFR_Status", "direction")) || 0;
            let fl = Number(system.values("LightsFL_Status", "direction")) || 0;
            let rr = Number(system.values("LightsRR_Status", "direction")) || 0;
            let rl = Number(system.values("LightsRL_Status", "direction")) || 0;
            return fr || fl || rr || rl;
        }


        //park_lights
        Image {
            source : "qrc:/img/lights/park_lights.png"
            width: 72
            height: 50
            opacity: lightsRow.isParkOn ? 1.0 : 0.05
        }

        //low_beams
        Image {
            source : "qrc:/img/lights/low_beams.png"
            width: 50
            height: 50
            opacity: lightsRow.isLowBeamsOn ? 1.0 : 0.05
        }

        //full_beams
        Image {
            source : "qrc:/img/lights/full_beams.png"
            width: 50
            height: 50
            opacity: lightsRow.isHighBeamsOn ? 1.0 : 0.05
        }

        //hazard_lights
        Image {
            source : "qrc:/img/lights/hazard_lights.png"
            width: 50
            height: 50
            opacity: lightsRow.isHazardOn ? 1.0 : 0.05
        }
    }
}