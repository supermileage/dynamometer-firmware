#ifndef _HARDWARE_KILLSWITCH_H_
#define _HARDWARE_KILLSWITCH_H_

#include "HardwareInput.h"
#include "BpmControl.h"

class KillSwitch: public HardwareInput {
    public:
        KillSwitch(BpmControl& bpmControl, pin_size_t killSwitchPin, bool _sessionActive) : _bpmControl(bpmControl), _killSwitchPin(killSwitchPin), _sessionActive(sessionActive){}
        ~KillSwitch(){}

		void init() override
    {
      pinMode(_killSwitchPin, INPUT_PULLUP);
    };

		void run() override
    {
      if (!digitalRead(_killSwitchPin) && _sessionActive) {
        _bpmControl.setControlSignal(ANALOG_MAX);
      }
    };

    private:
		  pin_size_t _killSwitchPin;
      BpmControl& _bpmControl;
      bool _sessionActive;
};

#endif
