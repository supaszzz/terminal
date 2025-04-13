#include "MainWindow.h"

const char* labelText;
MainWindow* mainWindow = nullptr;

void radio_cb(Fl_Widget* w) {
    labelText = w->label();
} 

MainWindow::MainWindow()
: Fl_Window(1280, 720, "Terminal")
{
    resizable(this);
    new ConfigPack();
    end();
}