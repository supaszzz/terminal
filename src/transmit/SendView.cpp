#include "SendView.h"

SendView::SendView() : Fl_Pack(0, 0, 0, 50) {
    type(Fl_Pack::HORIZONTAL);
    spacing(15);

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

    end();
}