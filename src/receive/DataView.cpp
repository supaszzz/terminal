#include "DataView.h"

DataView::DataView() : Fl_Text_Display(0, 0, 0, 500) {
    dataBuffer = new Fl_Text_Buffer();
    buffer(dataBuffer);
    wrap_mode(Fl_Text_Display::WRAP_AT_BOUNDS, 0);

    Serial.dataCb = [this](unsigned long toRead) {
        if (toRead == 0)
            return;

        std::vector<uint8_t> data(toRead);
        Serial.read(data.data(), toRead);
        dataBuffer->append((const char*)data.data());

        int lineCount = dataBuffer->count_lines(0, dataBuffer->length()) + 1;

        while (lineCount > 1000) {
            int start = dataBuffer->line_start(0);
            int end = dataBuffer->line_end(0) + 1;
            dataBuffer->remove(start, end);
            lineCount--;
        }

        insert_position(dataBuffer->length());
        show_insert_position();
    };
}