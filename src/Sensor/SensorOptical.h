#ifndef _SENSOR_OPTICAL_H_
#define _SENSOR_OPTICAL_H_

#include <stdint.h>
#include "pio_counter_program.pio.h"

// #define DEBUG_OPTICAL_ENABLED

#define SENSOR_OPTICAL_DEFAULT_READ_INTERVAL 1000

class SensorOptical {
    public:
        static const uint16_t NumApertures;
        static const float VelocityFactor;

        SensorOptical(PIO pio, uint stateMachine, uint32_t readInterval = SENSOR_OPTICAL_DEFAULT_READ_INTERVAL);
        ~SensorOptical();
        void begin();
        void handle();
        float getAngularVelocity();
        float getAngularAcceleration();
        float getLinearVelocity();
        void setReadInterval(uint32_t interval);
        uint32_t getReadInterval();

    private:
        PIO _pio;
        uint _stateMachine; 
        uint32_t _lastUpdateTime = 0;
        int32_t _lastUpdateCount = 0;
        int32_t _lastVelocity = 0;
        uint32_t _readInterval = 0;
        float _angularVelocity = 0;
        float _angularAcceleration = 0;

        #ifdef DEBUG_OPTICAL_ENABLED
        int32_t _lastDisplayCount = 0;
        #endif
};

#endif