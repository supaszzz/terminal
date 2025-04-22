#pragma once
#include <FL/Fl_Box.H>
#include <FL/fl_draw.H>
#include <cstdio>
#include <cstring>

class RecvBytesLabel: public Fl_Box {
    unsigned long totalBytes = 0;
    public:
        RecvBytesLabel();
        void update(unsigned long recvBytes);
        double formatSize(char* sizeUnit);
        void clear();
};