#ifndef MAX30102_H
#define MAX30102_H

#include <Wire.h>

class MAX30102 {
public:
    void begin();
    void update();           // read new samples
    int getBPM();            // estimated BPM
    int getSpO2();           // estimated SpO2

private:
    const int SAMPLES = 25;  // small buffer (fits UNO)
    uint32_t irBuffer[25];
    uint32_t redBuffer[25];

    int index = 0;
    bool bufferFilled = false;

    int bpm = 0;
    int spo2 = 0;

    void calculateBPM();
    void calculateSpO2();
};

#endif
