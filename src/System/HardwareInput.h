#ifndef _HARDWARE_INPUT_H_
#define _HARDWARE_INPUT_H_

#include <stdint.h>
#include <functional>
#include "settings.h"

typedef int32_t input_data_t;
typedef std::function<void(input_data_t)> InputCallback;

/**
 * @brief base class for all hardware ui inputs
*/
class HardwareInput {
    public:
        virtual ~HardwareInput() { }

        /**
         * @brief virtual init method implemented in derived classes: called once in setup
        */
        virtual void init() = 0;

        /**
         * @brief virtual run method implemented in derived classes: called every control loop
        */
        virtual void run() = 0;

        /**
         * @brief get current value of input
         * @note returns 0 by default, but should be implemented in Input classes whose initial
         * state is important for control or graphics (ie. buttons and potentiometer)
        */
        virtual input_data_t read() {
            return 0;
        }

        /**
         * @brief sets the callback action for this input
         * 
         * @note callback only called when input state changes
        */
        virtual void setAction(InputCallback action) { _action = action; }

    protected:
        InputCallback _action = [](int32_t) { /* default action does nothing */ };
};

#endif