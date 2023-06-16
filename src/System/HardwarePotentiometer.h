#ifndef _HARDWARE_POTENTIOMETER_H_
#define _HARDWARE_POTENTIOMETER_H_

#include <stdint.h>

#include "HardwareInput.h"

#define ALPHA 0.125f
#define POTENTIOMETER_MAX 1016

/**
 * @brief interprets analog pin as potentiometer value
 * 
 * @note computes exponential moving average to smooth over sampling variance: 
 * pico's ADC can vary +-2 units per sample
*/
class HardwarePotentiometer : public HardwareInput {
    public:
        HardwarePotentiometer(pin_size_t pin) : _pin(pin) { }

        ~HardwarePotentiometer() { }
        
        void init() override {
            pinMode(_pin, INPUT);
            _lastReadVal = analogRead(_pin);
        }

        void run() override {
            input_data_t readVal = _readInternal();

            if (readVal != _lastReadVal) {
                input_data_t data = POTENTIOMETER_MAX - readVal;
                
                // data value shouldn't be less than 0 but if it is, set it to zero
                (_action)(data < 0 ? 0 : data);
                _lastReadVal = readVal;
            }
        }

        input_data_t read() {
            return _readInternal();
        }

    private:
        pin_size_t _pin;
        input_data_t _lastReadVal = INT32_MIN;
        float _accumulator;

        inline input_data_t _readInternal() {
            // compute exponential moving average
            int32_t readVal = analogRead(_pin);
            float accumulator = static_cast<float>(_lastReadVal) * (1 - ALPHA);
            return static_cast<int32_t>(accumulator + static_cast<float>(readVal) * ALPHA);
        }


};

#endif