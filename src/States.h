// States.h
#ifndef STATES_H
#define STATES_H

#include <Arduino.h>
#include "BotMotions.h"
#include "colorSensing.h"

class States {
public:
    /*****************************************************************
    *                  Constructors & Deconstructors
    *****************************************************************/
    States(BotMotions *MyBot);



    /*****************************************************************
    *                  State Definitions
    *****************************************************************/
    void handleState0();
    void handleState1();
    void handleState2();
    void handleState3();
    void handleState4();
    void handleState5();
    void handleState6();
    void handleErrorState();

private:
    BotMotions *ourBot;
    colorSensing *cs;

};

#endif
