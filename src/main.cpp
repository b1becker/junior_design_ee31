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

// #include <Arduino.h>
// #include "States.h"
// #include "BotMotions.h"
// #include "WebSocket.h"

// // state machine
// #define LED0 13
// #define LED1 12
// #define LED2 11
// #define BUTTON_PIN A0

// // Motor A
// #define MOTOR_A1 4    // L293 IN1
// #define MOTOR_A2 7    // L293 IN2  
// #define ENA 10        // L293 EN1 (PWM pin for Motor A)

// // Motor B
// #define MOTOR_B1 12    // L293 IN3
// #define MOTOR_B2 8    // L293 IN4
// #define ENB 3         // L293 EN2 (PWM pin for Motor B)

// enum LightState {
//   STATE_0, STATE_1, STATE_2, STATE_3,
//   STATE_4, STATE_5, STATE_6, STATE_7
// };

// LightState currentState = STATE_0;
// int lastButtonState = HIGH;

// // Create global States object for the 2^3 states
// States states(LED0, LED1, LED2);

// BotMotions bm(MOTOR_A1, MOTOR_A2, MOTOR_B1, MOTOR_B2, ENA, ENB);

// void setup() {
//   // state machine setup
//   pinMode(LED0, OUTPUT);
//   pinMode(LED1, OUTPUT);
//   pinMode(LED2, OUTPUT);
//   pinMode(BUTTON_PIN, INPUT_PULLUP);

//   // Motor Setup
//   pinMode(MOTOR_A1, OUTPUT);
//   pinMode(MOTOR_A2, OUTPUT);
//   pinMode(MOTOR_B1, OUTPUT);
//   pinMode(MOTOR_B2, OUTPUT);

//   pinMode(ENA, OUTPUT);
//   pinMode(ENB, OUTPUT);
  
//   Serial.begin(9600);
// }

// void loop() {
//   Serial.write("hellowrld");
//   int currentButtonState = digitalRead(BUTTON_PIN);

//   if (lastButtonState == HIGH && currentButtonState == LOW) {
//     currentState = static_cast<LightState>((currentState + 1) % 8);
//   }

//   // When functional, will have bot go forward, backward, or whatever we want it to do
//   bm.loop();

//   switch (currentState) {
//     case STATE_0: states.handleState0(); break;
//     case STATE_1: states.handleState1(); break;
//     case STATE_2: states.handleState2(); break;
//     case STATE_3: states.handleState3(); break;
//     case STATE_4: states.handleState4(); break;
//     case STATE_5: states.handleState5(); break;
//     case STATE_6: states.handleState6(); break;
//     case STATE_7: states.handleState7(); break;
//   }

//   lastButtonState = currentButtonState;

//   // Motor Control - Motor A: MOTOR_A1, MOTOR_A2 & Motor B: MOTOR_B1, MOTOR_B2
// }

// #include "WebSocket.h"
// #include <Arduino.h>
// #include <ArduinoHttpClient.h>
// #include <WiFiNINA.h> 

// // Declare Connection Specifics
// String clientID = "56FC703ACE1A";
// char serverAddress[] = "34.28.153.91"; 
// int port = 80;
// WebSocket Server_31(serverAddress, port);

// int count = 0;

// void setup() {
//   Serial.begin(9600);
//   Server_31.PingSerial();
//   Server_31.NetworkConnect();
//   Server_31.SocketConnect(clientID);
//   Server_31.PingServer();
// }

// void loop() {
//   while (Server_31.ConnectionStatus() == true) {
//     if (count % 10000 == 0) {
//       Server_31.WriteServer("Hoang Mai");
//     }
//     count++;
//     delay(1); // Small delay to prevent overwhelming the loop
//   }

//   if(Server_31.ConnectionStatus() == false){
//     Serial.println("WebSocket connection lost.");
//   }
// }
