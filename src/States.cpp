#include <Arduino.h>
#include <WiFiNINA.h>
#include "States.h"
#include "BotMotions.h"
#include "colorSensing.h"
#include "collision.h"

#define StateDelay 50

// NOTE: Can't lower forward delay too much or color sensing/distance sensing
// voltage readings will fluctuate
#define FORWARD_DELAY 50

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
// void States::handleState00() {
//     String myCommand;
//     handleState1();
//     ourWeb->WriteServer("Place Bot on Black");
//     while (myCommand != "Black"){
//         myCommand = ourWeb->ReadServer();
//         delay(2);
//     }
//     ourWeb->WriteServer("Starting Calibration...");
//     ourLeftCS->Calibrate(COLOR_BLACK);
//     ourRightCS->Calibrate(COLOR_BLACK);
//     ourWeb->WriteServer("Black Done.");

//     //Red Calibration
//     ourWeb->WriteServer("Place Bot on Red");
//     while (myCommand != "Red"){
//         myCommand = ourWeb->ReadServer();
//         delay(2);
//     }
//     ourWeb->WriteServer("Starting Calibration...");
//     ourLeftCS->Calibrate(COLOR_RED);
//     ourRightCS->Calibrate(COLOR_RED);
//     ourWeb->WriteServer("Red Done.");

//     //Blue Calibration
//     ourWeb->WriteServer("Place Bot on Blue");
//     while (myCommand != "Blue"){
//         myCommand = ourWeb->ReadServer();
//         delay(2);
//     }
//     ourWeb->WriteServer("Starting Calibration...");
//     ourLeftCS->Calibrate(COLOR_BLUE);
//     ourRightCS->Calibrate(COLOR_BLUE);
//     ourWeb->WriteServer("Blue Done.");

//     //Yellow Calibration 
//     ourWeb->WriteServer("Place Bot on Yellow");
//     while (myCommand != "Yellow"){
//         myCommand = ourWeb->ReadServer();
//         delay(2);
//     }
//     ourWeb->WriteServer("Starting Calibration...");
//     handleState1();
//     ourLeftCS->Calibrate(COLOR_YELLOW);
//     handleState1();
//     ourRightCS->Calibrate(COLOR_YELLOW);
//     ourWeb->WriteServer("Yellow Done.");

//     handleState0();
    

//     ourWeb->WriteServer("Final Values");
//     String message;
//     message = "Black - Left: R=" + String(ourLeftCS->colorVal[COLOR_BLACK].red) + " B=" + String(ourLeftCS->colorVal[COLOR_BLACK].blue)
//         + " | Right: R=" + String(ourRightCS->colorVal[COLOR_BLACK].red) + " B=" + String(ourRightCS->colorVal[COLOR_BLACK].blue)
//         + "\nRed - Left: R=" + String(ourLeftCS->colorVal[COLOR_RED].red) + " B=" + String(ourLeftCS->colorVal[COLOR_RED].blue)
//         + " | Right: R=" + String(ourRightCS->colorVal[COLOR_RED].red) + " B=" + String(ourRightCS->colorVal[COLOR_RED].blue)
//         + "\nBlue - Left: R=" + String(ourLeftCS->colorVal[COLOR_BLUE].red) + " B=" + String(ourLeftCS->colorVal[COLOR_BLUE].blue)
//         + " | Right: R=" + String(ourRightCS->colorVal[COLOR_BLUE].red) + " B=" + String(ourRightCS->colorVal[COLOR_BLUE].blue)
//         + "\nYellow - Left: R=" + String(ourLeftCS->colorVal[COLOR_YELLOW].red) + " B=" + String(ourLeftCS->colorVal[COLOR_YELLOW].blue)
//         + " | Right: R=" + String(ourRightCS->colorVal[COLOR_YELLOW].red) + " B=" + String(ourRightCS->colorVal[COLOR_YELLOW].blue);
//     ourWeb->WriteServer(message);
// }

void States::handleState00() {
    String myCommand;
    
    // Calibrate all 4 colors
    const char* colors[] = {"Black", "Red", "Blue", "Yellow"};
    ColorTag colorTags[] = {COLOR_BLACK, COLOR_RED, COLOR_BLUE, COLOR_YELLOW};
    
    for (int i = 0; i < 4; i++) {
        ourWeb->WriteServer("Place Bot on " + String(colors[i]));
        myCommand = "";
        while (myCommand != colors[i]) {
            myCommand = ourWeb->ReadServer();
            delay(2);
        }
        ourWeb->WriteServer("Starting Calibration...");
        ourLeftCS->Calibrate(colorTags[i]);
        ourRightCS->Calibrate(colorTags[i]);
        ourWeb->WriteServer(String(colors[i]) + " Done.");
    }
    
    // Display all values
    ourWeb->WriteServer("Final Values");

    // Black
    ourWeb->WriteServer("Black - Left: R=" + String(ourLeftCS->colorVal[COLOR_BLACK].red) 
                    + " B=" + String(ourLeftCS->colorVal[COLOR_BLACK].blue)
                    + " | Right: R=" + String(ourRightCS->colorVal[COLOR_BLACK].red) 
                    + " B=" + String(ourRightCS->colorVal[COLOR_BLACK].blue));

    // Red
    ourWeb->WriteServer("Red - Left: R=" + String(ourLeftCS->colorVal[COLOR_RED].red) 
                    + " B=" + String(ourLeftCS->colorVal[COLOR_RED].blue)
                    + " | Right: R=" + String(ourRightCS->colorVal[COLOR_RED].red) 
                    + " B=" + String(ourRightCS->colorVal[COLOR_RED].blue));

    // Blue
    ourWeb->WriteServer("Blue - Left: R=" + String(ourLeftCS->colorVal[COLOR_BLUE].red) 
                    + " B=" + String(ourLeftCS->colorVal[COLOR_BLUE].blue)
                    + " | Right: R=" + String(ourRightCS->colorVal[COLOR_BLUE].red) 
                    + " B=" + String(ourRightCS->colorVal[COLOR_BLUE].blue));

    // Yellow
    ourWeb->WriteServer("Yellow - Left: R=" + String(ourLeftCS->colorVal[COLOR_YELLOW].red) 
                    + " B=" + String(ourLeftCS->colorVal[COLOR_YELLOW].blue)
                    + " | Right: R=" + String(ourRightCS->colorVal[COLOR_YELLOW].red) 
                    + " B=" + String(ourRightCS->colorVal[COLOR_YELLOW].blue));

    ourWeb->WriteServer("Ready to move!");
}

void States::laneFollow() {
    ourCollider->setup();
    handleState0();
    // hard coded inputs
    String LeftColor;
    String RightColor;
    String myCommand = ourWeb->ReadServer();
    bool wallFound = false;
    int distance;
    // Bot 1 receives the signal and moves forward for five seconds then stop.
    static unsigned long lastSend = 0;
    handleState1();
    while (myCommand != "Stop") {
        // distance = ourCollider->loop(&wallFound);


        ourRightCS->loop(RightColor);
        ourLeftCS->loop(LeftColor);
        
        
        
        
        if (millis() - lastSend > 2000) {      
            String message = "R: " + RightColor + " L: " + LeftColor + " D: " + String(distance);
            ourWeb->WriteServer(message);
            lastSend = millis();
        }
        
        


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
    delay(FORWARD_DELAY);
    
    Serial.println("Going Forward");
    // delay(StateDelay);
    ourBot->forward();
    delay(FORWARD_DELAY);
    
    
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
