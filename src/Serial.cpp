#include "Serial.h"

int SerialClass::connect(std::string port) {
    hSerial = CreateFileA(port.c_str(), GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL);
    if (hSerial == INVALID_HANDLE_VALUE)
        return 1;

    int configErr = config();
    if (configErr)
        return configErr;
    
    connected = true;
    return 0;
}

void SerialClass::reconfig() {
    if (connected)
        handleComError(config());
}

int SerialClass::config() {
    DCB serialParams = {0};
    if (!GetCommState(hSerial, &serialParams)) {
        CloseHandle(hSerial);
        return 2;
    }

    serialParams.BaudRate = baudRate;
    serialParams.ByteSize = dataBits;
    
    switch (stopBits) {
        case STOP_1:
            serialParams.StopBits = ONESTOPBIT;
            break;
        case STOP_1_5:
            serialParams.StopBits = ONE5STOPBITS;
            break;
        case STOP_2:
            serialParams.StopBits = TWOSTOPBITS;
    }

    switch (parityBit) {
        case NONE:
            serialParams.Parity = NOPARITY;
            break;
        case ODD:
            serialParams.Parity = ODDPARITY;
            break;
        case EVEN:
            serialParams.Parity = EVENPARITY;
            break;
        case MARK:
            serialParams.Parity = MARKPARITY;
            break;
        case SPACE:
            serialParams.Parity = SPACEPARITY;
    }

    if (!SetCommState(hSerial, &serialParams)) {
        CloseHandle(hSerial);
        return 3;
    }

    return 0;
}

void SerialClass::disconnect() {
    CloseHandle(hSerial);
    connected = false;
}

unsigned long SerialClass::write(uint8_t* data, size_t len) {
    DWORD bytesWritten;
    WriteFile(hSerial, data, len, &bytesWritten, NULL);
    return bytesWritten;
}

unsigned long SerialClass::read(uint8_t* buffer, size_t len) {
    DWORD bytesRead;
    ReadFile(hSerial, buffer, len, &bytesRead, NULL);
    return bytesRead;
}

unsigned long SerialClass::available() {
    COMSTAT comStat;
    DWORD errors;

    if (ClearCommError(hSerial, &errors, &comStat)) {
        return comStat.cbInQue;
    }

    return 0;
}

unsigned long SerialClass::scan() {
    ports.clear();
    char devices[65536];

    if (!QueryDosDeviceA(NULL, devices, sizeof(devices))) {
        return GetLastError();
    }

    char* ptr = devices;
    while (*ptr) {
        std::string device(ptr);
        if (device.rfind("COM", 0) == 0) {
            ports.push_back(device);
        }
        ptr += device.size() + 1;
    }
    return 0;
}

SerialClass Serial;