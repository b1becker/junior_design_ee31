#include <Arduino.h>
#include "BotMotions.h"

#define MOTION_DELAY 1700

#define TURN_SPEED 200
#define NEG_TURN_SPEED 100

#define SPEED 175

#define LSPEED 135
#define RSPEED 250

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
    forward();
    delay(MOTION_DELAY);
    backward();
    delay(1000);
    Serial.print("cycle complete \n");  
}

void BotMotions::forward() {
    Serial.println("going forward");
    digitalWrite(motor_b1, LOW);
    digitalWrite(motor_b2, HIGH);

    digitalWrite(motor_a1, LOW);
    digitalWrite(motor_a2, HIGH);



    //Left Motor
    analogWrite(enb, SPEED);
    

    //Right Motor
    analogWrite(ena, SPEED); 
    


    delay(MOTION_DELAY / 2);

    // stop();

}

void BotMotions::stop(){
    digitalWrite(motor_a1, LOW);
    digitalWrite(motor_a2, LOW);
    digitalWrite(motor_b1, LOW);
    digitalWrite(motor_b2, LOW);

    digitalWrite(enb, 0);
    digitalWrite(ena, 0);

    // Serial.println("assignment of pins in order ");
    // Serial.println(motor_a1);
    // Serial.println(motor_a2);
    // Serial.println(motor_b1);
    // Serial.println(motor_b2);
    // Serial.println(ena);
    // Serial.println(enb);
}

void BotMotions::backward() {
    digitalWrite(motor_b1, HIGH);
    digitalWrite(motor_b2, LOW);

    digitalWrite(motor_a1, HIGH);
    digitalWrite(motor_a2, LOW);

    //Left Motor
    analogWrite(enb, SPEED);

    //Right Motor
    analogWrite(ena, SPEED); 

    // delay(MOTION_DELAY);

    // stop();
}

// fix this
void BotMotions::left() {
    
    
    
    digitalWrite(motor_b1, LOW);
    digitalWrite(motor_b2, HIGH);
    analogWrite(enb, NEG_TURN_SPEED); 
    
    
    digitalWrite(motor_a1, LOW);
    digitalWrite(motor_a2, HIGH);
    analogWrite(ena, TURN_SPEED);  
    
    delay(MOTION_DELAY);
    stop();
    

}

void BotMotions::right() {
    // Left motor forward (faster)
    stop();
    digitalWrite(motor_b1, LOW);
    digitalWrite(motor_b2, HIGH);
    analogWrite(enb, TURN_SPEED);  
    
    // Right motor backward or slower
    digitalWrite(motor_a1, LOW);
    digitalWrite(motor_a2, HIGH);
    analogWrite(ena, NEG_TURN_SPEED);  
    
    delay(MOTION_DELAY);
    stop();
}

void BotMotions::pivotCW() {
    digitalWrite(motor_b1, HIGH);
    digitalWrite(motor_b2, LOW);

    digitalWrite(motor_a1, LOW);
    digitalWrite(motor_a2, HIGH);
    analogWrite(enb, LSPEED);
    analogWrite(ena, RSPEED); 

    delay(1124);
    stop();
}

void BotMotions::pivotCCW() {
    digitalWrite(motor_b1, LOW);
    digitalWrite(motor_b2, HIGH);

    digitalWrite(motor_a1, HIGH);
    digitalWrite(motor_a2, LOW);
    analogWrite(enb, RSPEED);
    analogWrite(ena, LSPEED); 

    delay(1124);
    stop();
}
