#pragma once
#include <FL/Fl_Pack.H>
#include <FL/Fl_Button.H>
#include "Serial.h"
#include "errors.h"

class ButtonPack: public Fl_Pack {
    Fl_Button* btnConnect;
    public:
        void updateConnectionStatus();
        ButtonPack();
};