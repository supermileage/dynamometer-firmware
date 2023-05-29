#include "ApplicationContext.h"

ApplicationContext::ApplicationContext(InputManager& manager, Adafruit_GFX& display, ControllerFactory& factory) :
    _inputManager(manager), _display(display), _factory(factory) { }

ApplicationContext::~ApplicationContext() { }

void ApplicationContext::begin() {
    _factory.setContext(this);
    _controller = _factory.create(APPLICATION_INITIAL_STATE);
    mutex_init(&_stateTransitionMutex);
}

uint t = 0;

void ApplicationContext::handle() {
    if (_nextState.state != NullState) {
        bool changeNow = false;
        if (_stateTransitionFlag) {
            mutex_enter_blocking(&_stateTransitionMutex);
            _stateTransitionFlag = false;
            mutex_exit(&_stateTransitionMutex);

            DEBUG_STATE_TRANSITION_LN("_stateTransitionFlag is true -- calling _changeStateInternal");
            _changeStateInternal(_nextState);
            _nextState.reset();
        }
    }

    if (millis() >= t + 500) {
        Serial.println(_controller.use_count());
        t = millis();
    }
}

void ApplicationContext::setNextState(ApplicationState state) {
    // push current state to _previousStates
    if (_nextState.state != NullState) {
        DEBUG_STATE_TRANSITION_LN("Already in state transition -- Aborting");
        return;
    }

    StateData data;
    data.state = _currentState;
    data.inFocus = _controller->getInFocus();
    _previousStates.push(data);
    
    // transition to new state
    _nextState.state = state;
    _nextState.inFocus = 0;
}

bool ApplicationContext::tryRevertState() {
    if (_nextState.state != NullState) {
        DEBUG_STATE_TRANSITION_LN("Already in state transition -- Aborting");
        return false;
    } else if (_previousStates.empty()) {
        DEBUG_STATE_TRANSITION_LN("_previousStates empty: No state to revert to");
        return false;
    }

    _nextState = _previousStates.top();
    _previousStates.pop();
    return true;
}

void ApplicationContext::setStateTransitionFlag() {
    if (_stateTransitionFlag) {
        DEBUG_STATE_TRANSITION_LN("Change state field already set to true");
        return;
    }
    DEBUG_STATE_TRANSITION_LN("Setting _stateTransitionFlag field to true");
    mutex_enter_blocking(&_stateTransitionMutex);
    _stateTransitionFlag = true;
    mutex_exit(&_stateTransitionMutex);
}

void ApplicationContext::_changeStateInternal(StateData data) {
    _currentState = data.state;
    
    DEBUG_STATE_TRANSITION_LN("Changing state to: " + app_util::stateToString(data.state));
    DEBUG_STATE_TRANSITION_LN("\t- with menu item in focus: " + String(data.inFocus));
    DEBUG_STATE_TRANSITION_LN("_controller.use_count() = " + String(_controller.use_count()));

    _controller = _factory.create(data);
}