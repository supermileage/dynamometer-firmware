#ifndef _HARDWARE_POTENTIOMETER_H_
#define _HARDWARE_POTENTIOMETER_H_

#include <stdint.h>

#include "HardwareInput.h"

#define POTENTIOMETER_MAX 1023

class HardwarePotentiometer : public HardwareInput {
    public:
        HardwarePotentiometer(pin_size_t pin) : _pin(pin) { }

        ~HardwarePotentiometer() { }
        
        void init() override {
            pinMode(_pin, INPUT);
        }

        void run() override {
            int32_t readVal = static_cast<int32_t>(analogRead(_pin));

            if (readVal != _lastReadVal) {
                (_action)(POTENTIOMETER_MAX - readVal);
                _lastReadVal = readVal;
            }
        }

    private:
        pin_size_t _pin;
        int32_t _lastReadVal = INT32_MIN;
};

#endif