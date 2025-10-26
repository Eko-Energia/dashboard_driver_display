#ifndef DBC_H
#define DBC_H

#include <cstdint>
#include <cstddef> 
#include <string>
struct deviceSpecs {
    uint8_t startBit;   // bit początkowy sygnału w ramce
    uint8_t length;     // długość sygnału w bitach
    float factor;       // mnożnik (scale)
    float offset;       // offset
    std::string dataType; // Typ danych (np. "uint", "int", "float", "double")
};


struct deviceInfo {
    uint32_t id;        // CAN ID
    deviceSpecs specs; 
    uint64_t rawData; // Ostatnio odczytane surowe dane
    
};

extern deviceInfo deviceList[];
extern const size_t deviceCount;

#endif // DBC_H

/*
{
    Temperature

    CAN ID: 0x77
    startbit: 2
    length: 6
    factor: 1.5
    offset: 0.0

}*/