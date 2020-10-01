#ifndef DAC_H
#define DAC_H

#define INSL_DSBL_PORT PIOB
#define INSL_DSBL_MSK (1<<1)

#define DAC_LDACX_PORT PIOB
#define DAC_LDACX_MSK (1<<0)

#define DAC_CSX_PORT PIOA
#define DAC_CSX_MSK (1<<29)

#define DAC_GAIN_PORT PIOB
#define DAC_GAIN_MSK (1<<9)

#include<SPI.h>

typedef enum{CONSTANT,ARBITRARY}Mode;

struct DAC
{
    static void init(void);
    static unsigned int _write(int value);
    static float write(float value);
    static int getWordAt(int index);
    static unsigned int currentToCode(float I);
    static float codeToCurrent(unsigned int value);
    static void update(void);
    static void clearArray(void);

    static volatile float current;
    static volatile float targetCurrent;
    static volatile unsigned int len;
    static volatile unsigned int* arr;
    static volatile unsigned int pos;
    static volatile Mode mode;
    static volatile bool intensityCorrection;
    static volatile bool temperatureCorrection;
};
volatile unsigned int DAC::len;
volatile unsigned int* DAC::arr;
volatile unsigned int DAC::pos;
volatile float DAC::current;
volatile float DAC::targetCurrent;
volatile Mode DAC::mode;
volatile bool DAC::intensityCorrection;
volatile bool DAC::temperatureCorrection;

#endif
