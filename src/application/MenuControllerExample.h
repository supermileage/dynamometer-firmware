#ifndef _MENU_CONTROLLER_EXAMPLE_H_
#define _MENU_CONTROLLER_EXAMPLE_H_

#include <map>

#include "settings.h"
#include "MenuViewExample.h"
#include "ApplicationContext.h"
#include "System/InputManager.h"
#include "ui/UIEventHandler.h"
#include "ui/UIButton.h"

class ApplicationContext;

/**
 * @brief manages control layer between data and gui
*/
class MenuControllerExample {
    public:
        MenuControllerExample(ApplicationContext& context, Adafruit_GFX& display, uint8_t inFocus = 0);
        ~MenuControllerExample();
        void init(InputManager& manager);
		uint8_t getInFocus();

    private:
        ApplicationContext& _context;
        MenuViewExample* _menu;
        std::map<uint8_t, std::pair<UIElement*, std::function<void()>>> _buttonCallbackMap;
        UIButton* _menuButtonCalibrate;
        UIButton* _menuButtonCtrl;
        UIButton* _menuButtonSettings;
        uint8_t _inFocus = 0;

        void _handleInputSerial(input_data_t arg);
        void _handleInputSelect(input_data_t arg);
        void _handleInputBack(input_data_t arg);
        void _handleInputBrakeButton(input_data_t arg);
        void _handleInputBrakePot(input_data_t arg);
        void _handleInputRotaryEncoder(input_data_t arg);
        void _handleInputRotarySwitch(input_data_t arg);
};

#endif