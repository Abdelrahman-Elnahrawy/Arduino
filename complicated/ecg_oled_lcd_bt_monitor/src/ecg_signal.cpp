#include "ecg_signal.h"

static inline int clamp_int(int v, int lo, int hi) { return v < lo ? lo : (v > hi ? hi : v); }

void ecg_buffer_init(int *buffer, uint8_t width, int baseline) {
  for (uint8_t i = 0; i < width; i++) buffer[i] = baseline;
}

int ecg_update_from_analog(int *buffer, uint8_t width, uint8_t analog_pin,
                           int analog_max, uint8_t ecg_height, uint8_t buzzer_pin) {
  int analog_val = analogRead(analog_pin);
  if (analog_val > analog_max) analog_val = analog_max;

  int ecg_val = map(analog_val, 0, analog_max, 0, ecg_height - 1);
  int percent = map(analog_val, 0, analog_max, 0, 100);
  percent = clamp_int(percent, 0, 100);

  // buzzer threshold: top 40% of waveform
  digitalWrite(buzzer_pin, (ecg_val >= (int)(ecg_height * 0.6f)) ? HIGH : LOW);

  // Shift left and append latest sample
  for (uint8_t i = 0; i < (uint8_t)(width - 1); i++) buffer[i] = buffer[i + 1];
  buffer[width - 1] = ecg_val;

  return percent;
}
