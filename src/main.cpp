#include <Arduino.h>
#include "States.h"

#define LED0 13
#define LED1 12
#define LED2 11
#define BUTTON_PIN A0

enum LightState {
  STATE_0, STATE_1, STATE_2, STATE_3,
  STATE_4, STATE_5, STATE_6, STATE_7
};

LightState currentState = STATE_0;
int lastButtonState = HIGH;

// Create global States object for the 2^3 states
States states(LED0, LED1, LED2);

void setup() {
  pinMode(LED0, OUTPUT);
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(BUTTON_PIN, INPUT_PULLUP);

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
}
