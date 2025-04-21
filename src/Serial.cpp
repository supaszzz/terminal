#include "Serial.h"

SerialClass Serial;

void onData(int fd, void* data) {
    Serial.dataCb(Serial.available());
}

void SerialClass::writeString(const char* str) {
    char* result = new char[strlen(str) + 3];
    result[0] = 0;
    unsigned char hexChar;
    while (const char* next = strchr(str, '$')) {
        strncat(result, str, next++ - str);
        if (*next == '$') {
            strncat(result, next, 1);
            str = next + 1;
        } else {
            sscanf(next, "%02hhx", &hexChar);
            strncat(result, (char*)&hexChar, 1);
            str = next + 2;
        }
    }
    strcat(result, str);
    if (!sendLFCR && sendCR)
        strcat(result, "\r");
    if (sendLF)
        strcat(result, "\n");
    if (sendLFCR && sendCR)
        strcat(result, "\r");
    write((uint8_t*)result, strlen(result));
    delete[] result;
}

int SerialClass::connect(const char* port) {
    hSerial = CreateFileA(port, GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL);
    if (hSerial == INVALID_HANDLE_VALUE)
        return 1;

    int configErr = config();
    if (configErr)
        return configErr;

    connected = true;
    Fl::add_fd((intptr_t)hSerial, FL_READ, onData, nullptr);
    portSelect->dropdown->deactivate();
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
    serialParams.fOutxCtsFlow = FALSE;
    serialParams.fRtsControl = RTS_CONTROL_DISABLE;
    serialParams.fInX = FALSE;
    serialParams.fOutX = FALSE;
    
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
    if (!connected)
        return;
    CloseHandle(hSerial);
    connected = false;
    portSelect->dropdown->activate();
}

unsigned long SerialClass::write(uint8_t* data, size_t len) {
    if (!connected)
        return 0;
    DWORD bytesWritten;
    WriteFile(hSerial, data, len, &bytesWritten, NULL);
    return bytesWritten;
}

unsigned long SerialClass::read(uint8_t* buffer, size_t len) {
    if (!connected)
        return 0;
    DWORD bytesRead;
    ReadFile(hSerial, buffer, len, &bytesRead, NULL);
    if (recvBytesLabel)
        recvBytesLabel->update(bytesRead);
    if (logFile)
        logFile->write((char*)buffer, bytesRead);
    return bytesRead;
}

unsigned long SerialClass::available() {
    if (!connected)
        return 0;
    COMSTAT comStat;
    DWORD errors;

    if (ClearCommError(hSerial, &errors, &comStat)) {
        return comStat.cbInQue;
    }

    return 0;
}

unsigned long SerialClass::scan() {
    disconnect();
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
    if (portSelect)
        portSelect->updatePorts();
    return 0;
}

bool SerialClass::startLog(const char* path) {
    if (logFile)
        stopLog();
    logFile = new std::ofstream(path, std::ios::app | std::ios::binary);
    if (!(*logFile)) {
        logFile = nullptr;
        return false;
    }
    return true;
}

void SerialClass::stopLog() {
    if (logFile) {
        logFile->close();
        logFile = nullptr;
    }
}