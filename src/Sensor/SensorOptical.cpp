#include "settings.h"
#include "SensorOptical.h"

// div of 8.0 works fine, but will count 2x when pio runs any faster
#define PIO_CLOCK_DIV 8.0f
#define MEGA 1000000
#define _PI 3.1415f

#define NUM_APERTURES 64
#define GEAR_RATIO 0.2f
#define ROLLER_RADIUS 0.08276057f // metres
#define INITIAL_ANGULAR_VELOCITY 0.0f
#define VELOCITY_FACTOR (GEAR_RATIO * ROLLER_RADIUS) // speed of vehicle [m/s] = velocity factor * angular velocity [rad/s]

const uint16_t SensorOptical::NumApertures = NUM_APERTURES;
const float SensorOptical::VelocityFactor = VELOCITY_FACTOR;

SensorOptical::SensorOptical(PIO pio, uint stateMachine, uint32_t readInterval) : _pio(pio), _stateMachine(stateMachine), _readInterval(readInterval) {}

SensorOptical::~SensorOptical() {}

void SensorOptical::begin()
{
    // sets optical sensor pin as input
    pinMode(OPTICAL_SENSOR_PIN, INPUT);

    // initialize pio_counter program (pseudo-assembly code used to track number of aperture passes)
    uint offset = pio_add_program(_pio, &pio_counter_program);
    pio_counter_init(_pio, _stateMachine, offset, OPTICAL_SENSOR_PIN, PIO_CLOCK_DIV);

    _lastUpdateTime = micros();
    _lastVelocity = INITIAL_ANGULAR_VELOCITY;
}

void SensorOptical::handle()
{

    // calculate how much time has passed since the last update
    uint32_t currentTime = micros();
    uint32_t deltaT;
    if (currentTime < _lastUpdateTime)
    {
        // overflow: compute interval with overflow
        deltaT = UINT32_MAX - _lastUpdateTime + currentTime + 1;
    }
    else
    {
        // no overflow
        deltaT = currentTime - _lastUpdateTime;
    }

    // check if we need to update the velocity values
    if (deltaT >= _readInterval)
    {
        // calculate angular velocity
        int32_t currentCount = pio_counter_get_count(_pio, _stateMachine);
        int32_t n = currentCount - _lastUpdateCount; // n is num apertures we've passed over since last velocity update

        _angularVelocity = ((float)n / NUM_APERTURES) * 2 * _PI * (MEGA / (float)deltaT);
        _lastUpdateCount = currentCount;
        _lastUpdateTime = currentTime;
        _lastVelocity = _angularVelocity;
    }

#ifdef DEBUG_OPTICAL_ENABLED
    if (pio_counter_get_count(_pio, _stateMachine) != _lastDisplayCount)
    {
        DEBUG_SERIAL_LN("pio_counter: " + String(pio_counter_get_count(_pio, _stateMachine)));
        _lastDisplayCount = pio_counter_get_count(_pio, _stateMachine);
    }
#endif
}

void SensorOptical::setReadInterval(uint32_t interval)
{
    _readInterval = interval;
}

uint32_t SensorOptical::getReadInterval()
{
    return _readInterval;
}

float SensorOptical::getAngularVelocity()
{
    return _angularVelocity;
}

float SensorOptical::getLinearVelocity()
{
    return VELOCITY_FACTOR * _angularVelocity;
}
