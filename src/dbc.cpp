#include "dbc.h"

/*
struct deviceSpecs {
    uint8_t startBit;   // bit początkowy sygnału w ramce
    uint8_t length;     // długość sygnału w bitach
    float factor;       // mnożnik (scale)
    float offset;       // offset
    std::string dataType; // Typ danych (np. "uint", "int", "float", "double")
};


struct deviceInfo {<
    uint32_t id;        // CAN ID
    deviceSpecs specs; 
    uint64_t rawData; // Ostatnio odczytane surowe dane
    
};*/

deviceInfo deviceList[] = {
    {0x10, {0, 8, 1, 0.0,"uint"} , 0},// Battery 0 - 100
    {0x01, {0, 8, 1, 0.0,"int8_t"} , 0},// Temperature -80 - 80 I guess
    {0x02, {0, 16, 1, 0.0,"uint"} , 0},// Mileage 0 - 65535 km, perla raczej nie zrobi wiecej
    {0x03, {0, 8, 1, 0.0,"uint"} , 0},// Speedometer 0 - 255
    {0x04, {0, 8, 1, 0.0,"char"} , 0},// Drivemode, narazie podawane poprostu jako literki w hex, nwm jak to bedzie dzialac z reszta auta
    {0x05, {0, 8, 1, 0.0,"int8_t"} , 0},// Engine power -10 <> 20 plus minus
    {0x06, {0, 1, 1, 0.0,"bool"} , 0},// Low beam
    {0x07, {0, 1, 1, 0.0,"bool"} , 0},// High beam
    {0x08, {0, 1, 1, 0.0,"bool"} , 0},// Parking lights
    {0x09, {0, 1, 1, 0.0,"bool"} , 0},// Hazard lights
    {0x0A, {0, 1, 1, 0.0,"bool"} , 0},// Right blinker
    {0x0B, {0, 1, 1, 0.0,"bool"} , 0},// Left blinker
    {0x0C, {0, 1, 1, 0.0,"bool"} , 0},// High temperature
    {0x0D, {0, 1, 1, 0.0,"bool"} , 0},// Engine failure
    {0x0E, {0, 1, 1, 0.0,"bool"} , 0},// Power failure
    {0x0F, {0, 1, 1, 0.0,"bool"} , 0},// Cruise control
    
    
};
const size_t deviceCount = sizeof(deviceList) / sizeof(deviceList[0]);

