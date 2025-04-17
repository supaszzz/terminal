#include "StopSelect.h"

StopSelect::StopSelect() : ParamSelect("Bity stopu", &Serial.stopBits, 3)
{
    this->entry("1", STOP_1, true);
    this->entry("1.5", STOP_1_5);
    this->entry("2", STOP_2);
    end();
}