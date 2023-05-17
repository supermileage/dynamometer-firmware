#include "settings.h"
#include "SensorOptical.h"

// div of 8.0 works fine, but will count 2x when pio runs any faster
#define PIO_CLOCK_DIV 8.0f
#define MEGA 1000000

#define NUM_APERTURES 64
#define GEAR_RATIO 0.2
#define ROLLER_RADIUS 0.08276057 // metres
#define VELOCITY_FACTOR (GEAR_RATIO * ROLLER_RADIUS) // speed of vehicle [m/s] = velocity factor * angular velocity [rad/s]

const uint16_t SensorOptical::NumApertures = NUM_APERTURES;
const float SensorOptical::VelocityFactor = VELOCITY_FACTOR; 

SensorOptical::SensorOptical(PIO pio, uint stateMachine, uint32_t readInterval) :
    _pio(pio), _stateMachine(stateMachine), _readInterval(readInterval) { }

SensorOptical::~SensorOptical() { }

String SensorOptical::getHumanName() {
    return "OpticalSensor";
}

void SensorOptical::begin() {
    pinMode(OPTICAL_SENSOR_PIN, INPUT);
	uint offset = pio_add_program(_pio, &pio_counter_program);
	pio_counter_init(_pio, _stateMachine, offset, OPTICAL_SENSOR_PIN, PIO_CLOCK_DIV);
    _lastUpdateTime = micros();
}

void SensorOptical::handle() {
    uint32_t currentTime = micros();
    if (currentTime >= _lastUpdateTime + _readInterval) {
        // n is num apertures we've passed over since last velocity update
        int32_t currentCount = pio_counter_get_count(_pio, _stateMachine);
        int32_t n = currentCount - _lastCount;
        uint32_t deltaT = currentTime - _lastUpdateTime;

        _angularVelocity = ((double)n / NUM_APERTURES) * TWO_PI * (MEGA / (double)deltaT);
        _lastCount = currentCount;
        _lastUpdateTime = currentTime;
    }

    #ifdef DEBUG_OPTICAL_ENABLED
    if (pio_counter_get_count(_pio, _stateMachine) != _lastDisplayCount) {
        DEBUG_SERIAL_LN("pio_counter: " + String(pio_counter_get_count(_pio, _stateMachine)));
        _lastDisplayCount = pio_counter_get_count(_pio, _stateMachine);
    }
    #endif
}

void SensorOptical::setReadInterval(uint32_t interval) {
    _readInterval = interval;
}

uint32_t SensorOptical::getReadInterval() {
    return _readInterval;
}

double SensorOptical::getAngularVelocity() {
    return _angularVelocity;
}

double SensorOptical::getLinearVelocity() {
    return VELOCITY_FACTOR * _angularVelocity;
}
