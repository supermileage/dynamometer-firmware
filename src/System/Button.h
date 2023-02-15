#ifndef BUTTON_H_
#define BUTTON_H_

#include "settings.h"

class Button {
	public:
		Button(int32_t pin, PinMode pinMode, void (*action)(void));
		~Button();
		void init();
		void run();

	private:
		int32_t _pin;
		PinMode _pinMode;
		void (*_action)(void) = NULL;
		uint64_t _lastReadHigh = 0;
};

#endif