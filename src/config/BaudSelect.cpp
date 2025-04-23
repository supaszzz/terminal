#include "BaudSelect.h"
using namespace std;

const unsigned int BaudSelect::defaultBauds[] = {
    600, 1200, 2400, 4800, 9600, 14400, 19200, 28800, 38400, 56000, 57600, 115200, 128000, 256000
};

BaudSelect::BaudSelect() : Fl_Grid(0, 0, 230, 0)
{
    box(FL_ENGRAVED_BOX);
    label("Baud rate");

    layout(5, 3, 5);
    for (int i = 0; i != (sizeof(defaultBauds) / sizeof(unsigned int)); i++) {
        auto btn = new Fl_Round_Button(0, 0, 0, 0);
        btn->copy_label(to_string(defaultBauds[i]).c_str());
        btn->type(FL_RADIO_BUTTON);

        btn->callback([](Fl_Widget* btn, void* data) {
            Serial.baudRate = *((unsigned int*)data);
            Serial.reconfig();
            Serial.useCustomBR = false;
        }, (void*)&defaultBauds[i]);

        if (defaultBauds[i] == 9600)
            btn->value(1);

        widget(btn, i % 5, i / 5);
    }

    auto btnCustom = new Fl_Round_Button(0, 0, 0, 0, "ręcznie");
    btnCustom->type(FL_RADIO_BUTTON);
    btnCustom->callback([](Fl_Widget*) {
        Serial.baudRate = Serial.customBR;
        Serial.reconfig();
        Serial.useCustomBR = true;
    });
    widget(btnCustom, 4, 2);

    show_grid(0);

    end();
}