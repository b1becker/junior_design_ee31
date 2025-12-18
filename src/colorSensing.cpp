#include <Arduino.h>
#include "colorSensing.h"
#include "Constants.h"

/********** Constructor ********
*
* Sets needed pin values
*
* Parameters:
*      Red LED Pin
*      Blue LED Pin
*      Photoresistor LED Pin
*
************************/
colorSensing::colorSensing(int red_led_pin, int blue_led_pin, int photoresistor_led_pin) {
    red_led = red_led_pin;
    blue_led = blue_led_pin;
    photoresistor_pin = photoresistor_led_pin;
}

/********** Setup ********
*
* Initializes needed pin modes and takes a test sample.
*
* Parameters:
*      None
*
************************/
void colorSensing::setup() {
    pinMode(red_led, OUTPUT);
    pinMode(blue_led, OUTPUT);
    pinMode(photoresistor_pin, INPUT);
    
}

/********** GreedyLoop ********
*
* Proof of concept function meant to test 
* alternative detection methods
*
* Parameters:
*      String address for output color.
*      ColorRef address for index
*
************************/
void colorSensing::greedyLoop(String &output_color, ColorRef &curr_index) {
    digitalWrite(red_led, HIGH);
    delay(COLOR_DELAY);
    int redv = analogRead(photoresistor_pin);
    digitalWrite(red_led, LOW);
    delay(COLOR_DELAY);

    digitalWrite(blue_led, HIGH);
    delay(COLOR_DELAY);
    int bluev = analogRead(photoresistor_pin);
    digitalWrite(blue_led, LOW);
    delay(COLOR_DELAY);

    int dRed = redv - curr_index.red;
    int dBlue = bluev - curr_index.blue; 
    int distSquared = dRed * dRed + dBlue * dBlue;

    if(distSquared < TOLERANCE) {
        return;
    }
    output_color = "Black";


}

/********** FUNCTION_NAME ********
*
*      Performs a color sensing cycle using a photoresistor and
*      red/blue LEDs. The cycle measures reflected light values
*      and compares them against reference colors to the find the
*      closest matching color. The detected color is updated internally. 
*
* Parameters:
*      String reference for detected color name.
*      ColorRef reference for data details.
*
************************/
void colorSensing::loop(String &output_color, ColorRef &curr_index) {
    digitalWrite(red_led, HIGH);
    delay(COLOR_DELAY);
    int redv = analogRead(photoresistor_pin);
    digitalWrite(red_led, LOW);
    delay(COLOR_DELAY);

    digitalWrite(blue_led, HIGH);
    delay(COLOR_DELAY);
    int bluev = analogRead(photoresistor_pin);
    digitalWrite(blue_led, LOW);
    delay(COLOR_DELAY);


    float minDist = 999999.0;
    int detectedColorIndex = COLOR_UNKNOWN;

    for (int i = 0; i < 4; i++) {
        float dRed = redv - colorVal[i].red;
        float dBlue = bluev - colorVal[i].blue;
        float distSquared = dRed * dRed + dBlue * dBlue;
        
        // Debug: print each distance
        Serial.print("Color ");
        Serial.print(i);
        Serial.print(" dist^2=");
        Serial.println(distSquared);
        
        if (distSquared < minDist) {
            minDist = distSquared;
            detectedColorIndex = i;
        }
    }
    curr_index = colorVal[detectedColorIndex];
    
    switch(detectedColorIndex) {
        case COLOR_BLUE:   
            output_color = "blue"; break;
        case COLOR_RED:    output_color = "red"; break;
        case COLOR_YELLOW: output_color = "yellow"; break;
        case COLOR_BLACK:  output_color = "black"; break;
        default:           output_color = "unknown"; break;
    }

    current = (ColorTag)detectedColorIndex;
}

/********** Read_Red ********
*
* Performs a photoresistor read in Red light.
*
* Parameters:
*      Int reference to red color variable.
*
************************/
void colorSensing::read_red(int &red_v) {
    digitalWrite(red_led, HIGH);
    delay(5);
    red_v = analogRead(photoresistor_pin);
    delay(5);
    Serial.print("RedV = "); Serial.println(red_v);
    digitalWrite(red_led, LOW);
    delay(10);
}

/********** Read_Blue ********
*
* Performs a photoresistor read in Blue light.
*
* Parameters:
*      Int reference to blue color variable.
*
************************/
void colorSensing::read_blue(int &blue_v) {
    digitalWrite(blue_led, HIGH);
    delay(5);
    blue_v = analogRead(photoresistor_pin);
    delay(5);
    Serial.print("RedV = "); Serial.println(blue_v);
    digitalWrite(blue_led, LOW);
    delay(10);
}

/********** colorDetector ********
*
* Checks given color values against calibrated color 
* values to return what color was detected
*
* Parameters:
*      
*
* Notes:
*      NOTES_EXCEPTIONS_ETC
************************/
String colorSensing::colorDetector(int bvout, int rvout, int maxv /*=1023*/) {
  float color_ratio = 1.0 * rvout / (rvout + bvout);

    if (color_ratio >= BLACK_RATIO - TOLERANCE and color_ratio <= BLACK_RATIO + TOLERANCE) {
        current = COLOR_BLACK;
    }
    else if (color_ratio >= RED_RATIO - TOLERANCE and color_ratio <= RED_RATIO + TOLERANCE) {
        current = COLOR_RED;
    }
    else if (color_ratio >= BLUE_RATIO - TOLERANCE and color_ratio <= BLUE_RATIO + TOLERANCE) {
        current = COLOR_BLUE;
    }
    else if (color_ratio >= YELLOW_RATIO - TOLERANCE and color_ratio <= YELLOW_RATIO + TOLERANCE) {
        current = COLOR_YELLOW;
    }
    else {
        current = COLOR_UNKNOWN;
    }

  return String(ColorTag(current));
}

/********** Calibrate ********
*
* Sets an average base color value for some color.
*
* Parameters:
*      Int representing the color we are setting
*
************************/
void colorSensing::Calibrate(int color){

    float redSum = 0.0;
    float blueSum = 0.0;
    int redv, bluev;

    for(int i = 0; i < SAMPLE_SIZE; i++) {
        read_red(redv);
        read_blue(bluev);
        redSum += redv;
        blueSum += bluev;
    }

    colorVal[color].red = redSum / 50.0;
    colorVal[color].blue = blueSum / 50.0;

}