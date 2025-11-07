#ifndef COLORSENSING_H
#define COLORSENSING_H
#include <Arduino.h>

enum ColorTag { COLOR_BLUE, COLOR_RED, COLOR_YELLOW, COLOR_BLACK, COLOR_UNKNOWN };


class colorSensing
{
private:
    /* data */
    int red_led;
    int blue_led;
    int photoresistor_pin;
    bool inRange(int v, int lo, int hi) { return v >= lo && v <= hi; }

public:
    colorSensing(int red_led_pin, int blue_led_pin, int photoresistor_led_pin);
    void loop(String &output_color);
    void setup();
    void read_red(int &red_v);
    void read_blue(int &blue_v);
    String colorDetector(int bvout, int rvout, int maxv);
    ColorTag current = COLOR_UNKNOWN;
    String colorSensed;
    // ~colorSensing();
};





#endif