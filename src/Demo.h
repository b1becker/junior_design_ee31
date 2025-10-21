#ifndef DEMO_H
#define DEMO_H

#include "BotMotions.h"
#include "WebSocket.h"
#include <Arduino.h>

class Demo {
public:
    /*****************************************************************
    *                  Constructors & Deconstructors
    *****************************************************************/
    Demo(BotMotions* robot, WebSocket* server);


    /*****************************************************************
    *                  Demo Definitions
    *****************************************************************/
   void remotePartnerMotions();
   void SoloDemo1();
   void SoloDemo2();
   void PartnerDemo();

private:
    BotMotions *ourBot;
    WebSocket *ourWeb;
};

#endif