#ifndef _MENU_CONTROLLER_EXAMPLE_H_
#define _MENU_CONTROLLER_EXAMPLE_H_

#include "settings.h"
#include "System/InputManager.h"
#include "MenuViewExample.h"

/**
 * @brief responds to user input and updates ui and data appropriately
*/
class MenuControllerExample {
    public:
        MenuControllerExample(Adafruit_GFX& display) {
            _menu = new MenuViewExample(display);
        }

        ~MenuControllerExample() { }
        
        void addInputHooks(InputManager& manager) {
            manager.registerAction( ID_SERIAL, [this](int32_t i) { _handleSerialInput(i); }; );
        }

        void init() {
            _inFocus = _menu->getUIElements[0];
            UIEventHandler::instance().addEvent( [_menu]() { _menu->init(); } );
            UIEventHandler::instance().addEvent( [_inFocus]() { _inFocus->focus(); } );
        }

    private:
        MenuViewExample* _menu = nullptr;
        UIElement* _inFocus = nullptr;

        void _handleSerialInput(int32_t i) {
            
            switch (i) {
                case 65:
                    UIEventHandler::instance().addEvent( [_inFocus]() { _inFocus->unfocus(); } );
                    
                    _cur = _cur == 0 ? _interactives.size() - 1 : _cur - 1;
                    cur = _interactives[_cur];
                    UIEventHandler::instance().addEvent([]() { cur->focus(); });
                    break;
                case 66:
                    UIEventHandler::instance().addEvent( [_inFocus]() { _inFocus->unfocus(); } );
                    cur->revert();
                    _cur = (_cur + 1) % _interactives.size();
                    cur = _interactives[_cur];
                    UIEventHandler::instance().addEvent([]() { cur->focus(); });
                    break;
                default:
                    // do nothing
                    break;
            }
        }


};

#endif