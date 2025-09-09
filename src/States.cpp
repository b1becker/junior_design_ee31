#include <Arduino.h>
#include <WiFiNINA.h>
#include "States.h"

States::States(int led0, int led1, int led2) {
    _led0 = led0;
    _led1 = led1;
    _led2 = led2;
}

void States::handleState0() {
    digitalWrite(_led0, LOW);
    digitalWrite(_led1, LOW);
    digitalWrite(_led2, LOW);
    Serial.println("In state 0");
}

void States::handleState1() {
    digitalWrite(_led0, HIGH);
    digitalWrite(_led1, LOW);
    digitalWrite(_led2, LOW);
    Serial.println("In state 1");
}

void States::handleState2() {
    digitalWrite(_led0, LOW);
    digitalWrite(_led1, HIGH);
    digitalWrite(_led2, LOW);
    Serial.println("In state 2");
}

void States::handleState3() {
    digitalWrite(_led0, HIGH);
    digitalWrite(_led1, HIGH);
    digitalWrite(_led2, LOW);
    Serial.println("In state 3");
}

void States::handleState4() {
    digitalWrite(_led0, LOW);
    digitalWrite(_led1, LOW);
    digitalWrite(_led2, HIGH);
    Serial.println("In state 4");
}

void States::handleState5() {
    digitalWrite(_led0, HIGH);
    digitalWrite(_led1, LOW);
    digitalWrite(_led2, HIGH);
    Serial.println("In state 5");
}

void States::handleState6() {
    digitalWrite(_led0, LOW);
    digitalWrite(_led1, HIGH);
    digitalWrite(_led2, HIGH);
    Serial.println("In state 6");
}

void States::handleState7() {
    digitalWrite(_led0, HIGH);
    digitalWrite(_led1, HIGH);
    digitalWrite(_led2, HIGH);
    Serial.println("In state 7");
}
