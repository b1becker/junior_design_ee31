#include <Arduino.h>
#include "collision.h"

using namespace std;

#define STD_DELAY 50
#define N_SAMPLES 10
#define DISTANCE_THRESHOLD 250




collision::collision(int photodiode_pin, int irLED_pin) {
    photodiode = photodiode_pin;
    irLED = irLED_pin;

    curr_buffer_index = 0;
}
// have to use standard for loop since low memory


void collision::setup() {
    pinMode(photodiode, INPUT);
    pinMode(irLED, OUTPUT);
    
    // Initialize buffers with N_SAMPLES readings using for loop
    Serial.println("Initializing collision sensor buffers...");
    
    for (int i = 0; i < N_SAMPLES; i++) {
        // irLED low and sample OFF
        digitalWrite(irLED, LOW);
        delay(STD_DELAY);
        offBuffer[i] = analogRead(photodiode);
        offAVG += offBuffer[i];
        
        // irLED high and sample ON
        digitalWrite(irLED, HIGH);
        delay(STD_DELAY);
        onBuffer[i] = analogRead(photodiode);
        onAVG += onBuffer[i];
    }
    
    // Calculate initial averages
    offAVG /= N_SAMPLES;
    onAVG /= N_SAMPLES;
    
    Serial.print("Initial offAVG: ");
    Serial.println(offAVG);
    Serial.print("Initial onAVG: ");
    Serial.println(onAVG);
}

int collision::loop(bool* wall) {
    // Get old values that will be replaced
    int curr_off_buffer = offBuffer[curr_buffer_index];
    int curr_on_buffer = onBuffer[curr_buffer_index];
    
    // irLED low and sample
    digitalWrite(irLED, LOW);
    delay(STD_DELAY);
    
    int curr_off_read = analogRead(photodiode);
    offBuffer[curr_buffer_index] = curr_off_read;
    
    // Update running average
    offAVG -= curr_off_buffer / N_SAMPLES;
    offAVG += curr_off_read / N_SAMPLES;
    
    Serial.print("offAVG: ");
    Serial.println(offAVG);
    delay(STD_DELAY);
    
    // irLED high and sample
    digitalWrite(irLED, HIGH);
    delay(STD_DELAY);
    
    int curr_on_read = analogRead(photodiode);
    onBuffer[curr_buffer_index] = curr_on_read;
    
    // Update running average
    onAVG -= curr_on_buffer / N_SAMPLES;
    onAVG += curr_on_read / N_SAMPLES;
    
    Serial.print("onAVG: ");
    Serial.println(onAVG);
    delay(STD_DELAY);
    
    // Advance circular buffer index with wraparound
    curr_buffer_index = (curr_buffer_index + 1) % N_SAMPLES;
    
    // reflection with ambient - ambient = just reflected
    int reflected = onAVG - offAVG;
    
    if (reflected > DISTANCE_THRESHOLD) {
        Serial.print("Collision approaching! Reflected = ");
        Serial.println(reflected);
        *wall = true;
    } else {
        Serial.print("Continue with clear path. Reflected = ");
        Serial.println(reflected);
        *wall = false;
    }
    
    return reflected;
}