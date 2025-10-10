// Simple Photoresistor Analog Read with LED Control
// UTI 1893 Photoresistor connected to A0
#include <Arduino.h>
#include "colorSensing.h"


#define STD_DELAY 50


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

void colorSensing::loop() {
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
    // Serial.print("RedV = "); Serial.println(redv);
    digitalWrite(red_led, LOW);
    
    delay(STD_DELAY);
    
    // Measure and print blue voltage output
    digitalWrite(blue_led, HIGH);
    delay(STD_DELAY);
    int bluev = analogRead(photoresistor_pin);
    // delay(STD_DELAY);
    digitalWrite(blue_led, LOW);
    // Serial.print("BlueV = "); Serial.println(bluev);

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

    Serial.print("Color = "); Serial.println(detectedColor);

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

String colorSensing::colorDetector(int bvout, int rvout, int maxv /*=1023*/) {
  // Sanity
  if (bvout < 0 || rvout < 0 || bvout > maxv || rvout > maxv) {
    current = COLOR_UNKNOWN;
    return String(ColorTag(current));
  }

  const int D = rvout - bvout;  // +D => Red higher than Blue
  const int S = rvout + bvout;  // overall brightness

  // --- Clusters from your new data (+ reasonable slack) ---

  // BLACK / "both very high":
  // Obs: Red ~1014–1018, Blue ~1009–1018  => S ~2025–2035, D near 0
  if (bvout >= 1008 && rvout >= 1010 && S >= 1990) {
    current = COLOR_BLACK;
    return String(ColorTag(current));
  }

  // BLUE:
  // Obs: Red ~1002–1003, Blue ~940–946 => D ~ +56..+63, S ~ 1942..2006
  if (inRange(bvout, 930, 960) && inRange(rvout, 990, 1015) &&
      D >= 45 && D <= 80 && S >= 1900 && S <= 2050) {
    current = COLOR_BLUE;
    return String(ColorTag(current));
  }

  // RED:
  // Obs: Blue ~995–999, Red ~950–963 => D ~ -47..-32, S ~ 1943..1962
  if (inRange(bvout, 990, 1010) && inRange(rvout, 940, 970) &&
      D <= -25 && D >= -70 && S >= 1900 && S <= 2050) {
    current = COLOR_RED;
    return String(ColorTag(current));
  }

  // YELLOW:
  // Obs: Blue ~938–941, Red ~913–917 => D ~ -28..-21, S ~ 1851..1858 (both lower)
  if (inRange(bvout, 930, 960) && inRange(rvout, 905, 930) &&
      D <= -15 && D >= -40 && S >= 1800 && S <= 1900) {
    current = COLOR_YELLOW;
    return String(ColorTag(current));
  }

  // --- Fallbacks (looser) ---
  if (S >= 1980 && bvout >= 1000 && rvout >= 1005 && abs(D) <= 25) {
    current = COLOR_BLACK;  // very bright, neutral-ish
    return String(ColorTag(current));
  }
  if (D >= 40 && S >= 1880) { current = COLOR_BLUE;   return String(ColorTag(current)); }
  if (D <= -30 && S >= 1880) { current = COLOR_RED;    return String(ColorTag(current)); }
  if (S <= 1920 && D <= -18 && D >= -45) {
    current = COLOR_YELLOW; return String(ColorTag(current));
  }

  current = COLOR_UNKNOWN;
  return String(ColorTag(current));
}