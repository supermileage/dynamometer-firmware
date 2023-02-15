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
    return "Optical Sensor RPM";
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
    // everything scaled * 1000
    // _n is scaled count of aperatures we've passed over since last read (count * 1000)
    uint32_t deltaT = micros() - _lastComputeTime;
    _lastComputeTime = micros();
    float ret = ((float)_n / NUM_APERATURES) * PI * (MEGA / (float)deltaT);
    _n = 0;
    return ret;
}
