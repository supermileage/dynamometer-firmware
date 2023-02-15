#include "SensorOptical.h"
#include "settings.h"

#define NUM_APERATURES 64
#define MEGA 1000000
#define PI 3.14

SensorOptical::SensorOptical(pin_size_t pinNumber, PinMode mode) {
    _pinNumber = pinNumber;
    _pinMode = mode;
}

SensorOptical::~SensorOptical() { }

String SensorOptical::getHumanName() {
    return "OpticalSensor";
}

void SensorOptical::begin() {
    pinMode(_pinNumber, _pinMode);
    _lastComputeTime = micros();
}

void SensorOptical::handle() {
    bool currentReadValue = digitalRead(_pinNumber);

    if (_lastReadValue != currentReadValue) {
        if (currentReadValue) {
            _n++;
        }
        _lastReadValue = currentReadValue;
        DEBUG_SERIAL_LN("Optical sensor went from low to high");
    }
}

/* Only computed as often as we ask for it */
float SensorOptical::getAngularVelocity() {
    // _n is scaled count apertures we've passed over since last call to getter
    uint32_t deltaT = micros() - _lastComputeTime;
    _lastComputeTime = micros();
    float ret = ((float)_n / NUM_APERATURES) * PI * (MEGA / (float)deltaT);
    _n = 0;
    return ret;
}
