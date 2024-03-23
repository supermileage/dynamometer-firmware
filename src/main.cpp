#include "Arduino.h"
#include "SPI.h"
#include "Wire.h"
#include "TFT_eSPI.h"
#include "XPT2046_Touchscreen.h"

#include "Sensor/SensorOptical.h"
#include "Sensor/SensorForce.h"

#include "application/ApplicationContext.h"
#include "application/ControllerFactory.h"
#include "graphics/colour.h"
#include "ui/UIEventHandler.h"

#include "System/HardwareDemuxer.h"
#include "System/HardwareInputSerial.h"
#include "System/HardwareDemuxButton.h"
#include "System/HardwarePotentiometer.h"
#include "System/HardwareRotaryEncoder.h"
#include "System/InputManager.h"
#include "System/ErrorLogger.h"

#include "settings.h"

/* system resources */
TFT_eSPI tft;

/* sensors */
SensorOptical optical(pio0, 0);
SensorForce force;

/* io */
InputManager inputManager;
HardwareInputSerial inputSerial;
HardwareDemuxer demuxer(DEMUX_SELECT0, DEMUX_SELECT1, DEMUX_OUT);
HardwareDemuxButton selectButton(demuxer, DEMUX_SELECT_SELECT, LED_SELECT, false);
HardwareDemuxButton backButton(demuxer, DEMUX_SELECT_BACK, LED_BACK, false);
HardwareDemuxButton brakeButton(demuxer, DEMUX_SELECT_BRAKE, LED_BRAKE, false);
HardwareDemuxButton encoderButton(demuxer, DEMUX_SELECT_ROT_EN_SW, LED_NULL, true);
HardwarePotentiometer pot(POT_IN);
HardwareRotaryEncoder rot(ROT_EN_A, ROT_EN_B);
KillSwitch killswitch(BPM_KILLSWITCH);

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
	SD.begin(SD_CS, SPI1);

	// sensor
	optical.begin();
	force.begin();

	// screen
	tft.begin();
	tft.setRotation(3);
	tft.fillScreen(COLOUR_BLACK);

	// ui inputs
	demuxer.init();
	inputManager.registerInput(ID_SERIAL, &inputSerial);
	inputManager.registerInput(ID_SELECT_BUTTON, &selectButton);
	inputManager.registerInput(ID_BACK_BUTTON, &backButton);
	inputManager.registerInput(ID_BRAKE_BUTTON, &brakeButton);
	inputManager.registerInput(ID_ROT_EN_SW, &encoderButton);
	inputManager.registerInput(ID_BRAKE_POT, &pot);
	inputManager.registerInput(ID_ROT_EN, &rot);
	inputManager.registerInput(ID_KILLSWITCH, &rot);
	inputManager.begin();

	// application
	ErrorUtil.init(ErrorLogger::LogAndPrint);
	context.begin();
}

void loop() {
	
	inputManager.handle();
	context.handle();
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
