#pragma once
#include <FL/Fl_Text_Display.H>
#include <FL/Fl_Text_Buffer.H>
#include "Serial.h"
#include <vector>
#include <cstdint>
#include <cstring>

class DataView : public Fl_Text_Display {
    Fl_Text_Buffer* dataBuffer = nullptr;
    bool hexEnabled = false;
    char byteCounter = 0;
    std::vector<char> dataCopy;
    void appendHex(uint8_t* str, unsigned long len);
    public:
        DataView();
        void findNext(const char* str, bool matchCase, bool backward = false);
        void setHex(bool enabled);
        void clear();
};