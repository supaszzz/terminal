#include "PortSelect.h"

PortSelect::PortSelect() : Fl_Pack(0, 0, 160, 0, "Port")
{
    spacing(8);
    dropdown = new Fl_Choice(0, 0, 0, 20);
    updatePorts();
    Serial.portSelect = this;

    new Fl_Box(0, 0, 0, 20, "Ręczny baud rate");
    auto customBR = new Fl_Input(0, 0, 0, 20);
    customBR->value("9600");
    customBR->when(FL_WHEN_CHANGED);
    customBR->callback([](Fl_Widget* w) {
        auto input = (Fl_Input*)w;
        auto value = atoi(input->value());
        if (value)
            Serial.baudRate = value;
        char baudStr[24] = {0};
        snprintf(baudStr, 24, "%d", Serial.baudRate);
        input->value(baudStr);
    });
    end();
}

void PortSelect::updatePorts() {
    dropdown->clear();
    for (std::string port : Serial.ports) {
        dropdown->add(port.c_str());
    }
    dropdown->value(0);
}