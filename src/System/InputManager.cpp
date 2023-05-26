#include "InputManager.h"

#include "settings.h"

InputManager::InputManager() { }

InputManager::~InputManager() { }

void InputManager::begin() {
    for (auto pair : _inputMap) {
        pair.second->init();
    }
}

void InputManager::handle() {
    for (auto pair : _inputMap) {
        pair.second->run();
    }
}

void InputManager::registerInput(uint8_t id, HardwareInput* input) {
    if (_inputMap.find(id) == _inputMap.end()) {
        _inputMap[id] = input;
    } else {
        DEBUG_SERIAL_LN("InputManager: already contains input with ID = " + String(id));
    }
}

void InputManager::registerAction(uint8_t id, InputCallback action) {
    if (_inputMap.find(id) != _inputMap.end()) {
        _inputMap[id]->setAction(action);
    } else {
        DEBUG_SERIAL_LN("InputManager: no input registered with ID = " + String(id));
    }
}
