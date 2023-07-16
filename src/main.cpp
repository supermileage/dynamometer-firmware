#include "Arduino.h"
#include "SPI.h"
#include "Wire.h"
#include "TFT_eSPI.h"
#include "graphics/fonts.h"

#include "Sensor/SensorOptical.h"
#include "Sensor/SensorForce.h"

#include "application/ApplicationContext.h"
#include "application/ControllerFactory.h"
#include "graphics/colour.h"
#include "ui/UIEventHandler.h"
#include "ui/ValueElement.h"

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

ValueElement value(tft);
ValueElement value1(tft);
ValueElement value2(tft);
ValueElement value3(tft);
ValueElement value4(tft);
ValueElement value5(tft);

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
	// context.begin();

	String label = "cur: ";
	String val = "00:000";
	String units = "A";

	// sandbox
	value.configureLabel(label, FREE_SERIF_9PT7B, COLOUR_WHITE)
		.configureValue(val, FREE_SERIF_BOLD_12PT7B, COLOUR_WHITE)
		.configureUnits(units, FREE_SERIF_9PT7B, COLOUR_WHITE)
		.setOrientation(Container::Row)
		.setPadding(4)
		.setPosition(ui_util::Point { .x = 0, .y = 40 })
		.setBackgroundColour(COLOUR_BLACK)
		.addBorder(COLOUR_LIGHTGREY);
	value1.configureLabel(label, FREE_SERIF_9PT7B, COLOUR_WHITE)
		.configureValue(val, FREE_SERIF_BOLD_12PT7B, COLOUR_WHITE)
		.configureUnits(units, FREE_SERIF_9PT7B, COLOUR_WHITE)
		.setOrientation(Container::Row)
		.setPadding(4)
		.setPosition(ui_util::Point { .x = 0, .y = 100 })
		.setBackgroundColour(COLOUR_BLACK)
		.addBorder(COLOUR_LIGHTGREY);
	value2.configureLabel(label, FREE_SERIF_9PT7B, COLOUR_WHITE)
		.configureValue(val, FREE_SERIF_BOLD_12PT7B, COLOUR_WHITE)
		.configureUnits(units, FREE_SERIF_9PT7B, COLOUR_WHITE)
		.setOrientation(Container::Row)
		.setPadding(4)
		.setPosition(ui_util::Point { .x = 160, .y = 160 })
		.setBackgroundColour(COLOUR_BLACK)
		.addBorder(COLOUR_LIGHTGREY);
	value3.configureLabel(label, FREE_SERIF_9PT7B, COLOUR_WHITE)
		.configureValue(val, FREE_SERIF_BOLD_12PT7B, COLOUR_WHITE)
		.configureUnits(units, FREE_SERIF_9PT7B, COLOUR_WHITE)
		.setOrientation(Container::Row)
		.setPadding(4)
		.setPosition(ui_util::Point { .x = 160, .y = 40 })
		.setBackgroundColour(COLOUR_BLACK)
		.addBorder(COLOUR_LIGHTGREY);
	value4.configureLabel(label, FREE_SERIF_9PT7B, COLOUR_WHITE)
		.configureValue(val, FREE_SERIF_BOLD_12PT7B, COLOUR_WHITE)
		.configureUnits(units, FREE_SERIF_9PT7B, COLOUR_WHITE)
		.setOrientation(Container::Row)
		.setPadding(4)
		.setPosition(ui_util::Point { .x = 160, .y = 100 })
		.setBackgroundColour(COLOUR_BLACK)
		.addBorder(COLOUR_LIGHTGREY);
	value5.configureLabel(label, FREE_SERIF_9PT7B, COLOUR_WHITE)
		.configureValue(val, FREE_SERIF_BOLD_12PT7B, COLOUR_WHITE)
		.configureUnits(units, FREE_SERIF_9PT7B, COLOUR_WHITE)
		.setOrientation(Container::Row)
		.setPadding(4)
		.setPosition(ui_util::Point { .x = 0, .y = 160 })
		.setBackgroundColour(COLOUR_BLACK)
		.addBorder(COLOUR_LIGHTGREY);

	UIEventHandler::instance().addEvent([]() {
		value.align();
		value1.align();
		value2.align();
		value3.align();
		value4.align();
		value5.align();
		value.draw();
		value1.draw();
		value2.draw();
		value3.draw();
		value4.draw();
		value5.draw();
	});
}

uint32_t g_lastUpdate = 0;
uint32_t g_lastThing = 0;

uint32_t g_before = 0;
uint32_t g_after = 0;
uint32_t g_sum = 0;
uint32_t g_count = 0;

void loop() {
	inputManager.handle();
	// context.handle();

	if (millis() >= g_lastThing + 29) {
		g_lastThing = millis();
		UIEventHandler::instance().addEvent( []() {
			g_before = micros();

			char buf[6] = { };
			uint32_t seconds = g_lastThing * 3;
			sprintf(buf, "%02lu:%03lu", seconds / 1000 % 100, seconds % 1000);
			String str = String(buf);
			value.updateValue(str);
			value1.updateValue(str);
			value2.updateValue(str);
			value3.updateValue(str);
			value4.updateValue(str);
			value5.updateValue(str);

			g_after = micros();
			g_sum += (g_after - g_before);
			++g_count;
		});
	}

	if (millis() > g_lastUpdate + 2000) {
    	DEBUG_SERIAL_LN("Core1 Heartbeat");
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
		Serial.println(String("average time per write: ") + String(g_sum / g_count) + String("us"));
		g_count = 0;
		g_sum = 0;
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

