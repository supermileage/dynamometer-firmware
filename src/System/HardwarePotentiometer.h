#ifndef _HARDWARE_POTENTIOMETER_H_
#define _HARDWARE_POTENTIOMETER_H_

#include <stdint.h>

#include "HardwareInput.h"

#define ALPHA 0.125f
#define POTENTIOMETER_MAX 1016

class HardwarePotentiometer : public HardwareInput {
    public:
        HardwarePotentiometer(pin_size_t pin) : _pin(pin) { }

        ~HardwarePotentiometer() { }
        
        void init() override {
            pinMode(_pin, INPUT);
            _lastReadVal = analogRead(_pin);
        }

        void run() override {
            int32_t readVal = analogRead(_pin);

            // compute exponential moving average ()
            float accumulator = static_cast<float>(_lastReadVal) * (1 - ALPHA);
            readVal = static_cast<int32_t>(accumulator + static_cast<float>(readVal) * ALPHA);

            if (readVal != _lastReadVal) {
                input_data_t data = POTENTIOMETER_MAX - readVal;
                (_action)(data < 0 ? 0 : data);
                _lastReadVal = readVal;
            }
        }

    private:
        pin_size_t _pin;
        input_data_t _lastReadVal = INT32_MIN;
        float _accumulator;
};

#endif