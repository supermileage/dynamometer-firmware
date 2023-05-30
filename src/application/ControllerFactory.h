#ifndef _CONTROLLER_FACTORY_H_
#define _CONTROLLER_FACTORY_H_

#include <memory>

#include "System/InputManager.h"
#include "Adafruit_GFX.h"
#include "ApplicationContext.h"
#include "ControllerBase.h"
#include "application.h"

class ApplicationContext;
class ControllerBase;

using namespace application;

/**
 * @brief controller factory class which handles construction of controller objects
 * @note added to resolve circular dependencies between ApplicationContext, ControllerBase and derived classes
*/
class ControllerFactory {
    public:
        ControllerFactory(Adafruit_GFX& display, InputManager& manager);

        /**
         * @brief create new controller base class for state info
         * @return pointer to new ControllerBase
         * @note delete must be called on returned object when it is disposed of
        */
        std::shared_ptr<ControllerBase> create(StateInfo& state);
        void setContext(ApplicationContext* context);

    private:
        Adafruit_GFX& _display;
        InputManager& _inputManager;
        ApplicationContext* _context;

        /**
         * @brief constructs new controller class for state info
         * @return pointer to new ControllerBase
         * @note delete must be called on returned object when it is disposed of
        */
        std::shared_ptr<ControllerBase> _createInternal(StateInfo& data);
};

#endif