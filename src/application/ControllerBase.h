#ifndef _CONTROLLER_BASE_H_
#define _CONTROLLER_BASE_H_

#include <stdint.h>
#include <functional>
#include <map>
#include <memory>

#include "TFT_eSPI.h"
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
class ControllerBase : public std::enable_shared_from_this<ControllerBase> {
    public:
        ControllerBase(ApplicationContext& context, TFT_eSPI& display);
        virtual ~ControllerBase();

        /**
         * @brief register all input handlers with input manager
         * @note must be called in derived classes to hook up all input handler methods
        */
        virtual void init(InputManager& manager);

        /**
         * @brief run controller
        */
        virtual void handle();

        /**
         * @brief returns index of current ui element in focus
        */
		uint8_t getInFocus();

        /**
         * @brief returns current state info object
        */
       StateInfo getStateInfo();

    protected:
        ApplicationContext& _context;
        TFT_eSPI& _display;
        StateInfo _info;
        uint8_t _inFocus = 0;

        /* hardware input handlers (assigned as InputCallback in init) */

        virtual void _handleInputSerial(input_data_t d);
        virtual void _handleInputEncoder(input_data_t d);
        virtual void _handleInputEncoderSelect(input_data_t d);
        virtual void _handleInputBack(input_data_t d);
        virtual void _handleInputSelect(input_data_t d);
        virtual void _handleInputBrakeButton(input_data_t d);
        virtual void _handleInputBrakePot(input_data_t d);

        inline int32_t _computeIndexOffset(int32_t index, int32_t offset, int32_t modVal) {
            return ((index + offset) % modVal + modVal) % modVal;
        }
};

#endif