#pragma once
#include <FL/Fl_Grid.H>
#include <FL/Fl_Round_Button.H>
#include <FL/fl_ask.H>
#include <string>
#include "Serial.h"
#include "errors.h"

class BaudSelect: public Fl_Grid {
    public:
        BaudSelect();
};