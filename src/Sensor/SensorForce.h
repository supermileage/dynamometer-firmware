#ifndef _SENSOR_FORCE_H_
#define _SENSOR_FORCE_H_

#include "Sensor.h"

class SensorForce : public Sensor {
    public:
        /*
         * Constructor
        */
        SensorForce(pin_size_t pinNumber, PinMode mode);

        /*
         * Destructor
        */
        ~SensorForce();

        String getHumanName() override;

        /*
         * initialization method (called at startup)
        */
        void begin() override;

        /*
         * handle method (called in loop)
        */
        void handle() override;

        /*
         * returns value representing current force on force sensor
        */
        float getForce();

    private:
        float _force;
};

#endif