#ifndef _SENSOR_H_
#define _SENSOR_H_

#include "settings.h"

class Sensor {
    public:
	
        /**
         * INTERFACE
         * @return Human name for this sensor type
         * */
        virtual String getHumanName() = 0;
};

#endif