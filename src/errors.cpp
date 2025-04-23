#include "errors.h"
#include <FL/fl_ask.H>

void handleComError(int err) {
    if (!err) return;
    switch (err) {
        case 1:
            fl_alert("Nie można otworzyć portu.");
            break;
        case 2:
            fl_alert("Nie można pobrać stanu portu.");
            break;
        case 3:
            fl_alert("Nie można ustawić stanu portu");
            break;
        case 4:
            fl_alert("Tryby zawsze 0 i zawsze 1 nie są wspierane na Linuxie.");
            break;
        case 5:
            fl_alert("1.5 bitu stopu nie jest wspierane na Linuxie.");
    }
}