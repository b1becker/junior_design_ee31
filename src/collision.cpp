#include <Arduino.h>
#include "Constants.h"
#include "Collision.h"

/********** Constructor ********
*
* Sets needed pin values
*
* Parameters:
*      Photodiode pin #
*      IR LED pin #
*
************************/
collision::collision(int photodiode_pin, int irLED_pin) {
    photodiode = photodiode_pin;
    irLED = irLED_pin;

    curr_buffer_index = 0;
}

/********** Setup ********
*
* Initializes needed pin modes and takes a test sample.
*
* Parameters:
*      None
*
************************/
void collision::setup() {
    pinMode(photodiode, INPUT);
    pinMode(irLED, OUTPUT);
    
    
    for (int i = 0; i < N_SAMPLES; i++) {
        // irLED low and sample OFF
        digitalWrite(irLED, LOW);
        delay(COLLIDE_DELAY);
        
        
        offBuffer[i] = analogRead(photodiode);
        offAVG += offBuffer[i];
        
        // irLED high and sample ON
        digitalWrite(irLED, HIGH);
        delay(COLLIDE_DELAY);
        
        onBuffer[i] = analogRead(photodiode);
        onAVG += onBuffer[i];
    }

    offAVG /= N_SAMPLES;
    onAVG /= N_SAMPLES;
}

/********** Loop ********
*
* Returns the distance detected from the collision sensor to 
* some object in front of it.
* Sets a boolean for whether a collision is incoming.
*
* Parameters:
*      Bool* for our wall boolean.
*
************************/
int collision::loop(bool* wall) {
    // Get old values that will be replaced
    int curr_off_buffer = offBuffer[curr_buffer_index];
    int curr_on_buffer = onBuffer[curr_buffer_index];
    
    // === OFF SAMPLE ===
    digitalWrite(irLED, LOW);
    delay(COLLIDE_DELAY);
    int curr_off_read = analogRead(photodiode);
    
    offBuffer[curr_buffer_index] = curr_off_read;
    
    // Update running average
    offAVG -= curr_off_buffer / N_SAMPLES;
    offAVG += curr_off_read / N_SAMPLES;
    
    // === ON SAMPLE ===
    digitalWrite(irLED, HIGH);
    delay(COLLIDE_DELAY);
    int curr_on_read = analogRead(photodiode);
    
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