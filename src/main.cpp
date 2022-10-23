#include <stdint.h>
#include "settings.h"
#include "System/Button.h"

/* Forward declarations */
void toggleBrakeModule();

/* Global variables */
bool g_runBrakeModule = false;
int64_t g_lastBrakeWrite = 0;
uint64_t g_lastPrintTime = 0;

Button button(BUTTON_PIN, INPUT_PULLUP, toggleBrakeModule);

void setup() {
	Serial.begin(9600);
	pinMode(BRAKE_CONTROL_PIN, OUTPUT);
	pinMode(LED_BUILTIN, OUTPUT);

	pinMode(6, OUTPUT);
	pinMode(A7, INPUT);
	button.init();
}

void loop() {
	button.run();

	if (g_runBrakeModule) {
		int64_t brakeVal = map(analogRead(POT_PIN), 0, 1023, 0, 255);

		if (brakeVal != g_lastBrakeWrite) {
			analogWrite(BRAKE_CONTROL_PIN, 255 - brakeVal);
			g_lastBrakeWrite = brakeVal;
		}
	}
}

/* Button Callback */
void toggleBrakeModule() {
	g_runBrakeModule = !g_runBrakeModule;

	if (g_runBrakeModule) {
		digitalWrite(LED_BUILTIN, HIGH);
	}
	else {
		digitalWrite(BRAKE_CONTROL_PIN, HIGH);
		digitalWrite(LED_BUILTIN, LOW);
	}

	Serial.println(String("Turning brake module ") + String((g_runBrakeModule ? "On" : "Off")));
}