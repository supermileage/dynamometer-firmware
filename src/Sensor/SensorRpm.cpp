#include "SensorRpm.h"
#include "settings.h"

#define APERATURES_PER_ROTATION 64

SensorRpm::SensorRpm(pin_size_t pinNumber, PinMode mode) {
    _pinNumber = pinNumber;
    _pinMode = mode;
}

SensorRpm::~SensorRpm() { }

String SensorRpm::getHumanName() {
    return "Optical Sensor RPM";
}

void SensorRpm::begin() {
    pinMode(_pinNumber, _pinMode);
}

void SensorRpm::handle() {
    // read pin 
    // check if value has changed and value is high
    // add 1 to counter
    // wait until counter reaches 16
    // read current time 

    // to calculate rpm: x us for APERATURES_PER_ROTATION open and APERATURES_PER_ROTATION close
    // means x us for 1 revolution
    // means 60*10^6/x revolutions in a minute
    unsigned long currentReadTime = micros();
    bool currentReadValue = digitalRead(_pinNumber);
    if (_lastReadValue != currentReadValue) {
        if (currentReadValue == 1) {
            if(++_n % APERATURES_PER_ROTATION == 0) {
                _rpm = (60 * 1000000) / (currentReadTime - _lastReadTime);
                _lastReadTime = currentReadTime;
                _n = 0; 
            }
        }
        _lastReadValue = currentReadValue;
        DEBUG_SERIAL_LN("Optical sensor went from low to high");
    }
}

float SensorRpm::getRpm() {
    return _rpm;
}
