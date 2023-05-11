#include "ApplicationContext.h"


ApplicationContext::ApplicationContext(InputManager& manager, Adafruit_GFX& display, ApplicationState state) :
    _inputManager(manager), _display(display), _currentState(MainMenu) {
    _controller = new MenuControllerExample(*this, _display);
}

void ApplicationContext::begin() {
    _controller->init(_inputManager);
}

void ApplicationContext::changeState(ApplicationState state) {
    _previousStates.push(_currentState);
    
    // TODO: state change code here
    _changeStateInternal(state);
}

void ApplicationContext::navigateBack() {
    if (_previousStates.empty()) {
        // error !
    } else {
        ApplicationState state = _previousStates.top();
        _previousStates.pop();
        _changeStateInternal(state);
    }
}

void ApplicationContext::_changeStateInternal(ApplicationState state) {
    _currentState = state;
    
    DEBUG_SERIAL_LN("Changing state to: " + stateToString(state));
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