#ifndef _HARDWARE_KILLSWITCH_H_
#define _HARDWARE_KILLSWITCH_H_

#include "HardwareInput.h"
#include "BpmControl.h"

/**
 * @brief reads input from a button connected through the demux
*/
class KillSwitch: public HardwareInput {
    public:
        KillSwitch(pin_size_t killSwitchPin, BpmControl& bpmControl);
        ~KillSwitch();
		void init() override
    {
      pinMode(_killSwitchPin, INPUT);
    };
		void run() override
    {
      if (!digitalRead(_killSwitchPin) && ) {
        _bpmControl.setControlSignal(ANALOG_MAX);
      }
    };

    private:
		  pin_size_t _killSwitchPin;
      BpmControl& _bpmControl;
};

#endif
