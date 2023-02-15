#ifndef _SENSOR_H_
#define _SENSOR_H_

#include "Arduino.h"

class Sensor {
    public:
	
        /**
         * INTERFACE
         * @return Human name for this sensor type
         * */
        virtual String getHumanName() = 0;
};

#endif