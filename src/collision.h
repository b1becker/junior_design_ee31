#ifndef COLLISION_H
#define COLLISION_H

class collision
{
private:
    int photodiode;
    int irLED;
    /* data */
public:
    int loop(bool* wall);
    void setup();
    collision(int photodiode_pin, int irLED_pin);
};


#endif