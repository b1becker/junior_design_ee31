#include <Arduino.h>
#include "BotMotions.h"

#define MOTION_DELAY 1700
#define TURN_DELAY 1124 / 8

#define TURN_SPEED 200
#define NEG_TURN_SPEED 100

#define FLSPEED 117
#define SPEED 117
#define FRSPEED 145

#define LSPEED 135
#define RSPEED 250

#define TURN90 780

/********** Constructor ********
*
* Assign Pin Values
*
* Parameters:
*      Pin Values
*
************************/
BotMotions::BotMotions(int motor_a1, int motor_a2, int motor_b1, int motor_b2, 
    int ena, int enb) {

    this->motor_a1 = motor_a1;
    this->motor_a2 = motor_a2;
    this->motor_b1 = motor_b1;
    this->motor_b2 = motor_b2;
    this->ena = ena;
    this->enb = enb;
    

}

/********** Stop ********
*
* Notes:
*      Make sure to call this before anything done.
************************/
void BotMotions::stop(){
    digitalWrite(motor_a1, LOW);
    digitalWrite(motor_a2, LOW);
    digitalWrite(motor_b1, LOW);
    digitalWrite(motor_b2, LOW);

    digitalWrite(enb, 0);
    digitalWrite(ena, 0);
}

/********** Forward ********
*
* Notes:
*      ENB: Right Motor
*      ENA: Left Motor
************************/
void BotMotions::forward() {
    digitalWrite(motor_b1, LOW);
    digitalWrite(motor_b2, HIGH);

    digitalWrite(motor_a1, LOW);
    digitalWrite(motor_a2, HIGH);

    analogWrite(enb, FRSPEED);
    analogWrite(ena, FLSPEED); 


    // stop();

}

/********** Backward ********
*
* Notes:
*      ENB: Left Motor
*      ENA: Right Motor
************************/
void BotMotions::backward() {
    digitalWrite(motor_b1, HIGH);
    digitalWrite(motor_b2, LOW);

    digitalWrite(motor_a1, HIGH);
    digitalWrite(motor_a2, LOW);

    analogWrite(enb, SPEED);
    analogWrite(ena, SPEED); 

    // delay(MOTION_DELAY);

    // stop();
}

/********** Left ********
*
* Notes:
*      Left Motor(ENB) < Right Motor(ENA)
************************/
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

/********** Right ********
*
* Notes:
*      Same Direction
*      Right Motor(ENA) < Left Motor(ENB)
************************/
void BotMotions::right() {
    stop();
    digitalWrite(motor_b1, LOW);
    digitalWrite(motor_b2, HIGH);
    analogWrite(enb, TURN_SPEED);  
    
    digitalWrite(motor_a1, LOW);
    digitalWrite(motor_a2, HIGH);
    analogWrite(ena, NEG_TURN_SPEED);  
    
    delay(MOTION_DELAY);
    stop();
}

/********** Clockwise ********
*
* Notes:
*      Diff motor directions
*      ENB Backward, ENA Forward
************************/
void BotMotions::pivotCW() {
    digitalWrite(motor_b1, HIGH);
    digitalWrite(motor_b2, LOW);

    digitalWrite(motor_a1, LOW);
    digitalWrite(motor_a2, HIGH);
    analogWrite(enb, LSPEED);
    analogWrite(ena, RSPEED); 

    delay(TURN_DELAY);
    stop();
}

/********** CounterClockwise ********
*
* Notes:
*      Diff motor directions
*      ENB Forward, ENA Backward
************************/
void BotMotions::pivotCCW() {
    digitalWrite(motor_b1, LOW);
    digitalWrite(motor_b2, HIGH);

    digitalWrite(motor_a1, HIGH);
    digitalWrite(motor_a2, LOW);
    analogWrite(enb, RSPEED);
    analogWrite(ena, LSPEED); 

    delay(TURN_DELAY);
    stop();
}

/********** left90 ********
*
* Notes:
*      Diff motor directions
*      ENB Forward, ENA Backward
************************/
void BotMotions::left90() {
    digitalWrite(motor_b1, LOW);
    digitalWrite(motor_b2, HIGH);

    digitalWrite(motor_a1, HIGH);
    digitalWrite(motor_a2, LOW);
    
    analogWrite(enb, FRSPEED * 2);
    analogWrite(ena, FLSPEED * 2); 

    delay(TURN90);
    stop();
}

/********** right90 ********
*
* Notes:
*      Diff motor directions
*      ENB Forward, ENA Backward
************************/
void BotMotions::right90() {
    digitalWrite(motor_b1, HIGH);
    digitalWrite(motor_b2, LOW);

    digitalWrite(motor_a1, LOW);
    digitalWrite(motor_a2, HIGH);

    analogWrite(enb, FRSPEED * 2);
    analogWrite(ena, FLSPEED * 2); 

    delay(TURN90);
    stop();
}