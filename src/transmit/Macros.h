#pragma once
#include <FL/Fl_Grid.H>
#include <FL/Fl_Pack.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Check_Button.H>
#include <FL/Fl_Native_File_Chooser.H>
#include "Serial.h"
#include "MacroEdit.h"
#include <cstdint>
#include <utility>
#include <fstream>

struct Macro {
    char data[2035]{};
    char name[13]{};
};

class Macros: public Fl_Grid {
    Macro entries[60];
    public:
        Macros();
};
