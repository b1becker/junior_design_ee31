#ifndef CONSTANTS_H
#define CONSTANTS_H


/*****************************************************************
*                  Interrupt Pin
*****************************************************************/
#define InterruptPin 13


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

#endif
