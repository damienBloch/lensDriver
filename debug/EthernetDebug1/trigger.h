#ifndef TRIGGER_H
#define TRIGGER_H

#define TRIG_PORT PIOA
#define TRIG_MSK (1<<4)
#include<DueTimer.h>

struct TRIG
{
    static void init(void);
    static void change(void);
    static void startSequence(void);
    static void stopSequence(void);
    static volatile bool state;
};
volatile bool TRIG::state;


#endif
