import QtQuick


Item {

   implicitWidth: lightsRow.implicitWidth

   implicitHeight: lightsRow.implicitHeight


   Row {

       spacing: 53

       id: lightsRow


       property bool isParkOn: {

           system.dataTick;

           Number(system.values("Dashboard_Lights", "Headlights")) === 1 || Number(system.values("Dashboard_Lights", "Headlights")) === 2;

       }


       property bool isLowBeamsOn: {

           system.dataTick;

           Number(system.values("Dashboard_Lights","Headlights")) === 3;

       }


       property bool isHighBeamsOn: {

           system.dataTick;

           Number(system.values("Dashboard_Lights","Headlights")) === 4;

       }


       property bool isHazardOn: {

           system.dataTick;

           Number(system.values("Dashboard_Lights","Emergency")) === 1;

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