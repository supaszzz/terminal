#include "SendView.h"

SendView::SendView() : Fl_Pack(0, 0, 0, 25) {
    type(Fl_Pack::HORIZONTAL);
    spacing(15);

    new Fl_Box(0, 0, 70, 0, "Polecenie:");

    auto input = new Fl_Input(0, 0, 720, 0);

    input->when(FL_WHEN_ENTER_KEY_ALWAYS);
    input->callback([](Fl_Widget* w) {
        auto input = (Fl_Input*)w;
        Serial.writeString(input->value());
        input->insert_position(input->size());
    });

    auto button = new Fl_Button(0, 0, 50, 0, "Wyślij");
    button->callback([](Fl_Widget* w, void* data) {
        auto input = (Fl_Input*)data;
        Serial.writeString(input->value());
        input->insert_position(input->size());
    }, (void*)input);

    auto crButton = new Fl_Check_Button(0, 0, 80, 0, "Dodaj CR");
    auto lfButton = new Fl_Check_Button(0, 0, 80, 0, "Dodaj LF");
    auto lfcrButton = new Fl_Check_Button(0, 0, 125, 0, "Zamień CR Z LF");

    crButton->callback([](Fl_Widget* w) {
        auto btn = (Fl_Check_Button*)w;
        Serial.sendCR = btn->value();
    });
    lfButton->callback([](Fl_Widget* w) {
        auto btn = (Fl_Check_Button*)w;
        Serial.sendLF = btn->value();
    });
    lfcrButton->callback([](Fl_Widget* w) {
        auto btn = (Fl_Check_Button*)w;
        Serial.sendLFCR = btn->value();
    });

    

    end();
}