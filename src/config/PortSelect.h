#pragma once
#include <FL/Fl_Pack.H>
#include <FL/Fl_Choice.H>
#include <FL/Fl_Box.H>
#include <string>
#include "Serial.h"

class PortSelect: public Fl_Pack {
    public:
        PortSelect();
        void updatePorts();
        Fl_Choice* dropdown = nullptr;
};