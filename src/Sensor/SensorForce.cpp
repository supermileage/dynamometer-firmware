#include "settings.h"
#include "SensorForce.h"

#define READ_INTERVAL 1000

#define MIN_READ_VALUE 103
#define MAX_READ_VALUE 977

SensorForce::SensorForce(pin_size_t pinNumber, PinMode mode) {
    _pinNumber = pinNumber;
    _pinMode = mode;
}

SensorForce::~SensorForce() { }

String SensorForce::getHumanName() {
    return "Force Sensor";
}

void SensorForce::begin() {
    pinMode(_pinNumber, _pinMode);
}

void SensorForce::handle() {
    if(millis() > _lastReadTime + READ_INTERVAL) {
        _lastReadTime = millis();
        
        int int_force = analogRead(_pinNumber);
        _force = ((float)(int_force < MIN_READ_VALUE ?
            0 : int_force - MIN_READ_VALUE) / (MAX_READ_VALUE - MIN_READ_VALUE)) * 25;
    }
}

float SensorForce::getForce() {
    return _force;
}

