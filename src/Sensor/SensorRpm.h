#ifndef SENSOR_RPM
#define SENSOR_RPM

#include <stdint.h>

#include "Sensor.h"
#include "Wire.h"

class SensorRpm: public Sensor {
    public:
        SensorRpm(pin_size_t pinNumber, PinMode mode);
        ~SensorRpm();
        String getHumanName() override;
        void begin() override;
        void handle() override;
        float getRpm();

    private:
        float _rpm = 0;
        uint8_t _pinNumber;
        PinMode _pinMode;
        unsigned long _lastReadTime = 0;
        uint32_t _lastReadValue = 0;
        uint32_t _n;
};

#endif