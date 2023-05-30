#include "ApplicationContext.h"

ApplicationContext::ApplicationContext(InputManager& manager, Adafruit_GFX& display, ControllerFactory& factory) :
    _inputManager(manager), _display(display), _factory(factory) { }

ApplicationContext::~ApplicationContext() { }

void ApplicationContext::begin() {
    mutex_init(&_stateTransitionMutex);
    _factory.setContext(this);

    _currentStateInfo.state = APPLICATION_INITIAL_STATE;
    _currentStateInfo.header = String(APPLICATION_INITIAL_HEADER);
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
        DEBUG_STATE_TRANSITION_LN("Current controller ref count: " + String(_controller.use_count()));
        t = millis();
    }
}

bool ApplicationContext::trySetNextState(StateInfo& info) {
    if (_nextStateInfo.state != NullState) {
        DEBUG_STATE_TRANSITION_LN("Already in state transition -- Aborting");
        return false;
    }

    DEBUG_SERIAL_LN("PUSHING STATE TO STACK:");
    _currentStateInfo.inFocus = _controller->getInFocus();
    _currentStateInfo.addToConfig(info);
    _currentStateInfo.print();
    _previousStates.push(_currentStateInfo);

    DEBUG_SERIAL_LN("ATTEMING TO TRANSITION TO STATE:");
    _nextStateInfo = info;
    _nextStateInfo.print();
    return true;
}

bool ApplicationContext::tryUpdateAndReturn(StateInfo& info) {
    if (_nextStateInfo.state != NullState) {
        DEBUG_STATE_TRANSITION_LN("Already in state transition -- Aborting");
        return false;
    }

    // remove previous state and update with new config info
    _nextStateInfo = _previousStates.top();
    _nextStateInfo.addToConfig(info);
    _previousStates.push(info);

    DEBUG_SERIAL_LN("ATTEMING TO TRANSITION TO STATE:");
    _nextStateInfo.print();
    
    return true;
}

bool ApplicationContext::tryRevertState() {
    if (_nextStateInfo.state != NullState) {
        DEBUG_SERIAL_LN("Already in state transition -- Aborting");
        return false;
    } else if (_previousStates.empty()) {
        DEBUG_SERIAL_LN("_previousStates empty: No state to revert to");
        return false;
    }

    _nextStateInfo = _previousStates.top();
    _previousStates.pop();

    DEBUG_SERIAL_LN("ATTEMING TO REVERT TO STATE:");
    _nextStateInfo.print();
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