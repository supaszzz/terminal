#pragma once
#include <vector>
#include <string>
#include <windows.h>
#include <cstdint>
#include <functional>
#include "errors.h"
#include <FL/Fl.H>
#include "config/PortSelect.h"
#include <cstring>
#include <string>
#include "receive/RecvBytesLabel.h"
#include <fstream>

class PortSelect;

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
        unsigned int customBR = 9600;

        DataBits dataBits = DATA_8;
        StopBits stopBits = STOP_1;
        Parity parityBit = NONE;

        bool sendCR = false;
        bool sendLF = false;
        bool sendLFCR = false;

        bool connected = false;
        std::function<void(unsigned long)> dataCb;
        std::vector<std::string> ports;

        PortSelect* portSelect = nullptr;
        RecvBytesLabel* recvBytesLabel = nullptr;

        int connect(const char* port);
        void disconnect();
        int config();
        void reconfig();
        void writeString(const char* str);
        unsigned long scan();
        unsigned long write(uint8_t* data, size_t len);
        unsigned long read(uint8_t* buffer, size_t len);
        unsigned long available();

        std::ofstream* logFile = nullptr;
        bool startLog(const char* path);
        void stopLog();
};

extern SerialClass Serial;