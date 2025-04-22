#include <Arduino.h>

void setup() {
    Serial.begin(19200);
}

void loop() {
    while (Serial.available()) {
        Serial.write(Serial.read());
    }
}
