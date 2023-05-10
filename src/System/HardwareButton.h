#ifndef _HARDWARE_BUTTON_H_
#define _HARDWARE_BUTTON_H_

#include <Arduino.h>
#include <stdint.h>

class HardwareButton {
	public:
		HardwareButton(int32_t pin, PinMode pinMode, void (*action)(void));
		~HardwareButton();
		void init();
		void run();

	private:
		int32_t _pin;
		PinMode _pinMode;
		void (*_action)(void) = NULL;
		uint64_t _lastReadHigh = 0;
};

#endif