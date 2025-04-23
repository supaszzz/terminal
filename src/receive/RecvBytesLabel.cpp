#include "RecvBytesLabel.h"

RecvBytesLabel::RecvBytesLabel() : Fl_Box(0, 0, 30, 0) {
    update(0);
}

void RecvBytesLabel::update(unsigned long bytesRecv) {
    totalBytes += bytesRecv;
    char text[1024];
    char sizeUnit[4];
    double formatted = formatSize(sizeUnit);
    snprintf(text, 1024, "Otrzymane dane: %lu B (%.2f %s)", totalBytes, formatted, sizeUnit);
    copy_label(text);
    size(fl_width(text) + 20, 0);
}

double RecvBytesLabel::formatSize(char* sizeUnit) {
    static const char* units[] = {"B", "KiB", "MiB", "GiB", "TiB"};
    double result = totalBytes;
    unsigned int unitVal = 0;
    while (result >= 1024 && unitVal != 4) {
        result /= 1024.0;
        unitVal++;
    }
    strcpy(sizeUnit, units[unitVal]);
    return result;
}

void RecvBytesLabel::clear() {
    totalBytes = 0;
    update(0);
}