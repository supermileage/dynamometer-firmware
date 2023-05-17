#ifndef _HARDWARE_INPUT_H_
#define _HARDWARE_INPUT_H_

#include <stdint.h>
#include <functional>

typedef int32_t input_data_t;
typedef std::function<void(input_data_t)> InputCallback;

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