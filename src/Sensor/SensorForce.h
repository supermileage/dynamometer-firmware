#ifndef _SENSOR_FORCE_H_
#define _SENSOR_FORCE_H_

class SensorForce {
    public:
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
        uint32_t _lastReadTime = 0;
};

#endif