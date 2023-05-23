#ifndef _MENU_CONTROLLER_EXAMPLE_H_
#define _MENU_CONTROLLER_EXAMPLE_H_

#include <map>

#include "settings.h"
#include "MenuViewExample.h"
#include "ApplicationContext.h"
#include "ControllerBase.h"
#include "System/InputManager.h"
#include "ui/UIEventHandler.h"
#include "ui/UIButton.h"

class ApplicationContext;

/**
 * @brief manages control layer between data and gui
*/
class MenuControllerExample : public ControllerBase {
    public:
        MenuControllerExample(ApplicationContext& context, Adafruit_GFX& display, uint8_t inFocus = 0);
        ~MenuControllerExample();
        void init(InputManager& manager);
		uint8_t getInFocus();

    private:
        ApplicationContext& _context;
        MenuViewExample* _menu;
        UIButton* _menuButtonCalibrate;
        UIButton* _menuButtonCtrl;
        UIButton* _menuButtonSettings;

        // ControllerBase already provides default input handler implementations, so you only
        // need to override the inputs you want to use

        void _handleInputSerial(input_data_t d) override;
};

#endif