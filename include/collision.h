#ifndef COLLISION_H
#define COLLISION_H

#define N_SAMPLES 10

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

private:

    int offBuffer[N_SAMPLES];
    int onBuffer[N_SAMPLES];
    int curr_buffer_index;

    int offAVG;
    int onAVG;

    int arraySum(int arr[], int size);

};


#endif