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
    auto rootPack = new Fl_Pack(10, 20, 1270, 700);
    new ConfigPack();
    new DataView();
    rootPack->end();
    end();
}