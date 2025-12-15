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
#include "Constants.h"

volatile bool interruptTriggered = false;
void interrupt();

int currentState = STATE_0;

String clientID = "56FC703ACE1A";
char serverAddress[] = "10.5.15.148"; //Brian-Hosted Server
// char serverAddress[] = "10.5.12.14"; //Josh-Hosted Server

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



void setup() {
    Serial.begin(9600);

    Server_31.NetworkConnect();
    Server_31.SocketConnect(clientID);
    Server_31.PingServer();

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
    while (Server_31.ConnectionStatus() == true) { 
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
                    my_demo.PartnerDemo1();
                    interruptTriggered = false;
                    break;
                case STATE_11:
                    my_demo.PartnerDemo2();
                    interruptTriggered = false;
                    break;
                case STATE_12:
                    my_states.laneFind("red");
                    break;
                case STATE_13:
                    my_states.forwardUntilCollision();
                    break;
                case STATE_14:
                    my_states.laneFollow();
                    break;
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
    Server_31.NetworkConnect();
    Server_31.SocketConnect(clientID);
    Server_31.PingServer();
}

void interrupt() {
  interruptTriggered = !interruptTriggered;
}


