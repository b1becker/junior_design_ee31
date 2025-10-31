#include <Arduino.h>
#include "collision.h"

#define STD_DELAY 50
#define N_SAMPLES 10
#define DISTANCE_THRESHOLD 10

collision::collision(int photodiode_pin, int irLED_pin) {
    photodiode = photodiode_pin;
    irLED = irLED_pin;
}

void collision::setup() {
    pinMode(photodiode, INPUT);
    pinMode(irLED, OUTPUT);
}

void collision::loop() {

    float onSUM = 0;
    float offSUM = 0; 

    // irLED high and sample
    digitalWrite(irLED, HIGH);
    delay(STD_DELAY);
    for (int i = 0; i < N_SAMPLES; i++) {
        offSUM += analogRead(photodiode);
    }
    int offAVG = offSUM / N_SAMPLES;

    // irLED low and sample
    digitalWrite(irLED, LOW);
    delay(STD_DELAY);
        for (int i = 0; i < N_SAMPLES; i++) {
        onSUM += analogRead(photodiode);
    }
    int onAVG = onSUM / N_SAMPLES;

    // reflection with ambient - ambient = just reflected
    int reflected = onAVG - offAVG;

    if (reflected > DISTANCE_THRESHOLD) {
        Serial.print("Collition approaching! Reflected = ");
        Serial.println(reflected);

    } else {
        Serial.print("Continue with clear path. Reflected = ");
        Serial.println(reflected);
    }

}