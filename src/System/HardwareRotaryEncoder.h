#ifndef _ROTARY_ENCODER_H_
#define _ROTARY_ENCODER_H_

#include "HardwareInput.h"

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
                    (_action)(1);
                } else if (valA && !valB) {
                    (_action)(-1);
                }
                _lastA = valA;
            }
        }

    private:
        pin_size_t _pinA;
        pin_size_t _pinB;
        PinStatus _lastA;
        int32_t _lastReadVal = 0;
};

#endif