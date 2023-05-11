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
        MenuControllerExample(ApplicationContext& context, Adafruit_GFX& display);
        ~MenuControllerExample();
        void init(InputManager& manager);

    private:
        ApplicationContext& _context;
        MenuViewExample* _menu;
        std::map<uint8_t, std::pair<UIElement*, std::function<void()>>> _buttonCallbackMap;
        UIButton* _menuButtonCalibrate;
        UIButton* _menuButtonCtrl;
        UIButton* _menuButtonSettings;
        uint8_t _inFocus = 0;

        void _handleInputSerial(int32_t arg);
        void _handleInputSelect(int32_t arg);
        void _handleInputBack(int32_t arg);
        void _handleInputBrakeButton(int32_t arg);
        void _handleInputBrakePot(int32_t arg);
};

#endif