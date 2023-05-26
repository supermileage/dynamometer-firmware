#ifndef _CONTROLLER_BASE_H_
#define _CONTROLLER_BASE_H_

#include <stdint.h>
#include <functional>
#include <map>

#include "Adafruit_GFX.h"
#include "System/InputManager.h"
#include "System/HardwareInput.h"
#include "ui/UIElement.h"
#include "ApplicationContext.h"
#include "application.h"

class ApplicationContext;

using namespace application;

/**
 * @brief provides means of hooking up inputs to ui views: all menu and ui-behavior classes will implement this class
 * @note input handlers do nothing by default: this means that derived classes only have to implement methods for the inputs
 * which they actually use
*/
class ControllerBase {
    public:
        ControllerBase(ApplicationContext& context, Adafruit_GFX& display, uint8_t inFocus = 0);
        virtual ~ControllerBase();

        /**
         * @brief register all input handlers with input manager
         * @note must be called in derived classes to hook up all input handler methods
        */
        virtual void init(InputManager& manager);

        /**
         * @brief returns index of current ui element in focus
        */
		uint8_t getInFocus();

    protected:
        ApplicationContext& _context;
        Adafruit_GFX& _display;
        std::map<uint8_t, std::pair<UIElement*, std::function<void()>>> _buttonCallbackMap;
        uint8_t _inFocus = 0;

        /* hardware input handlers (assigned as InputCallback in init) */

        virtual void _handleInputSerial(input_data_t d);
        virtual void _handleInputEncoder(input_data_t d);
        virtual void _handleInputEncoderSelect(input_data_t d);
        virtual void _handleInputBack(input_data_t d);
        virtual void _handleInputSelect(input_data_t d);
        virtual void _handleInputBrakeButton(input_data_t d);
        virtual void _handleInputBrakePot(input_data_t d);
};

#endif