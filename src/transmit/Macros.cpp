#include "Macros.h"

static Fl_Button* macroButtons[60];

void exportMacros(Fl_Widget*, void* data) {
    Fl_Native_File_Chooser fc;
    fc.title("Eksportuj jako");
    fc.type(Fl_Native_File_Chooser::BROWSE_SAVE_FILE);
    fc.filter("*.mcr");
    fc.preset_file("makra.mcr");
    
    if (fc.show() == 0) {
        std::ofstream file(fc.filename(), std::ios::binary | std::ios::out);

        if (!file.is_open()) {
            fl_alert("Nie można zapisać pliku!");
            return;
        }

        file.write((char*)data, 60 * sizeof(Macro));
        file.close();
    }
}

void importMacros(Fl_Widget*, void* data) {
    Fl_Native_File_Chooser fc;
    fc.title("Importuj z");
    fc.type(Fl_Native_File_Chooser::BROWSE_FILE);
    fc.filter("*.mcr");
    
    if (fc.show() == 0) {
        std::ifstream file(fc.filename(), std::ios::binary | std::ios::in);

        if (!file.is_open()) {
            fl_alert("Nie można otworzyć pliku!");
            return;
        }

        size_t fileSize = 60 * sizeof(Macro);
        auto buffer = new char[fileSize];
        file.read(buffer, fileSize);
        auto readSize = (size_t)file.gcount();
        file.get();

        if (readSize != fileSize || !file.eof()) {
            fl_alert("Niepoprawny format makr!");
            delete[] buffer;
            return;
        }

        file.close();

        memcpy(data, buffer, fileSize);
        delete[] buffer;

        for (Fl_Button* i : macroButtons)
            i->redraw();
    }
}

Macros::Macros() : Fl_Grid(0, 0, 0, 200) {
    box(FL_ENGRAVED_BOX);
    layout(4, 1, 5, 5);
    row_weight(3, 1);
    for (int i = 0; i != 3; i++)
        row_weight(i, 2);


    std::ifstream savedEntries(getMacroPath(), std::ios::binary | std::ios::in);
    if (savedEntries.is_open()) {
        savedEntries.read((char*)entries, 60 * sizeof(Macro));
        savedEntries.close();
    } else {
        for (int i = 0; i != 60; i++)
            snprintf(entries[i].name, 13, "Makro %d", (i % 20) + 1);
    }

    auto bottomPack = new Fl_Pack(0, 0, 0, 0);
    bottomPack->spacing(10);
    new Fl_Box(0, 0, 65, 0);
    bottomPack->type(Fl_Pack::HORIZONTAL);
    auto btnExport = new Fl_Button(0, 0, 130, 0, "Eksportuj makra...");
    auto btnImport = new Fl_Button(0, 0, 130, 0, "Importuj makra...");

    btnExport->callback(exportMacros, entries);
    btnImport->callback(importMacros, entries);

    auto editMode = new Fl_Check_Button(0, 0, 130, 0, "Tryb edycji");
    bottomPack->end();
    widget(bottomPack, 3, 0);

    char groupNo[] = "Grupa 1:";
    for (int i = 0; i < 3; i++) {
        auto pack = new Fl_Pack(0, 0, 0, 0);
        pack->type(Fl_Pack::HORIZONTAL);
        auto box = new Fl_Box(0, 0, 75, 0);
        box->copy_label(groupNo);
        groupNo[6]++;

        auto grid = new Fl_Grid(0, 0, 1200, 0);
        grid->layout(2, 10);

        for (int j = 0; j != 20; j++) {
            size_t index = i * 20 + j;
            auto macro = &entries[index];
            auto btn = new Fl_Button(0, 0, 0, 0, macro->name);
            btn->callback([](Fl_Widget* w, void* data) {
                auto [macro, editMode, entries] = *(std::tuple<Macro*, Fl_Check_Button*, Macro*>*)data;
                if (editMode->value()) {
                    new MacroEdit(macro, w, entries);
                    return;
                }
                Serial.writeString(macro->data);
            }, new std::tuple<Macro*, Fl_Check_Button*, Macro*>(macro, editMode, entries));
            grid->widget(btn, j / 10, j % 10);
            macroButtons[index] = btn;
        }
        grid->end();
        pack->end();
        widget(pack, i, 0);
    }

    end();
}