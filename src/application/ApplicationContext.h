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

        /**
         * @brief handle state transitions
        */
        void handle() override;

        /**
         * @brief set next state which this context will transition to
         * @note current state (before transition) will be added to previous states stack
        */
        void setNextState(ApplicationState state);

        /**
         * @brief trigger state change to previous state (from previous states stack)
         * @note does nothing if _previousStates is empty
        */        
        void revertState();

        /**
         * @brief sets changeState bool, indicating that context can safely transition to next state
         * @note this is to prevent race conditions between visual element deletion and rendering when we
         * transition between states
        */
        void setChangeState();
    
    private:
        InputManager& _inputManager;
        Adafruit_GFX& _display;
        ControllerFactory& _factory;
        ControllerBase* _controller;
        ApplicationState _currentState = APPLICATION_INITIAL_STATE;
        StateData _nextState = StateData { .state = NullState, .inFocus = 0 };
        std::stack<StateData> _previousStates;
        mutex_t _stateChangeMutex;
        bool _changeState = false;

        /**
         * @brief changes state to state represented by state param
        */
        void _changeStateInternal(StateData state);
};

#endif