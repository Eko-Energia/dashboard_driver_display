#include "can.h"
#include <bitset>
deviceInfo matchDevice(can_frame *frame, deviceInfo* devList, size_t devCount){
    for (size_t i = 0; i < devCount ; ++i) {
        if(devList[i].id == frame->can_id) {
            //std::cout << "MATCHDEVICE : Znaleziono urzadzenie o ID: 0x" << std::hex << frame->can_id << std::dec << std::endl; // DEBUG
            return devList[i]; 
        }
    }
    std::cout << "Nie znaleziono urzadzenia o pasujacym ID" << std::endl;
    return deviceInfo{};
}

void extractRawData(can_frame *frame, deviceInfo *devInfo) {
    uint64_t rawData = 0;
    for (uint8_t i = 0; i < devInfo->specs.length && i < (uint8_t)64; ++i) {
        uint8_t bitIndex   = devInfo->specs.startBit + i;      // globalny indeks bitu w ramce
        uint8_t  byteIndex  = bitIndex / (uint8_t)8;
        uint8_t  bitInByte  = bitIndex % (uint8_t)8;             // LSB=0

        uint8_t bitVal = (frame->data[byteIndex] >> (7 - bitInByte)) & 0x1;

        

        rawData |= (uint64_t)bitVal << (devInfo->specs.length - 1 - i);                   
    }
    //std::cout << "EXTRACT_RAW_DATA : Odczytane surowe dane z ramki : " << std::bitset<64>(rawData) << std::endl; // DEBUG
    //std::cout << "HEX: 0x" << std::hex << rawData <<  std::endl; // DEBUG

    devInfo->rawData = rawData;
    return;
        
}

CAN::CAN(const std::string& interface_name){
    can_socket = socket(PF_CAN, SOCK_RAW, CAN_RAW); // Otwarcie socketu

    if (can_socket < 0) {
            perror("Blad przy otwieraniu socketu");
            exit(1);
    }

    strcpy(ifr.ifr_name, interface_name.c_str());

    if (ioctl(can_socket, SIOCGIFINDEX, &ifr) < 0) {
            perror("Blad przy uzyskiwaniu indeksu interfejsu");
            close(can_socket);
            exit(1);
    }

    addr.can_family = AF_CAN;
    addr.can_ifindex = ifr.ifr_ifindex;

    if (bind(can_socket, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
        perror("Blad przy bindingu ");
        close(can_socket);
        exit(1);
    }
}

CAN::~CAN(){
    close(can_socket);
}


deviceInfo CAN::readFrame(){
    can_frame frame{};
    deviceInfo devInfo{};
    uint64_t rawData;

    int nbytes = read(can_socket, &frame, sizeof(can_frame));
    if (nbytes < 0) {
        perror("Blad odczytania ramki CAN");
        return deviceInfo{}; 
    }

    devInfo = matchDevice(&frame, deviceList, deviceCount);
    extractRawData(&frame, &devInfo);
    
    return devInfo;
}

