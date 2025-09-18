#include <Arduino.h>

#define LED_RED 5
#define LED_BLUE 6
#define SENSOR A0 
volatile int value = 0;

void set_up() {
    pinMode(LED_RED, OUTPUT);
    pinMode(LED_BLUE, OUTPUT);
    pinMode(SENSOR, INPUT);

    analogWrite(LED_RED, 0);
    analogWrite(LED_BLUE, 0);
}

void loop() {
    delay(500);
    value = analogRead(SENSOR);
    Serial.println(value);
    delay(500);
    
    if (value>100){
        Serial.println("White");
    } else if (value<15) { 
        Serial.println("Black");
    } else if (value<= 65 && value >50) {
        Serial.println("RED");
    } else if (value>=68 && value<80) {
        Serial.println("Green");
    } else if (value<30 && value>20) {
        Serial.println("Blue");
    }
}
