// States.h
#ifndef STATES_H
#define STATES_H

#include <Arduino.h>
#include "WebSocket.h"
#include "BotMotions.h"
#include "colorSensing.h"
#include "collision.h"

class States {
public:
    /*****************************************************************
    *                  Constructors & Deconstructors
    *****************************************************************/
    States(BotMotions *MyBot, WebSocket* server, collision *my_Collider, colorSensing *cs);



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
    void laneFollow(String output_color);

private:
    BotMotions *ourBot;
    WebSocket *ourWeb;
    colorSensing *ourCS;
    collision *ourCollider;
};

#endif
