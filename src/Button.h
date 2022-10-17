#include <Arduino.h>
#include <stdint.h>

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