#include "ConfigPack.h"

ConfigPack::ConfigPack()
: Fl_Pack(0, 0, 0, 100)
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