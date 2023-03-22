#ifndef _SENSOR_OPTICAL_H_
#define _SENSOR_OPTICAL_H_

#include <stdint.h>
#include "Sensor.h"
#include "PIO/pio_counter_program.pio.h"

#define SENSOR_OPTICAL_DEFAULT_READ_INTERVAL 1000

class SensorOptical: public Sensor {
    public:
        static const uint16_t NumApertures;
        static const float VelocityFactor;

        SensorOptical(PIO pio, uint stateMachine, uint32_t readInterval = SENSOR_OPTICAL_DEFAULT_READ_INTERVAL);
        ~SensorOptical();
        String getHumanName() override;
        void begin();
        void handle();
        double getAngularVelocity();
        double getLinearVelocity();
        void setReadInterval(uint32_t interval);
        uint32_t getReadInterval();

    private:
        PIO _pio;
        uint _stateMachine; 
        uint32_t _lastUpdateTime = 0;
        int32_t _lastUpdateCount = 0;
        uint32_t _readInterval = 0;
        double _angularVelocity = 0;

        // for debugging purposes
        int32_t _lastDisplayCount = 0;
};

#endif