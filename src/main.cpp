#include "Arduino.h"
#include "SPI.h"
#include "Wire.h"
#include "Adafruit_ILI9341.h"
#include "XPT2046_Touchscreen.h"
#include "Sensor/SensorOptical.h"

#include "application/ApplicationContext.h"
#include "graphics/colour.h"
#include "ui/UIEventHandler.h"

#include "System/HardwareDemuxer.h"
#include "System/HardwareInputSerial.h"
#include "System/HardwareDemuxButton.h"
#include "System/HardwarePotentiometer.h"
#include "System/HardwareRotaryEncoder.h"
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
HardwareDemuxer demuxer(DEMUX_SELECT0, DEMUX_SELECT1, DEMUX_OUT);
HardwareDemuxButton selectButton(demuxer, DEMUX_SELECT_SELECT, LED_SELECT, true);
HardwareDemuxButton backButton(demuxer, DEMUX_SELECT_BACK, LED_BACK, true);
HardwareDemuxButton brakeButton(demuxer, DEMUX_SELECT_BRAKE, LED_BRAKE, true);
HardwareDemuxButton encoderButton(demuxer, DEMUX_SELECT_ROT_EN_SW, LED_NULL, false);
HardwarePotentiometer pot(POT_IN);
HardwareRotaryEncoder rot(ROT_EN_A, ROT_EN_B);

/* ui */
ApplicationContext context(inputManager, tft, ApplicationContext::MainMenu);

/* global variables */
uint64_t c0_lastUpdateTime = 0;
int c0_lastCount = 0;

/* Core0 */
void setup() {
	Serial.begin(115200);

	tft.begin();
	tft.setRotation(3);
	tft.fillScreen(COLOUR_BLACK);

	inputManager.registerInput(ID_SERIAL, &inputSerial);
	inputManager.registerInput(ID_SELECT_BUTTON, &selectButton);
	inputManager.registerInput(ID_BACK_BUTTON, &backButton);
	inputManager.registerInput(ID_BRAKE_BUTTON, &brakeButton);
	inputManager.registerInput(ID_ROT_EN_SW, &encoderButton);
	inputManager.registerInput(ID_BRAKE_POT, &pot);
	inputManager.registerInput(ID_ROT_EN, &rot);

	// DEMUX TEST
	demuxer.init();

	// initialize all handleable objects
	delay(1000);
	Handleable::beginAll();

	// INPUT TEST
	// inputManager.registerAction(ID_BRAKE_BUTTON, [](input_data_t d) { Serial.printf("Brake button is %s\n", String(d == 0 ? "Low" : "High").c_str()); });
	// inputManager.registerAction(ID_ROT_EN_SW, [](input_data_t d) { Serial.printf("Rotary switch is %s\n", String(d == 0 ? "Low" : "High").c_str()); });
	// inputManager.registerAction(ID_ROT_EN, [](input_data_t d) { Serial.printf("Rotary encoder changed: %s\n", String(d).c_str()); });
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
}
