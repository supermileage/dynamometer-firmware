#ifndef _APPLICATION_CONTEXT_H_
#define _APPLICATION_CONTEXT_H_

#include <stack>

#include "Adafruit_GFX.h"
#include "System/Handleable.h"
#include "System/InputManager.h"
#include "application/MenuControllerExample.h"

class MenuControllerExample;

/**
 * @brief maintains state and state transitions of application
 */
class ApplicationContext : public Handleable {
    public:
		// represents different application states
		// ok to modify if states are added / removed
        enum ApplicationState { MainMenu, ManualControlMenu, CalibrationMenu, SettingsMenu };

		struct StateData {
			ApplicationState state;
			uint8_t inFocus;
		};

        ApplicationContext(InputManager& manager, Adafruit_GFX& display, ApplicationState state = MainMenu);

        ~ApplicationContext() { }
        void begin() override;
        void handle() override { }
        void changeState(ApplicationState state);
        void navigateBack();
    
    private:
        MenuControllerExample* _controller;
        InputManager& _inputManager;
        Adafruit_GFX& _display;
        ApplicationState _currentState;
        std::stack<StateData> _previousStates;

        void _changeStateInternal(StateData state);
        static const String stateToString(ApplicationState state);
};

#endif