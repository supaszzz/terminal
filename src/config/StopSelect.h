#pragma once
#include "ParamSelect.h"
#include "Serial.h"

class StopSelect: public ParamSelect<StopBits> {
    public:
        StopSelect();
};