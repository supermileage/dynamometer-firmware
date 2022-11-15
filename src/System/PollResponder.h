#ifndef _POLL_RESPONDER_H_
#define _POLL_RESPONDER_H_

#include "Handleable.h"

class PollResponder: public Handleable {
    public:
        PollResponder();
        ~PollResponder();
        void begin() override;
        void handle() override;
};

#endif