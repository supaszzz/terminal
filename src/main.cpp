#include <FL/Fl.H>
#include <FL/fl_ask.H>
#include "MainWindow.h"
#include "Serial.h"
#include <filesystem>
#include "paths.h"

int main(int argc, char ** argv) {
    std::filesystem::create_directories(getConfigPath());

    fl_font(FL_HELVETICA, 14);
    Serial.scan();
    mainWindow = new MainWindow();
    mainWindow->show(argc, argv);
    mainWindow->maximize();

    return Fl::run();
}
