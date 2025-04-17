#include "ButtonPack.h"

ButtonPack::ButtonPack()
: Fl_Pack(0, 0, 100, 100)
{
    box(FL_SHADOW_FRAME);
    begin();

    btnConnect = new Fl_Button(0, 0, 100, 20, "Połącz");
    btnConnect->callback([](Fl_Widget* w) {
        if (Serial.connected) {
            Serial.disconnect();
            w->label("Połącz");
            return;
        }
        int err = Serial.connect(Serial.portSelect->dropdown->text());
        if (err)
            return handleComError(err);
        w->label("Rozłącz");
    });

    auto btnScan = new Fl_Button(0, 0, 100, 20, "Skanuj");
    btnScan->callback([](Fl_Widget* w) {
        Serial.scan();
    });

    end();
}