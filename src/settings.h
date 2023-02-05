#ifndef SETTINGS_H_
#define SETTINGS_H_

#define GPIO_ADC0 26
#define GPIO_ADC1 27
#define GPIO_ADC2 28

/* IO */
#define BRAKE_CONTROL_PIN 6
#define BUTTON_PIN 2
#define POT_PIN GPIO_ADC0
#define FORCE_SENSOR GPIO_ADC1
#define OPTICAL_SENSOR 3

/* Debugging */
#define DEBUG_SERIAL_EN 1

#if DEBUG_SERIAL_EN
#define DEBUG_SERIAL_LN(x) Serial.println(x)
#else
#define DEBUG_SERIAL_LN(x) { }
#endif

#endif