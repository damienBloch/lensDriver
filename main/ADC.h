#ifndef ADC_H
#define ADC_H
#include<SPI.h>

#define ADC_RSTX_PORT PIOC
#define ADC_RSTX_MSK (1<<5)

#define ADC_CSX_PORT PIOB
#define ADC_CSX_MSK (1<<21)

#define ADC_RDYX_PORT PIOB
#define ADC_RDYX_MSK (1<<2)

struct A2DC
{
    static void init(void);
    static volatile unsigned int readValue;
    static void update(void);
    static void initReading(void);
    static unsigned int read(void);
    static volatile unsigned int _previousTime;
    static volatile float _filteredIntensity;
    static float codeToIntensity(int value);
};
volatile unsigned int A2DC::readValue;
volatile unsigned int A2DC::_previousTime;
volatile float A2DC::_filteredIntensity;
#endif
