#include "DataSelect.h"

DataSelect::DataSelect() : ParamSelect("Bity danych", &Serial.dataBits, 4) {
    this->entry("5", DATA_5);
    this->entry("6", DATA_6);
    this->entry("7", DATA_7);
    this->entry("8", DATA_8, true);
    end();
};