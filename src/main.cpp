#include "States.h"
#include "Demo.h"
#include "WebSocket.h"
#include "BotMotions.h"
#include "States.h"
#include "colorSensing.h"
#include "collision.h"
#include <Arduino.h>
#include <ArduinoHttpClient.h>
#include <WiFiNINA.h> 

volatile bool interruptTriggered = false;
void interrupt();


//Color Sensing Calibration:
#define Black 0
#define Red 1
#define Blue 2
#define Yellow 3


// Motor A (Right Motor)
#define MOTOR_A1 4    // L293 IN1
#define MOTOR_A2 7    // L293 IN2  
#define ENA 6        // L293 EN1 (PWM pin for Motor A)

// Motor B (Left Motor)
#define MOTOR_B1 12    // L293 IN3
#define MOTOR_B2 8    // L293 IN4
#define ENB 10         // L293 EN2 (PWM pin for Motor B)


// Left Color Sensor
#define L_Photoresistor_PIN A3 
#define RED_LED_PIN 5 
#define BLUE_LED_PIN 9

// Right Color Sensor TO-DO
#define R_Photoresistor_PIN A0

#define InterruptPin 13

// Collision Sensor
#define PHOTODIODE_PIN A2
#define IR_LED 2

// State Definition
#define STATE_00 100
#define STATE_0 0
#define STATE_1 1
#define STATE_2 2
#define STATE_3 3
#define STATE_4 4
#define STATE_5 5
#define STATE_6 6
#define STATE_7 7
#define STATE_8 8
#define STATE_9 9
#define STATE_10 10
#define STATE_11 11
#define STATE_12 12
#define STATE_13 13

int currentState = STATE_0;

// Declare Connection Data
String clientID = "56FC703ACE1A";
// char serverAddress[] = "10.5.15.148"; //Brian-Hosted Server
char serverAddress[] = "10.5.12.14"; //Josh-Hosted Server
char ssid[] = "tufts_eecs";
char password[] = "foundedin1883";
int port = 80;
bool zeroEnter = true;
int count = 0;
String message;

WebSocket Server_31(serverAddress, port, ssid, password);
colorSensing myLeftSensor(RED_LED_PIN, BLUE_LED_PIN, L_Photoresistor_PIN);
colorSensing myRightSensor(RED_LED_PIN, BLUE_LED_PIN, R_Photoresistor_PIN);
collision my_Collider(PHOTODIODE_PIN, IR_LED);
BotMotions my_Bot(MOTOR_A1, MOTOR_A2, MOTOR_B1, MOTOR_B2, ENA, ENB);

States my_states(&my_Bot, &Server_31, &my_Collider, &myLeftSensor, &myRightSensor);
Demo my_demo(&Server_31, &my_states);


/*****************************************************************
*                  SET ON WHEN SOCKET CONNECTED
*****************************************************************/
bool socketOn = true;

void setup() {
    Serial.begin(9600);
    if (socketOn == false) {
        Serial.println("Not looking for socket");
    }
    if (socketOn) {
        Server_31.NetworkConnect();
        Server_31.SocketConnect(clientID);
        Server_31.PingServer();
    }
    
    // Interrupt Setup
    pinMode(InterruptPin, INPUT_PULLUP);
    attachInterrupt(digitalPinToInterrupt(InterruptPin), interrupt, FALLING);
    
    // Motor Setup
    pinMode(MOTOR_A1, OUTPUT);
    pinMode(MOTOR_A2, OUTPUT);
    pinMode(MOTOR_B1, OUTPUT);
    pinMode(MOTOR_B2, OUTPUT);
    my_Bot.stop();
    // Set LED pins as outputs
    // color sensing setup
    pinMode(RED_LED_PIN, OUTPUT);
    pinMode(BLUE_LED_PIN, OUTPUT);
    pinMode(L_Photoresistor_PIN, INPUT);
    
    // Turn off LEDs initially
    digitalWrite(RED_LED_PIN, LOW);
    digitalWrite(BLUE_LED_PIN, LOW);
    
    my_Collider.setup();

}

void loop() {

    while (Server_31.ConnectionStatus() == true or (socketOn == false)) { 
        if (socketOn == true) {
            message = Server_31.ReadServer();
            if(message != "NULL") {
                currentState = message.toInt();
            }

            switch (currentState) {
                case STATE_00:
                    my_states.handleState00();
                    break;
                case STATE_0:
                    if (zeroEnter) {
                        Server_31.WriteServer("Ready to move!");
                        zeroEnter = false;
                    }
                    my_states.handleState0(); 
                    break;
                case STATE_1: 
                    my_states.handleState1(); 
                    break;
                case STATE_2: 
                    my_states.handleState2(); 
                    break;
                case STATE_3: 
                    my_states.leftState90(); 
                    break;
                case STATE_4: 
                    my_states.rightState90(); 
                    break;
                case STATE_5: 
                    my_states.handleState5(); 
                    break;
                case STATE_6: 
                    my_states.handleState6(); 
                    break;
                case STATE_7:
                    my_demo.remotePartnerMotions();
                    break;
                case STATE_8:
                    my_demo.SoloDemo1();
                    interruptTriggered = false;
                    break;
                case STATE_9:   
                    my_demo.SoloDemo2();
                    interruptTriggered = false;
                    break;
                case STATE_10:
                    my_demo.PartnerDemo();
                    break;
                case STATE_11:
                    my_states.laneFollow();
                    break;
                case STATE_12:
                    my_states.laneFind("red");
                    break;
                case STATE_13:
                    my_states.forwardUntilCollision();
            
                default:
                    my_states.handleErrorState();
                    currentState = 0;
                    break;
            }
            if(currentState != 0){
                currentState = 0;
                zeroEnter = true;
            }

            delay(1); 

            if(Server_31.ConnectionStatus() == false){
                Serial.println("WebSocket connection lost.");
                delay(1000);
            }
        }       
    }
    if (socketOn) {
        Server_31.NetworkConnect();
        Server_31.SocketConnect(clientID);
        Server_31.PingServer();
    }
}

void interrupt() {
  interruptTriggered = !interruptTriggered;
}


