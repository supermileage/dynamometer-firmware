#ifndef _SENSOR_FORCE_H_
#define _SENSOR_FORCE_H_

#include "Sensor.h"

class SensorForce {
    public:
        /*
         * Constructor
        */
        SensorForce(pin_size_t pinNumber, PinMode mode);

        /*
         * Destructor
        */
        ~SensorForce();

        /*
         * initialization method (called at startup)
        */
        void begin();

        /*
         * handle method (called in loop)
        */
        void handle();

        /*
         * returns value representing current force on force sensor
        */
        float getForce();

    private:
        float _force;
}

#endif