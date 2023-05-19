#ifndef _HARDWARE_BUTTON_H_
#define _HARDWARE_BUTTON_H_

#include "Arduino.h"
#include "HardwareInput.h"

class HardwareButton : public HardwareInput {
	public:
		HardwareButton(InputCallback action, pin_size_t pin, PinMode pinMode);
		~HardwareButton();
		void init() override;
		void run() override;

	private:
		pin_size_t _pin;
		PinMode _pinMode;
		PinStatus _lastRead = LOW;
		uint32_t _lastReadMillis = 0;
};

#endif