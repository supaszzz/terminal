#include "ParitySelect.h"

ParitySelect::ParitySelect() : ParamSelect("Bit parzystości", &Serial.parityBit, 5)
{
    this->entry("Brak", NONE, true);
    this->entry("Parzysty", EVEN);
    this->entry("Nieparzysty", ODD);
    this->entry("Zawsze 1", MARK);
    this->entry("Zawsze 0", SPACE);
    end();
}