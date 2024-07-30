#include "settings.h"
#include "SensorForce.h"

#define READ_INTERVAL 1000

#define MIN_READ_VALUE 103
#define MAX_READ_VALUE 977

SensorForce::~SensorForce() { }

void SensorForce::begin() {
    // sets force sensor pin as input
    pinMode(FORCE_SENSOR_PIN, INPUT);
}

void SensorForce::handle() {
    if(millis() > _lastReadTime + READ_INTERVAL) {
        _lastReadTime = millis();
        
        // read force sensor voltage and convert it to force
        int int_force = analogRead(FORCE_SENSOR_PIN);
        _force = ((float)(int_force < MIN_READ_VALUE ?
            0 : int_force - MIN_READ_VALUE) / (MAX_READ_VALUE - MIN_READ_VALUE)) * 25;
    }
}

float SensorForce::getForce() {
    return _force;
}

