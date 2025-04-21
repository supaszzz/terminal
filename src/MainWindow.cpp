#include "MainWindow.h"

const char* labelText;
MainWindow* mainWindow = nullptr;

void radio_cb(Fl_Widget* w) {
    labelText = w->label();
} 

MainWindow::MainWindow()
: Fl_Window(1280, 720, "Terminal")
{
    auto rootPack = new Fl_Pack(10, 20, 1260, 680);
    rootPack->spacing(10);
    new ConfigPack();
    new SendView();
    auto dataView = new DataView();
    new StatusPack(dataView);
    rootPack->end();
    end();

    resizable(rootPack);
    size_range(1280, 720);
}