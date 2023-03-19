#include "SensorOptical.h"
#include "settings.h"

#define CLOCK_DIV 8.0f
#define NUM_APERTURES 64
#define MEGA 1000000
#define PI 3.1415

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
    #ifdef DEBUG_OPTICAL_ENABLED
    if (pio_counter_get_count(_pio, 0) != _lastDisplayCount) {
		DEBUG_SERIAL_LN("pio_counter: " + String(pio_counter_get_count(_pio, _stateMachine)));
        _lastDisplayCount = pio_counter_get_count(_pio, _stateMachine);
	}
    #endif
}

float SensorOptical::getAngularVelocity() {
    // n is scaled count apertures we've passed over since last call to getter
    int32_t count = pio_counter_get_count(_pio, _stateMachine);
    int32_t n = count - _lastCount;
    _lastCount = count;

    uint32_t deltaT = micros() - _lastComputeTime;
    _lastComputeTime = micros();

    float ret = ((float)n / NUM_APERTURES) * 2 * PI * (MEGA / (float)deltaT);
    return ret;
}

float SensorOptical::getLinearVelocity() {
    float ret = VelocityFactor * getAngularVelocity();
    return ret;
}