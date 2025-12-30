#include "MAX30102.h"
#include <MAX30105.h>

MAX30105 particleSensor;

void MAX30102::begin() {
    particleSensor.begin(Wire, I2C_SPEED_FAST);
    particleSensor.setup();
    particleSensor.setPulseAmplitudeRed(0x1F);
    particleSensor.setPulseAmplitudeIR(0x1F);
}

void MAX30102::update() {
    if (!particleSensor.available()) return;

    uint32_t ir = particleSensor.getIR();
    uint32_t red = particleSensor.getRed();

    irBuffer[index] = ir;
    redBuffer[index] = red;

    index++;
    if (index >= SAMPLES) {
        index = 0;
        bufferFilled = true;
    }

    if (bufferFilled) {
        calculateBPM();
        calculateSpO2();
    }

    particleSensor.nextSample();
}

void MAX30102::calculateBPM() {
    long sum = 0;
    for (int i = 0; i < SAMPLES; i++) sum += irBuffer[i];
    long avg = sum / SAMPLES;

    // detect threshold crossings to estimate BPM
    int beats = 0;
    for (int i = 1; i < SAMPLES; i++) {
        if (irBuffer[i - 1] < avg && irBuffer[i] > avg) beats++;
    }

    bpm = beats * 12; // scale for 5 samples/sec approx
}

void MAX30102::calculateSpO2() {
    long irAvg = 0, redAvg = 0;
    for (int i = 0; i < SAMPLES; i++) {
        irAvg += irBuffer[i];
        redAvg += redBuffer[i];
    }
    irAvg /= SAMPLES;
    redAvg /= SAMPLES;

    // simple ratio method (not medically accurate)
    float ratio = (float)redAvg / (float)irAvg;

    spo2 = 110 - (ratio * 25);
    if (spo2 < 70) spo2 = 70;
    if (spo2 > 100) spo2 = 100;
}

int MAX30102::getBPM() {
    return bpm;
}

int MAX30102::getSpO2() {
    return spo2;
}
