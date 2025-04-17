#pragma once
#include <FL/Fl_Grid.H>
#include <FL/Fl_Round_Button.H>
#include "Serial.h"
#include <string>
#include <utility>

template<typename T>
class ParamSelect: public Fl_Grid {
    T* property = nullptr;
    protected:
        void entry(const char* label, T value, bool selected = false) {
            auto btn = new Fl_Round_Button(0, 0, 0, 20, label);
            btn->type(FL_RADIO_BUTTON);
            if (selected)
                btn->value(1);
            
            auto p = new std::pair<T*, T>(property, value);
            btn->callback([](Fl_Widget*, void* data) {
                auto* p = reinterpret_cast<std::pair<T*, T>*>(data);
                p->first[0] = p->second;
                Serial.reconfig();
            }, (void*)p);

            static int row = 0;
            widget(btn, row, 0);
            row++;
        }
    public:
        ParamSelect(const char* label, T* property, int rows) : Fl_Grid(0, 0, 100, 0, label) {
            box(FL_ENGRAVED_BOX);
            layout(rows, 1);
            this->property = property;
        }
};