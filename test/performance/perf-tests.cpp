#include "Arduino.h"
#include "SPI.h"

#include "settings.h"
#include "System/DataLogger.h"

#include "ui/UIEventHandler.h"
#include "SDCardTester.h"

/* system resources */
DataLogger logger;

/* global variables */
uint c0_lastUpdateTime = 0;
uint c1_lastUpdateTime = 0;

/* core0 */
void setup() {
	Serial.begin(115200);

	delay(2000);

	// sd card performance testing
	logger.init(SD_CS);
	
	SDCardTester tester = SDCardTester();
	tester.testFilePerformance(logger);
}

void loop() {
	if (millis() > c0_lastUpdateTime + 4000) {
		DEBUG_SERIAL_LN("Core 1 Heartbeat");
		c0_lastUpdateTime = millis();
	}
}

/* core1 */
void setup1() {
	UIEventHandler::instance().init();
}

void loop1() {
	UIEventHandler::instance().run();

	if (millis() > c1_lastUpdateTime + 4000) {
		DEBUG_SERIAL_LN("Core 2 Heartbeat");
		c1_lastUpdateTime = millis();
	}
}