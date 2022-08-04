#include <stdint.h>

#include "Arduino.h"
#include "settings.h"

#define DEBOUNCE_TIME 250
#define BRAKE_MODULE_PIN 2
#define BUTTON_PIN PIN_A0

/* Helper Classes */
class Button {
	public:
		Button(int32_t pin, PinMode pinMode, void (*action)(void)) : _pin(pin), _pinMode(pinMode), _action(action) {  }
		~Button() { }
		void init() {
			pinMode(_pin, _pinMode);
		}
		void run() {
			PinStatus read = digitalRead(_pin);
			uint64_t currentTime = millis();

			if (currentTime > _lastReadHigh + DEBOUNCE_TIME && read == LOW) {
				(_action)();
				_lastReadHigh = currentTime;
			}
		}

	private:
		int32_t _pin;
		PinMode _pinMode;
		void (*_action)(void) = NULL;
		uint64_t _lastReadHigh = 0;

};

/* Forward declarations */
void toggleBrakeModule();

/* Arduino Code */
Button button(BUTTON_PIN, INPUT_PULLUP, toggleBrakeModule);

void setup() {
	// pinMode(LED_BUILTIN, OUTPUT);
	Serial.begin(9600);
	pinMode(BRAKE_MODULE_PIN, OUTPUT);
	pinMode(LED_BUILTIN, OUTPUT);
	button.init();
}

void loop() {
	button.run();
}

/* Helper Functions */
bool g_moduleOn = false;

void toggleBrakeModule() {
	g_moduleOn = !g_moduleOn;

	if (g_moduleOn) {
		digitalWrite(BRAKE_MODULE_PIN, HIGH);
		digitalWrite(LED_BUILTIN, HIGH);
	}
	else {
		digitalWrite(BRAKE_MODULE_PIN, LOW);
		digitalWrite(LED_BUILTIN, LOW);
	}

	Serial.println(String("Turning brake module ") + String((g_moduleOn ? "On" : "Off")));
}