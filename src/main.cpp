#include <stdint.h>
#include "settings.h"
#include "System/Button.h"
#include "Sensor/SensorForce.h"
#include "Sensor/SensorRpm.h"

/* Forward declarations */
void toggleBrakeModule();

/* Global variables */
bool g_runBrakeModule = false;

/* Objects */
Button button(BUTTON_PIN, INPUT_PULLUP, toggleBrakeModule);
SensorForce sensorforce(FORCE_SENSOR, OUTPUT);
SensorRpm sensorRpm(OPTICAL_SENSOR, INPUT);

void setup() {
	Serial.begin(9600);
	pinMode(BRAKE_CONTROL_PIN, OUTPUT);
	pinMode(LED_BUILTIN, OUTPUT);

	button.init();
}

unsigned long _lastReadTime = 0;

void loop() {
	button.run();
	sensorforce.handle();
	sensorRpm.handle();
	if(millis() > _lastReadTime + 1000) {
        _lastReadTime = millis();
        DEBUG_SERIAL_LN(String(sensorRpm.getRpm()));
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