#include <Arduino.h>
#include <WiFiNINA.h>
#include "States.h"
#include "BotMotions.h"
#include "colorSensing.h"
// States::States(int led0, int led1, int led2) {
//     _led0 = led0;
//     _led1 = led1;   
//     _led2 = led2;
// }


States::States(int motor_a1, int motor_a2, int motor_b1, int motor_b2, int ena,
        int enb) {
    ourBot = new BotMotions(motor_a1, motor_a2, motor_b1, motor_b2, ena, enb);
    
    
}




void States::handleState0() {
    // digitalWrite(_led0, LOW);
    // digitalWrite(_led1, LOW);
    // digitalWrite(_led2, LOW);
    Serial.println("In state 0");
    delay(1000);
    ourBot->stop();
}

void States::handleState1() {
    // digitalWrite(_led0, HIGH);
    // digitalWrite(_led1, LOW);
    // digitalWrite(_led2, LOW);
    Serial.println("In state 1");
    delay(1000);
    ourBot->forward();
}

void States::handleState2() {
    // digitalWrite(_led0, LOW);
    // digitalWrite(_led1, HIGH);
    // digitalWrite(_led2, LOW);
    Serial.println("In state 2");
    delay(1000);
    ourBot->backward();
}

void States::handleState3() {
    // digitalWrite(_led0, HIGH);
    // digitalWrite(_led1, HIGH);
    // digitalWrite(_led2, LOW);
    Serial.println("In state 3");
    delay(1000);
    ourBot->pivotCW();
}

void States::handleState4() {
    // digitalWrite(_led0, LOW);
    // digitalWrite(_led1, LOW);
    // digitalWrite(_led2, HIGH);
    Serial.println("In state 4");
    delay(1000);
    ourBot->pivotCCW();
}

void States::handleState5() {
    // digitalWrite(_led0, HIGH);
    // digitalWrite(_led1, LOW);
    // digitalWrite(_led2, HIGH);
    Serial.println("In state 5");
    delay(1000);
    ourBot->right();
}

void States::handleState6() {
    // digitalWrite(_led0, LOW);
    // digitalWrite(_led1, HIGH);
    // digitalWrite(_led2, HIGH);
    Serial.println("In state 6");
    delay(1000);
    ourBot->left();
}

void States::handleErrorState() {
    // digitalWrite(_led0, LOW);
    // digitalWrite(_led1, HIGH);
    // digitalWrite(_led2, HIGH);
    Serial.println("MISINPUT: ABORT");
    delay(1000);

}
