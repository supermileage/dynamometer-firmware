#ifndef _ROTARY_ENCODER_H_
#define _ROTARY_ENCODER_H_

#include "HardwareInput.h"

// rotary encoder events can be a bit spammy, so update on interval
#define ENCODER_UPDATE_INTERVAL 40

/**
 * @brief Rotary encoder input class
 * 
 * @note data passed to InputCallback func is number of steps since last call
*/
class HardwareRotaryEncoder : public HardwareInput {
    public:
        HardwareRotaryEncoder(pin_size_t pinA, pin_size_t pinB) : _pinA(pinA), _pinB(pinB) { }
        ~HardwareRotaryEncoder() { }

        void init() override {
            pinMode(_pinA, INPUT);
            pinMode(_pinB, INPUT);
            _lastA = digitalRead(_pinA);
        }

        void run() override {
            PinStatus valA = digitalRead(_pinA);
            
            if (valA != _lastA) {
                PinStatus valB = digitalRead(_pinB);    
                
                if (valA && valB) {
                    ++_counter;
                } else if (valA && !valB) {
                    --_counter;
                }
                _lastA = valA;
            }

            // check if we should update
            if (millis() >= _lastUpdateMillis + ENCODER_UPDATE_INTERVAL) {
                _lastUpdateMillis = millis();

                if (_lastUpdateCount != _counter) {
                    // call action with number of steps since last update
                    (_action)(_counter - _lastUpdateCount);
                    _lastUpdateCount = _counter;
                }
            }
        }

    private:
        pin_size_t _pinA;
        pin_size_t _pinB;
        PinStatus _lastA;
        input_data_t _counter = 0;
        input_data_t _lastUpdateCount = 0;
        uint32_t _lastUpdateMillis = 0;
};

#endif