#include "BaudSelect.h"
using namespace std;

const unsigned int defaultBauds[] = {
    600, 1200, 2400, 4800, 9600, 14400, 19200, 28800, 38400, 56000, 57600, 115200, 128000, 256000
};

BaudSelect::BaudSelect() : Fl_Grid(0, 0, 200, 0)
{
    box(FL_BORDER_BOX);
    label("Baud rate");

    layout(5, 3);
    for (int i = 0; i != (sizeof(defaultBauds) / sizeof(unsigned int)); i++) {
        auto btn = new Fl_Round_Button(0, 0, 0, 0);
        btn->copy_label(to_string(defaultBauds[i]).c_str());
        btn->type(FL_RADIO_BUTTON);

        btn->callback([](Fl_Widget* btn, void* data) {
            Serial.baudRate = *((unsigned int*)data);
            Serial.reconfig();
        }, (void*)&defaultBauds[i]);

        widget(btn, i % 5, i / 5);
    }

    auto btnCustom = new Fl_Round_Button(0, 0, 0, 0, "ręcznie");
    btnCustom->type(FL_RADIO_BUTTON);
    widget(btnCustom, 4, 2);

    show_grid(0);

    end();
}