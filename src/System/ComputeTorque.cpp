#include <vector>
#include <thread>

#include "ComputeTorque.h"

double compute_torque(SensorOptical optical, double force, double angular_velocity, double angular_acceleration) {

    double I = 0.43911115;
    double a = compute_angular_acceleration(optical);
    double torque = I * a;
    return torque; 
    
}


double compute_angular_acceleration(SensorOptical optical) {
    float t = optical.getReadInterval();
    float vel1 = optical.getAngularVelocity();

    std::this_thread::sleep_for(std::chrono::milliseconds(static_cast<int>(t * 1000))); // Wait for interval t

    float vel2 = optical.getAngularVelocity();

    double angularAcceleration = (vel2-vel1)/t;

    return angularAcceleration;
}

