#include <Arduino.h>
#include "BotMotions.h"
#include "WebSocket.h"
#include "Demo.h"
#include "States.h"
#include "Constants.h"

/********** Constructir ********
*
* Links BotMotion Object
*
* Parameters:
*      Arduino Pins
*
************************/
Demo::Demo(WebSocket* server, States* myState) {
    ourWeb = server;
    ourState = myState;
}

/********** Remote Partner Check Off ********
*
*   Required logic to pass the partner check off
*
************************/
void Demo::remotePartnerMotions(){
    Serial.println("Remote Partner Check");
    pinMode(LED_BUILTIN, OUTPUT);
    
    digitalWrite(LED_BUILTIN, LOW);
    delay(10);
    digitalWrite(LED_BUILTIN, HIGH);
    delay(10);
    digitalWrite(LED_BUILTIN, LOW);

    ourWeb->WriteServer("State: 1");
    
    String partnerCommand = ourWeb->PartnerReadServer();

    while (partnerCommand != "State: 2") {
        partnerCommand = ourWeb->PartnerReadServer();
        if (partnerCommand != "NULL") {
            Serial.print(partnerCommand);
        }
        delay(1);
    }
    ourState->handleState1();
    delay(5000);
    ourState->handleState0();
}

/********** SoloDemo1 ********
*
* Run the required logic to execute a solo-demo starting from Pos1
*
************************/
void Demo::SoloDemo1(){ 
    ourState->forwardUntilCollision();
    InterruptReturn();  
    delay(DEMO_DELAY);

    ourState->rightState90();
    InterruptReturn(); 
    ourState->rightState90();
    InterruptReturn(); 
    
    ourState->TimeForward(2500);
    ourState->laneFind("red");
    InterruptReturn();  
    ourState->Nudge();

    InterruptReturn();  
    ourState->LeftColorTurn("red");
    InterruptReturn();  

    ourState->laneFollow();
    InterruptReturn();  

    ourState->leftState90();
    ourState->leftState90();
    ourState->Nudge();
    ourState->laneFind("yellow");
    InterruptReturn();  
    ourState->handleState4();
    InterruptReturn(); 
    ourState->Nudge();
    InterruptReturn();  

    ourState->LeftColorTurn("yellow");
    InterruptReturn();  
    ourState->laneFollow();
    InterruptReturn();  

    ourState->leftState90();
    ourState->forwardUntilCollision();
}

/********** PartnerDemo1 ********
*
* Run the required logic to execute a partner-demo as Bot 1
*
************************/
void Demo::PartnerDemo1(){
    String partnerCommand;
    partnerCommand = ourWeb->PartnerReadServer();

    ourState->forwardUntilCollision();
    InterruptReturn();  
    delay(DEMO_DELAY);

    ourState->rightState90();
    InterruptReturn(); 
    ourState->rightState90();
    InterruptReturn(); 
    ourState->TimeForward(2500);

    ourState->laneFind("red");
    InterruptReturn();  
    ourWeb->WriteServer("State: Red");

   InterruptReturn();  
    ourState->Nudge();
    InterruptReturn();  
    ourState->LeftColorTurn("red");
    InterruptReturn();  

    ourState->laneFollow();
    InterruptReturn();  

    ourState->leftState90();
    ourState->laneFind("yellow");
    InterruptReturn();  
    ourState->Nudge();
    InterruptReturn();  
    ourState->LeftColorTurn("yellow");
    InterruptReturn();
    while (partnerCommand != "State: Blue") {
        partnerCommand = ourWeb->PartnerReadServer();
        delay(1);
        InterruptReturn();  
    }
    ourWeb->WriteServer("State: Yellow");
    
    InterruptReturn();  
    ourState->laneFollow();
    InterruptReturn();  

    ourState->leftState90();
    ourState->forwardUntilCollision();

    while (partnerCommand != "State: Done") {
        ourWeb->WriteServer("State: Done");
        partnerCommand = ourWeb->PartnerReadServer();
        delay(1);
        InterruptReturn();  
    }
    ourWeb->WriteServer("Hooray!");
    
}

/********** SoloDemo2 ********
*
* Run the required logic to execute a solo-demo starting from Pos2
*
************************/
void Demo::SoloDemo2(){
    ourState->forwardUntilCollision();
    InterruptReturn();  

    ourState->rightState90();
    InterruptReturn(); 

    ourState->rightState90();
    InterruptReturn(); 

    ourState->laneFind("blue");
    InterruptReturn();  

    ourState->Nudge();

    ourState->LeftColorTurn("blue");
    InterruptReturn(); 

    ourState->laneFollow();
    InterruptReturn(); 

    ourState->leftState90();
    ourState->laneFind("yellow");
    InterruptReturn(); 

    ourState->Nudge();

    ourState->LeftColorTurn("yellow");
    ourState->laneFollow();

    InterruptReturn(); 
    delay(DEMO_DELAY);

    ourState->leftState90();
    ourState->Nudge();
    ourState->forwardUntilCollision();
}


/********** PartnerDemo2 ********
*
* Run the required logic to execute a partner-demo as Bot 2
*
************************/
void Demo::PartnerDemo2(){
    String partnerCommand;

    while (partnerCommand != "State: Red") {
        partnerCommand = ourWeb->PartnerReadServer();
        delay(1);
        InterruptReturn();  
    }

    ourState->forwardUntilCollision();
    InterruptReturn();  
    delay(DEMO_DELAY);

    ourState->leftState90();
    InterruptReturn(); 
    ourState->leftState90();
    delay(2500);
    InterruptReturn(); 

    ourState->laneFind("blue");
    InterruptReturn();  
    ourState->RightColorTurn("blue");
    InterruptReturn(); 

    ourWeb->WriteServer("State: Blue");
    ourState->laneFollow();
    InterruptReturn();  

    ourState->rightState90();
    ourState->laneFind("yellow");
    InterruptReturn(); 
    ourState->Nudge();
    ourState->RightColorTurn("yellow");
    partnerCommand = ourWeb->PartnerReadServer();
    ourWeb->WriteServer("Waiting to read finish");
    while (partnerCommand != "State: Done") {
        partnerCommand = ourWeb->PartnerReadServer();
        delay(1);
        InterruptReturn();  
    }
    ourWeb->WriteServer("finishing up lane following");
    ourState->laneFollow();
    InterruptReturn(); 

    ourState->rightState90();
    ourState->forwardUntilCollision();

   ourWeb->WriteServer("State: Done");
}
