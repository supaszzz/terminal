#include <Arduino.h>

void setup() {
    Serial.begin(19200);
    Serial.println("start esp");
}

void loop() {
    while (Serial.available()) {
        Serial.write(Serial.read());
    }
}
