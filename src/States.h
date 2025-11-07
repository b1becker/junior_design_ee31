// States.h
#ifndef STATES_H
#define STATES_H

#include <Arduino.h>
#include "WebSocket.h"
#include "BotMotions.h"
#include "colorSensing.h"

class States {
public:
    /*****************************************************************
    *                  Constructors & Deconstructors
    *****************************************************************/
    States(BotMotions *MyBot, WebSocket* server);



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

    // for lane following testing
    void goForward(String output_color, colorSensing &cs);

private:
    BotMotions *ourBot;
    WebSocket *ourWeb;
    colorSensing *cs;

};

#endif
