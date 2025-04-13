#pragma once
#include <vector>
#include <string>
#include <windows.h>
#include <cstdint>
#include "errors.h"

enum DataBits {
    DATA_5 = 5,
    DATA_6,
    DATA_7,
    DATA_8
};

enum StopBits {
    STOP_1,
    STOP_1_5,
    STOP_2
};

enum Parity {
    NONE,
    ODD,
    EVEN,
    MARK,
    SPACE
};

class SerialClass {
    HANDLE hSerial;
    public:
        unsigned int baudRate = 9600;
        DataBits dataBits = DATA_8;
        StopBits stopBits = STOP_1;
        Parity parityBit = NONE;
        bool connected = false;

        std::vector<std::string> ports;

        int connect(std::string port);
        void disconnect();
        int config();
        void reconfig();
        unsigned long scan();
        unsigned long write(uint8_t* data, size_t len);
        unsigned long read(uint8_t* buffer, size_t len);
        unsigned long available();
};

extern SerialClass Serial;