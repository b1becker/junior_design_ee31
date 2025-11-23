#ifndef BOTMOTIONS_H
#define BOTMOTIONS_H

class BotMotions
{
public:
    BotMotions(int motor_a1, int motor_a2, int motor_b1, int motor_b2, int ena,
        int enb);
    void loop();
    void stop();
    void forward();
    void backward();
    void left();
    void right();
    void pivotCW();
    void pivotCCW();

private:
    int motor_a1; 
    int motor_a2;
    int motor_b1;
    int motor_b2;
    int ena; 
    int enb;
};


#endif