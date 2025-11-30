#ifndef DEMO_H
#define DEMO_H

#include "BotMotions.h"
#include "WebSocket.h"
#include <Arduino.h>
#include "States.h"


class Demo {
public:
    /*****************************************************************
    *                  Constructors & Deconstructors
    *****************************************************************/
    Demo(WebSocket* server, States* myState);


    /*****************************************************************
    *                  Demo Definitions
    *****************************************************************/
   void remotePartnerMotions();
   void SoloDemo1();
   void SoloDemo2();
   void PartnerDemo();

private:
    WebSocket *ourWeb;
    States *ourState;
};

#endif