#include <Arduino.h>
#include "BotMotions.h"
#include "WebSocket.h"
#include "Demo.h"


/********** Constructir ********
*
* Links BotMotion Object
*
* Parameters:
*      Arduino Pins
*
************************/
Demo::Demo(BotMotions *MyBot, WebSocket* server) {
    ourBot = MyBot;
    ourWeb = server;
}

/********** Remote Partner Check Off ********
*
*   Required logic to pass the partner check off
*
************************/
void Demo::remotePartnerMotions(){
    // Both bots are next to each other and not moving.
    // Bot 1 flashes their Arduino LED.
    // Bot 1 communicates to Bot 2 to move forward for five seconds. 
    // Bot 2 receives the message and move forward for five seconds then stops.
    // When Bot 2 is finished moving forward, it flashes it's built-in LED. 
    // Bot 2 communicates to Bot 1 to move forward for five seconds. 
    // Bot 1 receives the signal and moves forward for five seconds then stop.
}

/********** SoloDemo1 ********
*
* Run the required logic to execute a solo-demo starting from Pos1
*
************************/
void Demo::SoloDemo1(){
// Cross to the other side, 
    ourBot->forward();
// Stop when it senses the wall at the top and turn around
    // If (wall detected) {
    //     ourBot->stop()
    // }

// Cross back to find the red lane, 
    // Two 90 degree turns to 180
    ourBot->pivotCCW(); 
    ourBot->pivotCCW();

    ourBot->forward();
    // If (red detected) {
    //     ourBot->stop()
    // }
    ourBot->pivotCCW();
    // INSERT color following action code (Likely new class)

    // Follow the red lane until it senses the wall at the right
    // Turn left and find the yellow lane
    // Follow the yellow lane until it senses the wall at the left
    // Turn left and return to the starting position
    ourBot->left();
    // If (wall detected) {
    //     ourBot->stop()
    // }
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

