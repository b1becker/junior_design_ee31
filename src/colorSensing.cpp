// Simple Photoresistor Analog Read with LED Control
// UTI 1893 Photoresistor connected to A0
#include <Arduino.h>
#include "colorSensing.h"

#define PHOTORESISTOR_PIN A0 
#define RED_LED_PIN 5 
#define BLUE_LED_PIN 9 
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

void setup() {
    Serial.begin(9600);

    // Set LED pins as outputs
    pinMode(RED_LED_PIN, OUTPUT);
    pinMode(BLUE_LED_PIN, OUTPUT);

    // Turn off both LEDs initially
    digitalWrite(RED_LED_PIN, LOW);
    digitalWrite(BLUE_LED_PIN, LOW);

    Serial.println("=== Photoresistor Analog Read with LEDs ===");
    Serial.println("Cover sensor with hand to see values change");
    Serial.println("Red LED = Bright light, Blue LED = Dark light");
    Serial.println();
    // digitalWrite(RED_LED_PIN, HIGH);
}

void loop() { 
    // Read photoresistor (0-1023) 
    // Measure and print red voltage output
    // delay(500);
    int redv = analogRead(PHOTORESISTOR_PIN);
    // delay(500);
    Serial.print("RedV = "); Serial.println(redv);
    delay(100);
    //digitalWrite(RED_LED_PIN, LOW);
    
    // Measure and print blue voltage output
//     digitalWrite(BLUE_LED_PIN, HIGH);
//     delay(500);
//     int bluev = analogRead(PHOTORESISTOR_PIN);
//     delay(500);
//    // digitalWrite(BLUE_LED_PIN, LOW);
//     Serial.print("BlueV = "); Serial.println(bluev);

}

// // void loop() { 
// //     // Read photoresistor (0-1023) 

// //     int raw = analogRead(PHOTORESISTOR_PIN);
// //     // If wired: collector->A0 with pull-up, emitter->GND, then more light => lower 'raw'.
// //     // Invert so brighter = bigger number:
// //     int light = 1023 - raw;
// //     // Map light level to LED brightness (0-255 for PWM) 
// //     int redBrightness = map(light, 0, 1023, 0, 255); 
// //     int blueBrightness = 255 - redBrightness; // Constrain values to valid PWM range 

// //     int brightness = map(light, 0, 1023, 0, 255);
// //     brightness = constrain(brightness, 0, 255);

// //     analogWrite(RED_LED_PIN, brightness);
// //     analogWrite(BLUE_LED_PIN, brightness);  // Same value for both

// //     delay(1000);

// //     // brightness = 0;
// //     // analogWrite(RED_LED_PIN, brightness);
// //     // analogWrite(BLUE_LED_PIN, brightness);  // Same value for both

// //     Serial.print("raw= ");
// //     Serial.print(raw);  

// //     Serial.print("  light(inv)= "); 
// //     Serial.print(light);

// //     Serial.print("  R=");  Serial.print(redBrightness);
// //     Serial.print("  B=");  Serial.println(blueBrightness);

// //     delay(1000);
// // }

// // colorSensing::colorSensing(/* args */)
// // {
// // }

// // colorSensing::~colorSensing()
// // {
// // }