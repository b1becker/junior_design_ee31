#include <Arduino.h>
#include "States.h"
#include "BotMotions.h"

// state machine
#define LED0 13
#define LED1 12
#define LED2 11
#define BUTTON_PIN A0

// Motor A
#define MOTOR_A1 5    // L293 IN1
#define MOTOR_A2 6    // L293 IN2  
#define ENA 10        // L293 EN1 (PWM pin for Motor A)

// Motor B
#define MOTOR_B1 9    // L293 IN3
#define MOTOR_B2 8    // L293 IN4
#define ENB 3         // L293 EN2 (PWM pin for Motor B)

enum LightState {
  STATE_0, STATE_1, STATE_2, STATE_3,
  STATE_4, STATE_5, STATE_6, STATE_7
};

LightState currentState = STATE_0;
int lastButtonState = HIGH;

// Create global States object for the 2^3 states
States states(LED0, LED1, LED2);

BotMotions bm(MOTOR_A1, MOTOR_A2, MOTOR_B1, MOTOR_B2, ENA, ENB);

void setup() {
  // state machine setup
  pinMode(LED0, OUTPUT);
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(BUTTON_PIN, INPUT_PULLUP);

  // Motor Setup
  pinMode(MOTOR_A1, OUTPUT);
  pinMode(MOTOR_A2, OUTPUT);
  pinMode(MOTOR_B1, OUTPUT);
  pinMode(MOTOR_B2, OUTPUT);

  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
  
  Serial.begin(9600);
}

void loop() {
  Serial.write("hellowrld");
  int currentButtonState = digitalRead(BUTTON_PIN);

  if (lastButtonState == HIGH && currentButtonState == LOW) {
    currentState = static_cast<LightState>((currentState + 1) % 8);
  }

  // When functional, will have bot go forward, backward, or whatever we want it to do
  bm.loop();

  switch (currentState) {
    case STATE_0: states.handleState0(); break;
    case STATE_1: states.handleState1(); break;
    case STATE_2: states.handleState2(); break;
    case STATE_3: states.handleState3(); break;
    case STATE_4: states.handleState4(); break;
    case STATE_5: states.handleState5(); break;
    case STATE_6: states.handleState6(); break;
    case STATE_7: states.handleState7(); break;
  }

  lastButtonState = currentButtonState;

  // Motor Control - Motor A: MOTOR_A1, MOTOR_A2 & Motor B: MOTOR_B1, MOTOR_B2
}


// Add this debug code to see what's actually happening
// void setup() {
//   Serial.begin(9600);

//   pinMode(MOTOR_A1, OUTPUT);
//   pinMode(MOTOR_A2, OUTPUT);
//   pinMode(MOTOR_B1, OUTPUT);
//   pinMode(MOTOR_B2, OUTPUT);
    
//   pinMode(ENA, OUTPUT);
//   pinMode(ENB, OUTPUT);
// }

// void loop() {
//   // Set motor to rotate forward at half speed
//   digitalWrite(MOTOR_B1, HIGH);
//   digitalWrite(MOTOR_B2, LOW);
//   analogWrite(ENB, 128); // Speed: 0 (stopped) to 255 (full speed)
//   delay(2000); // Run for 2 seconds

//   // Set motor to rotate backward at full speed
//   digitalWrite(MOTOR_B1, LOW);
//   digitalWrite(MOTOR_B2, HIGH);
//   analogWrite(ENB, 255);
//   delay(2000);

//   // Stop the motor
//   digitalWrite(MOTOR_B1, LOW);
//   digitalWrite(MOTOR_B2, LOW);
//   delay(1000);
//   Serial.print("cycle complete \n");
// }