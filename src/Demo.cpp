#include <Arduino.h>
#include "BotMotions.h"
#include "WebSocket.h"
#include "Demo.h"
#include "States.h"


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
    delay(STD_DELAY);

// Cross back to find the red lane, 
// Two 90 degree turns to 180
    ourState->rightState90();
    ourState->rightState90();

    // delay(STD_DELAY);
    ourState->laneFind("red");

    ourState->handleState4();
    ourState->laneFind("black");
// Follow the red lane until it senses the wall at the right
    ourState->leftState90();
    ourState->laneFollow();
// Turn left and find the yellow lane
    ourState->leftState90();

    ourState->laneFind("yellow");
    ourState->handleState4();
    ourState->laneFind("black");
// Follow the yellow lane until it senses the wall at the left
    ourState->leftState90();
    ourState->laneFollow();
// Turn left and return to the starting position
    ourState->leftState90();
    ourState->forwardUntilCollision();
}

/********** SoloDemo2 ********
*
* Run the required logic to execute a solo-demo starting from Pos2
*
************************/
void Demo::SoloDemo2(){
    // Cross to the other side
    // Stop when it senses the wall at the top and turn around 
    // Cross back to find the blue lane
    // Follow the blue lane until it senses the wall at the right
    // Turn right and find the yellow lane
    // Follow the yellow lane until it senses the wall at the left
    // Turn right and return to the starting position
}

/********** PartnerDemo ********
*
* Run the required logic to execute a partner-demo
*
************************/
void Demo::PartnerDemo(){

        /*
        Bot 1 beeps its horn and starts.  Bot 2 waits (W).   
        Once bot 1 has started moving along the red lane, it posts a "red lane found" signal to the server.  
        This tells bot 2 that it is safe to start.
        */
        
        /*
        Bot 2 beeps its horn and starts.  
        Bot 1 proceeds to the start of the yellow lane and waits.   
        Once bot 2 has started moving along the blue lane, it posts a "blue lane found" signal to the server.   
        This tells bot 1 that it is safe to proceed along the yellow lane.  
        Bot 1 sends an acknowledgment signal, which tells bot 2 that it is safe to continue to the start of the yellow lane.
        */

        /*
        Bot 1 follows the yellow lane and returns home. 
        Once home, it beeps its horn and posts a "returned" signal to the server.   
        This tells bot 2 that it is safe to proceed along the yellow lane.
        */

        /*
        Bot 2 follows the yellow lane and returns home.  
        Once home, it beeps its horn and posts a "returned" signal to the server.  
        Bot 1 acknowledges the signal with a horn beep.
        */
    
    
}

