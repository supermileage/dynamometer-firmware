#include "ControllerBase.h"

ControllerBase::ControllerBase(ApplicationContext& context, Adafruit_GFX& display) :
    _context(context), _display(display) { }

ControllerBase::~ControllerBase() {
    DEBUG_SERIAL_LN("~ControllerBase");
}

void ControllerBase::init(InputManager& manager) {
    manager.registerAction(ID_SERIAL, [this](input_data_t d) { this->_handleInputSerial(d); });
    manager.registerAction(ID_ROT_EN, [this](input_data_t d) { this->_handleInputEncoder(d); });
    manager.registerAction(ID_ROT_EN_SW, [this](input_data_t d) { this->_handleInputEncoderSelect(d); });
    manager.registerAction(ID_BACK_BUTTON, [this](input_data_t d) { this->_handleInputBack(d); });
    manager.registerAction(ID_SELECT_BUTTON, [this](input_data_t d) { this->_handleInputSelect(d); });
    manager.registerAction(ID_BRAKE_BUTTON, [this](input_data_t d) { this->_handleInputBrakeButton(d); });
    manager.registerAction(ID_BRAKE_POT, [this](input_data_t d) { this->_handleInputBrakePot(d); });
}

void ControllerBase::handle() {
    // default: do nothing
}

uint8_t ControllerBase::getInFocus() {
    return _inFocus;
}

StateInfo ControllerBase::getStateInfo() {
    return _info;
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
