#include <Arduino.h>
#include "BotMotions.h"
#include "WebSocket.h"
#include "Demo.h"
#include "States.h"

extern volatile bool interruptTriggered;

#define Running true
#define Complete false

#define STD_DELAY 1000

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

    // Bot 1 communicates to Bot 2 to move forward for five seconds. 
    ourWeb->WriteServer("State: 1");
    
    String partnerCommand = ourWeb->PartnerReadServer();

    // Bot 1 receives the signal and moves forward for five seconds then stop.
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
// Cross to the other side, 
    ourState->forwardUntilCollision();
    if(interruptTriggered) {return;}  
    delay(STD_DELAY);

// Cross back to find the red lane, 
// Two 90 degree turns to 180
    ourState->rightState90();
    if(interruptTriggered) {return;} 
    ourState->rightState90();
    if(interruptTriggered) {return;} 
    
    // delay(STD_DELAY);
    ourState->laneFind("red");
    if(interruptTriggered) {return;}  
    ourState->Nudge();
    // State4: pivot slight right
    // ourState->handleState4();
    if(interruptTriggered) {return;}  
    ourState->LeftColorTurn("red");
    if(interruptTriggered) {return;}  
// Follow the red lane until it senses the wall at the right
    // ourState->leftState90();
    ourState->laneFollow();
    if(interruptTriggered) {return;}  
// Turn left and find the yellow lane
    ourState->leftState90();
    ourState->laneFind("yellow");
    if(interruptTriggered) {return;}  
    ourState->handleState4();
    if(interruptTriggered) {return;} 
    ourState->Nudge();
    if(interruptTriggered) {return;}  
// Follow the yellow lane until it senses the wall at the left
    ourState->LeftColorTurn("yellow");
    if(interruptTriggered) {return;}  
    ourState->laneFollow();
    if(interruptTriggered) {return;}  
// Turn left and return to the starting position
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
    /*
    Bot 1 beeps its horn and starts.  Bot 2 waits (W).   
    Once bot 1 has started moving along the red lane, it posts a "red lane found" signal to the server.  
    This tells bot 2 that it is safe to start.
    */
// Cross to the other side, 
    ourState->forwardUntilCollision();
    if(interruptTriggered) {return;}  
    delay(STD_DELAY);

// Cross back to find the red lane, 
// Two 90 degree turns to 180
    ourState->rightState90();
    if(interruptTriggered) {return;} 
    ourState->rightState90();
    if(interruptTriggered) {return;} 
    
    // delay(STD_DELAY);
    ourState->laneFind("red");
    if(interruptTriggered) {return;}  
    ourWeb->WriteServer("State: Red");
    /*
    Bot 2 beeps its horn and starts.  
    Bot 1 proceeds to the start of the yellow lane and waits.   
    Once bot 2 has started moving along the blue lane, it posts a "blue lane found" signal to the server.   
    This tells bot 1 that it is safe to proceed along the yellow lane.  
    Bot 1 sends an acknowledgment signal, which tells bot 2 that it is safe to continue to the start of the yellow lane.
    */
// Turn left and find the yellow lane
    ourState->leftState90();
    ourState->laneFind("yellow");
    if(interruptTriggered) {return;}  
    ourState->handleState4();
    if(interruptTriggered) {return;} 
    ourState->Nudge();
    if(interruptTriggered) {return;}  
    ourState->LeftColorTurn("yellow");
    if(interruptTriggered) {return;}
    while (partnerCommand != "State: Blue") {
        partnerCommand = ourWeb->PartnerReadServer();
        delay(1);
        if(interruptTriggered) {return;}  
    }
    ourWeb->WriteServer("State: Yellow");
    /*
    Bot 1 follows the yellow lane and returns home. 
    Once home, it beeps its horn and posts a "returned" signal to the server.   
    This tells bot 2 that it is safe to proceed along the yellow lane.
    */
// Follow the yellow lane until it senses the wall at the left
    
    if(interruptTriggered) {return;}  
    ourState->laneFollow();
    if(interruptTriggered) {return;}  
