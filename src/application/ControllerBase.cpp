#include "ControllerBase.h"

ControllerBase::~ControllerBase() { }

void ControllerBase::init(InputManager& manager) {
    manager.registerAction(ID_SERIAL, [this](input_data_t d) { this->_handleInputSerial(d); });
    manager.registerAction(ID_ROT_ENCODER, [this](input_data_t d) { this->_handleInputEncoder(d); });
    manager.registerAction(ID_ROTARY_EN_SELECT, [this](input_data_t d) { this->_handleInputEncoderSelect(d); });
    manager.registerAction(ID_BACK, [this](input_data_t d) { this->_handleInputBack(d); });
    manager.registerAction(ID_SELECT, [this](input_data_t d) { this->_handleInputSelect(d); });
    manager.registerAction(ID_BRAKE_BUTTON, [this](input_data_t d) { this->_handleInputBrakeButton(d); });
    manager.registerAction(ID_BRAKE_POT, [this](input_data_t d) { this->_handleInputBrakePot(d); });
}

uint8_t ControllerBase::getInFocus() {
    return _inFocus;
}

/* Input handlers (assigned as InputCallback in init) */

void ControllerBase::_handleInputSerial(input_data_t d) {
    // default: do nothing
}

void ControllerBase::_handleInputEncoder(input_data_t d) {
    // default: do nothing
}

void ControllerBase::_handleInputEncoderSelect(input_data_t d) {
    // default: do nothing
}

void ControllerBase::_handleInputBack(input_data_t d) {
    // default: do nothing
}

void ControllerBase::_handleInputSelect(input_data_t d) {
    // default: do nothing
}

void ControllerBase::_handleInputBrakeButton(input_data_t d) {
    // default: do nothing
}

void ControllerBase::_handleInputBrakePot(input_data_t d) {
    // default: do nothing
}
