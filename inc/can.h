#ifndef CAN_H
#define CAN_H

#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <unistd.h>
#include <sys/ioctl.h>
#include <net/if.h>
#include <sys/socket.h>
#include <linux/can.h>
#include <linux/can/raw.h>
#include <string>
#include <iostream>
#include "dbc.h"

class CAN{
    public:
        CAN(const std::string& interface_name = "vcan0");
        ~CAN();

        deviceInfo readFrame(); // Zwraca surowe dane z ramki CAN
        

    private:
        int can_socket;
        sockaddr_can addr{};
        ifreq ifr{};
};


deviceInfo matchDevice(can_frame *frame, deviceInfo* devList, size_t devCount);
void extractRawData(can_frame *frame, deviceInfo *devInfo);
    

#endif // CAN_H