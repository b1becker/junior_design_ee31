#include <Arduino.h>

#define LED0 13
#define LED1 12
#define LED2 11
#define BUTTON_PIN A0

// Enumeration for the 8 states
enum LightState {
  STATE_0, // 000
  STATE_1, // 001
  STATE_2, // 010
  STATE_3, // 011
  STATE_4, // 100
  STATE_5, // 101
  STATE_6, // 110
  STATE_7  // 111
};

// Variable to store the current state
LightState currentState = STATE_0;

// Variable to store button states
int lastButtonState = HIGH;  // default HIGH because of INPUT_PULLUP

void setup() {
  pinMode(LED0, OUTPUT);
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);

  pinMode(BUTTON_PIN, INPUT_PULLUP); // button between A0 and GND
}

void loop() {
  int currentButtonState = digitalRead(BUTTON_PIN);

  // Detect button press (HIGH -> LOW transition)
  if (lastButtonState == HIGH && currentButtonState == LOW) {
    // Advance to next state (cycle back to STATE_0 after STATE_7)
    currentState = static_cast<LightState>((currentState + 1) % 8);
  }

  // Update LEDs based on state
  switch (currentState) {
    case STATE_0: digitalWrite(LED0, LOW); digitalWrite(LED1, LOW); digitalWrite(LED2, LOW); break;
    case STATE_1: digitalWrite(LED0, HIGH); digitalWrite(LED1, LOW);  digitalWrite(LED2, LOW);  break;
    case STATE_2: digitalWrite(LED0, LOW);  digitalWrite(LED1, HIGH); digitalWrite(LED2, LOW);  break;
    case STATE_3: digitalWrite(LED0, HIGH); digitalWrite(LED1, HIGH); digitalWrite(LED2, LOW);  break;
    case STATE_4: digitalWrite(LED0, LOW);  digitalWrite(LED1, LOW);  digitalWrite(LED2, HIGH); break;
    case STATE_5: digitalWrite(LED0, HIGH); digitalWrite(LED1, LOW);  digitalWrite(LED2, HIGH); break;
    case STATE_6: digitalWrite(LED0, LOW);  digitalWrite(LED1, HIGH); digitalWrite(LED2, HIGH); break;
    case STATE_7: digitalWrite(LED0, HIGH); digitalWrite(LED1, HIGH); digitalWrite(LED2, HIGH); break;
  }

  lastButtonState = currentButtonState;
}
