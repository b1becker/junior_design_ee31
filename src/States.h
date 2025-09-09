// States.h
#ifndef STATES_H
#define STATES_H

#include <Arduino.h>

class States {
public:
    // Constructor: pass LED pins if you want to keep things flexible
    States(int led0, int led1, int led2);

    // State handlers
    void handleState0();
    void handleState1();
    void handleState2();
    void handleState3();
    void handleState4();
    void handleState5();
    void handleState6();
    void handleState7();

private:
    int _led0, _led1, _led2;
};

#endif
