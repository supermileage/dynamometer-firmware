#include "ApplicationContext.h"

ApplicationContext::ApplicationContext(InputManager& manager, Adafruit_GFX& display, ControllerFactory& factory) :
    _inputManager(manager), _display(display), _factory(factory) { }

ApplicationContext::~ApplicationContext() { }

void ApplicationContext::begin() {
    mutex_init(&_stateTransitionMutex);
    _factory.setContext(this);

    _currentStateInfo.state = APPLICATION_INITIAL_STATE;
    _currentStateInfo.config[CONFIG_ID_MENU_HEADER] = String(APPLICATION_INITIAL_HEADER);
    _currentStateInfo.inFocus = 0;
    _controller = _factory.create(_currentStateInfo);
}

uint t = 0;

void ApplicationContext::handle() {
    if (_nextStateInfo.state != NullState) {
        bool changeNow = false;
        if (_stateTransitionFlag) {
            mutex_enter_blocking(&_stateTransitionMutex);
            _stateTransitionFlag = false;
            mutex_exit(&_stateTransitionMutex);

            DEBUG_STATE_TRANSITION_LN("_stateTransitionFlag is true -- calling _changeStateInternal");
            _changeStateInternal(_nextStateInfo);
            _nextStateInfo.reset();
        }
    }

    if (millis() >= t + 1000) {
        Serial.println("Current controller ref count: " + String(_controller.use_count()));
        t = millis();
    }
}

void ApplicationContext::setNextState(StateInfo& info) {
    // push current state to _previousStates
    if (_nextStateInfo.state != NullState) {
        DEBUG_STATE_TRANSITION_LN("Already in state transition -- Aborting");
        return;
    }

    _nextStateInfo = info;

    _currentStateInfo.inFocus = _controller->getInFocus();
    _previousStates.push(_currentStateInfo);
}

bool ApplicationContext::tryRevertState() {
    if (_nextStateInfo.state != NullState) {
        DEBUG_STATE_TRANSITION_LN("Already in state transition -- Aborting");
        return false;
    } else if (_previousStates.empty()) {
        DEBUG_STATE_TRANSITION_LN("_previousStates empty: No state to revert to");
        return false;
    }

    _nextStateInfo = _previousStates.top();
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

void ApplicationContext::_changeStateInternal(StateInfo& info) {
    _currentStateInfo = info;
    
    DEBUG_STATE_TRANSITION_LN("Changing state to: " + app_util::stateToString(info.state));
    DEBUG_STATE_TRANSITION_LN("\t- with menu item in focus: " + String(info.inFocus));
    DEBUG_STATE_TRANSITION_LN("_controller.use_count() = " + String(_controller.use_count()));

    _controller = _factory.create(info);
}