#pragma once
#include <FL/Fl_Window.H>
#include <FL/Fl_Round_Button.H>
#include <FL/Fl_Pack.H>
#include <FL/fl_ask.H>
#include "config/ConfigPack.h"
#include "receive/DataView.h"

class MainWindow: public Fl_Window {
    public:
        MainWindow();
};

extern MainWindow* mainWindow;