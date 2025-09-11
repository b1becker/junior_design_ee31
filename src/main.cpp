#include <Arduino.h>
#include "States.h"

#define LED0 13
#define LED1 12
#define LED2 11
#define BUTTON_PIN A0

// Motor A
#define MOTOR_A1 5   // Pin 14 of L293
#define MOTOR_A2 6   // Pin 10 of L293
// Motor B
#define MOTOR_B1 10  // Pin 7 of L293
#define MOTOR_B2 9   // Pin 2 of L293

enum LightState {
  STATE_0, STATE_1, STATE_2, STATE_3,
  STATE_4, STATE_5, STATE_6, STATE_7
};

LightState currentState = STATE_0;
int lastButtonState = HIGH;

// Create global States object for the 2^3 states
States states(LED0, LED1, LED2);

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

  Serial.begin(9600);
}

void loop() {
  // Serial.write("hellowrld");
  int currentButtonState = digitalRead(BUTTON_PIN);

  if (lastButtonState == HIGH && currentButtonState == LOW) {
    currentState = static_cast<LightState>((currentState + 1) % 8);
  }

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

  // Motor A clockwise for 2 sec
  digitalWrite(MOTOR_A1, HIGH);
  digitalWrite(MOTOR_A2, LOW);
  digitalWrite(MOTOR_B1, LOW);
  digitalWrite(MOTOR_B2, LOW);
  delay(2000);

  // Motor A counter-clockwise for 2 sec
  digitalWrite(MOTOR_A1, LOW);
  digitalWrite(MOTOR_A2, HIGH);
  digitalWrite(MOTOR_B1, LOW);
  digitalWrite(MOTOR_B2, LOW);
  delay(2000);

  // Motor B clockwise for 2 sec
  digitalWrite(MOTOR_A1, LOW);
  digitalWrite(MOTOR_A2, LOW);
  digitalWrite(MOTOR_B1, HIGH);
  digitalWrite(MOTOR_B2, LOW);
  delay(2000);

  // Motor B counter-clockwise for 2 sec
  digitalWrite(MOTOR_A1, LOW);
  digitalWrite(MOTOR_A2, LOW);
  digitalWrite(MOTOR_B1, LOW);
  digitalWrite(MOTOR_B2, HIGH);
  delay(2000);

  // Stop motors
  digitalWrite(MOTOR_A1, LOW);
  digitalWrite(MOTOR_A2, LOW);
  digitalWrite(MOTOR_B1, LOW);
  digitalWrite(MOTOR_B2, LOW);

  Serial.print("Motor complete");
      
}


// Simple continuous spin with L293x + Arduino

// #define IN1 5    // Arduino → L293x pin 2
// #define IN2 6    // Arduino → L293x pin 7
// #define ENA 9    // Arduino → L293x pin 1 (EN1,2)

// #define IN3 7    // Arduino → L293x pin 10
// #define IN4 8    // Arduino → L293x pin 15
// #define ENB 10   // Arduino → L293x pin 9 (EN3,4)

// void setup() {
//   pinMode(IN1, OUTPUT);
//   pinMode(IN2, OUTPUT);
//   pinMode(ENA, OUTPUT);

//   pinMode(IN3, OUTPUT);
//   pinMode(IN4, OUTPUT);
//   pinMode(ENB, OUTPUT);

//   // Motor A forward
//   digitalWrite(IN1, HIGH);
//   digitalWrite(IN2, LOW);
//   digitalWrite(ENA, HIGH);

//   // Motor B forward
//   digitalWrite(IN3, HIGH);
//   digitalWrite(IN4, LOW);
//   digitalWrite(ENB, HIGH);
// }

// void loop() {
//   // both motors spin forever
// }
// L293D


// This will run only one time.

