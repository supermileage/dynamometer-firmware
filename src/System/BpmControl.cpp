#include "HardwareInput.h"
#include "BpmControl.h"
#include "ErrorLogger.h"

#define ANALOG_MAX 1023
#define ANALOG_FREQ 20000

BpmControl::BpmControl(pin_size_t pinNum){
    _pinNum = pinNum;
}

void BpmControl::init(){
    pinMode(_pinNum, OUTPUT);
    analogWriteRange(ANALOG_MAX);
    analogWriteFreq(ANALOG_FREQ);
};

void BpmControl::setControlSignal(int32_t controlSignal){ 
    _controlSignal = controlSignal;
    if (_active == true){
        dyno_assert(_controlSignal >= 0 && _controlSignal <= 1023);
        analogWrite(_pinNum, _controlSignal);
    }
    else {
        analogWrite(_pinNum, 0);
    }
};

int32_t BpmControl::getControlSignal(void){ 
    return _controlSignal;
};

void BpmControl::setActive(bool active){
    _active = active;
    if (active == false) {
        analogWrite(_pinNum, 0);
    }
};

bool BpmControl::getStatus(void){
    return _active;
};
