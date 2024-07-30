#ifndef _SENSOR_FORCE_H_
#define _SENSOR_FORCE_H_

class SensorForce {
    public:
        /*
         * Destructor
        */
        ~SensorForce();

        /**
         * @brief Initialization method (called at startup). Sets force sensor pin as input.
        */
        void begin();

        /**
         * @brief Handle method (called in loop). Reads and saves the force sensor value at a specified time interval.
        */
        void handle();

        /**
         * @return Value representing current force on force sensor.
        */
        float getForce();

    private:
        float _force;
        uint32_t _lastReadTime = 0;
};

#endif