// Turn left and return to the starting position
    ourState->leftState90();
    ourState->forwardUntilCollision();
    ourWeb->WriteServer("State: Done");
    /*
    Bot 2 follows the yellow lane and returns home.  
    Once home, it beeps its horn and posts a "returned" signal to the server.  
    Bot 1 acknowledges the signal with a horn beep.
    */
    while (partnerCommand != "State: Done") {
        partnerCommand = ourWeb->PartnerReadServer();
        delay(1);
        if(interruptTriggered) {return;}  
    }
    ourWeb->WriteServer("Hooray!");
    
}

/********** SoloDemo2 ********
*
* Run the required logic to execute a solo-demo starting from Pos2
*
************************/
void Demo::SoloDemo2(){
// Cross to the other side
    ourState->forwardUntilCollision();
    if(interruptTriggered) {return;}  

// Stop when it senses the wall at the top and turn around 
    ourState->rightState90();
    if(interruptTriggered) {return;} 

    ourState->rightState90();
    if(interruptTriggered) {return;} 

// Cross back to find the blue lane
    ourState->laneFind("blue");
    if(interruptTriggered) {return;}  

    ourState->Nudge();

    ourState->LeftColorTurn("blue");
    if(interruptTriggered) {return;} 

// Follow the blue lane until it senses the wall at the right
    ourState->laneFollow();
    if(interruptTriggered) {return;} 

// Turn right and find the yellow lane
    ourState->leftState90();
    ourState->laneFind("yellow");
    if(interruptTriggered) {return;} 

    ourState->Nudge();

    ourState->LeftColorTurn("yellow");
    ourState->laneFollow();

    if(interruptTriggered) {return;} 
    delay(STD_DELAY);
// Follow the yellow lane until it senses the wall at the left
// Turn right and return to the starting position
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
    /*
    Bot 1 beeps its horn and starts.  Bot 2 waits (W).   
    Once bot 1 has started moving along the red lane, it posts a "red lane found" signal to the server.  
    This tells bot 2 that it is safe to start.
    */
    while (partnerCommand != "State: Red") {
        partnerCommand = ourWeb->PartnerReadServer();
        delay(1);
        if(interruptTriggered) {return;}  
    }
    /*
    Bot 2 beeps its horn and starts.  
    Bot 1 proceeds to the start of the yellow lane and waits.   
    Once bot 2 has started moving along the blue lane, it posts a "blue lane found" signal to the server.   
    This tells bot 1 that it is safe to proceed along the yellow lane.  
    Bot 1 sends an acknowledgment signal, which tells bot 2 that it is safe to continue to the start of the yellow lane.
    */
    ourWeb->WriteServer("Beep!");
// Cross to the other side
    ourState->forwardUntilCollision();
    if(interruptTriggered) {return;}  
    delay(STD_DELAY);
// Stop when it senses the wall at the top and turn around 
    ourState->leftState90();
    if(interruptTriggered) {return;} 
    ourState->leftState90();
    if(interruptTriggered) {return;} 
// Cross back to find the blue lane
    ourState->laneFind("blue");
    if(interruptTriggered) {return;}  
    ourState->RightColorTurn("blue");
    if(interruptTriggered) {return;} 
// Follow the blue lane until it senses the wall at the right
    ourWeb->WriteServer("State: Blue");
    ourState->laneFollow();
    if(interruptTriggered) {return;}  
    /*
    Bot 1 follows the yellow lane and returns home. 
    Once home, it beeps its horn and posts a "returned" signal to the server.   
    This tells bot 2 that it is safe to proceed along the yellow lane.
    */
// Turn right and find the yellow lane
    ourState->rightState90();
    ourState->laneFind("yellow");
    if(interruptTriggered) {return;} 
    ourState->Nudge();
    ourState->RightColorTurn("yellow");
    while (partnerCommand != "State: Done") {
        partnerCommand = ourWeb->PartnerReadServer();
        delay(1);
        if(interruptTriggered) {return;}  
    }
    ourState->laneFollow();
    if(interruptTriggered) {return;} 
// Follow the yellow lane until it senses the wall at the left
// Turn right and return to the starting position
    ourState->rightState90();
    ourState->forwardUntilCollision();
    /*
    Bot 2 follows the yellow lane and returns home.  
    Once home, it beeps its horn and posts a "returned" signal to the server.  
    Bot 1 acknowledges the signal with a horn beep.
    */ 
   ourWeb->WriteServer("State: Done");
}
