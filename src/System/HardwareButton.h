#ifndef _HARDWARE_BUTTON_H_
#define _HARDWARE_BUTTON_H_

#include "Arduino.h"
#include "HardwareInput.h"

/**
 * @brief class which represents hardware button ui input to system
*/
class HardwareButton : public HardwareInput {
	public:
		/**
		 * @brief constructs HardwareButton instance with pin and pinMode
		*/
		HardwareButton(pin_size_t pin, PinMode pinMode);

		/**
		 * @brief initialize pin
		*/
		void init() override;

		/**
		 * @brief read button pin and invoke callback if pin status has changed
		*/
		void run() override;

	private:
		pin_size_t _pin;
		PinMode _pinMode;
		PinStatus _lastRead = LOW;
		uint32_t _lastReadMillis = 0;
};

#endif