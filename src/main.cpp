#include "Arduino.h"
#include "SPI.h"
#include "Wire.h"
#include "Adafruit_GFX.h"
#include "Adafruit_ILI9341.h"
#include "XPT2046_Touchscreen.h"
#include "Sensor/SensorOptical.h"

#include "application/MenuViewExample.h"
#include "graphics/colour.h"
#include "ui/UIEventHandler.h"
#include "settings.h"

/* system resources */
Adafruit_ILI9341 tft = Adafruit_ILI9341(&SPI, TFT_DC, TFT_CS, TFT_RST);
XPT2046_Touchscreen ts(TOUCH_CS);

/* sensors */
SensorOptical optical(pio0, 0);

/* ui */
MenuViewExample menu(tft);
UIEventHandler uiCore;

/* global variables */
uint64_t c0_lastUpdateTime = 0;
int c0_lastCount = 0;

/* Core0 */
void setup() {
	Serial.begin(115200);

	tft.begin();
	tft.setRotation(3);
	tft.fillScreen(COLOUR_BLACK);

	delay(1000);
	uiCore.addEvent([]() { menu.init(); });
	Handleable::beginAll();
}

void loop() {
	if (millis() > c0_lastUpdateTime + 100) {
		c0_lastUpdateTime = millis();
		uiCore.addEvent([]() { menu.run(); });
	}

	Handleable::handleAll();
}

/* Core1 */
void setup1() {
	uiCore.init();
}

void loop1() {
	uiCore.run();
}
