#include <Arduino.h>
#include "BotMotions.h"

BotMotions::BotMotions(int motor_a1, int motor_a2, int motor_b1, int motor_b2, 
    int ena, int enb) {

    this->motor_a1 = motor_a1;
    this->motor_a2 = motor_a2;
    this->motor_b1 = motor_b1;
    this->motor_b2 = motor_b2;
    this->ena = ena;
    this->enb = enb;
}

void BotMotions::loop() {
    // Set motor to rotate forward at half speed
    digitalWrite(motor_b1, HIGH);
    digitalWrite(motor_b2, LOW);
    analogWrite(enb, 128); // Speed: 0 (stopped) to 255 (full speed)
    delay(2000); // Run for 2 seconds

    // Set motor to rotate backward at full speed
    digitalWrite(motor_b1, LOW);
    digitalWrite(motor_b2, HIGH);
    analogWrite(enb, 255);
    delay(2000);

    // Stop the motor
    digitalWrite(motor_b1, LOW);
    digitalWrite(motor_b2, LOW);
    delay(1000);
    Serial.print("cycle complete \n");  
}