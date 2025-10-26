#ifndef SYSTEM_H
#define SYSTEM_H

#include "can.h"  
#include <string>                    
#include <QQmlApplicationEngine>                        
#include "clock.h"                  
#include "valueinfo.h"                
#include "blinker.h"     

class System {
    public:

    System(QQmlApplicationEngine* engine, const std::string &bus_name = "can0");
    void start();
    void stop() {run_ = false;}

    CAN can;
    Clock clock;
    ValueInfo battery;
    ValueInfo temperature;
    ValueInfo mileage;
    ValueInfo speedometer;
    ValueInfo drivemode;
    ValueInfo engine_power;
    ValueInfo low_beam;
    ValueInfo high_beam;
    ValueInfo parking_lights;
    ValueInfo hazard_lights;
    Blinker blinkerRight;
    Blinker blinkerLeft;
    ValueInfo high_temperature;
    //ValueInfo open_door; Narazie nie uzywamy
    ValueInfo engine_failure;
    ValueInfo power_failure;
    ValueInfo cruise_control;

    private:
    bool run_;
};

double decodeRawData(uint64_t rawData, const deviceInfo& sig);
void passToSystem(deviceInfo *devInfo, System* system);



#endif // SYSTEM_H