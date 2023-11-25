#ifndef _COMPUTE_TORQUE_H_
#define _COMPUTE_TORQUE_H_

#include "SensorOptical.h"
#include "system_util.h"


//public methods:
class ComputeTorque {
    public:

        double compute_torque(double force, double angular_velocity, double angular_acceleration);

        double compute_angular_acceleration();

};

#endif