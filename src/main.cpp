#include "States.h"
#include "Demo.h"
#include "WebSocket.h"
#include "BotMotions.h"
#include "States.h"
#include "colorSensing.h"
#include <Arduino.h>
#include <ArduinoHttpClient.h>
#include <WiFiNINA.h> 

// Motor A (Right Motor)
#define MOTOR_A1 4    // L293 IN1
#define MOTOR_A2 7    // L293 IN2  
#define ENA 6        // L293 EN1 (PWM pin for Motor A)

// Motor B (Left Motor)
#define MOTOR_B1 12    // L293 IN3
#define MOTOR_B2 8    // L293 IN4
#define ENB 10         // L293 EN2 (PWM pin for Motor B)

#define PHOTORESISTOR_PIN A3 
#define RED_LED_PIN 5 
#define BLUE_LED_PIN 9

#define PHOTODIODE_PIN A2
#define IR_LED 10

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

int currentState = STATE_0;

// Declare Connection Data
String clientID = "56FC703ACE1A";
char serverAddress[] = "34.28.153.91";
char ssid[] = "tufts_eecs";
char password[] = "foundedin1883";
int port = 80;
WebSocket Server_31(serverAddress, port, ssid, password);

bool zeroEnter = true;
int count = 0;
String message;

BotMotions ourBot(MOTOR_A1, MOTOR_A2, MOTOR_B1, MOTOR_B2, ENA, ENB);

States my_states(&ourBot);
Demo my_demo(&ourBot, &Server_31);
colorSensing cs(RED_LED_PIN, BLUE_LED_PIN, PHOTORESISTOR_PIN);

// collision cll(PHOTODIODE_PIN, IR_LED);

#define STD_DELAY 50
#define N_SAMPLES 10
#define DISTANCE_THRESHOLD 10

// void setup () {
//     int photodiode = PHOTODIODE_PIN;
//     int irLED = IR_LED;
// }
// void setup() {
//     // Initialize Serial Monitor
//     Serial.begin(9600);
//     Server_31.NetworkConnect();
//     Server_31.SocketConnect(clientID);
//     Server_31.PingServer();

//     // Set all motor pins
//     pinMode(MOTOR_A1, OUTPUT);
//     pinMode(MOTOR_A2, OUTPUT);
//     pinMode(MOTOR_B1, OUTPUT);
//     pinMode(MOTOR_B2, OUTPUT);
//     pinMode(ENA, OUTPUT);
//     pinMode(ENB, OUTPUT);
    
//     // Set all color sensing pins
//     pinMode(RED_LED_PIN, OUTPUT);
//     pinMode(BLUE_LED_PIN, OUTPUT);
//     pinMode(PHOTORESISTOR_PIN, INPUT);

//     cs.setup();
    
//     // Turn off LEDs initially
//     // digitalWrite(red_led, LOW);
//     // digitalWrite(blue_led, LOW);

//     // Set all motor values low
//     my_states.handleState0();
    
// }


// void loop() {

//     pinMode(PHOTODIODE_PIN, INPUT);
//     pinMode(IR_LED, OUTPUT);
//     float onSUM = 0;
//     float offSUM = 0; 

//     // irLED high and sample
//     digitalWrite(IR_LED, HIGH);
//     delay(STD_DELAY);
//     for (int i = 0; i < N_SAMPLES; i++) {
//         offSUM += analogRead(PHOTODIODE_PIN);
//     }
//     int offAVG = offSUM / N_SAMPLES;

//     // irLED low and sample
//     digitalWrite(IR_LED, LOW);
//     delay(STD_DELAY);
//         for (int i = 0; i < N_SAMPLES; i++) {
//         onSUM += analogRead(PHOTODIODE_PIN);
//     }
//     int onAVG = onSUM / N_SAMPLES;

//     // reflection with ambient - ambient = just reflected
//     int reflected = onAVG - offAVG;

//     if (reflected > DISTANCE_THRESHOLD) {
//         Serial.print("Collition approaching! Reflected = ");
//         Serial.println(reflected);

//         //idk add bot movements to reflect this
//     } else {
//         Serial.print("Continue with clear path. Reflected = ");
//         Serial.println(reflected);
//         //idk add bot movements to reflect this
//     }
// }


void setup() {
    Serial.begin(9600);
    Server_31.NetworkConnect();
    Server_31.SocketConnect(clientID);
    Server_31.PingServer();
    // Motor Setup
    pinMode(MOTOR_A1, OUTPUT);
    pinMode(MOTOR_A2, OUTPUT);
    pinMode(MOTOR_B1, OUTPUT);
    pinMode(MOTOR_B2, OUTPUT);
    
    // Set LED pins as outputs
    // color sensing setup
    pinMode(RED_LED_PIN, OUTPUT);
    pinMode(BLUE_LED_PIN, OUTPUT);
    pinMode(PHOTORESISTOR_PIN, INPUT);
    
    // Turn off LEDs initially
    // digitalWrite(red_led, LOW);
    // digitalWrite(blue_led, LOW)
    
}


