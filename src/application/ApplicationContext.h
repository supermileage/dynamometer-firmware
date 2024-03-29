#ifndef _APPLICATION_CONTEXT_H_
#define _APPLICATION_CONTEXT_H_

#include <memory>

#include "TFT_eSPI.h"
#include "System/InputManager.h"
#include "System/system_util.h"

#include "ControllerFactory.h"
#include "ControllerBase.h"
#include "application.h"
#include "app_util.h"

class ControllerBase;
class ControllerFactory;

using namespace application;

// application always starts from main menu
#define APPLICATION_INITIAL_STATE       MainMenu
#define APPLICATION_INITIAL_HEADER      "main menu"
#define MAX_STACK_SIZE                  8

/**
 * @brief maintains state and state transitions of application
 */
class ApplicationContext {
    public:
        ApplicationContext(InputManager& manager, TFT_eSPI& display, ControllerFactory& factory);
        ~ApplicationContext();

        /**
         * @brief initialize application context
        */
        void begin();

        /**
         * @brief handle state transitions
        */
        void handle();

        /**
         * @brief try to set info for next state which this context will transition to
         * @returns bool indicating whether or not state transition has been triggered
         * @note current state info (before transition) will be added to previous states stack
        */
        bool trySetNextState(StateInfo& state);

        /**
         * @brief try updating and transitioning to previous state with current info (eg. return from config menu)
         * @returns bool indicating whether or not state transition has been triggered
         * @note current state info (before transition) will be added to previous states stack
        */
        bool tryUpdateAndReturn(StateInfo& state);

        /**
         * @brief trigger state change to previous state (from previous states stack)
         * @returns true if state change has been triggered, false otherwise
         * 
         * @note does nothing if _previousStates is empty
        */        
        bool tryRevertState();

        /**
         * @brief sets state transition flag, indicating that context can safely transition to next state
         * @note this is to prevent race conditions between visual element deletion and rendering when we
         * transition between states
        */
        void setStateTransitionFlag();
    
    private:
        InputManager& _inputManager;
        TFT_eSPI& _display;
        ControllerFactory& _factory;
        std::shared_ptr<ControllerBase> _controller = nullptr;
        StateInfo _currentStateInfo;
        StateInfo _nextStateInfo = StateInfo { .state = NullState, .inFocus = 0 };
        system_util::FixedStack<StateInfo, MAX_STACK_SIZE> _previousStates;
        mutex_t _stateTransitionMutex;
        bool _stateTransitionFlag = false;

        /**
         * @brief changes state to state represented by state param
        */
        void _changeStateInternal(StateInfo& state);
};

#endif