#include "Arduino.h"
#include "SPI.h"
#include "Wire.h"
#include "Adafruit_GFX.h"
#include "Adafruit_ILI9341.h"
#include "XPT2046_Touchscreen.h"
#include "Sensor/SensorOptical.h"

#include "application/ApplicationContext.h"
#include "application/ControllerFactory.h"
#include "graphics/colour.h"
#include "ui/UIEventHandler.h"
#include "System/HardwareInputSerial.h"
#include "System/InputManager.h"
#include "settings.h"

/* system resources */
Adafruit_ILI9341 tft = Adafruit_ILI9341(&SPI, LCD_DC, LCD_CS, LCD_RST);
XPT2046_Touchscreen ts(TOUCH_CS);

/* sensors */
SensorOptical optical(pio0, 0);

/* io */
InputManager inputManager;
HardwareInputSerial inputSerial;

/* ui */
ControllerFactory factory(tft, inputManager);
ApplicationContext context(inputManager, tft, factory);

/* global variables */
uint c0_lastUpdateTime = 0;
uint c1_lastUpdateTime = 0;
int c0_lastCount = 0;

/* Core0 */
void setup() {
	Serial.begin(115200);

	tft.begin();
	tft.setRotation(3);
	tft.fillScreen(COLOUR_BLACK);

	inputManager.registerInput(ID_SERIAL, &inputSerial);

	delay(1000);
	Handleable::beginAll();
}

void loop() {
	Handleable::handleAll();
}

/* Core1 */
void setup1() {
	UIEventHandler::instance().init();
}

void loop1() {
	UIEventHandler::instance().run();

	if (millis() > c1_lastUpdateTime + 2000) {
		DEBUG_SERIAL_LN("Core 2 Heartbeat");
		c1_lastUpdateTime = millis();
	}
}
