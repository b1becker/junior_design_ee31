// Simple Photoresistor Analog Read with LED Control
// UTI 1893 Photoresistor connected to A0
#include <Arduino.h>
#include "colorSensing.h"

#define PHOTORESISTOR_PIN A3 
#define RED_LED_PIN 5 
#define BLUE_LED_PIN 9

#define STD_DELAY 50
// Must be PWM pin 

// void setup() { 
//     Serial.begin(9600); 
//     pinMode(RED_LED_PIN, OUTPUT); 
//     pinMode(BLUE_LED_PIN, OUTPUT); 
//     Serial.println("PWM LED Fade Controller Started"); 
// } 

// colorSensing::colorSensing() {
//     Serial.print("yeerrrr");
// }

// To do; implement a queue to take running average of readings

void setup() {
    Serial.begin(9600);

    // Set LED pins as outputs
    pinMode(RED_LED_PIN, OUTPUT);
    pinMode(BLUE_LED_PIN, OUTPUT);

    // Turn off both LEDs initially
    digitalWrite(RED_LED_PIN, LOW);
    digitalWrite(BLUE_LED_PIN, LOW);

    pinMode(PHOTORESISTOR_PIN, INPUT);

    Serial.println("=== Photoresistor Analog Read with LEDs ===");
    Serial.println("Cover sensor with hand to see values change");
    Serial.println("Red LED = Bright light, Blue LED = Dark light");
    Serial.println();
}

volatile int photov;

void loop() { 

    
    digitalWrite(RED_LED_PIN, HIGH);
    delay(STD_DELAY);
    int redv = analogRead(PHOTORESISTOR_PIN);
    delay(STD_DELAY);
    Serial.print("RedV = "); Serial.println(redv);
    // digitalWrite(RED_LED_PIN, LOW);
    //digitalWrite(RED_LED_PIN, LOW);
    
    delay(STD_DELAY);
    
    // Measure and print blue voltage output
    // digitalWrite(BLUE_LED_PIN, HIGH);
    // delay(STD_DELAY);
    // int bluev = analogRead(PHOTORESISTOR_PIN);
    // delay(STD_DELAY);
    // digitalWrite(BLUE_LED_PIN, LOW);
    // Serial.print(""); Serial.println(bluev);
    

    // // red and blue section
    // digitalWrite(BLUE_LED_PIN, HIGH);
    // digitalWrite(RED_LED_PIN, HIGH);
    // delay(500);
    // int red_and_blue_v = analogRead(PHOTORESISTOR_PIN);
    // delay(100);
    // digitalWrite(BLUE_LED_PIN, LOW);
    // digitalWrite(RED_LED_PIN, LOW);
    // Serial.print("Red and Blue V = "); Serial.println(red_and_blue_v);

}

// void loop() { 
//     // Read photoresistor (0-1023) 

//     int raw = analogRead(PHOTORESISTOR_PIN);
//     // If wired: collector->A0 with pull-up, emitter->GND, then more light => lower 'raw'.
//     // Invert so brighter = bigger number:
//     int light = 1023 - raw;
//     // Map light level to LED brightness (0-255 for PWM) 
//     int redBrightness = map(light, 0, 1023, 0, 255); 
//     int blueBrightness = 255 - redBrightness; // Constrain values to valid PWM range 

//     int brightness = map(light, 0, 1023, 0, 255);
//     brightness = constrain(brightness, 0, 255);

//     analogWrite(RED_LED_PIN, brightness);
//     analogWrite(BLUE_LED_PIN, brightness);  // Same value for both

//     delay(1000);

//     // brightness = 0;
//     // analogWrite(RED_LED_PIN, brightness);
//     // analogWrite(BLUE_LED_PIN, brightness);  // Same value for both

//     Serial.print("raw= ");
//     Serial.print(raw);  

//     Serial.print("  light(inv)= "); 
//     Serial.print(light);

//     Serial.print("  R=");  Serial.print(redBrightness);
//     Serial.print("  B=");  Serial.println(blueBrightness);

//     delay(1000);
// }

// colorSensing::colorSensing(/* args */)
// {
// }

// colorSensing::~colorSensing()
// {
// }