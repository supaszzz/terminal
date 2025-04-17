#pragma once
#include <FL/Fl_Grid.H>
#include <FL/Fl_Round_Button.H>
#include <FL/fl_ask.H>
#include <string>
#include "Serial.h"

class BaudSelect: public Fl_Grid {
    Fl_Round_Button* selectedBtn = nullptr;
    static const unsigned int defaultBauds[];
    public:
        BaudSelect();
};