#include "SensorOptical.h"
#include "settings.h"

#define CLOCK_DIV 8.0f
#define NUM_APERTURES 64
#define MEGA 1000000
#define _PI 3.1415

#define READ_INTERVAL 1000 // microseconds

// constants to calculate velocity
#define GEAR_RATIO 0.2 
#define ROLLER_RADIUS 0.08276057 // metres

// #define DEBUG_OPTICAL_ENABLED

const uint16_t SensorOptical::NumApertures = NUM_APERTURES;
const float SensorOptical::VelocityFactor = GEAR_RATIO * ROLLER_RADIUS; // speed of vehicle [m/s] = velocity factor * angular velocity [rad/s]

SensorOptical::SensorOptical(PIO pio, uint stateMachine, pin_size_t pinNumber) {
    _pio = pio;
    _stateMachine = stateMachine;
    _pinNumber = pinNumber;
}

SensorOptical::~SensorOptical() { }

String SensorOptical::getHumanName() {
    return "OpticalSensor";
}

void SensorOptical::begin() {
    pinMode(OPTICAL_SENSOR_PIN, INPUT);
	uint offset = pio_add_program(_pio, &pio_counter_program);

    // div of 8.0 works fine, but will count 2x when pio runs any faster
	pio_counter_init(_pio, _stateMachine, offset, OPTICAL_SENSOR_PIN, CLOCK_DIV);
    _lastComputeTime = micros();
}

void SensorOptical::handle() {

    uint32_t currentTime = micros();
    if (currentTime > _lastUpdateTime + READ_INTERVAL) {

        // n is num apertures we've passed over since last velocity update
        int32_t currentCount = pio_counter_get_count(_pio, _stateMachine);
        int32_t n = currentCount - _lastUpdateCount;

        uint32_t deltaT = currentTime - _lastUpdateTime;

        _angularVelocity = ((float)n / NUM_APERTURES) * 2 * _PI * (MEGA / (float)deltaT);

        _lastUpdateCount = currentCount;
        _lastUpdateTime = currentTime;
    }


    #ifdef DEBUG_OPTICAL_ENABLED
    if (pio_counter_get_count(_pio, _stateMachine) != _lastDisplayCount) {
        DEBUG_SERIAL_LN("pio_counter: " + String(pio_counter_get_count(_pio, _stateMachine)));
        _lastDisplayCount = pio_counter_get_count(_pio, _stateMachine);
    }
    #endif
}

float SensorOptical::getAngularVelocity() {
    return _angularVelocity;
}

float SensorOptical::getLinearVelocity() {
    return VelocityFactor * getAngularVelocity();
}