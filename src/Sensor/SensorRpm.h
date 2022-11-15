#ifndef SENSOR_RPM
#define SENSOR_RPM

#include <stdint.h>

#include "Sensor.h"
#include "Wire.h"

class SensorRpm: public Sensor {
    public:
        SensorRpm();
        ~SensorRpm();
        void begin() override;
        void handle() override;
        uint32_t getRpm();

    private:
        uint32_t _rpm;
};

#endif