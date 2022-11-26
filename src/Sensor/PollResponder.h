#ifndef _POLL_RESPONDER_H_
#define _POLL_RESPONDER_H_

#include "../System/Handleable.h"
#include "Wire.h"

#include "SensorForce.h"

class PollResponder: public Handleable {
    public:
        PollResponder(TwoWire* wire, SensorForce* force);
        ~PollResponder();
        void begin() override;
        void handle() override;

    private:
        TwoWire* _wire;
        SensorForce* _force;

        static void _sendResponse();
        static void _flush();
};

#endif