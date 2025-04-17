#include "PortSelect.h"

PortSelect::PortSelect() : Fl_Pack(0, 0, 80, 0, "Port")
{
    dropdown = new Fl_Choice(0, 0, 0, 20);
    updatePorts();
    Serial.portSelect = this;
    end();
}

void PortSelect::updatePorts() {
    dropdown->clear();
    for (std::string port : Serial.ports) {
        dropdown->add(port.c_str());
    }
    dropdown->value(0);
}