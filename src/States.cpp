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
    
    ourRightCS = my_LeftCS;
    ourLeftCS = my_RightCS;
    
}

/********** State 00 ********
*
* Calibrates bot colors
*
************************/   
void States::handleState00() {
    String myCommand;
    
    // Calibrate all 4 colors
    const char *colors[] = {"Black", "Red", "Blue", "Yellow"};
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

/********** LaneFollow ********
*
* Follow some lane.
* Follows whatever color it starts on.
*
************************/
void States::laneFollow() {
    ourCollider->setup();
    handleState0();
    
    String LeftColor;
    String RightColor;
    String myCommand = ourWeb->ReadServer();

    ColorRef curr_ref_right;
    ColorRef curr_ref_left;
    bool wallFound = false;
    int distance;

    String target_color;
    ourRightCS->loop(target_color, curr_ref_right);

    
    static unsigned long lastSend = 0;
    handleState1();  // Start moving forward

    while (myCommand != "Stop") {
        // Get color readings
        ourRightCS->loop(RightColor, curr_ref_right);
        ourLeftCS->loop(LeftColor, curr_ref_left);

        if (millis() - lastSend > 2000) {      
            String message = "R: " + RightColor + " L: " + LeftColor + " D: " + String(distance);
            ourWeb->WriteServer(message);
            lastSend = millis();
        }

        distance = ourCollider->loop(&wallFound);
        if (wallFound == true) {
            handleState0();
            break;
        }
        handleState1();
        // Lane following logic (runs every loop, not in else-if)
        if (LeftColor != target_color && RightColor == target_color) {
            // Left sensor off line, right on line → turn left
            handleState3();
        }
        else if (RightColor != target_color && LeftColor == target_color) {
            // Right sensor off line, left on line → turn right
            handleState4();
        }
        else if (LeftColor == target_color && RightColor == target_color) {
            // Both on line → go straight
            handleState1();
        }
        else {
            // Both off line → stop or continue last action
            handleState3();  // or keep last state
        }
        
        // Check connection
        if (!ourWeb->ConnectionStatus()) {
            Serial.println("Connection lost");
            handleState0();
            break;
        }
        
        delay(1);
        myCommand = ourWeb->ReadServer();
    }
    
    handleState0();  // Stop when exiting
}

/********** LaneFind ********
*
* Runs forawrds till it finds given color.
*
* Parameters:
*      string for color
************************/
void States::laneFind(String targetColor) {
    // ourCollider->setup();
    handleState0();
    
    String LeftColor;
    String RightColor;

    ColorRef curr_ref_right;
    ColorRef curr_ref_left;

    String target_color = targetColor;

    handleState1();  // Start moving forward

    while (targetColor != RightColor || targetColor != LeftColor) {
        // Get color readings
        ourRightCS->loop(RightColor, curr_ref_right);
        ourLeftCS->loop(LeftColor, curr_ref_left);

        handleState1();
        delay(1);
    }
    handleState0();  // Stop when exiting
}

/********** State 0 ********
*
* Stops bot
*
************************/   
void States::handleState0() {
    // delay(StateDelay);
    ourBot->stop();
}

/********** State 1 ********
*
* Bot go forward
*
************************/   
void States::handleState1() {
    delay(FORWARD_DELAY);
    
    // Serial.println("Going Forward");
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
    // Serial.println("Going backwards");
    // delay(StateDelay);
    ourBot->backward();
}

/********** State 3 ********
*
* Clockwise spinning
*
************************/   
void States::handleState3() {
    // Serial.println("Pivoting Clockwise");
    delay(StateDelay / 8);
    ourBot->pivotCW();
}

/********** State 4 ********
*
* Counter Clockwise spinning
*
************************/   
void States::handleState4() {
    // Serial.println("Pivoting Counterclockwise");
    delay(StateDelay / 8);
    ourBot->pivotCCW();
}

/********** State 5 ********
*
* Bus a right
*
************************/   
void States::handleState5() {
    // Serial.println("Turning Right");
    // delay(StateDelay);
    ourBot->right();
}

/********** State 6 ********
*
* Bus a left
*
************************/   
void States::handleState6() {
    // Serial.println("Turning Left");
    // delay(StateDelay);
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

/********** State 8 ********
*
* Bot goes forward until collison detected
*
************************/ 
void States::forwardUntilCollision() {
    handleState0();
    Serial.println("going forward until collision");
    ourCollider->setup();
    int distance;

    bool wallFound = false;

    distance = ourCollider->loop(&wallFound);

    while (!wallFound) {
        handleState1();
        distance = ourCollider->loop(&wallFound);
        Serial.println("distance: ");
        Serial.println(distance);
        
    }
    
}

/********** State 10 ********
*
* Bot turns 90 degrees to the left
*
************************/ 
void States::leftState90() {
    ourBot->left90();
}

/********** State 9 ********
*
* Bot turns 90 degrees to the right
*
************************/ 
void States::rightState90() {
    ourBot->right90();
}