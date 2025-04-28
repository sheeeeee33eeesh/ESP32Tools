#include <ELECHOUSE_CC1101_SRC_DRV.h>

#define size 60
byte buffer[size];

void setup() {
  ELECHOUSE_cc1101.Init();
}

void loop() {
  int len = 60;
  for (int i = 0; i < len; i++) {
    buffer[i] = random(33, 127);
  }
  ELECHOUSE_cc1101.SendData(buffer, len);
}
