#ifndef SETTINGS_H_
#define SETTINGS_H_

/* Display */
#define TFT_DC 15
#define TFT_CS 17
#define TFT_RST 14
#define TOUCH_CS 13

/* IO */
#define GPIO_ADC0 26
#define GPIO_ADC1 27
#define GPIO_ADC2 28

#define BRAKE_CONTROL_PIN 6
#define BUTTON_PIN 1
#define POT_PIN GPIO_ADC0
#define FORCE_SENSOR GPIO_ADC1
#define OPTICAL_SENSOR_PIN 2

/* Debugging */
#define DEBUG_SERIAL_EN 1

#if DEBUG_SERIAL_EN
#define DEBUG_SERIAL_LN(x) Serial.println(x)
#else
#define DEBUG_SERIAL_LN(x) { }
#endif

#endif