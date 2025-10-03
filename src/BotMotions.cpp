#include <Arduino.h>
#include "BotMotions.h"

#define MOTION_DELAY 2000

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
    // digitalWrite(motor_b1, HIGH);
    // digitalWrite(motor_b2, LOW);
    // digitalWrite(motor_a1, HIGH);
    // digitalWrite(motor_a2, LOW);
    // analogWrite(enb, 128); // Speed: 0 (stopped) to 255 (full speed)
    // analogWrite(ena, 128); // Speed: 0 (stopped) to 255 (full speed)
    // delay(2000); // Run for 2 seconds

    // // Set motor to rotate backward at full speed
    // digitalWrite(motor_b1, LOW);
    // digitalWrite(motor_b2, HIGH);

    // digitalWrite(motor_a1, LOW);
    // digitalWrite(motor_a2, HIGH);
    // analogWrite(enb, 255);
    // analogWrite(ena, 255); 
    // delay(2000);

    // // Stop the motor
    // digitalWrite(motor_b1, LOW);
    // digitalWrite(motor_b2, LOW);
    left();
    delay(MOTION_DELAY);
    right();
    delay(1000);
    Serial.print("cycle complete \n");  
}

void BotMotions::forward() {
    digitalWrite(motor_b1, HIGH);
    digitalWrite(motor_b2, LOW);

    digitalWrite(motor_a1, HIGH);
    digitalWrite(motor_a2, LOW);
    analogWrite(enb, 255);
    analogWrite(ena, 255); 

    delay(MOTION_DELAY);

    digitalWrite(motor_a1, LOW);
    digitalWrite(motor_a2, LOW);
    digitalWrite(motor_b1, LOW);
    digitalWrite(motor_b2, LOW);

}

void BotMotions::stop(){
    digitalWrite(motor_a1, LOW);
    digitalWrite(motor_a2, LOW);
    digitalWrite(motor_b1, LOW);
    digitalWrite(motor_b2, LOW);
}

void BotMotions::backward() {
    digitalWrite(motor_b1, LOW);
    digitalWrite(motor_b2, HIGH);

    digitalWrite(motor_a1, LOW);
    digitalWrite(motor_a2, HIGH);
    analogWrite(enb, 255);
    analogWrite(ena, 255); 

    delay(MOTION_DELAY);

    digitalWrite(motor_a1, LOW);
    digitalWrite(motor_a2, LOW);
    digitalWrite(motor_b1, LOW);
    digitalWrite(motor_b2, LOW);
}

void BotMotions::left() {
    digitalWrite(motor_b1, HIGH);
    digitalWrite(motor_b2, LOW);

    digitalWrite(motor_a1, LOW);
    digitalWrite(motor_a2, HIGH);
    analogWrite(enb, 100);
    analogWrite(ena, 255); 

    delay(MOTION_DELAY);

    digitalWrite(motor_a1, LOW);
    digitalWrite(motor_a2, LOW);
    digitalWrite(motor_b1, LOW);
    digitalWrite(motor_b2, LOW);
}

void BotMotions::right() {
    digitalWrite(motor_b1, LOW);
    digitalWrite(motor_b2, HIGH);

    digitalWrite(motor_a1, HIGH);
    digitalWrite(motor_a2, LOW);
    analogWrite(enb, 255);
    analogWrite(ena, 100); 

    delay(MOTION_DELAY);

    digitalWrite(motor_a1, LOW);
    digitalWrite(motor_a2, LOW);
    digitalWrite(motor_b1, LOW);
    digitalWrite(motor_b2, LOW);
}
void BotMotions::pivotCW() {
    //TO-DO
}
void BotMotions::pivotCCW() {
    //TO-DO
}