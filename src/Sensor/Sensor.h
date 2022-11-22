#ifndef _SENSOR_H_
#define _SENSOR_H_

#include "Arduino.h"
#include "../System/Handleable.h"

class Sensor : public Handleable {
    public:
	
        /**
         * INTERFACE
         * @return Human name for this sensor type
         * */
        virtual String getHumanName() = 0;
};

#endif