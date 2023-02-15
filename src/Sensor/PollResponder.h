#ifndef _POLL_RESPONDER_H_
#define _POLL_RESPONDER_H_

#include "Wire.h"

#include "SensorForce.h"
#include "SensorOptical.h"

/* Singleton poll responder class */
class PollResponder {
    public:
        ~PollResponder();
        static PollResponder& instance();
        void begin(TwoWire* wire, SensorForce* force, SensorOptical* optical);

    private:
        static PollResponder* _instance;
        static TwoWire* _wire;
        static SensorForce* _force;
        static SensorOptical* _optical;

        PollResponder();
        void _flush();
        void _sendResponse();
};

#endif