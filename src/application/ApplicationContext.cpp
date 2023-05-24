#include "ApplicationContext.h"

ApplicationContext::ApplicationContext(InputManager& manager, Adafruit_GFX& display, ControllerFactory& factory) :
    _inputManager(manager), _display(display), _factory(factory) { }

ApplicationContext::~ApplicationContext() {
    if (_controller) {
        delete _controller;
    }
}

void ApplicationContext::begin() {
    _factory.setContext(this);
    _controller = _factory.create(APPLICATION_INITIAL_STATE);
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

void ApplicationContext::revertState() {
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
    
    DEBUG_SERIAL("Changing state to: " + app_util::stateToString(data.state));
	DEBUG_SERIAL_LN(" -- with menu item in focus: " + String(data.inFocus));

    delete _controller;
    _controller = _factory.create(data);
}