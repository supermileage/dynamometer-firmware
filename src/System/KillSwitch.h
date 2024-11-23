#ifndef _HARDWARE_KILLSWITCH_H_
#define _HARDWARE_KILLSWITCH_H_

#include "HardwareInput.h"
#include "BpmControl.h"

class KillSwitch: public HardwareInput {
    public:
        KillSwitch(BpmControl& bpmControl, pin_size_t killSwitchPin) : _bpmControl(bpmControl), _killSwitchPin(killSwitchPin){}
        ~KillSwitch(){}

		void init() override
    {
      pinMode(_killSwitchPin, INPUT_PULLUP);
    };

		void run() override
    {
      if (!digitalRead(_killSwitchPin) && _bpmControl.getStatus()) 
        _hasFault = true;
      else
        _hasFault = false;
    };

    bool getFaultStatus()
    {
      return _hasFault;
    }

    private:
		  pin_size_t _killSwitchPin;
      BpmControl& _bpmControl;
      bool _hasFault = false;
};

#endif
