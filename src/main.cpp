#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Button.H>
#include <FL/fl_callback_macros.H>

int main(int argc, char ** argv) {
    auto window = new Fl_Window(640, 100, "aaaaaaaaa");
    window->resizable(window);

    auto button = new Fl_Button(0, 0, 100, 100, "guzik");
    FL_INLINE_CALLBACK_1(button, Fl_Button*, button, button, {
        button->label("klikniety");
    });

    window->end();
    window->show(argc, argv);
    return Fl::run();
}
