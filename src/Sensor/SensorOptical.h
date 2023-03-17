#ifndef _SENSOR_OPTICAL_H_
#define _SENSOR_OPTICAL_H_

#include <stdint.h>
#include "Sensor.h"
#include "PIO/pio_counter_program.pio.h"

class SensorOptical: public Sensor {
    public:
        static const uint16_t NumApertures;
        SensorOptical(PIO pio, uint stateMachine, pin_size_t pinNumber);
        ~SensorOptical();
        String getHumanName() override;
        void begin();
        void handle();
        float getAngularVelocity();

    private:
        uint8_t _pinNumber;
        PIO _pio;
        uint _stateMachine; 
        uint32_t _lastComputeTime = 0;
        int32_t _lastCount = 0;
        int32_t _lastDisplayCount = 0;
};

#endif