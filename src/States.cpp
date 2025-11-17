#include <Arduino.h>
#include <WiFiNINA.h>
#include "States.h"
#include "BotMotions.h"
#include "colorSensing.h"
#include "collision.h"

#define StateDelay 500

#define Black 0
#define Red 1
#define Blue 2
#define Yellow 3

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
    }
    ourWeb->WriteServer("Starting Calibration...");
    ourCS->Calibrate(Black);
    ourWeb->WriteServer("Black Done.");

    //Red Calibration
    delay(StateDelay);
    ourWeb->WriteServer("Place Bot on Red");
    while (myCommand != "Red"){
        myCommand = ourWeb->ReadServer();
    }
    ourWeb->WriteServer("Starting Calibration...");
    ourCS->Calibrate(Red);
    ourWeb->WriteServer("Red Done.");

    //Blue Calibration
    delay(StateDelay);
    ourWeb->WriteServer("Place Bot on Blue");
    while (myCommand != "Blue"){
        myCommand = ourWeb->ReadServer();
    }
    ourWeb->WriteServer("Starting Calibration...");
    ourCS->Calibrate(Blue);
    ourWeb->WriteServer("Blue Done.");

    //Yellow Calibration 
    delay(StateDelay);
    ourWeb->WriteServer("Place Bot on Yellow");
    while (myCommand != "Yellow"){
        myCommand = ourWeb->ReadServer();
    }
    ourWeb->WriteServer("Starting Calibration...");
    ourCS->Calibrate(Yellow);
    ourWeb->WriteServer("Yellow Done.");
}

void States::laneFollow(String output_color) {
    // hard coded inputs
    String myCommand = ourWeb->ReadServer();
    bool wallFound = false;
    int distance;
    // Bot 1 receives the signal and moves forward for five seconds then stop.
    while (myCommand != "Stop") {
        distance = ourCollider->loop(&wallFound);
        ourWeb->WriteServer(String(distance)); 
        handleState1();
        // if (wallFound == true) {
        //     handleState0();
        //     break;
        // }
        

        ourCS->loop(output_color);
        Serial.println(output_color);
        delay(StateDelay);
        // if(output_color != "red") {
        //     // correct itself
        //     // correct to the left
        //     handleState3();
        //     ourCS->loop(output_color);
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
