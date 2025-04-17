#include "ConfigPack.h"

ConfigPack::ConfigPack()
: Fl_Pack(0, 0, 0, 110)
{
    type(Fl_Pack::HORIZONTAL);
    spacing(10);
    new ButtonPack();
    new PortSelect();
    new BaudSelect();
    new DataSelect();
    new ParitySelect();
    new StopSelect();
    end();
}