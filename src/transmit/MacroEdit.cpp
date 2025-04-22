#include "MacroEdit.h"

MacroEdit::MacroEdit(Macro* m, Fl_Widget* mBtn) : Fl_Window(512, 145, "Edycja makra") {
    set_modal();
    callback([](Fl_Widget* w) {
        Fl::delete_widget(w);
    });
    macro = m;
    macroBtn = mBtn;

    auto pack = new Fl_Pack(0, 0, 512, 145);
    auto grid = new Fl_Grid(0, 0, 0, 100);
    grid->layout(2, 2, 20, 10);
    grid->col_weight(0, 1);
    grid->col_weight(1, 6);

    auto nameLabel = new Fl_Box(0, 0, 0, 0, "Nazwa:");
    auto dataLabel = new Fl_Box(0, 0, 0, 0, "Polecenie:");
    grid->widget(nameLabel, 0, 0);
    grid->widget(dataLabel, 1, 0);

    nameInput = new Fl_Input(0, 0, 0, 0);
    dataInput = new Fl_Input(0, 0, 0, 0);
    grid->widget(nameInput, 0, 1);
    grid->widget(dataInput, 1, 1);

    nameInput->value(macro->name);
    dataInput->value(macro->data);

    grid->end();

    auto flex = new Fl_Pack(0, 0, 320, 30);
    flex->type(Fl_Pack::HORIZONTAL);
    
    new Fl_Box(0, 0, 166, 0);
    auto saveButton = new Fl_Button(0, 0, 80, 0, "Zapisz");
    new Fl_Box(0, 0, 20, 0);
    auto cancelButton = new Fl_Button(0, 0, 80, 0, "Anuluj");
    cancelButton->callback([](Fl_Widget*, void* data) {
        auto win = (MacroEdit*)data;
        win->hide();
        Fl::delete_widget(win);
    }, this);

    saveButton->callback([](Fl_Widget*, void* data) {
        auto win = (MacroEdit*)data;

        const char* strData = win->dataInput->value();
        const char* strName = win->nameInput->value();
        size_t lenData = strlen(strData);
        size_t lenName = strlen(strName);

        if (lenName == 0) {
            fl_alert("Nazwa nie może być pusta.");
            return;
        }
        if (lenName > 12) {
            fl_alert("Nazwa nie może być dłuższa niż 12 znaków.");
            return;
        }
        if (lenData == 0) {
            fl_alert("Polecenie nie może być puste.");
            return;
        }
        if (lenData > 2032) {
            fl_alert("Polecenie nie może być dłuższe niż 2032 znaki.");
            return;
        }

        strncpy(win->macro->data, strData, sizeof(win->macro->data));
        strncpy(win->macro->name, strName, sizeof(win->macro->name));
        win->macroBtn->redraw();
        win->hide();
        Fl::delete_widget(win);
    }, this);
    
    flex->end();

    pack->end();
    end();
    show();
}