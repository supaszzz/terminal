#include <FL/Fl.H>
#include <FL/fl_ask.H>
#include "MainWindow.h"
#include "Serial.h"

int main(int argc, char ** argv) {
    Serial.scan();
    mainWindow = new MainWindow();
    mainWindow->show(argc, argv);
    mainWindow->maximize();

    return Fl::run();
}
