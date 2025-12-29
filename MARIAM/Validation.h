#pragma once

bool isPulseValid(int x) {
  return (x >= 40 && x <= 200);
}

bool isSpO2Valid(int x) {
  return (x >= 70 && x <= 100);
}
