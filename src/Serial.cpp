#include "Serial.h"

SerialClass Serial;

void onData(int fd, void* data) {
    Serial.dataCb(Serial.available());
}

void lenncat(char* dest, size_t& destLen, const char* src, size_t srcLen) {
    strncpy(dest + destLen, src, srcLen);
    destLen += srcLen;
}

void lencat(char* dest, size_t& destLen, const char* src) {
    strcpy(dest + destLen, src);
    destLen += strlen(src);
}

void SerialClass::writeString(const char* str) {
    char* result = new char[strlen(str) + 3];
    size_t length = 0;
    unsigned char hexChar;
    while (const char* next = strchr(str, '$')) {
        lenncat(result, length, str, next++ - str);
        if (*next == '$') {
            lenncat(result, length, next, 1);
            str = next + 1;
        } else {
            sscanf(next, "%02hhx", &hexChar);
            lenncat(result, length, (char*)&hexChar, 1);
            str = next + 2;
        }
    }
    lencat(result, length, str);
    if (!sendLFCR && sendCR)
        lencat(result, length, "\r");
    if (sendLF)
        lencat(result, length, "\n");
    if (sendLFCR && sendCR)
        lencat(result, length, "\r");
    write((uint8_t*)result, length);
    delete[] result;
}

int SerialClass::connect(const char* port) {
#ifdef _WIN32
    hSerial = CreateFileA(port, GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL);
    if (hSerial == INVALID_HANDLE_VALUE)
        return 1;
#else
    hSerial = open(port, O_RDWR | O_NOCTTY | O_NONBLOCK);
    if (hSerial < 0)
        return 1;
#endif
    int configErr = config();
    if (configErr)
        return configErr;

    connected = true;
    Fl::add_fd((intptr_t)hSerial, FL_READ, onData, nullptr);
    portSelect->dropdown->deactivate();
    if (connectButton)
        connectButton->label("Rozłącz");
    return 0;
}

void SerialClass::reconfig() {
    if (connected) {
        int err = config();
        if (err) {
            disconnect();
            handleComError(err);
        }
    }
}

int SerialClass::config() {
#ifdef _WIN32
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
#else
    struct termios2 serialParams;
    if (ioctl(hSerial, TCGETS2, &serialParams) < 0) {
        close(hSerial);
        return 2;
    }

    serialParams.c_ispeed = baudRate;
    serialParams.c_ospeed = baudRate;
    serialParams.c_oflag = 0;
    serialParams.c_iflag = 0;
    serialParams.c_lflag = 0;
    serialParams.c_cflag = CREAD | CLOCAL | CBAUDEX;

    switch (parityBit) {
        case ODD:
            serialParams.c_cflag |= PARODD;
        case EVEN:
            serialParams.c_cflag |= PARENB;
            break;
        case MARK:
        case SPACE:
            close(hSerial);
            return 4;
    }

    switch (stopBits) {
        case STOP_1_5:
            close(hSerial);
            return 5;
        case STOP_2:
            serialParams.c_cflag |= CSTOPB;
    }

    switch (dataBits) {
        case DATA_5:
            serialParams.c_cflag |= CS5;
            break;
        case DATA_6:
            serialParams.c_cflag |= CS6;
            break;
        case DATA_7:
            serialParams.c_cflag |= CS7;
            break;
        case DATA_8:
            serialParams.c_cflag |= CS8;
    }

    serialParams.c_cc[VMIN] = 1;
    serialParams.c_cc[VTIME] = 0;

    if (ioctl(hSerial, TCSETS2, &serialParams) < 0) {
        close(hSerial);
        return 3;
    }
#endif
    return 0;
}

void SerialClass::disconnect() {
    if (!connected)
        return;
    Fl::remove_fd((intptr_t)hSerial);
#ifdef _WIN32
    CloseHandle(hSerial);
#else
    close(hSerial);
#endif
    connected = false;
    portSelect->dropdown->activate();
    if (connectButton)
        connectButton->label("Połącz");
}

unsigned long SerialClass::write(uint8_t* data, size_t len) {
    if (!connected)
        return 0;
#ifdef _WIN32
    DWORD bytesWritten;
    WriteFile(hSerial, data, len, &bytesWritten, NULL);
    return bytesWritten;
#else
    return ::write(hSerial, data, len);
#endif
}

unsigned long SerialClass::read(uint8_t* buffer, size_t len) {
    if (!connected)
        return 0;
#ifdef _WIN32
    DWORD bytesRead;
    ReadFile(hSerial, buffer, len, &bytesRead, NULL);
#else
    ssize_t bytesRead = ::read(hSerial, buffer, len);
#endif
    if (recvBytesLabel)
        recvBytesLabel->update(bytesRead);
    if (logFile)
        logFile->write((char*)buffer, bytesRead);
    return bytesRead;
}

unsigned long SerialClass::available() {
    if (!connected)
        return 0;
#ifdef _WIN32
    COMSTAT comStat;
    DWORD errors;

    if (ClearCommError(hSerial, &errors, &comStat)) {
        return comStat.cbInQue;
    }

    return 0;
#else
    int bytes;
    if (ioctl(hSerial, FIONREAD, &bytes) == -1)
        return 0;
    return bytes;
#endif
}

unsigned long SerialClass::scan() {
    disconnect();
    ports.clear();
#ifdef _WIN32
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
#else
    static const std::string prefixes[] = {
        "/dev/ttyS", "/dev/ttyUSB", "/dev/ttyACM"
    };

    for (auto& prefix : prefixes) {
        for (int i = 0; i != 32; i++) {
            std::string device = prefix + std::to_string(i);
            if (access(device.c_str(), F_OK) != -1)
                ports.push_back(device);
        }
    }
#endif
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