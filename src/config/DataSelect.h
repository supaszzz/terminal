#pragma once
#include "ParamSelect.h"
#include "Serial.h"

class DataSelect: public ParamSelect<DataBits> {
    public:
        DataSelect();
};