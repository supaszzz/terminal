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
    auto rootPack = new Fl_Pack(10, 20, 1260, 680);
    rootPack->spacing(20);
    new ConfigPack();
    new SendView();
    new DataView();
    rootPack->end();
    end();
}