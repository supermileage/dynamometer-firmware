#ifndef _SETTINGS_H_
#define _SETTINGS_H_

#include "Arduino.h"

/* Debug Settings */
#define DEBUG_SERIAL_EN     0
#define DYNO_ASSERT_EN      1
#define ERROR_LOGFILE_PATH  "error/logfile.txt"

#if DEBUG_SERIAL_EN
#define DEBUG_SERIAL_LN(x) Serial.println(x)
#define DEBUG_SERIAL_F(x, ...) Serial.printf(x, __VA_ARGS__)
#define DEBUG_SERIAL(x) Serial.print(x)
#else
#define DEBUG_SERIAL_LN(x) { }
#define DEBUG_SERIAL_F(x, ...) { }
#define DEBUG_SERIAL(x) { }
#endif

/* IO Settings */

/* General */

/* Screen */
#define LCD_MOSI    12
#define LCD_SCLK    13
#define LCD_RST     6
#define LCD_DC      7
#define LCD_CS      5
#define TOUCH_CS    14
#define SD_CS       8

/* Sensor */
#define OPTICAL_SENSOR_PIN  4
#define FORCE_SENSOR_PIN    28

/* Demux (Buttons) */
#define BUTTON_DEBOUNCE_MILLIS      50
#define DEMUX_SELECT0               8
#define DEMUX_SELECT1               9
#define DEMUX_OUT                   10
#define DEMUX_SELECT_SELECT         0x0
#define DEMUX_SELECT_BACK           0x1
#define DEMUX_SELECT_BRAKE          0x2
#define DEMUX_SELECT_ROT_EN_SW      0x3

/* Led */
#define LED_BACK    22
#define LED_SELECT  21
#define LED_BRAKE   27

/* Knobs */
#define POT_IN      26  // ADC0
#define ROT_EN_A    19
#define ROT_EN_B    20

// Input IDs
#define ID_SERIAL           0
#define ID_ROT_EN           1
#define ID_ROT_EN_SW        2
#define ID_BACK_BUTTON      3
#define ID_SELECT_BUTTON    4
#define ID_BRAKE_BUTTON     5
#define ID_BRAKE_POT        6

/* SD Card */
#define SD_CS       8

#endif