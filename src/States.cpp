#include <Arduino.h>
#include <WiFiNINA.h>
#include "States.h"
#include "BotMotions.h"
#include "colorSensing.h"
#include "collision.h"

#define StateDelay 50


/********** Constructir ********
*
* Makes BotMotion Object
*
* Parameters:
*      Arduino Pins
*
************************/
States::States(BotMotions *MyBot, WebSocket* server, collision *my_Collider, colorSensing *my_LeftCS, colorSensing *my_RightCS) {
    ourBot = MyBot;
    ourWeb = server;
    ourCollider = my_Collider;
    ourLeftCS = my_LeftCS;
    ourRightCS = my_RightCS;
}

/********** State 00 ********
*
* Calibrates bot colors
*
************************/   
void States::handleState00() {
    String myCommand;

    //Black Calibration
    delay(StateDelay);
    ourWeb->WriteServer("Place Bot on Black");
    while (myCommand != "Black"){
        myCommand = ourWeb->ReadServer();
        delay(2);
    }
    ourWeb->WriteServer("Starting Calibration...");
    ourLeftCS->Calibrate(COLOR_BLACK);
    ourRightCS->Calibrate(COLOR_BLACK);
    ourWeb->WriteServer("Black Done.");

    //Red Calibration
    delay(StateDelay);
    ourWeb->WriteServer("Place Bot on Red");
    while (myCommand != "Red"){
        myCommand = ourWeb->ReadServer();
        delay(2);
    }
    ourWeb->WriteServer("Starting Calibration...");
    ourLeftCS->Calibrate(COLOR_RED);
    ourRightCS->Calibrate(COLOR_RED);
    ourWeb->WriteServer("Red Done.");

    //Blue Calibration
    delay(StateDelay);
    ourWeb->WriteServer("Place Bot on Blue");
    while (myCommand != "Blue"){
        myCommand = ourWeb->ReadServer();
        delay(2);
    }
    ourWeb->WriteServer("Starting Calibration...");
    ourLeftCS->Calibrate(COLOR_BLUE);
    ourRightCS->Calibrate(COLOR_BLUE);
    ourWeb->WriteServer("Blue Done.");

    //Yellow Calibration 
    delay(StateDelay);
    ourWeb->WriteServer("Place Bot on Yellow");
    while (myCommand != "Yellow"){
        myCommand = ourWeb->ReadServer();
        delay(2);
    }
    ourWeb->WriteServer("Starting Calibration...");
    ourLeftCS->Calibrate(COLOR_YELLOW);
    ourRightCS->Calibrate(COLOR_YELLOW);
    ourWeb->WriteServer("Yellow Done.");

    ourWeb->WriteServer("Final Values");
    String message;
    message = "Black, Left: " + String(ourLeftCS->colorVal[COLOR_BLACK]) +  " Right: " + String(ourRightCS->colorVal[COLOR_BLACK]);
    ourWeb->WriteServer(message);
    message = "Red, Left: " + String(ourLeftCS->colorVal[COLOR_RED]) +  " Right: " + String(ourRightCS->colorVal[COLOR_RED]);
    ourWeb->WriteServer(message);
    message = "Blue, Left: " + String(ourLeftCS->colorVal[COLOR_BLUE]) +  " Right: " + String(ourRightCS->colorVal[COLOR_BLUE]);
    ourWeb->WriteServer(message);
    message = "Yellow, Left: " + String(ourLeftCS->colorVal[COLOR_YELLOW]) +  " Right: " + String(ourRightCS->colorVal[COLOR_YELLOW]);
    ourWeb->WriteServer(message);
}

void States::laneFollow() {
    ourCollider->setup();
    // hard coded inputs
    String LeftColor;
    String RightColor;
    String myCommand = ourWeb->ReadServer();
    bool wallFound = false;
    int distance;
    // Bot 1 receives the signal and moves forward for five seconds then stop.
    static unsigned long lastSend = 0;
    while (myCommand != "Stop") {
        distance = ourCollider->loop(&wallFound);
        ourLeftCS->loop(LeftColor);
        ourRightCS->loop(RightColor);
        
        if (millis() - lastSend > 2000) {      
            String message = "R: " + RightColor + " L: " + LeftColor + " D: " + String(distance);
            ourWeb->WriteServer(message);
            lastSend = millis();
        }

        
        handleState1();
        // if (wallFound == true) {
        //     handleState0();
        //     break;
        // }
        

        

        // if(LeftColor != "red" && RightColor == "red") {
        //     // We have veered left
        //     handleState4();
        // } else if (RightColor != "red" && LeftColor == "red"){
        //     handleState3();
        // } else {
        //     handleState1();
        // }
        // if(output_color != "red") {
        //     // correct itself
        //     // correct to the left
        //     handleState3();
        //     ourLeftCS->loop(output_color);
        //     if(output_color != "red") {
        //         // correct to the right
        //         handleState4();
        //         handleState4();
        //         handleState4();
        //     }
        // }
        // else {
        //     handleState1();
        // }
        if (!ourWeb->ConnectionStatus()) {
            Serial.println("Connection lost");
            break;
        }
        
        
        delay(1);
        myCommand = ourWeb->ReadServer();
        delay(1);
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
    // delay(StateDelay);
    ourBot->forward();
}

/********** State 2 ********
*
* Back up da bot
*
************************/   
void States::handleState2() {
    delay(StateDelay);
    ourBot->backward();
}

/********** State 3 ********
*
* Clockwise spinning
*
************************/   
void States::handleState3() {
    delay(StateDelay / 8);
    ourBot->pivotCW();
}

/********** State 4 ********
*
* Counter Clockwise spinning
*
************************/   
void States::handleState4() {
    delay(StateDelay / 8);
    ourBot->pivotCCW();
}

/********** State 5 ********
*
* Bus a right
*
************************/   
void States::handleState5() {
    delay(StateDelay);
    ourBot->right();
}

/********** State 6 ********
*
* Bus a left
*
************************/   
void States::handleState6() {
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
