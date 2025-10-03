#ifndef COLORSENSING_H
#define COLORSENSING_H

#include <Arduino.h>



class colorSensing
{
private:
    /* data */
    int red_led;
    int blue_led;
    int photoresistor_pin;
public:
    colorSensing(int red_led_pin, int blue_led_pin, int photoresistor_led_pin);
    void loop();
    void setup();
    void read_red(int &red_v);
    void read_blue(int &blue_v);

    // ~colorSensing();
};





#endif