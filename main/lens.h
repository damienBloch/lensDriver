#ifndef LENS_H
#define LENS_H
#include<Wire.h>

struct LENS
{
    static void init(void);
    static float getTemperature(void);
    static volatile float temperature;
};
volatile float LENS::temperature;
#endif
