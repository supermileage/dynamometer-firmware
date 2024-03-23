#ifndef _HARDWARE_KILLSWITCH_H_
#define _HARDWARE_KILLSWITCH_H_

#include <stdint.h>

/**
 * @brief reads input from a button connected through the demux
*/
class KillSwitch : public HardwareInput {
    public:
        KillSwitch(pin_size_t ledPin);
        ~KillSwitch();
		void init() override;
		void run() override;

    private:
		pin_size_t _killSwitchPin;
        uint8_t state; 
};

#endif