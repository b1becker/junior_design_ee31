#ifndef BOTMOTIONS_H
#define BOTMOTIONS_H

class BotMotions
{
private:
    int motor_a1; 
    int motor_a2;
    int motor_b1;
    int motor_b2;
    int ena; 
    int enb;
    /* data */
public:
    BotMotions(int motor_a1, int motor_a2, int motor_b1, int motor_b2, int ena,
        int enb);
    void loop();
    void forward();
    void backward();
    void left();
    void right();
    void NinetyLeft();
    // ~BotMotions();
};


#endif