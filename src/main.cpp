#include "settings.h"

#include "System/Handleable.h"
#include "Sensor/SensorForce.h"
#include "Sensor/SensorRpm.h"

/* Forward declarations */
// void toggleBrakeModule();

/* Timing */
#define ARR_SIZE 150
uint64_t g_loopArr[ARR_SIZE] = { };
uint8_t g_loopIndex = 0;
uint64_t g_lastPrintTime = 0;
uint64_t g_lastLoopTime = 0;
bool g_reset = false;

/* Objects */
SensorForce sensorforce(FORCE_SENSOR, OUTPUT);
SensorRpm sensorRpm(OPTICAL_SENSOR, INPUT);

void setup() {
	Serial.begin(9600);
}

unsigned long _lastReadTime = 0;

void loop() {
	sensorforce.handle();
	sensorRpm.handle();
	if(millis() > _lastReadTime + 1000) {
        _lastReadTime = millis();
        DEBUG_SERIAL_LN(String(sensorRpm.getRpm()));
	}	
}

/* Button Callback */
// void toggleBrakeModule() {
// 	g_runBrakeModule = !g_runBrakeModule;

// 	if (g_runBrakeModule) {
// 		digitalWrite(LED_BUILTIN, HIGH);
// 	}
// 	else {
// 		digitalWrite(BRAKE_CONTROL_PIN, HIGH);
// 		digitalWrite(LED_BUILTIN, LOW);
// 	}
// 	Serial.println(String("Turning brake module ") + String((g_runBrakeModule ? "On" : "Off")));
// }