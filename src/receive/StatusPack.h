#pragma once
#include <FL/Fl_Pack.H>
#include <FL/Fl_Check_Button.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Native_File_Chooser.H>
#include "Serial.h"
#include "DataView.h"
#include "RecvBytesLabel.h"
#include <ctime>

class StatusPack: public Fl_Pack {
    static const char* labelLogStart;
    static const char* labelLogEnd;
    Fl_Input* searchInput = nullptr;
    Fl_Check_Button* btnCase = nullptr;
    DataView* dataView = nullptr;
    public:
        StatusPack(DataView *dv);
};