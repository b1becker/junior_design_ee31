#include <Arduino.h>
#include <WiFiNINA.h>
#include "States.h"
#include "BotMotions.h"
#include "colorSensing.h"
#include "collision.h"

#define StateDelay 500

/********** Constructir ********
*
* Makes BotMotion Object
*
* Parameters:
*      Arduino Pins
*
************************/
States::States(BotMotions *MyBot, WebSocket* server, collision *my_Collider, colorSensing *my_CS) {
    ourBot = MyBot;
    ourWeb = server;
    ourCollider = my_Collider;
    ourCS = my_CS;
}

void States::laneFollow(String output_color) {
    // hard coded inputs
    String myCommand = ourWeb->ReadServer();
    bool wallFound = false;
    int distance;
    // Bot 1 receives the signal and moves forward for five seconds then stop.
    while (myCommand != "Stop") {
        distance = ourCollider->loop(&wallFound);
        // ourWeb->WriteServer(String(distance)); 
        if (wallFound == true) {
            handleState0();
            break;
        }
        
        // UPDATE COLOR READING EVERY LOOP (no assignment needed)
        ourCS->loop(output_color);
        
        if(output_color != "red") {
            // correct itself
            // correct to the left
            handleState3();
            ourCS->loop(output_color);
            if(output_color != "red") {
                // correct to the right
                handleState4();
                handleState4();
                handleState4();
            }
        }
        else {
            handleState1();
        }
        delay(1);
        myCommand = ourWeb->ReadServer();
    }
}

/********** State 0 ********
*
* Stops bot
*
************************/   
void States::handleState0() {
    delay(StateDelay);
    ourBot->stop();
}

/********** State 1 ********
*
* Bot go forward
*
************************/   
void States::handleState1() {
    Serial.println("Going Forward");
    // delay(StateDelay);
    ourBot->forward();
}

/********** State 2 ********
*
* Back up da bot
*
************************/   
void States::handleState2() {
    Serial.println("Going backwards");
    delay(StateDelay);
    ourBot->backward();
}

/********** State 3 ********
*
* Clockwise spinning
*
************************/   
void States::handleState3() {
    Serial.println("Pivoting Clockwise");
    delay(StateDelay / 8);
    ourBot->pivotCW();
}

/********** State 4 ********
*
* Counter Clockwise spinning
*
************************/   
void States::handleState4() {
    Serial.println("Pivoting Counterclockwise");
    delay(StateDelay / 8);
    ourBot->pivotCCW();
}

/********** State 5 ********
*
* Bus a right
*
************************/   
void States::handleState5() {
    Serial.println("Turning Right");
    delay(StateDelay);
    ourBot->right();
}

/********** State 6 ********
*
* Bus a left
*
************************/   
void States::handleState6() {
    Serial.println("Turning Left");
    delay(StateDelay);
    ourBot->left();
    
}

/********** State 7 ********
*
* Uh oh error scary
*
************************/   
void States::handleErrorState() {
    Serial.println("MISINPUT: ABORT");
    delay(StateDelay);

}
