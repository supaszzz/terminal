#include "ConfigPack.h"

ConfigPack::ConfigPack()
: Fl_Pack(10, 20, 1280, 100)
{
    type(Fl_Pack::HORIZONTAL);
    spacing(10);
    new ButtonPack();
    new BaudSelect();
    new DataSelect();
    new ParitySelect();
    new StopSelect();
    end();
}