void loop() {
    while (Server_31.ConnectionStatus() == true) { 
        message = Server_31.ReadServer();
        
        if(message != "NULL")
        {
            currentState = message.toInt();
        }

        switch (currentState) {
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
                my_states.handleState3(); 
                break;
            case STATE_4: 
                my_states.handleState4(); 
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
                break;
            case STATE_9:   
                my_demo.SoloDemo2();
                break;
            case STATE_10:
                my_demo.PartnerDemo();
                break;
            default: 
                my_states.handleErrorState(); 
                break;
        }
        if(currentState != 0){
            currentState = 0;
            zeroEnter = true;
        }
        
        // cs.loop();
            
        delay(1); 
    }
        
    if(Server_31.ConnectionStatus() == false){
        Serial.println("WebSocket connection lost.");
    }
}












    // // Simple Photoresistor Analog Read with LED Control
    // // UTI 1893 Photoresistor connected to A0
    // #include <Arduino.h>
    
    // #define PHOTORESISTOR_PIN A0 
    // #define RED_LED_PIN 5 
    // #define BLUE_LED_PIN 9 
    // // Must be PWM pin 
     
    // void setup() { 
    //   Serial.begin(9600); 
    //   pinMode(RED_LED_PIN, OUTPUT); 
    //   pinMode(BLUE_LED_PIN, OUTPUT); 
    //   Serial.println("PWM LED Fade Controller Started"); 
    // } 
    
    // void loop() { 
    //   // Read photoresistor (0-1023) 
      
    //   int raw = analogRead(PHOTORESISTOR_PIN);
    //   // If wired: collector->A0 with pull-up, emitter->GND, then more light => lower 'raw'.
    //   // Invert so brighter = bigger number:
    //   int light = 1023 - raw;
    //   // Map light level to LED brightness (0-255 for PWM) 
    //   int redBrightness = map(light, 0, 1023, 0, 255); 
    //   int blueBrightness = 255 - redBrightness; // Constrain values to valid PWM range 
      
    //   int brightness = map(light, 0, 1023, 0, 255);
    //   brightness = constrain(brightness, 0, 255);
    
    //   analogWrite(RED_LED_PIN, brightness);
    //   analogWrite(BLUE_LED_PIN, brightness);  // Same value for both
    
    //   Serial.print("raw= ");
    //   Serial.print(raw);  
      
    //   Serial.print("  light(inv)= "); 
    //   Serial.print(light);
      
    //   Serial.print("  R=");  Serial.print(redBrightness);
    //   Serial.print("  B=");  Serial.println(blueBrightness);
    
    //   delay(100);
    // }
    
    
    
    // #define PHOTORESISTOR_PIN A0
    // #define RED_LED_PIN 5
    // #define BLUE_LED_PIN 9
    
    // void setup() {
    //   Serial.begin(9600);
      
    //   // Set LED pins as outputs
    //   pinMode(RED_LED_PIN, OUTPUT);
    //   pinMode(BLUE_LED_PIN, OUTPUT);
      
    //   // Turn off both LEDs initially
    //   digitalWrite(RED_LED_PIN, LOW);
    //   digitalWrite(BLUE_LED_PIN, LOW);
      
    //   Serial.println("=== Photoresistor Analog Read with LEDs ===");
    //   Serial.println("Cover sensor with hand to see values change");
    //   Serial.println("Red LED = Bright light, Blue LED = Dark light");
    //   Serial.println();
    // }
    
    // void loop() {
    //   // Read the analog value from photoresistor (0-1023)
    //   int lightLevel = analogRead(PHOTORESISTOR_PIN);
      
    //   // Convert to voltage for reference
    //   float voltage = lightLevel * (5.0 / 1023.0);
      
    //   // Print the readings
    //   Serial.print("Analog Value: ");
    //   Serial.print(lightLevel);
    //   Serial.print(" | Voltage: ");
    //   Serial.print(voltage, 2);
    //   Serial.print("V | Light: ");
      
    //   // Control LEDs and interpret the light level
    //   if (lightLevel > 800) {
    //     digitalWrite(RED_LED_PIN, HIGH);
    //     digitalWrite(BLUE_LED_PIN, LOW);
    //     Serial.println("Very Bright - RED LED ON");
    //   } else if (lightLevel > 500) {
    //     digitalWrite(RED_LED_PIN, HIGH);
    //     digitalWrite(BLUE_LED_PIN, LOW);
    //     Serial.println("Bright - RED LED ON");
    //   } else if (lightLevel > 200) {
    //     digitalWrite(RED_LED_PIN, LOW);
    //     digitalWrite(BLUE_LED_PIN, LOW);
    //     Serial.println("Medium - BOTH LEDs OFF");
    //   } else {
    //     digitalWrite(RED_LED_PIN, LOW);
    //     digitalWrite(BLUE_LED_PIN, HIGH);
    //     Serial.println("Dark - BLUE LED ON");
    //   }
      
    //   delay(500); // Read every half second
    // }
