// States.h
#ifndef STATES_H
#define STATES_H

#include <Arduino.h>
#include "BotMotions.h"
#include "colorSensing.h"

class States {
public:
    // Constructor: pass LED pins if you want to keep things flexible
    // States(int led0, int led1, int led2);
    States(int motor_a1, int motor_a2, int motor_b1, int motor_b2, int ena,
        int enb);

    // State handlers
    void handleState0();
    void handleState1();
    void handleState2();
    void handleState3();
    void handleState4();
    void handleState5();
    void handleState6();

private:
    BotMotions *ourBot;
    colorSensing *cs;

    int _led0, _led1, _led2;
};

#endif
