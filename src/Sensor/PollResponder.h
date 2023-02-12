#ifndef _POLL_RESPONDER_H_
#define _POLL_RESPONDER_H_

#include "Wire.h"

#include "SensorForce.h"
#include "SensorRpm.h"

/* Singleton poll responder class */
class PollResponder {
    public:
        ~PollResponder();
        static PollResponder& instance();
        void begin(TwoWire* wire, SensorForce* force, SensorRpm* rpm);
        void sendResponse();

    private:
        static PollResponder* _instance;
        static TwoWire* _wire;
        static SensorForce* _force;
        static SensorRpm* _rpm;

        PollResponder();
        static void _flush();
};

#endif