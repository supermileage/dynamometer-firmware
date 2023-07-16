#include "Arduino.h"
#include "SPI.h"
#include "Wire.h"
#include "TFT_eSPI.h"

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
TFT_eSPI tft = TFT_eSPI();

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

/* ui */
ControllerFactory factory(tft, inputManager);
ApplicationContext context(inputManager, tft, factory);

/* global variables */
uint c0_lastUpdateTime = 0;
uint c1_lastUpdateTime = 0;
int c0_lastCount = 0;

/* example forward declarations */

#define DEG2RAD 0.0174532925

void fillSegment(int x, int y, int start_angle, int sub_angle, int r, unsigned int colour);
unsigned int brightness(unsigned int colour, int brightness);

uint8_t inc = 0;
unsigned int col = 0;

/* end example forward declarations */

/* Core0 */
void setup() {
	Serial.begin(115200);
	SD.begin(SD_CS, SPI1);

	// sensor
	optical.begin();
	force.begin();

	tft.init();
	tft.setRotation(3);
	tft.fillScreen(TFT_BLACK);

	// ui inputs
	demuxer.init();
	inputManager.registerInput(ID_SERIAL, &inputSerial);
	inputManager.registerInput(ID_SELECT_BUTTON, &selectButton);
	inputManager.registerInput(ID_BACK_BUTTON, &backButton);
	inputManager.registerInput(ID_BRAKE_BUTTON, &brakeButton);
	inputManager.registerInput(ID_ROT_EN_SW, &encoderButton);
	inputManager.registerInput(ID_BRAKE_POT, &pot);
	inputManager.registerInput(ID_ROT_EN, &rot);
	inputManager.begin();

	// application
	ErrorUtil.init(ErrorLogger::LogAndPrint);
	context.begin();
}

uint32_t g_lastUpdate = 0;

void loop() {
	inputManager.handle();
	context.handle();

	// // Draw 4 pie chart segments
	// fillSegment(160, 120, 0, 60, 100, TFT_RED);
	// fillSegment(160, 120, 60, 30, 100, TFT_GREEN);
	// fillSegment(160, 120, 60 + 30, 120, 100, TFT_BLUE);
	// fillSegment(160, 120, 60 + 30 + 120, 150, 100, TFT_YELLOW);

	// delay(4000);

	// // Erase old chart with 360 degree black plot
	// fillSegment(160, 120, 0, 360, 100, TFT_BLACK);

	if (millis() > g_lastUpdate + 2000) {
    	Serial.println("Core1 Heartbeat");
    	g_lastUpdate = millis();
  	}
}

/* Core1 */
void setup1() {
	// screen
	UIEventHandler::instance().init();
}

void loop1() {
	UIEventHandler::instance().run();

	if (millis() > c1_lastUpdateTime + 2000) {
		DEBUG_SERIAL_LN("Core 2 Heartbeat");
		c1_lastUpdateTime = millis();
	}
}


// TEST CODE

// #########################################################################
// Draw circle segments
// #########################################################################

// x,y == coords of centre of circle
// start_angle = 0 - 359
// sub_angle   = 0 - 360 = subtended angle
// r = radius
// colour = 16 bit colour value

void fillSegment(int x, int y, int start_angle, int sub_angle, int r, unsigned int colour)
{
  // Calculate first pair of coordinates for segment start
  float sx = cos((start_angle - 90) * DEG2RAD);
  float sy = sin((start_angle - 90) * DEG2RAD);
  uint16_t x1 = sx * r + x;
  uint16_t y1 = sy * r + y;

  // Draw colour blocks every inc degrees
  for (int i = start_angle; i < start_angle + sub_angle; i++) {

    // Calculate pair of coordinates for segment end
    int x2 = cos((i + 1 - 90) * DEG2RAD) * r + x;
    int y2 = sin((i + 1 - 90) * DEG2RAD) * r + y;

    tft.fillTriangle(x1, y1, x2, y2, x, y, colour);

    // Copy segment end to sgement start for next segment
    x1 = x2;
    y1 = y2;
  }
}

// #########################################################################
// Return the 16 bit colour with brightness 0-100%
// #########################################################################
unsigned int brightness(unsigned int colour, int brightness)
{
  uint8_t red   = colour >> 11;
  uint8_t green = (colour & 0x7E0) >> 5;
  uint8_t blue  = colour & 0x1F;

  blue =  (blue * brightness)/100;
  green = (green * brightness)/100;
  red =   (red * brightness)/100;

  return (red << 11) + (green << 5) + blue;
}

