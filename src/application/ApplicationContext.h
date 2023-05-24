#ifndef _APPLICATION_CONTEXT_H_
#define _APPLICATION_CONTEXT_H_

#include <stack>

#include "Adafruit_GFX.h"
#include "System/Handleable.h"
#include "System/InputManager.h"

#include "ControllerFactory.h"
#include "ControllerBase.h"
#include "application.h"
#include "app_util.h"

class ControllerBase;
class ControllerFactory;

using namespace application;

// application always starts from main menu
#define APPLICATION_INITIAL_STATE MainMenu

/**
 * @brief maintains state and state transitions of application
 */
class ApplicationContext : public Handleable {
    public:
        ApplicationContext(InputManager& manager, Adafruit_GFX& display, ControllerFactory& factory);
        ~ApplicationContext();

        /**
         * @brief initialize application context
        */
        void begin() override;
        void handle() override { }

        /**
         * @brief trigger state change to new state
         * @param state the state to transition to
         * 
         * @note current state (before transition) will be added to previous states stack
        */
        void changeState(ApplicationState state);

        /**
         * @brief trigger state change to previous state (from previous states stack)
         * @note does nothing if _previousStates is empty
        */        
        void revertState();
    
    private:
        InputManager& _inputManager;
        Adafruit_GFX& _display;
        ControllerFactory& _factory;
        ControllerBase* _controller;
        ApplicationState _currentState = APPLICATION_INITIAL_STATE;
        std::stack<StateData> _previousStates;

        /**
         * @brief changes state to state represented by state param
        */
        void _changeStateInternal(StateData state);
};

#endif