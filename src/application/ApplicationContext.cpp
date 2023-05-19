#include "ApplicationContext.h"


ApplicationContext::ApplicationContext(InputManager& manager, Adafruit_GFX& display, ApplicationState state) :
    _inputManager(manager), _display(display), _currentState(MainMenu) {
    _controller = new MenuControllerExample(*this, _display);
}

void ApplicationContext::begin() {
    _controller->init(_inputManager);
}

void ApplicationContext::changeState(ApplicationState state) {
	// push current state to _previousStates
	StateData data;
	data.state = _currentState;
	data.inFocus = _controller->getInFocus();
    _previousStates.push(data);
    
    // transition to new state
	data.state = state;
	data.inFocus = 0;
    _changeStateInternal(data);
}

void ApplicationContext::navigateBack() {
    if (_previousStates.empty()) {
        // error !
    } else {
        StateData state = _previousStates.top();
        _previousStates.pop();
        _changeStateInternal(state);
    }
}

void ApplicationContext::_changeStateInternal(StateData data) {
    _currentState = data.state;
    
    DEBUG_SERIAL("Changing state to: " + stateToString(data.state));
	DEBUG_SERIAL_LN(" -- with menu item in focus: " + String(data.inFocus));
}

const String ApplicationContext::stateToString(ApplicationState state) {
    switch (state) {
        case MainMenu:
            return "Main Menu";
            break;
        case ManualControlMenu:
            return "Manual Control";
            break;
        case CalibrationMenu:
            return "Calibration";
            break;
        case SettingsMenu:
            return "Settings";
            break;
        default:
            return "Does not exist";
            break;
    }
}