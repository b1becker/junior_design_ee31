#ifndef CONSTANTS_H
#define CONSTANTS_H



/*****************************************************************
*                  Interrupt Pin
*****************************************************************/
#define InterruptPin 13
extern volatile bool interruptTriggered;
#define InterruptReturn() \
    do {                        \
        if (interruptTriggered) return; \
    } while (0)


/*****************************************************************
*                  Motor Pins
*****************************************************************/
#define MOTOR_A1 4    // L293 IN1
#define MOTOR_A2 7    // L293 IN2  
#define ENA 6        // L293 EN1 

#define MOTOR_B1 12    // L293 IN3
#define MOTOR_B2 8    // L293 IN4
#define ENB 10         // L293 EN2


/*****************************************************************
*                  Sensor Pins
*****************************************************************/
#define L_Photoresistor_PIN A3 
#define RED_LED_PIN 5 
#define BLUE_LED_PIN 9

#define R_Photoresistor_PIN A0

#define PHOTODIODE_PIN A2
#define IR_LED 2


/*****************************************************************
*                  State Definitions
*****************************************************************/
#define STATE_00 100
enum State {
    STATE_0, STATE_1, STATE_2, STATE_3,
    STATE_4, STATE_5, STATE_6, STATE_7,
    STATE_8, STATE_9, STATE_10, STATE_11,
    STATE_12, STATE_13, STATE_14
};
#define StateDelay 50
#define FORWARD_DELAY 50

/*****************************************************************
*                  Demo Definitions
*****************************************************************/
#define Running true
#define Complete false
#define DEMO_DELAY 1000


/*****************************************************************
*                  BotMotions Definitions
*****************************************************************/
#define MOTION_DELAY 1700
#define TURN_DELAY 1124 / 8
#define TURN_SPEED 200
#define NEG_TURN_SPEED 100
#define FLSPEED 114
#define FRSPEED 155
#define TURN90 820

/*****************************************************************
*                  Collison Definitions
*****************************************************************/
#define COLLIDE_DELAY 1
#define N_SAMPLES 5
#define DISTANCE_THRESHOLD 15

/*****************************************************************
*                  Color Sensing Definitions
*****************************************************************/
#define Black 0
#define Red 1
#define Blue 2
#define Yellow 3
#define COLOR_DELAY 5
#define BUFFER_SIZE 5
#define SAMPLE_SIZE 50
#define BLACK_RATIO 0.53
#define RED_RATIO 0.51
#define BLUE_RATIO 0.65
#define YELLOW_RATIO 0.45
#define TOLERANCE 15000

#endif
