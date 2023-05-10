#ifndef _HARDWARE_INPUT_H_
#define _HARDWARE_INPUT_H_

#include <stdint.h>
#include <functional>

typedef std::function<void(int32_t)> InputCallback;

class HardwareInput {
    public:
        virtual ~HardwareInput() { }
        virtual void init() = 0;
        virtual void run() = 0;
        void setAction(InputCallback action) { _action = action; }

    protected:
        InputCallback _action = [](int32_t) { }; // default action
};

#endif