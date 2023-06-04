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
            DEBUG_SERIAL_LN("_stateTransitionFlag is true -- calling _changeStateInternal");
            _changeStateInternal(_nextStateInfo);
            _nextStateInfo.reset();

            mutex_enter_blocking(&_stateTransitionMutex);
            _stateTransitionFlag = false;
            mutex_exit(&_stateTransitionMutex);
        }
    }

    if (millis() >= t + 1000) {
        DEBUG_SERIAL_LN("Current controller ref count: " + String(_controller.use_count()));
        t = millis();
    }
}

bool ApplicationContext::trySetNextState(StateInfo& info) {
    if (_nextStateInfo.state != NullState) {
        DEBUG_SERIAL_LN("Already in state transition -- Aborting");
        return false;
    }

    _currentStateInfo.inFocus = _controller->getInFocus();
    _currentStateInfo.addToConfig(info);
    _previousStates.push(_currentStateInfo);
    DEBUG_SERIAL_LN("PUSHING STATE TO STACK:");
    DEBUG_SERIAL_LN(_currentStateInfo.toString());

    _nextStateInfo = info;
    DEBUG_SERIAL_LN("ATTEMPTING TO TRANSITION TO STATE:");
    DEBUG_SERIAL_LN(_nextStateInfo.toString());
    return true;
}

bool ApplicationContext::tryUpdateAndReturn(StateInfo& info) {
    if (_nextStateInfo.state != NullState) {
        DEBUG_SERIAL_LN("Already in state transition -- Aborting");
        return false;
    }

    // remove previous state and update with new config info
    _nextStateInfo = _previousStates.top();
    _nextStateInfo.addToConfig(info);
    _previousStates.push(info);

    DEBUG_SERIAL_LN("ATTEMPTING TO TRANSITION TO STATE:");
    DEBUG_SERIAL_LN(_nextStateInfo.toString());
    return true;
}

bool ApplicationContext::tryRevertState() {
    if (_nextStateInfo.state != NullState) {
        DEBUG_SERIAL_LN("Already in state transition -- Aborting");
        return false;
    } else if (_previousStates.empty()) {
        DEBUG_SERIAL_LN("No previous state to revert to");
        return false;
    }

    _nextStateInfo = _previousStates.top();
    _previousStates.pop();

    DEBUG_SERIAL_LN("ATTEMPTING TO REVERT TO STATE:");
    DEBUG_SERIAL_LN(_nextStateInfo.toString());
    return true;
}

void ApplicationContext::setStateTransitionFlag() {
    if (_stateTransitionFlag) {
        DEBUG_SERIAL_LN("Change state field already set to true");
        return;
    }
    DEBUG_SERIAL_LN("Setting _stateTransitionFlag field to true");
    mutex_enter_blocking(&_stateTransitionMutex);
    _stateTransitionFlag = true;
    mutex_exit(&_stateTransitionMutex);
}

void ApplicationContext::_changeStateInternal(StateInfo& info) {
    _currentStateInfo = info;
    
    DEBUG_SERIAL_LN("Changing state to: " + app_util::stateToString(info.state));
    DEBUG_SERIAL_LN("\t- with menu item in focus: " + String(info.inFocus));
    DEBUG_SERIAL_LN("Current controller ref count = " + String(_controller.use_count()));

    _controller = _factory.create(info);
}