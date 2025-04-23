#include "DataView.h"

DataView::DataView() : Fl_Text_Display(0, 0, 0, 500) {
    dataBuffer = new Fl_Text_Buffer();
    buffer(dataBuffer);
    wrap_mode(Fl_Text_Display::WRAP_AT_BOUNDS, 0);
    textfont(FL_COURIER);

    Serial.dataCb = [this](unsigned long toRead) {
        if (toRead == 0)
            return;

        std::vector<uint8_t> data(toRead);
        Serial.read(data.data(), toRead);

        if (hexEnabled) {
            appendHex(data.data(), toRead);
        } else {
            dataBuffer->append((const char*)data.data(), toRead);
        }

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

void DataView::findNext(const char* str, bool matchCase, bool backward) {
    int index, hasFound, selStart, selEnd;
    dataBuffer->selection_position(&selStart, &selEnd);
    if (backward)
        hasFound = dataBuffer->search_backward(selStart == selEnd ? dataBuffer->length() - 1 : selStart - 1, str, &index, matchCase);
    else
        hasFound = dataBuffer->search_forward(selEnd, str, &index, matchCase);

    if (hasFound) {
        int endPos = index + strlen(str);
        dataBuffer->select(index, endPos);
        insert_position(endPos);
        show_insert_position();
    } else {
        fl_beep();
        dataBuffer->select(0, 0);
    }
}

void DataView::setHex(bool enabled) {
    hexEnabled = enabled;

    if (enabled) {
        dataCopy.clear();
        auto textCopy = dataBuffer->text();
        auto len = dataBuffer->length();
        dataBuffer->text("");
        byteCounter = 0;
        appendHex((uint8_t*)textCopy, len);
        free(textCopy);
    } else {
        dataBuffer->text("");
        dataBuffer->append(dataCopy.data(), dataCopy.size());
    }

    insert_position(dataBuffer->length());
    show_insert_position();
}

void DataView::appendHex(uint8_t* str, unsigned long len) {
    char nextByte[4];
    for (unsigned long i = 0; i < len; i++) {
        auto val = str[i];
        snprintf(nextByte, 4, "%02hhX ", val);
        dataBuffer->append((const char*)nextByte, 3);
        byteCounter++;
        if (byteCounter == 16) {
            dataBuffer->append("\r\n");
            byteCounter = 0;
        }
        dataCopy.push_back((char)val);
    }
}

void DataView::clear() {
    dataBuffer->text("");
    dataCopy.clear();
    byteCounter = 0;
}