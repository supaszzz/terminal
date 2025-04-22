#pragma once
#include <FL/Fl_Window.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Input.H>
#include <FL/fl_ask.H>
#include <FL/Fl_Pack.H>
#include <FL/Fl_Grid.H>
#include "Macros.h"
#include <cstring>

struct Macro;

class MacroEdit: public Fl_Window {
    Macro* macro;
    Fl_Widget* macroBtn;
    Fl_Input* nameInput;
    Fl_Input* dataInput;
    public:
        MacroEdit(Macro* m, Fl_Widget* mBtn);
};