// Simple Photoresistor Analog Read with LED Control
// UTI 1893 Photoresistor connected to A0
#include <Arduino.h>
#include "colorSensing.h"

#define STD_DELAY 50


colorSensing::colorSensing(int red_led_pin, int blue_led_pin, int photoresistor_led_pin) {
    red_led = red_led_pin;
    blue_led = blue_led_pin;
    photoresistor_pin = photoresistor_led_pin;

}

void colorSensing::setup() {
    pinMode(red_led, OUTPUT);
    pinMode(blue_led, OUTPUT);
    pinMode(photoresistor_pin, INPUT);

    // Turn off LEDs initially
    
}

void colorSensing::loop() {
    // red flash
    digitalWrite(red_led, HIGH);
    delay(STD_DELAY);
    int redv = analogRead(photoresistor_pin);
    delay(STD_DELAY);
    Serial.print("RedV = "); Serial.println(redv);
    digitalWrite(red_led, LOW);
    
    delay(STD_DELAY);
    
    // Measure and print blue voltage output
    digitalWrite(blue_led, HIGH);
    delay(STD_DELAY);
    int bluev = analogRead(photoresistor_pin);
    delay(STD_DELAY);
    digitalWrite(blue_led, LOW);
    Serial.print(""); Serial.println(bluev);
}

void colorSensing::read_red(int &red_v) {
    digitalWrite(red_led, HIGH);
    delay(STD_DELAY);
    red_v = analogRead(photoresistor_pin);
    delay(STD_DELAY);
    Serial.print("RedV = "); Serial.println(red_v);
    digitalWrite(red_led, LOW);
}

void colorSensing::read_blue(int &blue_v) {
    digitalWrite(blue_led, HIGH);
    delay(STD_DELAY);
    blue_v = analogRead(photoresistor_pin);
    delay(STD_DELAY);
    Serial.print("RedV = "); Serial.println(blue_v);
    digitalWrite(blue_led, LOW);
}

