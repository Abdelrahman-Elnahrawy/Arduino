#include "max3010x_sensor.h"

static const int MAX_SAMPLES = 25; // ~5s window at 5 Hz
static uint32_t ir_buffer[MAX_SAMPLES];
static uint32_t red_buffer[MAX_SAMPLES];
static int sample_index = 0;
static bool buffer_filled = false;
static int pulse_bpm = 0;
static int spo2_pct  = 0;

void max3010x_begin(MAX30105 &sensor) {
  if (!sensor.begin(Wire, I2C_SPEED_FAST)) {
    // sensor not found; continue gracefully
  }
  sensor.setup();
  sensor.setPulseAmplitudeRed(0x1F);
  sensor.setPulseAmplitudeIR(0x1F);
}

void max3010x_update_and_compute(MAX30105 &sensor) {
  if (!sensor.available()) return;

  uint32_t ir  = sensor.getIR();
  uint32_t red = sensor.getRed();

  ir_buffer[sample_index]  = ir;
  red_buffer[sample_index] = red;

  sample_index++;
  if (sample_index >= MAX_SAMPLES) { sample_index = 0; buffer_filled = true; }

  if (buffer_filled) {
    long ir_sum = 0; for (int i = 0; i < MAX_SAMPLES; i++) ir_sum += ir_buffer[i];
    long red_sum = 0; for (int i = 0; i < MAX_SAMPLES; i++) red_sum += red_buffer[i];
    long ir_avg  = ir_sum  / MAX_SAMPLES;
    long red_avg = red_sum / MAX_SAMPLES;

    // BPM: count rising edges around avg IR
    int beats = 0;
    for (int i = 1; i < MAX_SAMPLES; i++) {
      if (ir_buffer[i - 1] < (uint32_t)ir_avg && ir_buffer[i] >= (uint32_t)ir_avg) beats++;
    }
    pulse_bpm = beats * 12; // 5s window => *12 to get bpm

    // SpO2: naive ratio
    float ratio = (ir_avg > 0) ? ((float)red_avg / (float)ir_avg) : 1.0f;
    int est = (int)(110.0f - (ratio * 25.0f));
    if (est < 70) est = 70; if (est > 100) est = 100;
    spo2_pct = est;
  }

  sensor.nextSample();
}

int max3010x_get_bpm()  { return pulse_bpm; }
int max3010x_get_spo2() { return spo2_pct; }
