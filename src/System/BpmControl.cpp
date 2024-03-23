#include "HardwareInput.h"
#include "BpmControl.h"

#define ANALOG_MIN 0
#define ANALOG_MAX 1023
#define ANALOG_FREQ 20000

BpmControl::BpmControl (pin_size_t pinNum){
    _pinNum = pinNum;
}

void BpmControl::init (){
    pinMode(_pinNum, OUTPUT);
    analogWriteRange(ANALOG_MAX);
    analogWriteFreq(ANALOG_FREQ);
};

void BpmControl::setControlSignal (int32_t controlSignal){ 
    if (_active == true){
        if (controlSignal >= 0 && controlSignal <= 1023){
            analogWrite (_pinNum, controlSignal);
        }
    }
    else {
        analogWrite (_pinNum, 0);
    }
};

void BpmControl::setActive (bool active){
    _active = active;
    if (active == false) {
        analogWrite (_pinNum, 0);
    }
};