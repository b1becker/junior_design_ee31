#include <Arduino.h>
#include <WiFiNINA.h>
#include "States.h"
#include "BotMotions.h"
#include "ColorSensing.h"
#include "Collision.h"
#include "Constants.h"


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

/*****************************************************************
*                  Simple Functions
*****************************************************************/

/********** State 0 ********
*
* Stops bot
*
************************/   
void States::handleState0() {
    ourBot->stop();
}

/********** State 1 ********
*
* Bot go forward
*
************************/   
void States::handleState1() {
    delay(FORWARD_DELAY);
    ourBot->forward();
    delay(FORWARD_DELAY);
    
    
}

/********** State 2 ********
*
* Back up da bot
*
************************/   
void States::handleState2() {
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
    ourBot->right();
}

/********** State 6 ********
*
* Bus a left
*
************************/   
void States::handleState6() {
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

/********** leftState90 ********
*
* Bot turns 90 degrees to the left
*
************************/ 
void States::leftState90() {
    ourBot->left90();
}

/********** rightState90 ********
*
* Bot turns 90 degrees to the right
*
************************/ 
void States::rightState90() {
    ourBot->right90();
}

/********** Nudge ********
*
* Moves the bot forward a teensy amount
*
************************/
void States::Nudge() {
    ourBot->forward();
    delay(500);
    ourBot->stop();
}

/********** TimeForward ********
*
* Moves the bot forward for a given amount of time.
*
* Parameters:
*      Length of time in ms to move forward for.
*
************************/
void States::TimeForward(int time) {
    ourBot->forward();
    delay(time);
    ourBot->stop();
}


/*****************************************************************
*                  Complex Functions
*****************************************************************/

/********** LaneFollow ********
*
* Follow some lane.
* Follows whatever color it starts on.
*
************************/
void States::laneFollow() {
    
    handleState0();
    Serial.println("follwinguntil collision");
    delay(FORWARD_DELAY);
    
    String LeftColor;
    String RightColor;
    String myCommand = ourWeb->ReadServer();

    ColorRef curr_ref_right;
    ColorRef curr_ref_left;
    bool wallFound = false;

    int distance;

    String target_color;
    ourRightCS->loop(target_color, curr_ref_right);

    handleState1(); 

    static unsigned long four_seconds_buffer = millis();

    while (true) {
        ourRightCS->loop(RightColor, curr_ref_right);
        ourLeftCS->loop(LeftColor, curr_ref_left);

        
        handleState1();

        if (LeftColor != target_color && RightColor == target_color) {
            handleState3();
        }
        else if (RightColor != target_color && LeftColor == target_color) {
            handleState4();
        }
        else if (LeftColor == target_color && RightColor == target_color) {
            handleState1();
        }
        else {
            handleState3();
        }

        if(myCommand == "Stop") {break;}
        myCommand = ourWeb->ReadServer();
    }
    handleState0();
}

/********** LaneFind ********
*
* Runs forawrds till it finds given color.
*
* Parameters:
*      string for color
************************/
void States::laneFind(String targetColor) {
    handleState0();
    
    String LeftColor;
    String RightColor;
    ColorRef curr_ref_right;
    ColorRef curr_ref_left;
    String target_color = targetColor;

    handleState1();

    while (targetColor != RightColor || targetColor != LeftColor) {
        ourRightCS->loop(RightColor, curr_ref_right);
        ourLeftCS->loop(LeftColor, curr_ref_left);

        handleState1();
        delay(1);
        if(interruptTriggered){break;}
    }
    handleState0();
}

/********** forwardUntilCollision ********
*
* Bot goes forward until collison detected
*
************************/ 
void States::forwardUntilCollision() {
    
    String message = ourWeb->ReadServer();
    handleState0();
    Serial.println("going forward until collision");
    delay(FORWARD_DELAY);
    ourCollider->setup();
    int distance;

    bool wallFound = false;

    distance = ourCollider->loop(&wallFound);
    
    unsigned long startTime = millis(); 
    const unsigned long maxDuration = 500;

    while (true) {
        if (wallFound == true) {
            handleState0();
            break;
        }
        
        handleState1();
        distance = ourCollider->loop(&wallFound);


        if(interruptTriggered){break;}
        if(message == "Stop") {break;}
        message = ourWeb->ReadServer();
    }
    
    handleState0();
}

/********** LeftColorTUrn ********
*
* Turns left until target color is detected
*
* Parameters:
*      String: Color to find
*
************************/
void States::LeftColorTurn(String targetColor) {
    handleState0();
    
    String RightColor;
    ColorRef curr_ref_right;
    String target_color = targetColor;

    handleState4();

    while (targetColor != RightColor) {
        ourRightCS->loop(RightColor, curr_ref_right);

        handleState4();
        delay(1);
        if(interruptTriggered){break;}
    }
    handleState0();
}

/********** RightColorTUrn ********
*
* Turns right until target color is detected
*
* Parameters:
*      String: Color to find
*
************************/
void States::RightColorTurn(String targetColor) {
    handleState0();
    
    String RightColor;

    ColorRef curr_ref_right;

    String target_color = targetColor;

    handleState3();

    while (targetColor != RightColor) {
        ourRightCS->loop(RightColor, curr_ref_right);

        handleState3();
        delay(1);
        if(interruptTriggered){break;}
    }
    handleState0();
}

