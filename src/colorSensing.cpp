// Simple Photoresistor Analog Read with LED Control
// UTI 1893 Photoresistor connected to A0
#include <Arduino.h>
#include "colorSensing.h"

// the normalised ratio formula can be computed using V_ratio = V_red / (V_red + V_blue)

#define STD_DELAY 50

#define BLACK_RATIO 0.53
#define RED_RATIO 0.03
#define BLUE_RATIO 0.68
#define YELLOW_RATIO 0.45
#define TOLERANCE 0.05 // +- 0.0015


colorSensing::colorSensing(int red_led_pin, int blue_led_pin, int photoresistor_led_pin) {
    red_led = red_led_pin;
    blue_led = blue_led_pin;
    photoresistor_pin = photoresistor_led_pin;

}

void colorSensing::setup() {
    pinMode(red_led, OUTPUT);
    pinMode(blue_led, OUTPUT);
    pinMode(photoresistor_pin, INPUT);

    // Turn off LEDs initially
    
}

void colorSensing::loop(String &output_color) {
    // // digitalWrite(red_led, HIGH);
    // int vout = analogRead(photoresistor_pin);
    // delay(STD_DELAY);
    // Serial.print("Vout = ");Serial.println(vout);
    // delay(STD_DELAY);

    // red flash
    digitalWrite(red_led, HIGH);
    delay(STD_DELAY);
    int redv = analogRead(photoresistor_pin);
    // delay(STD_DELAY);
    Serial.print("RedV = "); Serial.println(redv);
    digitalWrite(red_led, LOW);
    
    delay(STD_DELAY);
    
    // Measure and print blue voltage output
    digitalWrite(blue_led, HIGH);
    delay(STD_DELAY);
    int bluev = analogRead(photoresistor_pin);
    // delay(STD_DELAY);
    digitalWrite(blue_led, LOW);
    Serial.print("BlueV = "); Serial.println(bluev);

    delay(STD_DELAY);

    String color = colorDetector(bluev, redv, 1023);
    String detectedColor;

    if (color == "0") {
        detectedColor = "blue";
    } else if (color == "1") {
        detectedColor = "red";
    } else if (color == "2") {
        detectedColor = "yellow";
    } else if (color == "3"){
        detectedColor = "black";
    } else {
        detectedColor = "unknown";
    }

    output_color = detectedColor;
    

    delay(STD_DELAY);
}

void colorSensing::read_red(int &red_v) {
    digitalWrite(red_led, HIGH);
    delay(STD_DELAY);
    red_v = analogRead(photoresistor_pin);
    delay(STD_DELAY);
    Serial.print("RedV = "); Serial.println(red_v);
    digitalWrite(red_led, LOW);
}

void colorSensing::read_blue(int &blue_v) {
    digitalWrite(blue_led, HIGH);
    delay(STD_DELAY);
    blue_v = analogRead(photoresistor_pin);
    delay(STD_DELAY);
    Serial.print("RedV = "); Serial.println(blue_v);
    digitalWrite(blue_led, LOW);
}

// String colorSensing::colorDetector(int bvout, int rvout, int maxv) {
//     // Sanity on inputs
//     if (bvout < 0 || rvout < 0 || bvout > maxv || rvout > maxv) {
//         current = COLOR_UNKNOWN;
//         return String(ColorTag(current));
//     }

//     // From your data (with a little margin)
//     const bool blue   = inRange(bvout, 915, 930) && inRange(rvout, 1000, 1015);
//     const bool red    = inRange(bvout, 980, 995) && inRange(rvout, 935, 965);
//     const bool black  = inRange(bvout, 1000, maxv) && inRange(rvout, 1008, maxv);
//     // Yellow is lower on both channels; RedV slightly > BlueV
//     const bool yellow = inRange(bvout, 910, 950) && inRange(rvout, 920, 960)
//                         && (rvout - bvout >= 5) && (rvout - bvout <= 30);
//     // const bool yellow = inRange(bvout, 880, 970) && inRange(rvout, 900, 990) &&
//     //                     (rvout - bvout >= 2 && rvout - bvout <= 60) && (rvout + bvout < 1950);

//     if (blue)   { current = COLOR_BLUE;   return String(ColorTag(current)); }
//     if (red)    { current = COLOR_RED;    return String(ColorTag(current)); }
//     if (black)  { current = COLOR_BLACK;  return String(ColorTag(current)); }
//     if (yellow) { current = COLOR_YELLOW; return String(ColorTag(current)); }

//     // Fallback heuristic using the difference
//     int D = rvout - bvout; // +D => red channel higher
//     if (bvout < 960 && rvout < 980 && D >= 5  && D <= 35) { current = COLOR_YELLOW; return String(ColorTag(current)); }
//     if (bvout >= 1000 && rvout >= 1005 && D >= 0 && D <= 20) { current = COLOR_BLACK; return String(ColorTag(current)); }
//     if (bvout <= 935 && rvout >= 1000 && D >= 60) { current = COLOR_BLUE; return String(ColorTag(current)); }
//     if (bvout >= 980 && rvout <= 970 && D <= -20) { current = COLOR_RED;  return String(ColorTag(current)); }

//     current = COLOR_UNKNOWN;
//     return String(ColorTag(current));
// }

// Blue: Red-780 Blue-359
// Black: Red-800 Blue-677
// Red: Red-638 Blue-589
// Yellow: Red-554 Blue-317

String colorSensing::colorDetector(int bvout, int rvout, int maxv /*=1023*/) {
  // Sanity
  float color_ratio = 1.0 * rvout / (rvout + bvout);

  Serial.println("Color ratio: ");
  Serial.println(color_ratio);
  // red
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