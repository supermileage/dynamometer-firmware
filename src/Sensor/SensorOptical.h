#ifndef _SENSOR_OPTICAL_H_
#define _SENSOR_OPTICAL_H_

#include <stdint.h>
#include "Sensor.h"
#include "PIO/pio_counter_program.pio.h"

class SensorOptical: public Sensor {
    public:
        static const uint16_t NumApertures;
        static const float VelocityFactor;
        SensorOptical(PIO pio, uint stateMachine, pin_size_t pinNumber);
        ~SensorOptical();
        String getHumanName() override;
        void begin();
        void handle();
        float getAngularVelocity();
        float getLinearVelocity();

    private:
        uint8_t _pinNumber;
        PIO _pio;
        uint _stateMachine; 
        uint32_t _startTime = 0;
        uint32_t _currentTime = 0;
        int32_t _startCount = 0;
        int32_t _currentCount = 0;
};

#endif