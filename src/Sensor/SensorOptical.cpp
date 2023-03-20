#include "SensorOptical.h"
#include "settings.h"

#define CLOCK_DIV 8.0f
#define NUM_APERTURES 64
#define MEGA 1000000
#define PI 3.1415

// #define DEBUG_OPTICAL_ENABLED

const uint16_t SensorOptical::NumApertures = NUM_APERTURES;

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
    
    // check if an aperture has passed since the last handle() call
    if (pio_counter_get_count(_pio, _stateMachine) != _currentCount) {
        // aperture has passed, so update current count and current aperture time
        _currentCount = pio_counter_get_count(_pio, _stateMachine);
        _currentTime = micros();

        
        #ifdef DEBUG_OPTICAL_ENABLED
        DEBUG_SERIAL_LN("pio_counter: " + String(pio_counter_get_count(_pio, _stateMachine)));
        #endif
    }
}

float SensorOptical::getAngularVelocity() {
    // n is scaled count apertures we've passed over since last call to getter
    int32_t n = _currentCount - _lastUpdateCount;
    _lastUpdateCount = _currentCount;

    uint32_t deltaT = _currentTime - _lastUpdateTime;
    _lastUpdateTime = _currentTime;

    float ret = ((float)n / NUM_APERTURES) * 2 * PI * (MEGA / (float)deltaT);
    return ret;
}
