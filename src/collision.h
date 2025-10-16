#ifndef COLLISION_H
#define COLLISION_H

class collision
{
private:
    int photodiode;
    int irLED;
    /* data */
public:
    void loop();
    void setup();
    collision(int photodiode_pin, int irLED_pin);
};


#endif