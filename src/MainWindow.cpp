#include "MainWindow.h"

const char* labelText;
MainWindow* mainWindow = nullptr;

void radio_cb(Fl_Widget* w) {
    labelText = w->label();
} 

MainWindow::MainWindow()
: Fl_Window(1366, 960, "Terminal")
{
    auto rootPack = new Fl_Pack(10, 20, 1346, 940);
    rootPack->spacing(10);
    new ConfigPack();
    new Fl_Box(0, 0, 0, 20, "Makra");
    new Macros();
    new SendView();
    auto dataView = new DataView();
    new StatusPack(dataView);
    rootPack->end();
    end();

    resizable(rootPack);
    size_range(1366, 960);
}