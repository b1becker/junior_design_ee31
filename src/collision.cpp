#include <Arduino.h>
#include "collision.h"

using namespace std;

#define STD_DELAY 1
#define N_SAMPLES 7
#define DISTANCE_THRESHOLD 110


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
    // Serial.println("Initializing collision sensor buffers...");
    
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
}

int collision::loop(bool* wall) {
    // Get old values that will be replaced
    int curr_off_buffer = offBuffer[curr_buffer_index];
    int curr_on_buffer = onBuffer[curr_buffer_index];
    
    // === FIRST OFF SAMPLE ===
    digitalWrite(irLED, LOW);
    delay(STD_DELAY);
    int off_sample1 = analogRead(photodiode);
    delay(STD_DELAY);
    
    // === SECOND OFF SAMPLE ===
    int off_sample2 = analogRead(photodiode);
    delay(STD_DELAY);
    
    // Average the two off samples
    int curr_off_read = (off_sample1 + off_sample2) / 2;
    offBuffer[curr_buffer_index] = curr_off_read;
    
    // Update running average
    offAVG -= curr_off_buffer / N_SAMPLES;
    offAVG += curr_off_read / N_SAMPLES;
    
    // === FIRST ON SAMPLE ===
    digitalWrite(irLED, HIGH);
    delay(STD_DELAY);
    int on_sample1 = analogRead(photodiode);
    delay(STD_DELAY);
    
    // === SECOND ON SAMPLE ===
    int on_sample2 = analogRead(photodiode);
    delay(STD_DELAY);
    
    // Average the two on samples
    int curr_on_read = (on_sample1 + on_sample2) / 2;
    onBuffer[curr_buffer_index] = curr_on_read;
    
    // Update running average
    onAVG -= curr_on_buffer / N_SAMPLES;
    onAVG += curr_on_read / N_SAMPLES;
    
    // Advance circular buffer with wrap around
    curr_buffer_index = (curr_buffer_index + 1) % N_SAMPLES;
    
    int reflected = onAVG - offAVG;
    
    if (reflected > DISTANCE_THRESHOLD) {
        *wall = true;
    } else {
        *wall = false;
    }
    
    return reflected;
}