#ifndef _SENSOR_OPTICAL_H_
#define _SENSOR_OPTICAL_H_

#include <stdint.h>

#include "Sensor.h"
#include "Wire.h"

class SensorOptical: public Sensor {
    public:
        SensorOptical(pin_size_t pinNumber, PinMode mode);
        ~SensorOptical();
        String getHumanName() override;
        void begin();
        void handle();
        float getAngularVelocity();

    private:
        uint8_t _pinNumber;
        PinMode _pinMode;
        uint64_t _lastComputeTime = 0;
        uint32_t _lastReadValue = 0;
        uint32_t _n = 0;
};

#endif