#ifndef _HARDWARE_INPUT_SERIAL_H_
#define _HARDWARE_INPUT_SERIAL_H_

#include "Arduino.h"
#include "HardwareInput.h"

class HardwareInputSerial : public HardwareInput {
    public:
        ~HardwareInputSerial() { }

        void init() override { }

        void run() override {
            while (Serial.available()) {
                (_action)((int32_t)Serial.read());
            }
        }
};

#endif