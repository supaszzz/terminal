#pragma once
#include <FL/Fl_Text_Display.H>
#include <FL/Fl_Text_Buffer.H>
#include "Serial.h"
#include <vector>
#include <cstdint>

class DataView : public Fl_Text_Display {
    Fl_Text_Buffer* dataBuffer = nullptr;
    public:
        DataView();
};