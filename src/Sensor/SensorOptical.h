#ifndef _SENSOR_OPTICAL_H_
#define _SENSOR_OPTICAL_H_

#include <stdint.h>
#include "pio_counter_program.pio.h"

// #define DEBUG_OPTICAL_ENABLED

#define SENSOR_OPTICAL_DEFAULT_READ_INTERVAL 1000

class SensorOptical {
    public:
        // Number of aperture openings on the optical wheel
        static const uint16_t NumApertures;

        // speed of vehicle [m/s] = velocity factor * angular velocity [rad/s]
        static const float VelocityFactor;

        /**
         * @brief Constructor
         * @param pio Pio object
         * @param stateMachine State machine object
         * @param readInterval Update time interval in microseconds
        */
        SensorOptical(PIO pio, uint stateMachine, uint32_t readInterval = SENSOR_OPTICAL_DEFAULT_READ_INTERVAL);

        // Destructor
        ~SensorOptical();
        
        /**
         * @brief Initialization method (called at startup). Sets optical sensor pin as input, and initializes pio_counter_program.
        */
        void begin();

        /**
         * @brief Handle method (called in loop). Calculates angular velocity of the optical wheel at a specified time interval.
        */
        void handle();

        /**
         * @return Value representing current angular velocity [rad/s].
        */
        float getAngularVelocity();
        
        /**
         * @return Value representing current velocity of vehicle [m/s].
        */
        float getLinearVelocity();
        
        /**
         * @brief Set the time interval to update the angular velocity. 
         * @note A smaller time interval means measurements are more precise in the time domain, however, each individual measurement is less precise. This should not be a problem if a rolling average is applied to velocity.
         * 
         * @param interval Time interval in microseconds
        */
        void setReadInterval(uint32_t interval);

        /**
         * @return Current time interval to update the angular velocity.
        */
        uint32_t getReadInterval();

    private:
        PIO _pio;
        uint _stateMachine; 
        uint32_t _lastUpdateTime = 0;
        int32_t _lastUpdateCount = 0;
        uint32_t _readInterval = 0;
        float _angularVelocity = 0;

        #ifdef DEBUG_OPTICAL_ENABLED
        int32_t _lastDisplayCount = 0;
        #endif
};

#endif