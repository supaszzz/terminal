#include "StatusPack.h"

const char* StatusPack::labelLogStart = "Start log";
const char* StatusPack::labelLogEnd = "Stop log";

StatusPack::StatusPack(DataView* dv) : Fl_Pack(0, 0, 0, 25) {
    type(Fl_Pack::HORIZONTAL);
    spacing(5);
    auto clearButton = new Fl_Button(0, 0, 80, 0, "Wyczyść"); //naprawić
    clearButton->callback([](Fl_Widget*, void* data) {
        auto dv = (DataView*)data;
        dv->clear();
        Serial.recvBytesLabel->clear();
    }, (void*)dv);

    auto logButton = new Fl_Button(0, 0, 80, 0);
    logButton->label(labelLogStart);
    logButton->callback([](Fl_Widget* w) {
        if (Serial.logFile) {
            Serial.stopLog();
            w->label(StatusPack::labelLogStart);
            return;
        }
        Fl_Native_File_Chooser fc;
        fc.title("Zapisz log jako");
        fc.type(Fl_Native_File_Chooser::BROWSE_SAVE_FILE);
        fc.filter("*.log");

        time_t now = time(NULL);
        char name[512];
        snprintf(name, 512, "log_%lld.log", now);
        fc.preset_file(name);

        if (fc.show() == 0) {
            if (Serial.startLog(fc.filename())) {
                w->label(StatusPack::labelLogEnd);
            } else {
                fl_message("Nie udało się zapisać pliku");
            }
        }
    });

    new Fl_Box(0, 0, 50, 0);
    new Fl_Box(0, 0, 75, 0, "Wyszukaj:");
    searchInput = new Fl_Input(0, 0, 180, 0);
    auto btnPrev = new Fl_Button(0, 0, 80, 0, "Poprzedni");
    auto btnNext = new Fl_Button(0, 0, 80, 0, "Następny");
    btnCase = new Fl_Check_Button(0, 0, 200, 0, "Znacząca wielkość liter");
    dataView = dv;

    auto nextFn = [](Fl_Widget*, void* data) {
        auto self = (StatusPack*)data;
        self->dataView->findNext(self->searchInput->value(), self->btnCase->value());
    };

    searchInput->when(FL_WHEN_ENTER_KEY_ALWAYS);
    searchInput->callback(nextFn, this);

    btnNext->callback(nextFn, this);

    btnPrev->callback([](Fl_Widget*, void* data) {
        auto self = (StatusPack*)data;
        self->dataView->findNext(self->searchInput->value(), self->btnCase->value(), true);
    }, this);

    auto btnAsHex = new Fl_Check_Button(0, 0, 200, 0, "Pokaż jako hex");
    btnAsHex->callback([](Fl_Widget* w, void* data) {
        auto dv = (DataView*)data;
        dv->setHex(((Fl_Check_Button*)w)->value());
    }, dv);

    Serial.recvBytesLabel = new RecvBytesLabel();

    end();
}